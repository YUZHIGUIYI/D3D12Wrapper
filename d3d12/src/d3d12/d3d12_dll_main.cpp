//
// Created by ZZK on 2024/11/16.
//

#include <gfxshim/common/dll_manager.h>
#include <gfxshim/common/d3d12_dispatch_table.h>

constexpr std::string_view s_tracer_dll_path = "d3d12_tracer.dll";
constexpr std::string_view s_system_dll_path = "C:/Windows/System32/d3d12.dll";
constexpr std::string_view s_dll_initialize_func_name = "InjectD3D12Tracer";
constexpr std::string_view s_dll_release_func_name = "ReleaseD3D12Tracer";

static gfxshim::DLLManager<gfxshim::D3D12DispatchTable> s_d3d12_dll_manager{};

static void InitializeDLLManager()
{
	using namespace gfxshim;
	static std::once_flag initialize_once_flag{};
	std::call_once(initialize_once_flag, [] {
		s_d3d12_dll_manager.Initialize(s_system_dll_path, s_tracer_dll_path, s_dll_initialize_func_name, [] (LibraryHandle system_dll, D3D12DispatchTable *d3d12_dispatch_table) {
			if (system_dll != nullptr && d3d12_dispatch_table != nullptr)
			{
				d3d12_dispatch_table->D3D12CreateDevice = reinterpret_cast<PFN_D3D12_CREATE_DEVICE>(GetProcAddress(system_dll, "D3D12CreateDevice"));
				d3d12_dispatch_table->D3D12GetInterface = reinterpret_cast<PFN_D3D12_GET_INTERFACE>(GetProcAddress(system_dll, "D3D12GetInterface"));
				d3d12_dispatch_table->D3D12GetDebugInterface = reinterpret_cast<PFN_D3D12_GET_DEBUG_INTERFACE>(GetProcAddress(system_dll, "D3D12GetDebugInterface"));
				d3d12_dispatch_table->D3D12SerializeRootSignature = reinterpret_cast<PFN_D3D12_SERIALIZE_ROOT_SIGNATURE>(GetProcAddress(system_dll, "D3D12SerializeRootSignature"));
				d3d12_dispatch_table->D3D12SerializeVersionedRootSignature = reinterpret_cast<PFN_D3D12_SERIALIZE_VERSIONED_ROOT_SIGNATURE>(GetProcAddress(system_dll, "D3D12SerializeVersionedRootSignature"));
				d3d12_dispatch_table->D3D12CreateRootSignatureDeserializer = reinterpret_cast<PFN_D3D12_CREATE_ROOT_SIGNATURE_DESERIALIZER>(GetProcAddress(system_dll, "D3D12CreateRootSignatureDeserializer"));
				d3d12_dispatch_table->D3D12CreateVersionedRootSignatureDeserializer = reinterpret_cast<PFN_D3D12_CREATE_VERSIONED_ROOT_SIGNATURE_DESERIALIZER>(GetProcAddress(system_dll, "D3D12CreateVersionedRootSignatureDeserializer"));
				d3d12_dispatch_table->D3D12EnableExperimentalFeatures = reinterpret_cast<D3D12DispatchTable::PFN_D3D12_ENABLE_EXPERIMENTAL_FEATURES>(GetProcAddress(system_dll, "D3D12EnableExperimentalFeatures"));
			}
		});
	});
}

static void ReleaseDLLManager()
{
	static std::once_flag release_once_flag{};
	std::call_once(release_once_flag, [] {
		s_d3d12_dll_manager.Release(s_dll_release_func_name);
	});
}

HRESULT WINAPI D3D12GetDebugInterface(_In_ REFIID riid, _COM_Outptr_opt_ void **ppvDebug)
{
	InitializeDLLManager();
    const HRESULT result = s_d3d12_dll_manager.QueryDispatchTable().D3D12GetDebugInterface(riid, ppvDebug);
    return result;
}

HRESULT WINAPI D3D12GetInterface(_In_ REFCLSID rclsid, _In_ REFIID riid, _COM_Outptr_opt_ void **ppvDebug )
{
	InitializeDLLManager();
    const HRESULT result = s_d3d12_dll_manager.QueryDispatchTable().D3D12GetInterface(rclsid, riid, ppvDebug);
    return result;
}

HRESULT WINAPI D3D12CreateDevice(
    _In_opt_ IUnknown *pAdapter,
    D3D_FEATURE_LEVEL MinimumFeatureLevel,
    _In_ REFIID riid,
    _COM_Outptr_opt_ void **ppDevice)
{
	InitializeDLLManager();
    const HRESULT result = s_d3d12_dll_manager.QueryDispatchTable().D3D12CreateDevice(pAdapter, MinimumFeatureLevel, riid, ppDevice);
	return result;
}

HRESULT WINAPI D3D12SerializeRootSignature(
        _In_ const D3D12_ROOT_SIGNATURE_DESC *pRootSignature,
        _In_ D3D_ROOT_SIGNATURE_VERSION Version,
        _Out_ ID3DBlob **ppBlob,
        _Always_(_Outptr_opt_result_maybenull_) ID3DBlob **ppErrorBlob)
{
	InitializeDLLManager();
    const HRESULT result = s_d3d12_dll_manager.QueryDispatchTable().D3D12SerializeRootSignature(pRootSignature, Version, ppBlob, ppErrorBlob);
    return result;
}

HRESULT WINAPI D3D12SerializeVersionedRootSignature(
        _In_ const D3D12_VERSIONED_ROOT_SIGNATURE_DESC *pRootSignature,
        _Out_ ID3DBlob **ppBlob,
        _Always_(_Outptr_opt_result_maybenull_) ID3DBlob **ppErrorBlob)
{
	InitializeDLLManager();
    const HRESULT result = s_d3d12_dll_manager.QueryDispatchTable().D3D12SerializeVersionedRootSignature(pRootSignature, ppBlob, ppErrorBlob);
    return result;
}

HRESULT WINAPI D3D12CreateRootSignatureDeserializer(
        _In_reads_bytes_(SrcDataSizeInBytes) LPCVOID pSrcData,
        _In_ SIZE_T SrcDataSizeInBytes,
        _In_ REFIID pRootSignatureDeserializerInterface,
        _Out_ void **ppRootSignatureDeserializer)
{
	InitializeDLLManager();
    const HRESULT result = s_d3d12_dll_manager.QueryDispatchTable().D3D12CreateRootSignatureDeserializer(pSrcData, SrcDataSizeInBytes, pRootSignatureDeserializerInterface, ppRootSignatureDeserializer);
    return result;
}

HRESULT WINAPI D3D12CreateVersionedRootSignatureDeserializer(
        _In_reads_bytes_(SrcDataSizeInBytes) LPCVOID pSrcData,
        _In_ SIZE_T SrcDataSizeInBytes,
        _In_ REFIID pRootSignatureDeserializerInterface,
        _Out_ void **ppRootSignatureDeserializer)
{
	InitializeDLLManager();
    const HRESULT result = s_d3d12_dll_manager.QueryDispatchTable().D3D12CreateVersionedRootSignatureDeserializer(pSrcData, SrcDataSizeInBytes, pRootSignatureDeserializerInterface, ppRootSignatureDeserializer);
    return result;
}

HRESULT WINAPI D3D12EnableExperimentalFeatures(
        UINT                               NumFeatures,
        _In_count_(NumFeatures) const IID *pIIDs,
        _In_opt_count_(NumFeatures) void  *pConfigurationStructs,
        _In_opt_count_(NumFeatures) UINT  *pConfigurationStructSizes)
{
	InitializeDLLManager();
    const HRESULT result = s_d3d12_dll_manager.QueryDispatchTable().D3D12EnableExperimentalFeatures(NumFeatures, pIIDs, pConfigurationStructs, pConfigurationStructSizes);
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