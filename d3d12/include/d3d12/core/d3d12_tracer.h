//
// Created by ZZK on 2024/7/31.
//

#pragma once

#include <d3d12/common/d3d12_wrap_common.h>

namespace gfxshim
{
    struct RenderTargetViewInfo
    {
        ID3D12Resource *d3d12_resource = nullptr;
        D3D12_RESOURCE_STATES resource_state = D3D12_RESOURCE_STATE_RENDER_TARGET;
        bool cube_map = false;
    };

    struct D3D12Tracer
    {
    private:
        std::unordered_map<uint64_t, RenderTargetViewInfo> render_target_view_info_storage;
        std::unordered_map<uint64_t, RenderTargetViewInfo> render_target_view_info_per_execution;
        std::unordered_map<ID3D12Resource *, uint64_t> resource_to_rtv_map;
        std::wstring per_draw_dump_prefix = L"ExecuteCM_";
        std::atomic<uint32_t> execution_count{ 0 };
        std::atomic<bool> per_draw_dump_ready{ false };

        struct DumpDecoration
        {
            DumpDecoration(D3D12Tracer &in_tracer, const std::wstring &in_string);
            std::wstring &operator()();
            D3D12Tracer  &tracer;
            std::wstring decorated_string;
        };

    private:
        D3D12Tracer();

    public:
        static D3D12Tracer &GetInstance();

        // Store render target view resource during creation
        void StoreRTVAndResource(uint64_t rtv_descriptor, ID3D12Resource *resource, const D3D12_RENDER_TARGET_VIEW_DESC *render_target_view_desc);

        // Check whether rtv resource has been included
        bool CheckRTVResourceSavedStatus(ID3D12Resource *resource) const;

        // Store render target view resource during output merger
        void UpdateRTVState(uint64_t rtv_descriptor, D3D12_RESOURCE_STATES resource_state = D3D12_RESOURCE_STATE_RENDER_TARGET);

        // Clear render target view state after execution, thread-safely
        void ClearRTVInfo();

        uint32_t IncreaseExecutionCount();

        uint32_t CheckExecutionCount() const;

        // Thread-safe per draw dump
        void PerDrawDump(ID3D12CommandQueue *command_queue);
    };
}
