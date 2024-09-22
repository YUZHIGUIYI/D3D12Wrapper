//
// Created by ZZK on 2024/7/31.
//

#pragma once

#include <d3d12/common/d3d12_wrap_common.h>
#include <DirectXTexCustomized.h>
#include <mutex>

namespace DirectX
{
    struct CaptureTextureDesc;
}
namespace gfxshim
{
    enum class RootSignatureType
    {
        Graphics,
        Compute
    };

    struct RenderTargetViewInfo
    {
        ID3D12Resource *d3d12_resource = nullptr;
        D3D12_RENDER_TARGET_VIEW_DESC rtv_desc = {};
        D3D12_RESOURCE_STATES resource_state = D3D12_RESOURCE_STATE_RENDER_TARGET;
        bool cube_map = false;
    };

    struct DepthStencilViewInfo
    {
        ID3D12Resource *d3d12_resource = nullptr;
        D3D12_RESOURCE_STATES resource_state = D3D12_RESOURCE_STATE_DEPTH_WRITE;
    };

    struct UnorderedAccessViewInfo
    {
        ID3D12Resource *d3d12_resource = nullptr;
        D3D12_UNORDERED_ACCESS_VIEW_DESC uav_desc = {};
        D3D12_RESOURCE_STATES resource_state = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
    };

    // Currently only concern root table
    struct RootSignatureInfo
    {
        std::unordered_map<uint32_t, std::vector<D3D12_DESCRIPTOR_RANGE1>> index_to_descriptor_ranges_mapping{};
    };

    struct RootSignatureIndex
    {
        uint64_t blob_pointer = 0;
        ID3D12RootSignature *compute_root_signature = nullptr;
    };

    // Command signature information, only concern about draw and dispatch
    struct CommandSignatureInfo
    {
        D3D12_INDIRECT_ARGUMENT_TYPE indirect_type = D3D12_INDIRECT_ARGUMENT_TYPE_VERTEX_BUFFER_VIEW;
    };

    struct D3D12DeviceTracer
    {
    private:
        // Blob pointer to root signature mapping
        std::unordered_map<uint64_t, ID3D12RootSignature *> blob_to_root_signature_mapping;
        // Blob pointer to root signature creation information mapping
        std::unordered_map<uint64_t, RootSignatureInfo> blob_to_root_signature_info_mapping;
        // Root signature pointer to blob pointer mapping
        std::unordered_map<ID3D12RootSignature *, uint64_t> root_signature_pointer_to_blob_mapping;

        // Render target view and its creation resource
        std::unordered_map<uint64_t, RenderTargetViewInfo> render_target_view_info_storage;
        // Depth stencil view and its creation resource
        std::unordered_map<uint64_t, DepthStencilViewInfo> depth_stencil_view_info_storage;
        // Unordered access view and its creation resource
        std::unordered_map<uint64_t, UnorderedAccessViewInfo> unordered_access_view_info_storage;

        // Command signature pointer to its information
        std::unordered_map<uint64_t, CommandSignatureInfo> command_signature_info_storage;

        // Buffer GPU virtual address to its creation resource
        std::unordered_map<uint64_t, ID3D12Resource *> root_buffer_info_storage;

        // Mutex
        std::mutex lock_mutex;

        // CBV_SRV_UAV descriptor size
        uint32_t srv_uav_descriptor_size = 0;

    public:
        // Store render target view resource during creation
        void StoreRTVAndResource(uint64_t rtv_descriptor, ID3D12Resource *resource, const D3D12_RENDER_TARGET_VIEW_DESC *render_target_view_desc);

        // Store depth stencil view resource during creation
        void StoreDSVAndResource(uint64_t dsv_descriptor, ID3D12Resource *resource, const D3D12_DEPTH_STENCIL_VIEW_DESC *depth_stencil_view_desc);

        // Store unordered access view resource during creation
        void StoreUAVAndResource(uint64_t uav_descriptor, ID3D12Resource *resource, const D3D12_UNORDERED_ACCESS_VIEW_DESC *unordered_access_view_desc);

        // Store buffer gpu va to resource mapping
        void StoreRootBufferMapping(ID3D12Resource *buffer);

        // Store command signature information during creation
        void StoreCommandSignature(uint64_t command_signature_pointer, const D3D12_COMMAND_SIGNATURE_DESC *command_signature_desc);

        // Store blob pointer to root signature mapping
        void UpdateBlobToRootSignatureMapping(uint64_t blob_pointer, ID3D12RootSignature *root_signature = nullptr);

        // Store blob pointer to root signature description mapping, parse root uav and root table
        void StoreBlobToRootSignatureDescMapping(uint64_t blob_pointer, const D3D12_ROOT_SIGNATURE_DESC *root_signature_desc);

        // Store blob pointer to versioned root signature description mapping, parse root uav and root table
        void StoreBlobToVersionedRootSignatureDescMapping(uint64_t blob_pointer, const D3D12_VERSIONED_ROOT_SIGNATURE_DESC *versioned_root_signature_desc);

        // Query compute blob and compute root signature
        RootSignatureIndex QueryComputeRootSignature(ID3D12RootSignature *compute_root_signature);

        // Query CBV_SRV_UAV descriptor size
        [[nodiscard]] uint32_t QueryNonSamplerDescriptorSize() const;

        // Query indirect argument through command signature
        D3D12_INDIRECT_ARGUMENT_TYPE QueryIndirectArgumentType(uint64_t command_signature_pointer);

        // Query root buffer via gpu virtual address
        ID3D12Resource *QueryRootBuffer(uint64_t gpu_va);

        // Set descriptor size
        void SetDescriptorSize(ID3D12Device *device);

        // Update render target view information during invoking ID3D12GraphicsCommandList::OMSetRenderTargets
        void UpdateRTVStatePerDraw(uint64_t rtv_descriptor, std::unordered_map<uint64_t, RenderTargetViewInfo> &render_target_view_info_per_draw);

        // Update depth stencil view information during invoking ID3D12GraphicsCommandList::OMSetRenderTargets
        void UpdateDSVStatePerDraw(uint64_t dsv_descriptor, std::unordered_map<uint64_t, DepthStencilViewInfo> &depth_stencil_view_info_per_draw);

        // Update unordered access view information during invoking ID3D12GraphicsCommandList::SetComputeRootUnorderedAccessView
        void UpdateUAVStatePerDispatch(uint64_t starting_gpu_descriptor, std::unordered_map<uint64_t, UnorderedAccessViewInfo> &unordered_access_view_info_per_dispatch);

        // Update unordered access view information during invoking ID3D12GraphicsCommandList::SetComputeRootDescriptorTable
        void UpdateUAVStatePerDispatch(uint32_t root_parameter_index, uint64_t starting_gpu_descriptor, uint64_t cur_blob_pointer,
                                        ID3D12DescriptorHeap *cur_descriptor_heap, std::unordered_map<uint64_t, UnorderedAccessViewInfo> &unordered_access_view_info_per_dispatch);
    };

    struct D3D12CommandListTracer
    {
    private:
        // Device resources owner
        D3D12DeviceTracer &device_tracer;

        // Per execution dump assets
        std::unordered_map<uint64_t, RenderTargetViewInfo> render_target_view_info_per_execution;

        // Per draw dump assets
        std::unordered_map<uint64_t, RenderTargetViewInfo> render_target_view_info_per_draw;
        std::unordered_map<uint64_t, DepthStencilViewInfo> depth_stencil_view_info_per_draw;
        std::vector<DirectX::CaptureTextureDesc> capture_rtv_texture_desc_storage_per_execution;
        std::vector<DirectX::CaptureTextureDesc> capture_dsv_texture_desc_storage_per_execution;
        // std::vector<DirectX::CaptureTextureDesc> capture_texture_desc_old_storage;
        std::vector<std::wstring> capture_rtv_texture_filepath_storage;
        std::vector<std::wstring> capture_dsv_texture_filepath_storage;

        // Per dispatch dump assets
        std::unordered_map<uint64_t, UnorderedAccessViewInfo> unordered_access_view_info_per_dispatch;
        std::vector<DirectX::CaptureTextureDesc> capture_uav_texture_desc_storage_per_execution;
        std::vector<std::wstring> capture_uav_texture_filepath_storage;

        // Current descriptor heap
        std::vector<ID3D12DescriptorHeap *> cur_descriptor_heaps{};
        ID3D12RootSignature *cur_compute_root_signature = nullptr;
        uint64_t cur_blob_pointer = 0;

        // For execution
        HANDLE fence_event = nullptr;

        std::wstring per_draw_dump_prefix{};
        uint32_t execution_count_limit = 5;
        uint32_t draw_count_limit = 180;
        uint32_t dispatch_count_limit = 10;
        std::atomic<uint32_t> execution_count{ 0 };
        std::atomic<uint32_t> draw_count{ 0 };
        std::atomic<uint32_t> dispatch_count{ 0 };
        std::atomic<bool> per_execution_dump_ready{ false };
        std::atomic<bool> per_draw_dump_ready{ false };
        std::atomic<bool> per_dispatch_dump_ready{ false };
        std::atomic<bool> dump_finish{ false };

        enum class DecorationFlag : uint8_t
        {
            DumpRTV,
            DumpDSV,
            DumpUAV,
        };

        struct DumpDecoration
        {
            explicit DumpDecoration(const D3D12CommandListTracer &in_tracer, const std::wstring &action_string, DecorationFlag dump_flag);
            std::wstring &operator()();
            std::wstring decorated_string;
        };

    public:
        explicit D3D12CommandListTracer(D3D12DeviceTracer &device_tracer_ref, uint32_t command_list_id);

        ~D3D12CommandListTracer();

        D3D12CommandListTracer(const D3D12CommandListTracer &) = delete;
        D3D12CommandListTracer &operator=(const D3D12CommandListTracer &) = delete;
        D3D12CommandListTracer(D3D12CommandListTracer &&) = delete;
        D3D12CommandListTracer &operator=(D3D12CommandListTracer &&) = delete;

        // Deferred per-draw-dump by recording copy command of read back resource
        void CollectStagingResourcePerDraw(ID3D12Device *device, ID3D12GraphicsCommandList *pCommandList);

        // Deferred per-dispatch-dump by recording copy command of read back resource
        void CollectStagingResourcePerDispatch(ID3D12Device *device, ID3D12GraphicsCommandList *pCommandList);

        // Deferred per-execute-indirect-dump by recording copy command of read back resource
        void CollectStagingResourcePerIndirect(ID3D12Device *device, ID3D12GraphicsCommandList *command_list_pointer, uint64_t command_signature_pointer);

        // Deferred per-draw-dump after command queue signal, immediately dump into dds or binary file
        void PerDrawDump(ID3D12Fence *fence, uint64_t fence_value);

        // Deferred per-dispatch-dump after command queue signal, immediately dump into dds or binary file
        void PerDispatchDump(ID3D12Fence *fence, uint64_t fence_value);

        // Clear render target view and depth stencil view information, invoke before update rtv and dsv states
        void ClearRTVAndDSVStatesPerDraw();

        // Update render target view information during invoking ID3D12GraphicsCommandList::OMSetRenderTargets
        void UpdateRTVStatePerDraw(uint64_t rtv_descriptor);

        // Update depth stencil view information during invoking ID3D12GraphicsCommandList::OMSetRenderTargets
        void UpdateDSVStatePerDraw(uint64_t dsv_descriptor);

        // Record descriptor heaps during invoking ID3D12GraphicsCommandList::SetDescriptorHeaps
        void ResetDescriptorHeaps(uint32_t descriptor_heaps_num, ID3D12DescriptorHeap *const *descriptor_heaps_ptr);

        // Record compute pipeline root signature during invoking ID3D12GraphicsCommandList::SetComputeRootSignature
        void ResetComputePipelineRootSignature(ID3D12RootSignature *compute_root_signature);

        // Update unordered access view information during invoking ID3D12GraphicsCommandList::SetComputeRootUnorderedAccessView
        void UpdateUAVStatePerDispatch(uint64_t starting_gpu_descriptor);

        // Update unordered access view information during invoking ID3D12GraphicsCommandList::SetComputeRootDescriptorTable
        void UpdateUAVStatePerDispatch(uint32_t root_parameter_index, uint64_t starting_gpu_descriptor);

        // Increase execution count
        void Advance();

    private:
        uint32_t IncreaseExecutionCount();

        uint32_t CheckExecutionCount() const;

        uint32_t IncreaseDrawCount();

        uint32_t CheckDrawCount() const;

        uint32_t IncreaseDispatchCount();

        uint32_t CheckDispatchCount() const;

        void SetDumpFinish();

        bool CheckDumpFinish() const;
    };
}
