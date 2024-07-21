#include <d3d12/core/d3d12_device_wrap.h>
#include <libloaderapi.h>

struct D3D12Hook
{
    using PFN_D3D12_ENABLE_EXPERIMENTAL_FEATURES = HRESULT(WINAPI *)(
            UINT                                   NumFeatures,
            _In_count_(NumFeatures) const IID*     pIIDs,
            _In_opt_count_(NumFeatures) void*      pConfigurationStructs,
            _In_opt_count_(NumFeatures) UINT*      pConfigurationStructSizes);

    PFN_D3D12_GET_DEBUG_INTERFACE pfn_get_debug_interface = nullptr;
    PFN_D3D12_GET_INTERFACE pfn_get_interface = nullptr;

    PFN_D3D12_CREATE_DEVICE pfn_create_device = nullptr;

    PFN_D3D12_SERIALIZE_ROOT_SIGNATURE pfn_serialize_root_signature = nullptr;
    PFN_D3D12_SERIALIZE_VERSIONED_ROOT_SIGNATURE pfn_serialize_versioned_root_signature = nullptr;

    PFN_D3D12_CREATE_ROOT_SIGNATURE_DESERIALIZER pfn_create_root_signature_deserializer = nullptr;
    PFN_D3D12_CREATE_VERSIONED_ROOT_SIGNATURE_DESERIALIZER pfn_create_versioned_root_signature_deserializer = nullptr;

    PFN_D3D12_ENABLE_EXPERIMENTAL_FEATURES pfn_enable_experimental_features = nullptr;

    HMODULE d3d12_module = nullptr;

    D3D12Hook()
    {
        AllocConsole();
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);  // Debug only
        d3d12_module = LoadLibraryA("C:/Windows/System32/D3D12.dll");
        if (d3d12_module)
        {
            D3D12_WRAPPER_DEBUG("Successfully initialize D3D12 hook.");
            pfn_get_debug_interface = (PFN_D3D12_GET_DEBUG_INTERFACE)GetProcAddress(d3d12_module, "D3D12GetDebugInterface");
            pfn_get_interface = (PFN_D3D12_GET_INTERFACE)GetProcAddress(d3d12_module, "D3D12GetInterface");
            pfn_create_device = (PFN_D3D12_CREATE_DEVICE)GetProcAddress(d3d12_module, "D3D12CreateDevice");
            pfn_serialize_root_signature = (PFN_D3D12_SERIALIZE_ROOT_SIGNATURE)GetProcAddress(d3d12_module, "D3D12SerializeRootSignature");
            pfn_serialize_versioned_root_signature = (PFN_D3D12_SERIALIZE_VERSIONED_ROOT_SIGNATURE)GetProcAddress(d3d12_module, "D3D12SerializeVersionedRootSignature");
            pfn_create_root_signature_deserializer = (PFN_D3D12_CREATE_ROOT_SIGNATURE_DESERIALIZER)GetProcAddress(d3d12_module, "D3D12CreateRootSignatureDeserializer");
            pfn_create_versioned_root_signature_deserializer = (PFN_D3D12_CREATE_VERSIONED_ROOT_SIGNATURE_DESERIALIZER)GetProcAddress(d3d12_module,
                                                                                                "D3D12CreateVersionedRootSignatureDeserializer");
            pfn_enable_experimental_features = (PFN_D3D12_ENABLE_EXPERIMENTAL_FEATURES)GetProcAddress(d3d12_module, "D3D12EnableExperimentalFeatures");
        } else
        {
            D3D12_WRAPPER_ERROR("Failed to initialize D3D12 hook.");
        }
    }

    ~D3D12Hook()
    {
        if (d3d12_module)
        {
            FreeLibrary(d3d12_module);
            remove_hooks();
        }
    }

    void remove_hooks()
    {
        pfn_get_debug_interface = nullptr;
        pfn_get_interface = nullptr;
        pfn_create_device = nullptr;
        pfn_serialize_root_signature = nullptr;
        pfn_serialize_versioned_root_signature = nullptr;
        pfn_create_root_signature_deserializer = nullptr;
        pfn_create_versioned_root_signature_deserializer = nullptr;

        pfn_enable_experimental_features = nullptr;
    }
};

std::unique_ptr<D3D12Hook> s_d3d12_hook = std::make_unique<D3D12Hook>();

HRESULT WINAPI D3D12GetDebugInterface( _In_ REFIID riid, _COM_Outptr_opt_ void** ppvDebug )
{
    HRESULT result = E_UNEXPECTED;
    if (s_d3d12_hook->pfn_get_debug_interface)
    {
        return s_d3d12_hook->pfn_get_debug_interface(riid, ppvDebug);
    }
    return result;
}

HRESULT WINAPI D3D12GetInterface( _In_ REFCLSID rclsid, _In_ REFIID riid, _COM_Outptr_opt_ void** ppvDebug )
{
    HRESULT result = E_UNEXPECTED;
    if (s_d3d12_hook->pfn_get_interface)
    {
        return s_d3d12_hook->pfn_get_interface(rclsid, riid, ppvDebug);
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
    if (s_d3d12_hook->pfn_create_device)
    {
        result = s_d3d12_hook->pfn_create_device(pAdapter, MinimumFeatureLevel, riid, ppDevice);
        D3D12_WRAPPER_DEBUG("Call D3DCreateDevice.");
        if (ppDevice != nullptr && (*ppDevice != nullptr))
        {
            D3D12_WRAPPER_DEBUG("Real device pointer: {}.", *ppDevice);
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
            D3D12_WRAPPER_DEBUG("Fake device pointer: {}.", reinterpret_cast<void *>(wrapped_device));
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
    if (s_d3d12_hook->pfn_serialize_root_signature)
    {
        return s_d3d12_hook->pfn_serialize_root_signature(pRootSignature, Version, ppBlob, ppErrorBlob);
    }
    return result;
}

HRESULT WINAPI D3D12SerializeVersionedRootSignature(
        _In_ const D3D12_VERSIONED_ROOT_SIGNATURE_DESC* pRootSignature,
        _Out_ ID3DBlob** ppBlob,
        _Always_(_Outptr_opt_result_maybenull_) ID3DBlob** ppErrorBlob)
{
    HRESULT result = E_UNEXPECTED;
    if (s_d3d12_hook->pfn_serialize_versioned_root_signature)
    {
        return s_d3d12_hook->pfn_serialize_versioned_root_signature(pRootSignature, ppBlob, ppErrorBlob);
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
    if (s_d3d12_hook->pfn_create_root_signature_deserializer)
    {
        return s_d3d12_hook->pfn_create_root_signature_deserializer(pSrcData, SrcDataSizeInBytes, pRootSignatureDeserializerInterface, ppRootSignatureDeserializer);
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
    if (s_d3d12_hook->pfn_create_versioned_root_signature_deserializer)
    {
        return s_d3d12_hook->pfn_create_versioned_root_signature_deserializer(pSrcData, SrcDataSizeInBytes, pRootSignatureDeserializerInterface, ppRootSignatureDeserializer);
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
    if (s_d3d12_hook->pfn_enable_experimental_features)
    {
        return s_d3d12_hook->pfn_enable_experimental_features(NumFeatures, pIIDs, pConfigurationStructs, pConfigurationStructSizes);
    }
    return result;
}

BOOL WINAPI DllMain(HINSTANCE hinst_dll, DWORD fdw_reason, LPVOID lpv_reserved)
{
    if (fdw_reason == DLL_PROCESS_DETACH)
    {
        // Only cleanup if the process is not exiting
        if (lpv_reserved == nullptr)
        {
            s_d3d12_hook.reset();
        }
    }

    return TRUE;
}







