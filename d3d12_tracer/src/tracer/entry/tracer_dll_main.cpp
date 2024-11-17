//
// Created by ZZK on 2024/11/14.
//

#include <tracer/hooks/d3d12_hook_manager.h>

EXTERN_C bool WINAPI InjectD3D12Tracer(gfxshim::D3D12DispatchTable *in_d3d12_dispatch_table)
{
	gfxshim::D3D12HookManager::GetInstance().InitializeD3D12DispatchTable(*in_d3d12_dispatch_table);
	in_d3d12_dispatch_table->D3D12CreateDevice = gfxshim::D3D12HookManager::D3D12CreateDevice;
	in_d3d12_dispatch_table->D3D12GetInterface = gfxshim::D3D12HookManager::D3D12GetInterface;
	in_d3d12_dispatch_table->D3D12EnableExperimentalFeatures = gfxshim::D3D12HookManager::D3D12EnableExperimentalFeatures;
	in_d3d12_dispatch_table->D3D12GetDebugInterface = gfxshim::D3D12HookManager::D3D12GetDebugInterface;
	in_d3d12_dispatch_table->D3D12SerializeRootSignature = gfxshim::D3D12HookManager::D3D12SerializeRootSignature;
	in_d3d12_dispatch_table->D3D12CreateRootSignatureDeserializer = gfxshim::D3D12HookManager::D3D12CreateRootSignatureDeserializer;
	in_d3d12_dispatch_table->D3D12SerializeVersionedRootSignature = gfxshim::D3D12HookManager::D3D12SerializeVersionedRootSignature;
	in_d3d12_dispatch_table->D3D12CreateVersionedRootSignatureDeserializer = gfxshim::D3D12HookManager::D3D12CreateVersionedRootSignatureDeserializer;

	return true;
}

EXTERN_C bool WINAPI InjectDXGITracer(gfxshim::DXGIDispatchTable *in_dxgi_dispatch_table)
{
	gfxshim::D3D12HookManager::GetInstance().InitializeDXGIDispatchTable(*in_dxgi_dispatch_table);
	in_dxgi_dispatch_table->DXGICreateFactory = gfxshim::D3D12HookManager::CreateDXGIFactory;
	in_dxgi_dispatch_table->DXGICreateFactory1 = gfxshim::D3D12HookManager::CreateDXGIFactory1;
	in_dxgi_dispatch_table->DXGICreateFactory2 = gfxshim::D3D12HookManager::CreateDXGIFactory2;
	in_dxgi_dispatch_table->DXGIGetDebugInterface1 = gfxshim::D3D12HookManager::DXGIGetDebugInterface1;
	in_dxgi_dispatch_table->DXGIDeclareAdapterRemovalSupport = gfxshim::D3D12HookManager::DXGIDeclareAdapterRemovalSupport;

	return true;
}

EXTERN_C void WINAPI ReleaseD3D12Tracer(gfxshim::D3D12DispatchTable *in_d3d12_dispatch_table)
{
	// TODO: implement
}

EXTERN_C void WINAPI ReleaseDXGITracer(gfxshim::DXGIDispatchTable *in_dxgi_dispatch_table)
{
	// TODO: implement
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	return TRUE;
}