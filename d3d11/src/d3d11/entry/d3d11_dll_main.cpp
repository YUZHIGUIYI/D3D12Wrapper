//
// Created by ZZK on 2024/9/4.
//

#include <d3d11.h>
#include <windows.graphics.directx.direct3d11.interop.h>
#include <string>
#include <memory>
#include <vector>
#include <array>
#include <gfxshim/common/dll_manager.h>

constexpr std::string_view s_tracer_dll_path = "d3d11_tracer.dll";
constexpr std::string_view s_system_dll_path = "C:\\Windows\\System32\\d3d11.dll";
constexpr std::string_view s_dll_initialize_func_name = "InjectD3D11Tracer";
constexpr std::string_view s_dll_release_func_name = "ReleaseD3D11Tracer";

struct D3D11DispatchTable
{
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

    PFN_CREATE_DIRECT3D11_DEVICE_FROM_DXGI_DEVICE create_direct3d11_device_from_dxgi_device = nullptr;
    PFN_CREATE_DIRECT3D11_SURFACE_FROM_DXGI_SURFACE create_direct3d11_surface_from_dxgi_surface = nullptr;
    PFN_D3D11_CREATE_DEVICE d3d11_create_device = nullptr;
    PFN_D3D11_CREATE_DEVICE_AND_SWAP_CHAIN d3d11_create_device_and_swap_chain = nullptr;
    PFN_D3D11ON12_CREATE_DEVICE d3d11on12_create_device = nullptr;
    PFN_D3D11_CORE_CREATE_DEVICE d3d11_core_create_device = nullptr;
};

static gfxshim::DLLManager<D3D11DispatchTable> s_d3d11_dll_manager{};

static void InitializeDLLManager()
{
    using namespace gfxshim;
	static std::once_flag initialize_once_flag{};
	std::call_once(initialize_once_flag, [] {
		s_d3d11_dll_manager.Initialize(s_system_dll_path, s_tracer_dll_path, s_dll_initialize_func_name, [] (LibraryHandle system_dll, D3D11DispatchTable *d3d11_dispatch_table) {
			if (system_dll != nullptr && d3d11_dispatch_table != nullptr)
			{
                d3d11_dispatch_table->create_direct3d11_device_from_dxgi_device = reinterpret_cast<D3D11DispatchTable::PFN_CREATE_DIRECT3D11_DEVICE_FROM_DXGI_DEVICE>(GetProcAddress(system_dll, "CreateDirect3D11DeviceFromDXGIDevice"));
                d3d11_dispatch_table->create_direct3d11_surface_from_dxgi_surface = reinterpret_cast<D3D11DispatchTable::PFN_CREATE_DIRECT3D11_SURFACE_FROM_DXGI_SURFACE>(GetProcAddress(system_dll, "CreateDirect3D11SurfaceFromDXGISurface"));
                d3d11_dispatch_table->d3d11_create_device = reinterpret_cast<PFN_D3D11_CREATE_DEVICE>(GetProcAddress(system_dll, "D3D11CreateDevice"));
                d3d11_dispatch_table->d3d11_create_device_and_swap_chain = reinterpret_cast<PFN_D3D11_CREATE_DEVICE_AND_SWAP_CHAIN>(GetProcAddress(system_dll, "D3D11CreateDeviceAndSwapChain"));
                d3d11_dispatch_table->d3d11on12_create_device = reinterpret_cast<D3D11DispatchTable::PFN_D3D11ON12_CREATE_DEVICE>(GetProcAddress(system_dll, "D3D11On12CreateDevice"));
                d3d11_dispatch_table->d3d11_core_create_device = reinterpret_cast<D3D11DispatchTable::PFN_D3D11_CORE_CREATE_DEVICE>(GetProcAddress(system_dll, "D3D11CoreCreateDevice"));
            }
		});
	});
}

static void ReleaseDLLManager()
{
    static std::once_flag release_once_flag{};
	std::call_once(release_once_flag, [] {
		s_d3d11_dll_manager.Release(s_dll_release_func_name);
	});
}

STDAPI CreateDirect3D11DeviceFromDXGIDevice(
        _In_         IDXGIDevice* dxgiDevice,
        _COM_Outptr_ IInspectable** graphicsDevice)
{
    InitializeDLLManager();
    const auto result = s_d3d11_dll_manager.QueryDispatchTable().create_direct3d11_device_from_dxgi_device(dxgiDevice, graphicsDevice);
    return result;
}

STDAPI CreateDirect3D11SurfaceFromDXGISurface(
        _In_         IDXGISurface* dxgiSurface,
        _COM_Outptr_ IInspectable** graphicsSurface)
{
    InitializeDLLManager();
    const auto result = s_d3d11_dll_manager.QueryDispatchTable().create_direct3d11_surface_from_dxgi_surface(dxgiSurface, graphicsSurface);
    return result;
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
        _COM_Outptr_opt_ ID3D11DeviceContext** ppImmediateContext)
{
    InitializeDLLManager();
    const auto result = s_d3d11_dll_manager.QueryDispatchTable().d3d11_create_device(pAdapter, DriverType, Software, Flags,
                                                                pFeatureLevels, FeatureLevels, SDKVersion,
                                                                ppDevice, pFeatureLevel, ppImmediateContext);
    return result;
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
        _COM_Outptr_opt_ ID3D11DeviceContext** ppImmediateContext)
{
    InitializeDLLManager();
    const auto result = s_d3d11_dll_manager.QueryDispatchTable().d3d11_create_device_and_swap_chain(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, pSwapChainDesc,
                                    ppSwapChain, ppDevice, pFeatureLevel, ppImmediateContext);
    return result;
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
    InitializeDLLManager();
    const auto result = s_d3d11_dll_manager.QueryDispatchTable().d3d11on12_create_device(pDevice, Flags, pFeatureLevels, FeatureLevels, ppCommandQueues, NumQueues,
                                                            NodeMask, ppDevice, ppImmediateContext, pChosenFeatureLevel);
    return result;
}

HRESULT WINAPI D3D11CoreCreateDevice(
                    IDXGIFactory *pFactory,
                    IDXGIAdapter *pAdapter,
                    UINT Flags,
                    const D3D_FEATURE_LEVEL *pFeatureLevels,
                    UINT FeatureLevels,
                    ID3D11Device **ppDevice)
{
    InitializeDLLManager();
    const auto result = s_d3d11_dll_manager.QueryDispatchTable().d3d11_core_create_device(pFactory, pAdapter, Flags,
                                                                    pFeatureLevels, FeatureLevels, ppDevice);
    return result;
}

BOOL WINAPI DllMain(HINSTANCE hinst_dll, DWORD fdw_reason, LPVOID lpv_reserved)
{
    if (fdw_reason == DLL_PROCESS_DETACH)
    {
        if (lpv_reserved == nullptr)
        {
            ReleaseDLLManager();
        }
    }
    return TRUE;
}