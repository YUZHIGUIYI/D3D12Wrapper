//
// Created by ZZK on 2024/7/25.
//
#pragma once

#include <d3d12/common/d3d12_wrap_common.h>
#include <d3d12/common/object_pool.h>
#include <d3d12/tracer/d3d12_tracer.h>
#include <span>

class WrappedID3D12Device;
class WrappedID3D12CommandQueue;
class WrappedID3D12CommandAllocator;
class WrappedID3D12GraphicsCommandList;

namespace gfxshim
{
    enum class WrappedResourceType : uint8_t
    {
        Device,
        CommandQueue,
        CommandAllocator,
        GraphicsCommandList
    };

    struct WrappedResource
    {
        void               *raw_resource_ptr = nullptr;
        WrappedResourceType resource_type    = WrappedResourceType::Device;
    };

    struct D3D12DispatchTable
    {
        // Note: There is no typedef in d3d12.h for D3D12EnableExperimentalFeatures.
        using PFN_D3D12_ENABLE_EXPERIMENTAL_FEATURES = HRESULT(WINAPI *)(
                UINT                                   NumFeatures,
                _In_count_(NumFeatures) const IID*     pIIDs,
                _In_opt_count_(NumFeatures) void*      pConfigurationStructs,
                _In_opt_count_(NumFeatures) UINT*      pConfigurationStructSizes);

        // Functions processed for capture. These are the D3D12 functions exported by d3d12.dll and documented on MSDN.
        PFN_D3D12_CREATE_DEVICE                                D3D12CreateDevice = nullptr ;
        PFN_D3D12_CREATE_ROOT_SIGNATURE_DESERIALIZER           D3D12CreateRootSignatureDeserializer = nullptr;
        PFN_D3D12_CREATE_VERSIONED_ROOT_SIGNATURE_DESERIALIZER D3D12CreateVersionedRootSignatureDeserializer = nullptr;
        PFN_D3D12_GET_DEBUG_INTERFACE                          D3D12GetDebugInterface = nullptr;
        PFN_D3D12_SERIALIZE_ROOT_SIGNATURE                     D3D12SerializeRootSignature = nullptr;
        PFN_D3D12_SERIALIZE_VERSIONED_ROOT_SIGNATURE           D3D12SerializeVersionedRootSignature = nullptr;
        PFN_D3D12_GET_INTERFACE                                D3D12GetInterface = nullptr;
        PFN_D3D12_ENABLE_EXPERIMENTAL_FEATURES                 D3D12EnableExperimentalFeatures = nullptr;
    };

    struct D3D12HookManager
    {
    private:
        struct ResourceManagerImpl
        {
            util::ThreadSafeObjectPool<WrappedID3D12Device>              wrapped_device_pool;
            util::ThreadSafeObjectPool<WrappedID3D12CommandQueue>        wrapped_command_queue_pool;
            util::ThreadSafeObjectPool<WrappedID3D12CommandAllocator>    wrapped_command_allocator_pool;
            util::ThreadSafeObjectPool<WrappedID3D12GraphicsCommandList> wrapped_command_list_pool;
        };

        std::unique_ptr<ResourceManagerImpl> resource_manager_impl = nullptr;
        std::unordered_map<void *, WrappedResource> wrapped_resource_storage;
        std::unordered_map<ID3D12GraphicsCommandList *, std::unique_ptr<D3D12CommandListTracer>> command_list_tracer_storage{};
        D3D12DeviceTracer device_tracer{};
        HMODULE d3d12_module = nullptr;
        D3D12DispatchTable dispatch_table{};

    private:
        D3D12HookManager();

    public:
        static D3D12HookManager &GetInstance();

        ~D3D12HookManager();

        [[nodiscard]] const D3D12DispatchTable &DispatchTable() const;

        D3D12HookManager(const D3D12HookManager &) = delete;
        D3D12HookManager &operator=(const D3D12HookManager &) = delete;
        D3D12HookManager(D3D12HookManager &&) = delete;
        D3D12HookManager &operator=(D3D12HookManager &&) = delete;

        // Construct resource
        template <typename T, typename ... Args>
        T *ConstructResource(Args&& ... args);

        // Destroy resource
        template <typename T>
        void DestroyResource(T *resource_ptr);

        // Destroy resource with type
        void DestroyResource(const WrappedResource &wrapped_resource);

        // Register command list tracer
        void RegisterCommandListTracer(ID3D12GraphicsCommandList *command_list_pointer);

        // Store render target view resource during creation
        void StoreRTVAndResource(uint64_t rtv_descriptor, ID3D12Resource *resource, const D3D12_RENDER_TARGET_VIEW_DESC *render_target_view_desc);

        // Store depth stencil view resource during creation
        void StoreDSVAndResource(uint64_t dsv_descriptor, ID3D12Resource *resource, const D3D12_DEPTH_STENCIL_VIEW_DESC *depth_stencil_view_desc);

        // Store unordered access view resource during creation
        void StoreUAVAndResource(uint64_t uav_descriptor, ID3D12Resource *resource, const D3D12_UNORDERED_ACCESS_VIEW_DESC *unordered_access_view_desc);

        // Store command signature information during creation
        void StoreCommandSignature(uint64_t command_signature_pointer, const D3D12_COMMAND_SIGNATURE_DESC *command_signature_desc);

        // Store blob pointer to root signature mapping
        void UpdateBlobToRootSignatureMapping(uint64_t blob_pointer, ID3D12RootSignature *root_signature = nullptr);

        // Store blob pointer to root signature description mapping, parse root uav and root table
        void StoreBlobToRootSignatureDescMapping(uint64_t blob_pointer, const D3D12_ROOT_SIGNATURE_DESC *root_signature_desc);

        // Store blob pointer to versioned root signature description mapping, parse root uav and root table
        void StoreBlobToVersionedRootSignatureDescMapping(uint64_t blob_pointer, const D3D12_VERSIONED_ROOT_SIGNATURE_DESC *versioned_root_signature_desc);

        // Get D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV descriptor size
        void SetDescriptorSize(ID3D12Device *device);

    public:
        // Update render target view and depth stencil view information during invoking ID3D12GraphicsCommandList::OMSetRenderTargets
        void UpdateRTVAndDSVStatesPerDraw(ID3D12GraphicsCommandList *command_list_pointer, uint32_t render_target_descriptors_num, const D3D12_CPU_DESCRIPTOR_HANDLE *render_target_descriptors, const D3D12_CPU_DESCRIPTOR_HANDLE *depth_stencil_descriptor);

        // Update unordered access view information during invoking ID3D12GraphicsCommandList::SetComputeRootUnorderedAccessView
        void UpdateUAVStatePerDispatch(ID3D12GraphicsCommandList *command_list_pointer, uint64_t starting_gpu_descriptor);

        // Update unordered access view information during invoking ID3D12GraphicsCommandList::SetComputeRootDescriptorTable
        void UpdateUAVStatePerDispatch(ID3D12GraphicsCommandList *command_list_pointer, uint32_t root_parameter_index, uint64_t starting_gpu_descriptor);

        // Deferred per-draw-dump by recording copy command of read back resource
        void CollectStagingResourcePerDraw(ID3D12Device *device, ID3D12GraphicsCommandList *command_list_pointer);

        // Deferred per-dispatch-dump by recording copy command of read back resource
        void CollectStagingResourcePerDispatch(ID3D12Device *device, ID3D12GraphicsCommandList *command_list_pointer);

        // Deferred per-execute-indirect-dump by recording copy command of read back resource
        void CollectStagingResourcePerIndirect(ID3D12Device *device, ID3D12GraphicsCommandList *command_list_pointer, uint64_t command_signature_pointer);

        // Record descriptor heaps during invoking ID3D12GraphicsCommandList::SetDescriptorHeaps
        void ResetDescriptorHeaps(ID3D12GraphicsCommandList *command_list_pointer, uint32_t descriptor_heaps_num, ID3D12DescriptorHeap *const *descriptor_heaps_pointer);

        // Record compute pipeline root signature during invoking ID3D12GraphicsCommandList::SetComputeRootSignature
        void ResetComputePipelineRootSignature(ID3D12GraphicsCommandList *command_list_pointer, ID3D12RootSignature *compute_root_signature);

        /*
         * Deferred per-draw-dump after command queue signal, immediately dump into dds or binary file;
         * deferred per-dispatch-dump after command queue signal, immediately dump into dds or binary file
         */
        void PerDrawAndDispatchDump(std::span<ID3D12GraphicsCommandList *> graphics_command_list_pointers, ID3D12Fence *fence, uint64_t fence_value);

    public:
        // Wrap exported d3d12 functions
        HRESULT WINAPI D3D12GetDebugInterface(_In_ REFIID riid, _COM_Outptr_opt_ void **ppvDebug);

        HRESULT WINAPI D3D12GetInterface(_In_ REFCLSID rclsid, _In_ REFIID riid, _COM_Outptr_opt_ void **ppvDebug);

        HRESULT WINAPI D3D12CreateDevice(_In_opt_ IUnknown *pAdapter,
                                        D3D_FEATURE_LEVEL MinimumFeatureLevel,
                                        _In_ REFIID riid,
                                        _COM_Outptr_opt_ void **ppDevice);

        HRESULT WINAPI D3D12SerializeRootSignature(
                _In_ const D3D12_ROOT_SIGNATURE_DESC *pRootSignature,
                _In_ D3D_ROOT_SIGNATURE_VERSION Version,
                _Out_ ID3DBlob **ppBlob,
                _Always_(_Outptr_opt_result_maybenull_) ID3DBlob **ppErrorBlob);

        HRESULT WINAPI D3D12SerializeVersionedRootSignature(
                _In_ const D3D12_VERSIONED_ROOT_SIGNATURE_DESC *pRootSignature,
                _Out_ ID3DBlob **ppBlob,
                _Always_(_Outptr_opt_result_maybenull_) ID3DBlob **ppErrorBlob);

        HRESULT WINAPI D3D12CreateRootSignatureDeserializer(
                _In_reads_bytes_(SrcDataSizeInBytes) LPCVOID pSrcData,
                _In_ SIZE_T SrcDataSizeInBytes,
                _In_ REFIID pRootSignatureDeserializerInterface,
                _Out_ void **ppRootSignatureDeserializer);

        HRESULT WINAPI D3D12CreateVersionedRootSignatureDeserializer(
                _In_reads_bytes_(SrcDataSizeInBytes) LPCVOID pSrcData,
                _In_ SIZE_T SrcDataSizeInBytes,
                _In_ REFIID pRootSignatureDeserializerInterface,
                _Out_ void **ppRootSignatureDeserializer);

        HRESULT WINAPI D3D12EnableExperimentalFeatures(
                UINT                               NumFeatures,
                _In_count_(NumFeatures) const IID *pIIDs,
                _In_opt_count_(NumFeatures) void  *pConfigurationStructs,
                _In_opt_count_(NumFeatures) UINT  *pConfigurationStructSizes);
    };

    template <typename T, typename ... Args>
    T *D3D12HookManager::ConstructResource(Args&& ... args)
    {
        if constexpr (std::is_same_v<T, WrappedID3D12Device>)
        {
            auto *resource = resource_manager_impl->wrapped_device_pool.construct_at(std::forward<Args>(args)...);
            wrapped_resource_storage.try_emplace(resource, resource, WrappedResourceType::Device);
            return resource;
        } else if constexpr (std::is_same_v<T, WrappedID3D12CommandQueue>)
        {
            auto *resource = resource_manager_impl->wrapped_command_queue_pool.construct_at(std::forward<Args>(args)...);
            wrapped_resource_storage.try_emplace(resource, resource, WrappedResourceType::CommandQueue);
            return resource;
        } else if constexpr (std::is_same_v<T, WrappedID3D12CommandAllocator>)
        {
            auto *resource = resource_manager_impl->wrapped_command_allocator_pool.construct_at(std::forward<Args>(args)...);
            wrapped_resource_storage.try_emplace(resource, resource, WrappedResourceType::CommandAllocator);
            return resource;
        } else if constexpr (std::is_same_v<T, WrappedID3D12GraphicsCommandList>)
        {
            auto *resource = resource_manager_impl->wrapped_command_list_pool.construct_at(std::forward<Args>(args)...);
            wrapped_resource_storage.try_emplace(resource, resource, WrappedResourceType::GraphicsCommandList);
            return resource;
        } else
        {
            static_assert(false, "Unsupported resource type");
        }
    }

    template <typename T>
    void D3D12HookManager::DestroyResource(T *resource_ptr)
    {
        if constexpr (std::is_same_v<T, WrappedID3D12Device>)
        {
            resource_manager_impl->wrapped_device_pool.destroy_at(resource_ptr);
        } else if constexpr (std::is_same_v<T, WrappedID3D12CommandQueue>)
        {
            resource_manager_impl->wrapped_command_queue_pool.destroy_at(resource_ptr);
        } else if constexpr (std::is_same_v<T, WrappedID3D12CommandAllocator>)
        {
            resource_manager_impl->wrapped_command_allocator_pool.destroy_at(resource_ptr);
        } else if constexpr (std::is_same_v<T, WrappedID3D12GraphicsCommandList>)
        {
            resource_manager_impl->wrapped_command_list_pool.destroy_at(resource_ptr);
        } else
        {
            static_assert(false, "Unsupported resource type");
        }
    }
}