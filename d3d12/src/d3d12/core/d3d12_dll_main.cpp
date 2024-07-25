#include <d3d12/core/d3d12_hook_manager.h>
#include <d3d12/core/d3d12_device_wrap.h>

HRESULT WINAPI D3D12GetDebugInterface( _In_ REFIID riid, _COM_Outptr_opt_ void** ppvDebug )
{
    HRESULT result = E_UNEXPECTED;
    auto &&d3d12_hook_manager = gfxshim::D3D12HookManager::GetInstance();
    if (d3d12_hook_manager.DispatchTable().D3D12GetDebugInterface != nullptr)
    {
        return d3d12_hook_manager.DispatchTable().D3D12GetDebugInterface(riid, ppvDebug);
    }
    return result;
}

HRESULT WINAPI D3D12GetInterface( _In_ REFCLSID rclsid, _In_ REFIID riid, _COM_Outptr_opt_ void** ppvDebug )
{
    HRESULT result = E_UNEXPECTED;
    auto &&d3d12_hook_manager = gfxshim::D3D12HookManager::GetInstance();
    if (d3d12_hook_manager.DispatchTable().D3D12GetInterface != nullptr)
    {
        return d3d12_hook_manager.DispatchTable().D3D12GetInterface(rclsid, riid, ppvDebug);
    }
    return result;
}

HRESULT WINAPI D3D12CreateDevice(
    _In_opt_ IUnknown* pAdapter,
    D3D_FEATURE_LEVEL MinimumFeatureLevel,
    _In_ REFIID riid,
    _COM_Outptr_opt_ void** ppDevice )
{
    HRESULT result = E_UNEXPECTED;
    auto &&d3d12_hook_manager = gfxshim::D3D12HookManager::GetInstance();
    if (d3d12_hook_manager.DispatchTable().D3D12CreateDevice != nullptr)
    {
        result = d3d12_hook_manager.DispatchTable().D3D12CreateDevice(pAdapter, MinimumFeatureLevel, riid, ppDevice);
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
            WrappedID3D12Device *wrapped_device = WrappedID3D12Device::create(real_device);
            *ppDevice = wrapped_device;
            D3D12_WRAPPER_DEBUG("Wrapped device pointer: {}", reinterpret_cast<void *>(wrapped_device));
        }
    }

    return result;
}

HRESULT WINAPI D3D12SerializeRootSignature(
        _In_ const D3D12_ROOT_SIGNATURE_DESC* pRootSignature,
        _In_ D3D_ROOT_SIGNATURE_VERSION Version,
        _Out_ ID3DBlob** ppBlob,
        _Always_(_Outptr_opt_result_maybenull_) ID3DBlob** ppErrorBlob)
{
    HRESULT result = E_UNEXPECTED;
    auto &&d3d12_hook_manager = gfxshim::D3D12HookManager::GetInstance();
    if (d3d12_hook_manager.DispatchTable().D3D12SerializeRootSignature != nullptr)
    {
        D3D12_WRAPPER_DEBUG("Invoke D3D12SerializeRootSignature");
        return d3d12_hook_manager.DispatchTable().D3D12SerializeRootSignature(pRootSignature, Version, ppBlob, ppErrorBlob);
    }
    return result;
}

HRESULT WINAPI D3D12SerializeVersionedRootSignature(
        _In_ const D3D12_VERSIONED_ROOT_SIGNATURE_DESC* pRootSignature,
        _Out_ ID3DBlob** ppBlob,
        _Always_(_Outptr_opt_result_maybenull_) ID3DBlob** ppErrorBlob)
{
    HRESULT result = E_UNEXPECTED;
    auto &&d3d12_hook_manager = gfxshim::D3D12HookManager::GetInstance();
    if (d3d12_hook_manager.DispatchTable().D3D12SerializeVersionedRootSignature != nullptr)
    {
        D3D12_WRAPPER_DEBUG("Invoke D3D12SerializeVersionedRootSignature");
        return d3d12_hook_manager.DispatchTable().D3D12SerializeVersionedRootSignature(pRootSignature, ppBlob, ppErrorBlob);
    }
    return result;
}

HRESULT WINAPI D3D12CreateRootSignatureDeserializer(
        _In_reads_bytes_(SrcDataSizeInBytes) LPCVOID pSrcData,
        _In_ SIZE_T SrcDataSizeInBytes,
        _In_ REFIID pRootSignatureDeserializerInterface,
        _Out_ void** ppRootSignatureDeserializer)
{
    HRESULT result = E_UNEXPECTED;
    auto &&d3d12_hook_manager = gfxshim::D3D12HookManager::GetInstance();
    if (d3d12_hook_manager.DispatchTable().D3D12CreateRootSignatureDeserializer != nullptr)
    {
        D3D12_WRAPPER_DEBUG("Invoke D3D12CreateRootSignatureDeserializer");
        return d3d12_hook_manager.DispatchTable().D3D12CreateRootSignatureDeserializer(pSrcData, SrcDataSizeInBytes, pRootSignatureDeserializerInterface, ppRootSignatureDeserializer);
    }
    return result;
}

HRESULT WINAPI D3D12CreateVersionedRootSignatureDeserializer(
        _In_reads_bytes_(SrcDataSizeInBytes) LPCVOID pSrcData,
        _In_ SIZE_T SrcDataSizeInBytes,
        _In_ REFIID pRootSignatureDeserializerInterface,
        _Out_ void** ppRootSignatureDeserializer)
{
    HRESULT result = E_UNEXPECTED;
    auto &&d3d12_hook_manager = gfxshim::D3D12HookManager::GetInstance();
    if (d3d12_hook_manager.DispatchTable().D3D12CreateVersionedRootSignatureDeserializer != nullptr)
    {
        D3D12_WRAPPER_DEBUG("Invoke D3D12CreateVersionedRootSignatureDeserializer");
        return d3d12_hook_manager.DispatchTable().D3D12CreateVersionedRootSignatureDeserializer(pSrcData, SrcDataSizeInBytes, pRootSignatureDeserializerInterface, ppRootSignatureDeserializer);
    }
    return result;
}

HRESULT WINAPI D3D12EnableExperimentalFeatures(
        UINT                                    NumFeatures,
        _In_count_(NumFeatures) const IID*     pIIDs,
        _In_opt_count_(NumFeatures) void*      pConfigurationStructs,
        _In_opt_count_(NumFeatures) UINT*      pConfigurationStructSizes)
{
    HRESULT result = E_INVALIDARG;
    auto &&d3d12_hook_manager = gfxshim::D3D12HookManager::GetInstance();
    if (d3d12_hook_manager.DispatchTable().D3D12EnableExperimentalFeatures != nullptr)
    {
        D3D12_WRAPPER_DEBUG("Invoke D3D12EnableExperimentalFeatures");
        return d3d12_hook_manager.DispatchTable().D3D12EnableExperimentalFeatures(NumFeatures, pIIDs, pConfigurationStructs, pConfigurationStructSizes);
    }
    return result;
}

BOOL WINAPI DllMain(HINSTANCE hinst_dll, DWORD fdw_reason, LPVOID lpv_reserved)
{
    return TRUE;
}







