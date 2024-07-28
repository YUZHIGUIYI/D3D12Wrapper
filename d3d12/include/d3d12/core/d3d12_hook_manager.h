//
// Created by ZZK on 2024/7/25.
//

#include <d3d12/common/d3d12_wrap_common.h>
#include <d3d12/common/object_pool.h>

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

    struct RenderTargetViewState
    {
        ID3D12Resource *pResource = nullptr;
        uint32_t Subresource = 0;
        D3D12_RESOURCE_STATES resource_state = D3D12_RESOURCE_STATE_RENDER_TARGET;
    };

    struct D3D12Tracer
    {
    private:
        std::unordered_map<uint64_t, ID3D12Resource *> render_target_resource_storage;
        std::unordered_map<uint64_t, RenderTargetViewState> render_target_state_before_execution;
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

    public:
        D3D12Tracer();

        static D3D12Tracer &GetInstance();

        // Store render target view resource during creation
        void StoreRTVAndResource(uint64_t rtv_descriptor, ID3D12Resource *resource);

        // Check whether rtv resource has been included
        bool CheckRTVResourceStoredStatus(ID3D12Resource *resource);

        // Store render target view resource during output merger
        void UpdateRTVState(uint64_t rtv_descriptor, D3D12_RESOURCE_STATES resource_state = D3D12_RESOURCE_STATE_RENDER_TARGET);

        // Clear render target view state after execution
        void ClearRTVState();

        uint32_t IncreaseExecutionCount();

        uint32_t CheckExecutionCount() const;

        void PerDrawDump(ID3D12CommandQueue *command_queue);
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