//
// Created by ZZK on 2024/7/25.
//

#include <d3d12/core/d3d12_hook_manager.h>
#include <d3d12/core/d3d12_device_wrap.h>
#include <d3d12/core/d3d12_command_queue_wrap.h>
#include <d3d12/core/d3d12_command_allocator_wrap.h>
#include <d3d12/core/d3d12_command_list_wrap.h>

namespace gfxshim
{
    D3D12HookManager::D3D12HookManager()
    : resource_manager_impl(std::make_unique<ResourceManagerImpl>())
    {
        char system_directory[MAX_PATH];
        uint32_t result = GetSystemDirectory(system_directory, MAX_PATH);
        if (result == 0)
        {
            D3D12_WRAPPER_ERROR("Failed to retrieve system directory");
            return;
        }

        std::string core_lib_directory(system_directory);
        d3d12_module = LoadLibraryA((core_lib_directory + "\\d3d12.dll").c_str());
        if (d3d12_module == nullptr)
        {
            D3D12_WRAPPER_ERROR("Failed to load d3d12.dll");
            return;
        }

        dispatch_table.D3D12GetDebugInterface = (PFN_D3D12_GET_DEBUG_INTERFACE)GetProcAddress(d3d12_module, "D3D12GetDebugInterface");
        dispatch_table.D3D12GetInterface = (PFN_D3D12_GET_INTERFACE)GetProcAddress(d3d12_module, "D3D12GetInterface");
        dispatch_table.D3D12CreateDevice = (PFN_D3D12_CREATE_DEVICE)GetProcAddress(d3d12_module, "D3D12CreateDevice");
        dispatch_table.D3D12SerializeRootSignature = (PFN_D3D12_SERIALIZE_ROOT_SIGNATURE)GetProcAddress(d3d12_module, "D3D12SerializeRootSignature");
        dispatch_table.D3D12SerializeVersionedRootSignature = (PFN_D3D12_SERIALIZE_VERSIONED_ROOT_SIGNATURE)GetProcAddress(d3d12_module, "D3D12SerializeVersionedRootSignature");
        dispatch_table.D3D12CreateRootSignatureDeserializer = (PFN_D3D12_CREATE_ROOT_SIGNATURE_DESERIALIZER)GetProcAddress(d3d12_module, "D3D12CreateRootSignatureDeserializer");
        dispatch_table.D3D12CreateVersionedRootSignatureDeserializer = (PFN_D3D12_CREATE_VERSIONED_ROOT_SIGNATURE_DESERIALIZER)GetProcAddress(d3d12_module, "D3D12CreateVersionedRootSignatureDeserializer");
        dispatch_table.D3D12EnableExperimentalFeatures = (D3D12DispatchTable::PFN_D3D12_ENABLE_EXPERIMENTAL_FEATURES)GetProcAddress(d3d12_module, "D3D12EnableExperimentalFeatures");

        AllocConsole();
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
        D3D12_WRAPPER_DEBUG("Initialized D3D12 hook manager successfully");
    }

    D3D12HookManager::~D3D12HookManager()
    {
        if (d3d12_module)
        {
            FreeLibrary(d3d12_module);
            dispatch_table = {};
        }
        for (auto &&wrapped_resource_pair : wrapped_resource_storage)
        {
            DestroyResource(wrapped_resource_pair.second);
        }
        resource_manager_impl->wrapped_device_pool.deallocate();
        resource_manager_impl->wrapped_command_queue_pool.deallocate();
        resource_manager_impl->wrapped_command_allocator_pool.deallocate();
        resource_manager_impl->wrapped_command_list_pool.deallocate();

        D3D12_WRAPPER_DEBUG("Release D3D12 hook manager successfully");
    }

    void D3D12HookManager::DestroyResource(const WrappedResource &wrapped_resource)
    {
        if (wrapped_resource.resource_type == WrappedResourceType::Device)
        {
            DestroyResource<WrappedID3D12Device>(reinterpret_cast<WrappedID3D12Device *>(wrapped_resource.raw_resource_ptr));
        } else if (wrapped_resource.resource_type == WrappedResourceType::CommandQueue)
        {
            DestroyResource<WrappedID3D12CommandQueue>(reinterpret_cast<WrappedID3D12CommandQueue *>(wrapped_resource.raw_resource_ptr));
        } else if (wrapped_resource.resource_type == WrappedResourceType::CommandAllocator)
        {
            DestroyResource<WrappedID3D12CommandAllocator>(reinterpret_cast<WrappedID3D12CommandAllocator *>(wrapped_resource.raw_resource_ptr));
        } else if (wrapped_resource.resource_type == WrappedResourceType::GraphicsCommandList)
        {
            DestroyResource<WrappedID3D12GraphicsCommandList>(reinterpret_cast<WrappedID3D12GraphicsCommandList *>(wrapped_resource.raw_resource_ptr));
        }
    }

    const D3D12DispatchTable &D3D12HookManager::DispatchTable() const
    {
        return dispatch_table;
    }

    D3D12HookManager &D3D12HookManager::GetInstance()
    {
        static D3D12HookManager s_d3d12_hook_manager{};
        return s_d3d12_hook_manager;
    }

    HRESULT WINAPI D3D12HookManager::D3D12GetDebugInterface(_In_ REFIID riid, _COM_Outptr_opt_ void **ppvDebug)
    {
        HRESULT result = E_UNEXPECTED;
        if (dispatch_table.D3D12GetDebugInterface != nullptr)
        {
            result = dispatch_table.D3D12GetDebugInterface(riid, ppvDebug);
            D3D12_WRAPPER_DEBUG("Invoke D3D12GetDebugInterface");
        }
        return result;
    }

    HRESULT WINAPI D3D12HookManager::D3D12GetInterface(_In_ REFCLSID rclsid, _In_ REFIID riid, _COM_Outptr_opt_ void **ppvDebug)
    {
        HRESULT result = E_UNEXPECTED;
        if (dispatch_table.D3D12GetInterface != nullptr)
        {
            result = dispatch_table.D3D12GetInterface(rclsid, riid, ppvDebug);
            D3D12_WRAPPER_DEBUG("Invoke D3D12GetInterface");
        }
        return result;
    }

    HRESULT WINAPI D3D12HookManager::D3D12CreateDevice(_In_opt_ IUnknown *pAdapter,
                                                        D3D_FEATURE_LEVEL MinimumFeatureLevel,
                                                        _In_ REFIID riid,
                                                        _COM_Outptr_opt_ void **ppDevice)
    {
        HRESULT result = E_UNEXPECTED;
        if (dispatch_table.D3D12CreateDevice != nullptr)
        {
            result = dispatch_table.D3D12CreateDevice(pAdapter, MinimumFeatureLevel, riid, ppDevice);
            D3D12_WRAPPER_DEBUG("Invoke D3D12CreateDevice");
            if (ppDevice != nullptr && (*ppDevice != nullptr))
            {
                D3D12_WRAPPER_DEBUG("Real device pointer: {}", *ppDevice);
            }
        }

        if(SUCCEEDED(result) && ppDevice != nullptr && (*ppDevice != nullptr))
        {
            ID3D12Device *real_device = nullptr;

            if(riid == __uuidof(ID3D12Device) || riid == __uuidof(ID3D12Device) || riid == __uuidof(ID3D12Device2) || riid == __uuidof(ID3D12Device3) || riid == __uuidof(ID3D12Device4) ||
                riid == __uuidof(ID3D12Device5) || riid == __uuidof(ID3D12Device6) || riid == __uuidof(ID3D12Device7) || riid == __uuidof(ID3D12Device8) ||
                riid == __uuidof(ID3D12Device9) || riid == __uuidof(ID3D12Device10))
            {
                real_device = reinterpret_cast<ID3D12Device *>(*ppDevice);
                auto *wrapped_device = ConstructResource<WrappedID3D12Device>(real_device);
                *ppDevice = wrapped_device;
                D3D12_WRAPPER_DEBUG("Wrapped device pointer: {}", reinterpret_cast<void *>(wrapped_device));
            }
        }

        return result;
    }

    HRESULT WINAPI D3D12HookManager::D3D12SerializeRootSignature(
            _In_ const D3D12_ROOT_SIGNATURE_DESC *pRootSignature,
            _In_ D3D_ROOT_SIGNATURE_VERSION Version,
            _Out_ ID3DBlob **ppBlob,
            _Always_(_Outptr_opt_result_maybenull_) ID3DBlob **ppErrorBlob)
    {
        HRESULT result = E_UNEXPECTED;
        if (dispatch_table.D3D12SerializeRootSignature != nullptr)
        {
            result = dispatch_table.D3D12SerializeRootSignature(pRootSignature, Version, ppBlob, ppErrorBlob);
            D3D12_WRAPPER_DEBUG("Invoke D3D12SerializeRootSignature");
        }
        return result;
    }

    HRESULT WINAPI D3D12HookManager::D3D12SerializeVersionedRootSignature(
            _In_ const D3D12_VERSIONED_ROOT_SIGNATURE_DESC *pRootSignature,
            _Out_ ID3DBlob **ppBlob,
            _Always_(_Outptr_opt_result_maybenull_) ID3DBlob **ppErrorBlob)
    {
        HRESULT result = E_UNEXPECTED;
        if (dispatch_table.D3D12SerializeVersionedRootSignature != nullptr)
        {
            result = dispatch_table.D3D12SerializeVersionedRootSignature(pRootSignature, ppBlob, ppErrorBlob);
            D3D12_WRAPPER_DEBUG("Invoke D3D12SerializeVersionedRootSignature");
        }
        return result;
    }

    HRESULT WINAPI D3D12HookManager::D3D12CreateRootSignatureDeserializer(
            _In_reads_bytes_(SrcDataSizeInBytes) LPCVOID pSrcData,
            _In_ SIZE_T SrcDataSizeInBytes,
            _In_ REFIID pRootSignatureDeserializerInterface,
            _Out_ void **ppRootSignatureDeserializer)
    {
        HRESULT result = E_UNEXPECTED;
        if (dispatch_table.D3D12CreateRootSignatureDeserializer != nullptr)
        {
            result = dispatch_table.D3D12CreateRootSignatureDeserializer(pSrcData, SrcDataSizeInBytes, pRootSignatureDeserializerInterface, ppRootSignatureDeserializer);
            D3D12_WRAPPER_DEBUG("Invoke D3D12CreateRootSignatureDeserializer");
        }
        return result;
    }

    HRESULT WINAPI D3D12HookManager::D3D12CreateVersionedRootSignatureDeserializer(
            _In_reads_bytes_(SrcDataSizeInBytes) LPCVOID pSrcData,
            _In_ SIZE_T SrcDataSizeInBytes,
            _In_ REFIID pRootSignatureDeserializerInterface,
            _Out_ void **ppRootSignatureDeserializer)
    {
        HRESULT result = E_UNEXPECTED;
        if (dispatch_table.D3D12CreateVersionedRootSignatureDeserializer != nullptr)
        {
            result = dispatch_table.D3D12CreateVersionedRootSignatureDeserializer(pSrcData, SrcDataSizeInBytes, pRootSignatureDeserializerInterface, ppRootSignatureDeserializer);
            D3D12_WRAPPER_DEBUG("Invoke D3D12CreateVersionedRootSignatureDeserializer");
        }
        return result;
    }

    HRESULT WINAPI D3D12HookManager::D3D12EnableExperimentalFeatures(
            UINT                               NumFeatures,
            _In_count_(NumFeatures) const IID *pIIDs,
            _In_opt_count_(NumFeatures) void  *pConfigurationStructs,
            _In_opt_count_(NumFeatures) UINT  *pConfigurationStructSizes)
    {
        HRESULT result = E_UNEXPECTED;
        if (dispatch_table.D3D12EnableExperimentalFeatures != nullptr)
        {
            result = dispatch_table.D3D12EnableExperimentalFeatures(NumFeatures, pIIDs, pConfigurationStructs, pConfigurationStructSizes);
            D3D12_WRAPPER_DEBUG("Invoke D3D12EnableExperimentalFeatures");
        }
        return result;
    }
}