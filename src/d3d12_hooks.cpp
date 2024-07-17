#include "d3d12_device_wrap.h"
#include <libloaderapi.h>
#include <minwindef.h>
#include <cassert>
#include <sstream>
#include <iostream>
#include <d3dcommon.h>

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
        freopen_s((FILE **)stdout, "CONOUT$", "w", stdout);
        d3d12_module = LoadLibraryA("C:/Windows/System32/D3D12.dll");
        if (d3d12_module)
        {
            std::cout << "Successfully initialize DLL\n";
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
            std::cout << "Failed to initialize DLL\n";
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
    assert(s_d3d12_hook->pfn_create_device && "CreateDeviceFuncPointer can not be nullptr");
    if (s_d3d12_hook->pfn_create_device)
    {
        result = s_d3d12_hook->pfn_create_device(pAdapter, MinimumFeatureLevel, riid, ppDevice);
        std::cout << "D3DCreateDevice\n";
        std::cout << "Result: " << result << '\n';
        std::cout << "Device: " << ppDevice << '\n';
    } else
    {
        return E_UNEXPECTED;
    }

    if(SUCCEEDED(result) && ppDevice)
    {
        ID3D12Device *real_device = reinterpret_cast<ID3D12Device *>(*ppDevice);

        if(riid == __uuidof(ID3D12Device1))
        {
            ID3D12Device1 *dev1 = (ID3D12Device1 *)*ppDevice;
            real_device = (ID3D12Device *)dev1;
        }
        else if(riid == __uuidof(ID3D12Device2))
        {
            ID3D12Device2 *dev2 = (ID3D12Device2 *)*ppDevice;
            real_device = (ID3D12Device *)dev2;
        }
        else if(riid == __uuidof(ID3D12Device3))
        {
            ID3D12Device3 *dev3 = (ID3D12Device3 *)*ppDevice;
            real_device = (ID3D12Device *)dev3;
        }
        else if(riid == __uuidof(ID3D12Device4))
        {
            ID3D12Device4 *dev4 = (ID3D12Device4 *)*ppDevice;
            real_device = (ID3D12Device *)dev4;
        }
        else if(riid == __uuidof(ID3D12Device5))
        {
            ID3D12Device5 *dev5 = (ID3D12Device5 *)*ppDevice;
            real_device = (ID3D12Device *)dev5;
        }
        else if(riid == __uuidof(ID3D12Device6))
        {
            ID3D12Device6 *dev6 = (ID3D12Device6 *)*ppDevice;
            real_device = (ID3D12Device *)dev6;
        }
        else if(riid == __uuidof(ID3D12Device7))
        {
            ID3D12Device7 *dev7 = (ID3D12Device7 *)*ppDevice;
            real_device = (ID3D12Device *)dev7;
        }
        else if(riid == __uuidof(ID3D12Device8))
        {
            ID3D12Device8 *dev8 = (ID3D12Device8 *)*ppDevice;
            real_device = (ID3D12Device *)dev8;
        }
        else if(riid == __uuidof(ID3D12Device9))
        {
            ID3D12Device9 *dev9 = (ID3D12Device9 *)*ppDevice;
            real_device = (ID3D12Device *)dev9;
        }
        else if(riid == __uuidof(ID3D12Device10))
        {
            ID3D12Device10 *dev10 = (ID3D12Device10 *)*ppDevice;
            real_device = (ID3D12Device *)dev10;
        }

        WrappedID3D12Device *wrap_device = WrappedID3D12Device::create(real_device);

        *ppDevice = (ID3D12Device *)wrap_device;

        if(riid == __uuidof(ID3D12Device1))
        {
            *ppDevice = (ID3D12Device1 *)wrap_device;
        }
        else if(riid == __uuidof(ID3D12Device2))
        {
            *ppDevice = (ID3D12Device2 *)wrap_device;
        }
        else if(riid == __uuidof(ID3D12Device3))
        {
            *ppDevice = (ID3D12Device3 *)wrap_device;
        }
        else if(riid == __uuidof(ID3D12Device4))
        {
            *ppDevice = (ID3D12Device4 *)wrap_device;
        }
        else if(riid == __uuidof(ID3D12Device5))
        {
            *ppDevice = (ID3D12Device5 *)wrap_device;
        }
        else if(riid == __uuidof(ID3D12Device6))
        {
            *ppDevice = (ID3D12Device6 *)wrap_device;
        }
        else if(riid == __uuidof(ID3D12Device7))
        {
            *ppDevice = (ID3D12Device7 *)wrap_device;
        }
        else if(riid == __uuidof(ID3D12Device8))
        {
            *ppDevice = (ID3D12Device8 *)wrap_device;
        }
        else if(riid == __uuidof(ID3D12Device9))
        {
            *ppDevice = (ID3D12Device9 *)wrap_device;
        }
        else if(riid == __uuidof(ID3D12Device10))
        {
            *ppDevice = (ID3D12Device10 *)wrap_device;
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
    switch (fdw_reason)
    {
        case DLL_PROCESS_DETACH:
        {
            // Only cleanup if the process is not exiting
            if (lpv_reserved == nullptr)
            {
                s_d3d12_hook.reset();
            }
            break;
        }
        default:
            break;
    }

    return TRUE;
}







