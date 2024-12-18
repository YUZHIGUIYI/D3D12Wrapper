//
// Created by ZZK on 2024/11/11.
//

#include <gfxshim/common/dll_manager.h>
#include <gfxshim/common/dxgi_dispatch_table.h>

constexpr std::string_view s_tracer_dll_path = "d3d12_tracer.dll";
constexpr std::string_view s_system_dll_path = "C:\\Windows\\System32\\dxgi.dll";
constexpr std::string_view s_dll_initialize_func_name = "InjectDXGITracer";
constexpr std::string_view s_dll_release_func_name = "ReleaseDXGITracer";

static gfxshim::DLLManager<gfxshim::DXGIDispatchTable> s_dxgi_dll_manager{};

static void InitializeDLLManager()
{
	using namespace gfxshim;
	static std::once_flag initialize_once_flag{};
	std::call_once(initialize_once_flag, [] {
		s_dxgi_dll_manager.Initialize(s_system_dll_path, s_tracer_dll_path, s_dll_initialize_func_name, [] (LibraryHandle system_dll, DXGIDispatchTable *dxgi_dispatch_table) {
			if (system_dll != nullptr && dxgi_dispatch_table != nullptr)
			{
				dxgi_dispatch_table->DXGICreateFactory = reinterpret_cast<DXGIDispatchTable::PFN_DXGI_CREATE_FACTORY>(GetProcAddress(system_dll, "CreateDXGIFactory"));
				dxgi_dispatch_table->DXGICreateFactory1 = reinterpret_cast<DXGIDispatchTable::PFN_DXGI_CREATE_FACTORY1>(GetProcAddress(system_dll, "CreateDXGIFactory1"));
				dxgi_dispatch_table->DXGICreateFactory2 = reinterpret_cast<DXGIDispatchTable::PFN_DXGI_CREATE_FACTORY2>(GetProcAddress(system_dll, "CreateDXGIFactory2"));
				dxgi_dispatch_table->DXGIGetDebugInterface1 = reinterpret_cast<DXGIDispatchTable::PFN_DXGI_GET_DEBUG_INTERFACE1>(GetProcAddress(system_dll, "DXGIGetDebugInterface1"));
				dxgi_dispatch_table->DXGIDeclareAdapterRemovalSupport = reinterpret_cast<DXGIDispatchTable::PFN_DXGI_DECLARE_ADAPTER_REMOVAL_SUPPORT>(GetProcAddress(system_dll, "DXGIDeclareAdapterRemovalSupport"));
			}
		});
	});
}

static void ReleaseDLLManager()
{
	static std::once_flag release_once_flag{};
	std::call_once(release_once_flag, [] {
		s_dxgi_dll_manager.Release(s_dll_release_func_name);
	});
}

EXTERN_C HRESULT WINAPI CreateDXGIFactory(REFIID riid, void **ppFactory)
{
	InitializeDLLManager();
	const auto result = s_dxgi_dll_manager.QueryDispatchTable().DXGICreateFactory(riid, ppFactory);
	return result;
}

EXTERN_C HRESULT WINAPI CreateDXGIFactory1(REFIID riid, void **ppFactory)
{
	InitializeDLLManager();
	const auto result = s_dxgi_dll_manager.QueryDispatchTable().DXGICreateFactory1(riid, ppFactory);
	return result;
}

EXTERN_C HRESULT WINAPI CreateDXGIFactory2(UINT Flags, REFIID riid, void **ppFactory)
{
	InitializeDLLManager();
	const auto result = s_dxgi_dll_manager.QueryDispatchTable().DXGICreateFactory2(Flags, riid, ppFactory);
	return result;
}

EXTERN_C HRESULT WINAPI DXGIDeclareAdapterRemovalSupport()
{
	InitializeDLLManager();
	const auto result = s_dxgi_dll_manager.QueryDispatchTable().DXGIDeclareAdapterRemovalSupport();
	return result;
}

EXTERN_C HRESULT WINAPI DXGIGetDebugInterface1(UINT Flags, REFIID riid, void **ppDebug)
{
	InitializeDLLManager();
	const auto result = s_dxgi_dll_manager.QueryDispatchTable().DXGIGetDebugInterface1(Flags, riid, ppDebug);
	return result;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_DETACH)
	{
		if (lpvReserved == nullptr)
		{
			ReleaseDLLManager();
		}
	}
	return TRUE;
}

