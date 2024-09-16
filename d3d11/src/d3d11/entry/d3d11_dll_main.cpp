//
// Created by ZZK on 2024/9/4.
//

#include <d3d11.h>
#include <windows.graphics.directx.direct3d11.interop.h>
#include <string>
#include <memory>
#include <vector>

struct D3D11HookManager
{
public:
    using PFN_CREATE_DIRECT3D11_DEVICE_FROM_DXGI_DEVICE = HRESULT(WINAPI *)(_In_ IDXGIDevice*,_COM_Outptr_ IInspectable**);
    using PFN_CREATE_DIRECT3D11_SURFACE_FROM_DXGI_SURFACE = HRESULT(WINAPI *)(_In_ IDXGISurface*, _COM_Outptr_ IInspectable**);
    using PFN_D3D11ON12_CREATE_DEVICE = HRESULT(WINAPI *)( _In_ IUnknown*, UINT,
                                                            _In_reads_opt_( FeatureLevels ) CONST D3D_FEATURE_LEVEL*, UINT FeatureLevels,
                                                            _In_reads_opt_( NumQueues ) IUnknown* CONST*, UINT NumQueues,
                                                            UINT, _COM_Outptr_opt_ ID3D11Device**, _COM_Outptr_opt_ ID3D11DeviceContext**,
                                                            _Out_opt_ D3D_FEATURE_LEVEL*);
    using PFN_D3D11_CORE_CREATE_DEVICE = HRESULT(WINAPI *)(IDXGIFactory*, IDXGIAdapter*, UINT, const D3D_FEATURE_LEVEL*, UINT, ID3D11Device**);
    using PFN_D3D11_CORE_CREATE_LAYERED_DEVICE = HRESULT(WINAPI *)(const void*, DWORD, const void*, REFIID, void**);
    using PFN_D3D11_CORE_GET_LAYERED_DEVICE_SIZE = SIZE_T(WINAPI *)(const void*, DWORD);
    using PFN_D3D11_CORE_REGISTER_LAYERS = HRESULT(WINAPI *)(const void*, DWORD);
#if defined(ENABLE_D3D12_WRAPPER)
    using PFN_QUERY_REAL_DEVICE = HRESULT(*)(IUnknown *, IUnknown **);
    using PFN_QUERY_REAL_COMMAND_QUEUE = HRESULT(*)(IUnknown *, IUnknown **);
#endif

    PFN_CREATE_DIRECT3D11_DEVICE_FROM_DXGI_DEVICE create_direct3d11_device_from_dxgi_device = nullptr;
    PFN_CREATE_DIRECT3D11_SURFACE_FROM_DXGI_SURFACE create_direct3d11_surface_from_dxgi_surface = nullptr;
    PFN_D3D11_CREATE_DEVICE d3d11_create_device = nullptr;
    PFN_D3D11_CREATE_DEVICE_AND_SWAP_CHAIN d3d11_create_device_and_swap_chain = nullptr;
    PFN_D3D11ON12_CREATE_DEVICE d3d11on12_create_device = nullptr;
    PFN_D3D11_CORE_CREATE_DEVICE d3d11_core_create_device = nullptr;
    PFN_D3D11_CORE_CREATE_LAYERED_DEVICE d3d11_core_create_layered_device = nullptr;
    PFN_D3D11_CORE_GET_LAYERED_DEVICE_SIZE d3d11_core_get_layered_device_size = nullptr;
    PFN_D3D11_CORE_REGISTER_LAYERS d3d11_core_register_layers = nullptr;
#if defined(ENABLE_D3D12_WRAPPER)
    PFN_QUERY_REAL_DEVICE query_real_device = nullptr;
    PFN_QUERY_REAL_COMMAND_QUEUE query_real_command_queue = nullptr;
#endif

private:
    HMODULE d3d11_module = nullptr;
    HMODULE d3d11on12_module = nullptr;

public:
    D3D11HookManager()
    {
        LoadD3D11Module();
        LoadD3D12ExportedFunctions();
    }

    void LoadD3D11Module()
    {
        if (d3d11_module != nullptr && d3d11on12_module != nullptr)
        {
            return;
        }

        char system_directory[MAX_PATH];
        if (const uint32_t result = GetSystemDirectory(system_directory, MAX_PATH); result == 0)
        {
            return;
        }

        const std::string core_lib_directory{ system_directory };
        d3d11_module = LoadLibraryA((core_lib_directory + "\\d3d11.dll").c_str());
        d3d11on12_module = LoadLibraryA((core_lib_directory + "\\d3d11on12.dll").c_str());
        if (d3d11_module == nullptr)
        {
            return;
        }

        create_direct3d11_device_from_dxgi_device = reinterpret_cast<PFN_CREATE_DIRECT3D11_DEVICE_FROM_DXGI_DEVICE>(GetProcAddress(d3d11_module, "CreateDirect3D11DeviceFromDXGIDevice"));
        create_direct3d11_surface_from_dxgi_surface = reinterpret_cast<PFN_CREATE_DIRECT3D11_SURFACE_FROM_DXGI_SURFACE>(GetProcAddress(d3d11_module, "CreateDirect3D11SurfaceFromDXGISurface"));
        d3d11_create_device = reinterpret_cast<PFN_D3D11_CREATE_DEVICE>(GetProcAddress(d3d11_module, "D3D11CreateDevice"));
        d3d11_create_device_and_swap_chain = reinterpret_cast<PFN_D3D11_CREATE_DEVICE_AND_SWAP_CHAIN>(GetProcAddress(d3d11_module, "D3D11CreateDeviceAndSwapChain"));
        d3d11on12_create_device = reinterpret_cast<PFN_D3D11ON12_CREATE_DEVICE>(GetProcAddress(d3d11_module, "D3D11On12CreateDevice"));
        d3d11_core_create_device = reinterpret_cast<PFN_D3D11_CORE_CREATE_DEVICE>(GetProcAddress(d3d11_module, "D3D11CoreCreateDevice"));
        d3d11_core_create_layered_device = reinterpret_cast<PFN_D3D11_CORE_CREATE_LAYERED_DEVICE>(GetProcAddress(d3d11_module, "D3D11CoreCreateLayeredDevice"));
        d3d11_core_get_layered_device_size = reinterpret_cast<PFN_D3D11_CORE_GET_LAYERED_DEVICE_SIZE>(GetProcAddress(d3d11_module, "D3D11CoreGetLayeredDeviceSize"));
        d3d11_core_register_layers = reinterpret_cast<PFN_D3D11_CORE_REGISTER_LAYERS>(GetProcAddress(d3d11_module, "D3D11CoreRegisterLayers"));
    }

    void LoadD3D12ExportedFunctions()
    {
#if defined(ENABLE_D3D12_WRAPPER)
        if (query_real_device != nullptr && query_real_command_queue != nullptr)
        {
            return;
        }
        if (const auto d3d12_module = LoadLibraryA("d3d12.dll"); d3d12_module != nullptr)
        {
            query_real_device = reinterpret_cast<PFN_QUERY_REAL_DEVICE>(GetProcAddress(d3d12_module, "QueryRealDevice"));
            query_real_command_queue = reinterpret_cast<PFN_QUERY_REAL_COMMAND_QUEUE>(GetProcAddress(d3d12_module, "QueryRealCommandQueue"));
        }
#endif
    }

    void LoadD3D11On12Module()
    {
        if (d3d11on12_module == nullptr)
        {
            char system_directory[MAX_PATH];
            if (const uint32_t result = GetSystemDirectory(system_directory, MAX_PATH); result == 0)
            {
                return;
            }

            const std::string core_lib_directory{ system_directory };
            d3d11on12_module = LoadLibraryA((core_lib_directory + "\\d3d11on12.dll").c_str());
        }
    }

    ~D3D11HookManager()
    {
        if (d3d11_module)
        {
            FreeLibrary(d3d11_module);
            d3d11_module = nullptr;
            create_direct3d11_device_from_dxgi_device = nullptr;
            create_direct3d11_surface_from_dxgi_surface = nullptr;
            d3d11_create_device = nullptr;
            d3d11_create_device_and_swap_chain = nullptr;
            d3d11on12_create_device = nullptr;
        }
        if (d3d11on12_module)
        {
            FreeLibrary(d3d11on12_module);
            d3d11on12_module = nullptr;
        }
    }
};

auto s_d3d11_hook = std::make_unique<D3D11HookManager>();

STDAPI CreateDirect3D11DeviceFromDXGIDevice(
        _In_         IDXGIDevice* dxgiDevice,
        _COM_Outptr_ IInspectable** graphicsDevice)
{
    if (s_d3d11_hook->create_direct3d11_device_from_dxgi_device)
    {
        const auto result = s_d3d11_hook->create_direct3d11_device_from_dxgi_device(dxgiDevice, graphicsDevice);
        return result;
    }
    return E_UNEXPECTED;
}

STDAPI CreateDirect3D11SurfaceFromDXGISurface(
        _In_         IDXGISurface* dgxiSurface,
        _COM_Outptr_ IInspectable** graphicsSurface)
{
    if (s_d3d11_hook->create_direct3d11_surface_from_dxgi_surface)
    {
        const auto result = s_d3d11_hook->create_direct3d11_surface_from_dxgi_surface(dgxiSurface, graphicsSurface);
        return result;
    }
    return E_UNEXPECTED;
}

HRESULT WINAPI D3D11CreateDevice(
        _In_opt_ IDXGIAdapter* pAdapter,
        D3D_DRIVER_TYPE DriverType,
        HMODULE Software,
        UINT Flags,
        _In_reads_opt_( FeatureLevels ) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
        UINT FeatureLevels,
        UINT SDKVersion,
        _COM_Outptr_opt_ ID3D11Device** ppDevice,
        _Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
        _COM_Outptr_opt_ ID3D11DeviceContext** ppImmediateContext )
{
    if (s_d3d11_hook->d3d11_create_device)
    {
        const auto result = s_d3d11_hook->d3d11_create_device(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion,
                                    ppDevice, pFeatureLevel, ppImmediateContext);
        return result;
    }
    return E_UNEXPECTED;
}

HRESULT WINAPI D3D11CreateDeviceAndSwapChain(
        _In_opt_ IDXGIAdapter* pAdapter,
        D3D_DRIVER_TYPE DriverType,
        HMODULE Software,
        UINT Flags,
        _In_reads_opt_( FeatureLevels ) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
        UINT FeatureLevels,
        UINT SDKVersion,
        _In_opt_ CONST DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
        _COM_Outptr_opt_ IDXGISwapChain** ppSwapChain,
        _COM_Outptr_opt_ ID3D11Device** ppDevice,
        _Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
        _COM_Outptr_opt_ ID3D11DeviceContext** ppImmediateContext )
{
    if (s_d3d11_hook->d3d11_create_device_and_swap_chain)
    {
        const auto result = s_d3d11_hook->d3d11_create_device_and_swap_chain(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, pSwapChainDesc,
                                    ppSwapChain, ppDevice, pFeatureLevel, ppImmediateContext);
        return result;
    }
    return E_UNEXPECTED;
}

HRESULT WINAPI D3D11On12CreateDevice(
        _In_ IUnknown* pDevice,
        UINT Flags,
        _In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
        UINT FeatureLevels,
        _In_reads_opt_(NumQueues) IUnknown* CONST* ppCommandQueues,
        UINT NumQueues,
        UINT NodeMask,
        _COM_Outptr_opt_ ID3D11Device** ppDevice,
        _COM_Outptr_opt_ ID3D11DeviceContext** ppImmediateContext,
        _Out_opt_ D3D_FEATURE_LEVEL* pChosenFeatureLevel)
{
    if (s_d3d11_hook->d3d11on12_create_device)
    {
#if defined(ENABLE_D3D12_WRAPPER)
        if (pDevice != nullptr && ppCommandQueues != nullptr)
        {
            s_d3d11_hook->LoadD3D11On12Module();
            IUnknown *real_device = nullptr;
            std::vector<IUnknown *> real_queues{};
            if (s_d3d11_hook->query_real_device != nullptr)
            {
                if (const auto result = s_d3d11_hook->query_real_device(pDevice, &real_device); FAILED(result)) return result;
            }
            if (s_d3d11_hook->query_real_command_queue != nullptr)
            {
                for (uint32_t i = 0; i < NumQueues; ++i)
                {
                    IUnknown *real_command_queue = nullptr;
                    if (const auto result = s_d3d11_hook->query_real_command_queue(ppCommandQueues[i], &real_command_queue); FAILED(result)) return result;
                    real_queues.emplace_back(real_command_queue);
                }
            }
            const auto result = s_d3d11_hook->d3d11on12_create_device(real_device, Flags, pFeatureLevels, FeatureLevels, real_queues.data(), real_queues.size(), NodeMask, ppDevice,
                                        ppImmediateContext, pChosenFeatureLevel);
            return result;
        }
#endif
        {
            const auto result = s_d3d11_hook->d3d11on12_create_device(pDevice, Flags, pFeatureLevels, FeatureLevels, ppCommandQueues, NumQueues, NodeMask, ppDevice,
                                        ppImmediateContext, pChosenFeatureLevel);
            return result;
        }
    }
    return E_UNEXPECTED;
}

HRESULT WINAPI D3D11CoreCreateDevice(
                    IDXGIFactory *pFactory,
                    IDXGIAdapter *pAdapter,
                    UINT Flags,
                    const D3D_FEATURE_LEVEL *pFeatureLevels,
                    UINT FeatureLevels,
                    ID3D11Device **ppDevice)
{
    if (s_d3d11_hook->d3d11_core_create_device)
    {
        const auto result = s_d3d11_hook->d3d11_core_create_device(pFactory, pAdapter, Flags, pFeatureLevels,
                                    FeatureLevels, ppDevice);
        return result;
    }
    return E_UNEXPECTED;
}

HRESULT WINAPI D3D11CoreCreateLayeredDevice(
                    const void *unknown0,
                    DWORD unknown1,
                    const void *unknown2,
                    REFIID riid,
                    void **ppvObj)
{
    if (s_d3d11_hook->d3d11_core_create_layered_device)
    {
        const auto result = s_d3d11_hook->d3d11_core_create_layered_device(unknown0, unknown1, unknown2, riid, ppvObj);
        return result;
    }
    return E_UNEXPECTED;
}

SIZE_T WINAPI D3D11CoreGetLayeredDeviceSize(const void* unknown0, DWORD unknown1)
{
    if (s_d3d11_hook->d3d11_core_get_layered_device_size)
    {
        const auto result = s_d3d11_hook->d3d11_core_get_layered_device_size(unknown0, unknown1);
        return result;
    }
    return 0;
}

HRESULT WINAPI D3D11CoreRegisterLayers(const void* unknown0, DWORD unknown1)
{
    if (s_d3d11_hook->d3d11_core_register_layers)
    {
        const auto result = s_d3d11_hook->d3d11_core_register_layers(unknown0, unknown1);
        return result;
    }
    return E_UNEXPECTED;
}

BOOL WINAPI DllMain(HINSTANCE hinst_dll, DWORD fdw_reason, LPVOID lpv_reserved)
{
    return TRUE;
}