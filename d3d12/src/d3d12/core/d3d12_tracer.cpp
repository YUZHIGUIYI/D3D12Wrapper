//
// Created by ZZK on 2024/7/31.
//

#include <d3d12/core/d3d12_tracer.h>
#include <DirectXTex.h>
#include <numeric>

#pragma comment(lib,"dxguid.lib")

namespace gfxshim
{
    static void TransitionResource(
                ID3D12GraphicsCommandList* command_list,
                ID3D12Resource* resource,
                D3D12_RESOURCE_STATES state_before,
                D3D12_RESOURCE_STATES state_after) noexcept
    {
        if (state_before == state_after)
        {
            return;
        }

        D3D12_RESOURCE_BARRIER barrier_desc{};
        barrier_desc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        barrier_desc.Transition.pResource = resource;
        barrier_desc.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
        barrier_desc.Transition.StateBefore = state_before;
        barrier_desc.Transition.StateAfter = state_after;

        command_list->ResourceBarrier(1, &barrier_desc);
    }

    static HRESULT CaptureBuffer(ID3D12CommandQueue *command_queue, ID3D12Resource *target_resource, const std::wstring &filepath,
                                D3D12_RESOURCE_STATES before_state = D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATES after_state = D3D12_RESOURCE_STATE_RENDER_TARGET)
    {
        HRESULT result = E_INVALIDARG;

        auto target_resource_desc = target_resource->GetDesc();
        if (target_resource_desc.Dimension != D3D12_RESOURCE_DIMENSION_BUFFER || target_resource_desc.Width > std::numeric_limits<uint32_t>::max())
        {
            return result;
        }

        // Get device
        ComPtr<ID3D12Device> device = nullptr;
        result = command_queue->GetDevice(IID_ID3D12Device, reinterpret_cast<void **>(device.GetAddressOf()));
        if (FAILED(result))
        {
            return result;
        }

        // Create a command allocator
        ComPtr<ID3D12CommandAllocator> command_alloc = nullptr;
        result = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_ID3D12CommandAllocator, reinterpret_cast<void **>(command_alloc.GetAddressOf()));
        if (FAILED(result))
        {
            return result;
        }

        // Spin up a new command list
        ComPtr<ID3D12GraphicsCommandList> command_list = nullptr;
        result = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, command_alloc.Get(), nullptr, IID_ID3D12GraphicsCommandList, reinterpret_cast<void **>(command_list.GetAddressOf()));
        if (FAILED(result))
        {
            return result;
        }

        // Create a fence
        ComPtr<ID3D12Fence> fence = nullptr;
        result = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_ID3D12Fence, reinterpret_cast<void **>(fence.GetAddressOf()));
        if (FAILED(result))
        {
            return result;
        }

        D3D12_RESOURCE_DESC staging_resource_desc{};
        staging_resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        staging_resource_desc.Alignment = 0;
        staging_resource_desc.Width = target_resource_desc.Width;
        staging_resource_desc.Height = 1;
        staging_resource_desc.DepthOrArraySize = 1;
        staging_resource_desc.MipLevels = 1;
        staging_resource_desc.Format = DXGI_FORMAT_UNKNOWN;
        staging_resource_desc.SampleDesc.Count = 1;
        staging_resource_desc.SampleDesc.Quality = 0;
        staging_resource_desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        staging_resource_desc.Flags = D3D12_RESOURCE_FLAG_NONE;

        D3D12_HEAP_PROPERTIES staging_heap_props{};
        staging_heap_props.Type = D3D12_HEAP_TYPE_READBACK;
        staging_heap_props.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        staging_heap_props.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
        staging_heap_props.CreationNodeMask = 1;
        staging_heap_props.VisibleNodeMask = 1;

        // Create a staging texture
        ComPtr<ID3D12Resource> staging_resource = nullptr;
        result = device->CreateCommittedResource(
                &staging_heap_props,
                D3D12_HEAP_FLAG_NONE,
                &staging_resource_desc,
                D3D12_RESOURCE_STATE_COPY_DEST,
                nullptr,
                IID_ID3D12Resource,
                reinterpret_cast<void **>(staging_resource.GetAddressOf()));
        if (FAILED(result))
        {
            return result;
        }

        // Transition the resource if necessary
        TransitionResource(command_list.Get(), target_resource, before_state, D3D12_RESOURCE_STATE_COPY_SOURCE);

        // Copy resource
        command_list->CopyResource(staging_resource.Get(), target_resource);

        // Transition the resource to the next state
        TransitionResource(command_list.Get(), target_resource, D3D12_RESOURCE_STATE_COPY_SOURCE, after_state);

        result = command_list->Close();
        if (FAILED(result))
        {
            return result;
        }

        // Execute the command list
        std::array<ID3D12CommandList *, 1> command_lists{ command_list.Get() };
        command_queue->ExecuteCommandLists(command_lists.size(), command_lists.data());

        // Signal the fence
        result = command_queue->Signal(fence.Get(), 1);
        if (FAILED(result))
        {
            return result;
        }

        // Block until the copy is complete
        while (fence->GetCompletedValue() < 1)
        {
#if defined(_WIN32)
            SwitchToThread();
#else
            std::this_thread::yield();
#endif
        }

        // Read back and write to file
        D3D12_RANGE read_range{ 0, static_cast<size_t>(staging_resource_desc.Width) };
        D3D12_RANGE write_range{ 0, 0 };
        void *mapped_data = nullptr;
        result = staging_resource->Map(0, &read_range, &mapped_data);
        if (FAILED(result))
        {
            return result;
        }

        std::ofstream output_file{ filepath, std::ios::binary };
        if (output_file.is_open())
        {
            output_file.write(reinterpret_cast<char *>(mapped_data), static_cast<std::streamsize>(staging_resource_desc.Width));
        } else
        {
            D3D12_WRAPPER_DEBUG("Failed to open output binary file");
        }

        staging_resource->Unmap(0, &write_range);

        return S_OK;
    }

    D3D12Tracer::DumpDecoration::DumpDecoration(gfxshim::D3D12Tracer &in_tracer, const std::wstring &in_string)
            : tracer(in_tracer)
    {
        auto current_execution_count = in_tracer.CheckExecutionCount();
        decorated_string = in_string + std::to_wstring(current_execution_count) + L"_";
    }

    std::wstring &D3D12Tracer::DumpDecoration::operator()()
    {
        return decorated_string;
    }

    D3D12Tracer::D3D12Tracer() = default;

    D3D12Tracer &D3D12Tracer::GetInstance()
    {
        static D3D12Tracer d3d12_tracer{};
        return d3d12_tracer;
    }

    void D3D12Tracer::StoreRTVAndResource(uint64_t rtv_descriptor, ID3D12Resource *resource, const D3D12_RENDER_TARGET_VIEW_DESC *render_target_view_desc)
    {
        bool is_cube_map = false;
        if (render_target_view_desc->ViewDimension == D3D12_RTV_DIMENSION_TEXTURE2DARRAY)
        {
            if (render_target_view_desc->Texture2DArray.FirstArraySlice == 0 && render_target_view_desc->Texture2DArray.ArraySize == 6)
            {
                is_cube_map = true;
            }
        }
        render_target_view_info_storage[rtv_descriptor] = { resource, D3D12_RESOURCE_STATE_RENDER_TARGET, is_cube_map };
    }

    bool D3D12Tracer::CheckRTVResourceSavedStatus(ID3D12Resource *resource) const
    {
        for (auto &&each_rtv_resource : render_target_view_info_storage)
        {
            if (resource == each_rtv_resource.second.d3d12_resource)
            {
                return true;
            }
        }
        return false;
    }

    void D3D12Tracer::UpdateRTVState(uint64_t rtv_descriptor, D3D12_RESOURCE_STATES resource_state)
    {
        if (render_target_view_info_per_execution.contains(rtv_descriptor))
        {
            render_target_view_info_per_execution[rtv_descriptor].resource_state = resource_state;
        } else
        {
            ID3D12Resource *resource = nullptr;
            bool is_cube_map = false;
            if (render_target_view_info_storage.contains(rtv_descriptor))
            {
                auto &&rtv_state = render_target_view_info_storage[rtv_descriptor];
                resource = rtv_state.d3d12_resource;
                is_cube_map = rtv_state.cube_map;
            }
            render_target_view_info_per_execution[rtv_descriptor] = { resource, resource_state, is_cube_map };
        }
    }

    void D3D12Tracer::ClearRTVInfo()
    {
        if (per_draw_dump_ready.load(std::memory_order_seq_cst)) return;
        render_target_view_info_per_execution.clear();
    }

    uint32_t D3D12Tracer::IncreaseExecutionCount()
    {
        return execution_count.fetch_add(1, std::memory_order_seq_cst);
    }

    uint32_t D3D12Tracer::CheckExecutionCount() const
    {
        return execution_count.load(std::memory_order_seq_cst);
    }

    void D3D12Tracer::PerDrawDump(ID3D12CommandQueue *command_queue)
    {
        if (per_draw_dump_ready.load(std::memory_order_seq_cst)) return;

        if (CheckExecutionCount() >= 20) return;  // TODO: just for testing per-draw-dump

        D3D12_WRAPPER_DEBUG("Begin to per-draw-dump");

        static uint32_t index = 0;
        DumpDecoration dump_decoration{ *this, this->per_draw_dump_prefix };
        per_draw_dump_ready.store(true, std::memory_order_seq_cst);
        for (auto &&render_target_state : render_target_view_info_per_execution)
        {
            auto *target_resource = render_target_state.second.d3d12_resource;
            if (target_resource == nullptr)
            {
                continue;
            }

            auto resource_desc = target_resource->GetDesc();
            if (resource_desc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER)
            {
                std::wstring render_target_filepath = dump_decoration.decorated_string + std::to_wstring(index) + L".bin";
                CaptureBuffer(command_queue, target_resource, render_target_filepath);
            } else
            {
                std::wstring render_target_filepath = dump_decoration.decorated_string + std::to_wstring(index) + L".dds";
                DirectX::ScratchImage scratch_image{};
                DirectX::CaptureTexture(command_queue, target_resource, render_target_state.second.cube_map, scratch_image);
                const auto *image = scratch_image.GetImages();
                DirectX::SaveToDDSFile(*image, DirectX::DDS_FLAGS_NONE, render_target_filepath.c_str());
            }
            ++index;
        }
        per_draw_dump_ready.store(false, std::memory_order_seq_cst);
        IncreaseExecutionCount();

        D3D12_WRAPPER_DEBUG("End per-draw-dump");
    }
}