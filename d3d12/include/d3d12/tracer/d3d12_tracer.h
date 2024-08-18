//
// Created by ZZK on 2024/7/31.
//

#pragma once

#include <d3d12/common/d3d12_wrap_common.h>

namespace DirectX
{
    struct CaptureTextureDesc;
}
namespace gfxshim
{
    struct RenderTargetViewInfo
    {
        ID3D12Resource *d3d12_resource = nullptr;
        D3D12_RESOURCE_STATES resource_state = D3D12_RESOURCE_STATE_RENDER_TARGET;
        bool cube_map = false;
    };

    struct DepthStencilViewInfo
    {
        ID3D12Resource *d3d12_resource = nullptr;
        D3D12_RESOURCE_STATES resource_state = D3D12_RESOURCE_STATE_DEPTH_WRITE;
    };

    struct D3D12Tracer
    {
    private:
        // Render target view and its creation resource
        std::unordered_map<uint64_t, RenderTargetViewInfo> render_target_view_info_storage;
        // Depth stencil view and its creation resource
        std::unordered_map<uint64_t, DepthStencilViewInfo> depth_stencil_view_info_storage;

        // Per execution dump assets
        std::unordered_map<uint64_t, RenderTargetViewInfo> render_target_view_info_per_execution;

        // Per draw dump assets
        std::unordered_map<uint64_t, RenderTargetViewInfo> render_target_view_info_per_draw;
        std::unordered_map<uint64_t, DepthStencilViewInfo> depth_stencil_view_info_per_draw;
        std::vector<DirectX::CaptureTextureDesc> capture_rtv_texture_desc_storage_per_execution;
        std::vector<DirectX::CaptureTextureDesc> capture_dsv_texture_desc_storage_per_execution;
        std::vector<DirectX::CaptureTextureDesc> capture_texture_desc_old_storage;
        std::vector<std::wstring> capture_rtv_texture_filepath_storage;
        std::vector<std::wstring> capture_dsv_texture_filepath_storage;
        HANDLE fence_event = nullptr;

        std::wstring per_draw_dump_prefix = L"ExecuteCM_";
        std::atomic<uint32_t> execution_count{ 0 };
        std::atomic<uint32_t> draw_count{ 0 };
        std::atomic<bool> per_execution_dump_ready{ false };
        std::atomic<bool> per_draw_dump_ready{ false };

        enum class DecorationFlag : uint8_t
        {
            Dump_RTV,
            Dump_DSV,
            Dump_UAV,
        };

        struct DumpDecoration
        {
            DumpDecoration(D3D12Tracer &in_tracer, const std::wstring &action_string, DecorationFlag dump_flag);
            std::wstring &operator()();
            D3D12Tracer  &tracer;
            std::wstring decorated_string;
        };

    private:
        D3D12Tracer();

    public:
        ~D3D12Tracer();

        D3D12Tracer(const D3D12Tracer &) = delete;
        D3D12Tracer &operator=(const D3D12Tracer &) = delete;
        D3D12Tracer(D3D12Tracer &&) = delete;
        D3D12Tracer &operator=(D3D12Tracer &&) = delete;

        static D3D12Tracer &GetInstance();

        // Store render target view resource during creation
        void StoreRTVAndResource(uint64_t rtv_descriptor, ID3D12Resource *resource, const D3D12_RENDER_TARGET_VIEW_DESC *render_target_view_desc);

        // Store depth stencil view resource during creation
        void StoreDSVAndResource(uint64_t dsv_descriptor, ID3D12Resource *resource, const D3D12_DEPTH_STENCIL_VIEW_DESC *depth_stencil_view_desc);

        // Check whether rtv resource has been included
        bool CheckRTVResourceSavedStatus(ID3D12Resource *resource) const;

        // Store render target view resource during output merger
        void UpdateRTVStatePerExecution(uint64_t rtv_descriptor, D3D12_RESOURCE_STATES resource_state = D3D12_RESOURCE_STATE_RENDER_TARGET);

        // Thread-safe per-execution-dump
        void PerExecutionDump(ID3D12CommandQueue *command_queue);

        // Deferred per-draw-dump by recording copy command of read back resource
        void CollectStagingResourcePerDraw(ID3D12Device *device, ID3D12GraphicsCommandList *pCommandList);

        // Deferred per-draw-dump after command queue signal, immediately dump into dds or binary file
        void PerDrawDump(ID3D12Fence *fence, uint64_t fence_value);

        // Update render target view information during invoking ID3D12GraphicsCommandList::OMSetRenderTargets
        void UpdateRTVStatePerDraw(uint64_t rtv_descriptor);

        // Update depth stencil view information during invoking ID3D12GraphicsCommandList::OMSetRenderTargets
        void UpdateDSVStatePerDraw(uint64_t dsv_descriptor);

    private:
        uint32_t IncreaseExecutionCount();

        uint32_t CheckExecutionCount() const;

        uint32_t IncreaseDrawCount();

        uint32_t CheckDrawCount() const;
    };
}
