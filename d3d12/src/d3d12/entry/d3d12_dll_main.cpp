#include <d3d12/tracer/d3d12_hook_manager.h>

HRESULT WINAPI D3D12GetDebugInterface(_In_ REFIID riid, _COM_Outptr_opt_ void **ppvDebug)
{
    HRESULT result = E_UNEXPECTED;
    result = gfxshim::D3D12HookManager::GetInstance().D3D12GetDebugInterface(riid, ppvDebug);
    return result;
}

HRESULT WINAPI D3D12GetInterface(_In_ REFCLSID rclsid, _In_ REFIID riid, _COM_Outptr_opt_ void **ppvDebug )
{
    HRESULT result = E_UNEXPECTED;
    result = gfxshim::D3D12HookManager::GetInstance().D3D12GetInterface(rclsid, riid, ppvDebug);
    return result;
}

HRESULT WINAPI D3D12CreateDevice(
    _In_opt_ IUnknown *pAdapter,
    D3D_FEATURE_LEVEL MinimumFeatureLevel,
    _In_ REFIID riid,
    _COM_Outptr_opt_ void **ppDevice)
{
    HRESULT result = gfxshim::D3D12HookManager::GetInstance().D3D12CreateDevice(pAdapter, MinimumFeatureLevel, riid, ppDevice);
    return result;
}

HRESULT WINAPI D3D12SerializeRootSignature(
        _In_ const D3D12_ROOT_SIGNATURE_DESC *pRootSignature,
        _In_ D3D_ROOT_SIGNATURE_VERSION Version,
        _Out_ ID3DBlob **ppBlob,
        _Always_(_Outptr_opt_result_maybenull_) ID3DBlob **ppErrorBlob)
{
    HRESULT result = gfxshim::D3D12HookManager::GetInstance().D3D12SerializeRootSignature(pRootSignature, Version, ppBlob, ppErrorBlob);
    return result;
}

HRESULT WINAPI D3D12SerializeVersionedRootSignature(
        _In_ const D3D12_VERSIONED_ROOT_SIGNATURE_DESC *pRootSignature,
        _Out_ ID3DBlob **ppBlob,
        _Always_(_Outptr_opt_result_maybenull_) ID3DBlob **ppErrorBlob)
{
    HRESULT result = gfxshim::D3D12HookManager::GetInstance().D3D12SerializeVersionedRootSignature(pRootSignature, ppBlob, ppErrorBlob);
    return result;
}

HRESULT WINAPI D3D12CreateRootSignatureDeserializer(
        _In_reads_bytes_(SrcDataSizeInBytes) LPCVOID pSrcData,
        _In_ SIZE_T SrcDataSizeInBytes,
        _In_ REFIID pRootSignatureDeserializerInterface,
        _Out_ void **ppRootSignatureDeserializer)
{
    HRESULT result = gfxshim::D3D12HookManager::GetInstance().D3D12CreateRootSignatureDeserializer(pSrcData, SrcDataSizeInBytes, pRootSignatureDeserializerInterface, ppRootSignatureDeserializer);
    return result;
}

HRESULT WINAPI D3D12CreateVersionedRootSignatureDeserializer(
        _In_reads_bytes_(SrcDataSizeInBytes) LPCVOID pSrcData,
        _In_ SIZE_T SrcDataSizeInBytes,
        _In_ REFIID pRootSignatureDeserializerInterface,
        _Out_ void **ppRootSignatureDeserializer)
{
    HRESULT result = gfxshim::D3D12HookManager::GetInstance().D3D12CreateVersionedRootSignatureDeserializer(pSrcData, SrcDataSizeInBytes, pRootSignatureDeserializerInterface, ppRootSignatureDeserializer);
    return result;
}

HRESULT WINAPI D3D12EnableExperimentalFeatures(
        UINT                               NumFeatures,
        _In_count_(NumFeatures) const IID *pIIDs,
        _In_opt_count_(NumFeatures) void  *pConfigurationStructs,
        _In_opt_count_(NumFeatures) UINT  *pConfigurationStructSizes)
{
    HRESULT result = gfxshim::D3D12HookManager::GetInstance().D3D12EnableExperimentalFeatures(NumFeatures, pIIDs, pConfigurationStructs, pConfigurationStructSizes);
    return result;
}

BOOL WINAPI DllMain(HINSTANCE hinst_dll, DWORD fdw_reason, LPVOID lpv_reserved)
{
    return TRUE;
}







