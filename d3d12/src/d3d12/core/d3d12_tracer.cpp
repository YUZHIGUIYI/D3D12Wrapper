//
// Created by ZZK on 2024/7/31.
//

#include <d3d12/core/d3d12_tracer.h>
#include <DirectXTex.h>

namespace gfxshim
{
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
            if (render_target_state.second.d3d12_resource != nullptr)
            {
                std::wstring render_target_file = dump_decoration.decorated_string + std::to_wstring(index) + L".dds";
                DirectX::ScratchImage scratch_image{};
                DirectX::CaptureTexture(command_queue, render_target_state.second.d3d12_resource, render_target_state.second.cube_map, scratch_image);
                const auto *image = scratch_image.GetImages();
                DirectX::SaveToDDSFile(*image, DirectX::DDS_FLAGS_NONE, render_target_file.c_str());
                ++index;
            }
        }
        per_draw_dump_ready.store(false, std::memory_order_seq_cst);
        IncreaseExecutionCount();

        D3D12_WRAPPER_DEBUG("End per-draw-dump");
    }
}