//
// Created by ZZK on 2024/7/31.
//

#include <d3d12/tracer/d3d12_tracer.h>
#include <numeric>
#include <DirectXTexCustomized.h>

#pragma comment(lib,"dxguid.lib")

namespace gfxshim
{
    D3D12Tracer::DumpDecoration::DumpDecoration(gfxshim::D3D12Tracer &in_tracer, const std::wstring &action_string, DecorationFlag dump_flag)
    : tracer(in_tracer)
    {
        auto current_execution_count = in_tracer.CheckExecutionCount();
        decorated_string = in_tracer.per_draw_dump_prefix + std::to_wstring(current_execution_count);
        if (dump_flag == DecorationFlag::Dump_RTV)
        {
            decorated_string += action_string + L"_RTV_";
        } else if (dump_flag == DecorationFlag::Dump_DSV)
        {
            decorated_string += action_string + L"_DSV_";
        } else
        {
            decorated_string += action_string + L"_UAV_";
        }
    }

    std::wstring &D3D12Tracer::DumpDecoration::operator()()
    {
        return decorated_string;
    }

    D3D12Tracer::D3D12Tracer()
    {
        fence_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        D3D12_WRAPPER_ASSERT(fence_event != nullptr, "Fence event can not be nullptr");
    }

    D3D12Tracer::~D3D12Tracer()
    {
        if (fence_event != nullptr)
        {
            CloseHandle(fence_event);
        }
    }

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
        render_target_view_info_storage[rtv_descriptor] = RenderTargetViewInfo{ resource, D3D12_RESOURCE_STATE_RENDER_TARGET, is_cube_map };
    }

    void D3D12Tracer::StoreDSVAndResource(uint64_t dsv_descriptor, ID3D12Resource *resource, const D3D12_DEPTH_STENCIL_VIEW_DESC *depth_stencil_view_desc)
    {
        depth_stencil_view_info_storage[dsv_descriptor] = DepthStencilViewInfo{ resource, D3D12_RESOURCE_STATE_DEPTH_WRITE };
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

    void D3D12Tracer::UpdateRTVStatePerExecution(uint64_t rtv_descriptor, D3D12_RESOURCE_STATES resource_state)
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

    uint32_t D3D12Tracer::IncreaseExecutionCount()
    {
        return execution_count.fetch_add(1, std::memory_order_seq_cst);
    }

    uint32_t D3D12Tracer::CheckExecutionCount() const
    {
        return execution_count.load(std::memory_order_seq_cst);
    }

    uint32_t D3D12Tracer::IncreaseDrawCount()
    {
        return draw_count.fetch_add(1, std::memory_order_seq_cst);
    }

    uint32_t D3D12Tracer::CheckDrawCount() const
    {
        return draw_count.load(std::memory_order_seq_cst);
    }

    void D3D12Tracer::PerExecutionDump(ID3D12CommandQueue *command_queue)
    {
        if (per_execution_dump_ready.load(std::memory_order_seq_cst)) return;

        if (CheckExecutionCount() >= 21) return;  // TODO: just for testing per-execution-dump

        D3D12_WRAPPER_DEBUG("Begin to per-execution-dump");

        static uint32_t index = 0;
        DumpDecoration dump_decoration{ *this, L"_Draw", DecorationFlag::Dump_RTV };
        per_execution_dump_ready.store(true, std::memory_order_seq_cst);
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
                DirectX::CaptureBufferImmediately(command_queue, target_resource, render_target_filepath.c_str());
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

        // Clear render target view information before next execution
        render_target_view_info_per_execution.clear();

        per_execution_dump_ready.store(false, std::memory_order_seq_cst);
        IncreaseExecutionCount();

        D3D12_WRAPPER_DEBUG("End per-execution-dump");
    }

    void D3D12Tracer::CollectStagingResourcePerDraw(ID3D12Device *device, ID3D12GraphicsCommandList *pCommandList)
    {
        if (CheckDrawCount() > 180) return;  // TODO: test deferred per-draw-dump

        D3D12_WRAPPER_DEBUG("Begin to deferred per-draw-dump");

        uint32_t rtv_index = 0;
        uint32_t dsv_index = 0;
        std::wstring draw_action_string = L"_Draw_" + std::to_wstring(CheckDrawCount());
        DumpDecoration dump_decoration_rtv{ *this, draw_action_string, DecorationFlag::Dump_RTV };
        DumpDecoration dump_decoration_dsv{ *this, draw_action_string, DecorationFlag::Dump_DSV };
        per_draw_dump_ready.store(true, std::memory_order_seq_cst);
        for (auto &&render_target_state : render_target_view_info_per_draw)
        {
            auto *target_resource = render_target_state.second.d3d12_resource;
            if (target_resource == nullptr)
            {
                continue;
            }

            auto resource_desc = target_resource->GetDesc();
            DirectX::CaptureTextureDesc capture_texture_desc{};
            std::wstring render_target_filepath = dump_decoration_rtv.decorated_string + std::to_wstring(rtv_index);
            if (resource_desc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER)
            {
                render_target_filepath += L".bin";
                DirectX::CaptureBufferDeferred(device, pCommandList, target_resource, capture_texture_desc);

            } else
            {
                render_target_filepath += L".dds";
                DirectX::CaptureTextureDeferred(device, pCommandList, target_resource, capture_texture_desc, render_target_state.second.cube_map);
            }
            capture_rtv_texture_filepath_storage.emplace_back(std::move(render_target_filepath));
            capture_rtv_texture_desc_storage_per_execution.emplace_back(std::move(capture_texture_desc));
            ++rtv_index;
        }

        for (auto &&depth_stencil_state : depth_stencil_view_info_per_draw)
        {
            auto &&depth_stencil_info = depth_stencil_state.second;
            if (depth_stencil_info.d3d12_resource == nullptr)
            {
                continue;
            }

            DirectX::CaptureTextureDesc capture_texture_desc{};
            std::wstring depth_stencil_filepath = dump_decoration_dsv.decorated_string + std::to_wstring(dsv_index) + L".bin";
            DirectX::CaptureTextureDeferred(device, pCommandList, depth_stencil_info.d3d12_resource, capture_texture_desc, false, false,
                                            depth_stencil_info.resource_state, depth_stencil_info.resource_state);
            capture_dsv_texture_filepath_storage.emplace_back(std::move(depth_stencil_filepath));
            capture_dsv_texture_desc_storage_per_execution.emplace_back(std::move(capture_texture_desc));
            ++dsv_index;
        }

        IncreaseDrawCount();

        D3D12_WRAPPER_DEBUG("End deferred per-draw-dump");
    }

    void D3D12Tracer::PerDrawDump(ID3D12Fence *fence, uint64_t fence_value)
    {
        if (CheckExecutionCount() > 24) return;  // TODO: test deferred per-draw-dump

        if (fence->GetCompletedValue() < fence_value)
        {
            fence->SetEventOnCompletion(fence_value, fence_event);
            WaitForSingleObjectEx(fence_event, INFINITE, FALSE);
        }

        for (size_t i = 0; i < capture_rtv_texture_desc_storage_per_execution.size(); ++i)
        {
            auto &&capture_texture_desc = capture_rtv_texture_desc_storage_per_execution[i];
            if (capture_texture_desc.capturedResourceDesc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER)
            {
                DirectX::SaveToBinFileImmediately(capture_texture_desc, capture_rtv_texture_filepath_storage[i].c_str());
            } else
            {
                DirectX::SaveToDDSFileImmediately(capture_texture_desc, DirectX::DDS_FLAGS_NONE, capture_rtv_texture_filepath_storage[i].c_str());
            }
            capture_texture_desc_old_storage.emplace_back(std::move(capture_texture_desc));
        }

        for (size_t i = 0; i < capture_dsv_texture_desc_storage_per_execution.size(); ++i)
        {
            auto &&capture_texture_desc = capture_dsv_texture_desc_storage_per_execution[i];
            DirectX::SaveToBinFileImmediately(capture_texture_desc, capture_dsv_texture_filepath_storage[i].c_str());
            capture_texture_desc_old_storage.emplace_back(std::move(capture_texture_desc));
        }

        capture_rtv_texture_desc_storage_per_execution.clear();
        capture_rtv_texture_filepath_storage.clear();
        render_target_view_info_per_draw.clear();

        capture_dsv_texture_desc_storage_per_execution.clear();
        capture_dsv_texture_filepath_storage.clear();
        depth_stencil_view_info_per_draw.clear();

        IncreaseExecutionCount();
    }

    void D3D12Tracer::UpdateRTVStatePerDraw(uint64_t rtv_descriptor)
    {
        if (per_draw_dump_ready.load(std::memory_order_seq_cst))
        {
            render_target_view_info_per_draw.clear();
            depth_stencil_view_info_per_draw.clear();
            per_draw_dump_ready.store(false, std::memory_order_seq_cst);
        }

        // Render target view
        if (render_target_view_info_per_draw.contains(rtv_descriptor))
        {
            render_target_view_info_per_draw[rtv_descriptor].resource_state = D3D12_RESOURCE_STATE_RENDER_TARGET;
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
            render_target_view_info_per_draw.try_emplace(rtv_descriptor, resource, D3D12_RESOURCE_STATE_RENDER_TARGET, is_cube_map);
        }
    }

    void D3D12Tracer::UpdateDSVStatePerDraw(uint64_t dsv_descriptor)
    {
        // Depth stencil view
        if (depth_stencil_view_info_per_draw.contains(dsv_descriptor))
        {
            depth_stencil_view_info_per_draw[dsv_descriptor].resource_state = D3D12_RESOURCE_STATE_DEPTH_WRITE;  // TODO: check
        } else
        {
            ID3D12Resource *resource = nullptr;
            if (depth_stencil_view_info_storage.contains(dsv_descriptor))
            {
                auto &&dsv_state = depth_stencil_view_info_storage[dsv_descriptor];
                resource = dsv_state.d3d12_resource;
            }
            depth_stencil_view_info_per_draw.try_emplace(dsv_descriptor, resource, D3D12_RESOURCE_STATE_DEPTH_WRITE);
        }
    }
}