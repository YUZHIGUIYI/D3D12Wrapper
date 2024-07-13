#include "hooks.h"
#include "d3d12_device_wrap.h"
#include <libloaderapi.h>
#include <minwindef.h>

struct D3D12Hook final : LibrayHook
{
    PFN_D3D12_GET_DEBUG_INTERFACE pfn_get_debug_interface = nullptr;
    PFN_D3D12_GET_INTERFACE pfn_get_interface = nullptr;
    PFN_D3D12_CREATE_DEVICE pfn_create_device = nullptr;

    D3D12Hook() = default;
    ~D3D12Hook() final = default;
    
    void register_hooks() final
    {
        HMODULE d3d12_module = GetModuleHandleA("d3d12.dll");
        if (d3d12_module)
        {
            pfn_get_debug_interface = (PFN_D3D12_GET_DEBUG_INTERFACE)GetProcAddress(d3d12_module, "D3D12GetDebugInterface");
            pfn_get_interface = (PFN_D3D12_GET_INTERFACE)GetProcAddress(d3d12_module, "D3D12GetInterface");
            pfn_create_device = (PFN_D3D12_CREATE_DEVICE)GetProcAddress(d3d12_module, "D3D12CreateDevice");
        }
    }

    void remove_hooks() final
    {
        pfn_get_debug_interface = nullptr;
        pfn_get_interface = nullptr;
        pfn_create_device = nullptr;
    }
};

inline static D3D12Hook s_d3d12_hook{};

HRESULT WINAPI D3D12CreateDevice(
    _In_opt_ IUnknown* pAdapter,
    D3D_FEATURE_LEVEL MinimumFeatureLevel,
    _In_ REFIID riid, // Expected: ID3D12Device
    _COM_Outptr_opt_ void** ppDevice )
{
    HRESULT result = E_UNEXPECTED;
    if (s_d3d12_hook.pfn_create_device)
    {
        result = s_d3d12_hook.pfn_create_device(pAdapter, MinimumFeatureLevel, riid, ppDevice);
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

