//
// Created by ZZK on 2024/11/11.
//

#include <dxgi/core.h>

EXTERN_C HRESULT WINAPI CreateDXGIFactory(REFIID riid, void **ppFactory)
{
	return S_OK;
}

EXTERN_C HRESULT WINAPI CreateDXGIFactory1(REFIID riid, void **ppFactory)
{
	return S_OK;
}

EXTERN_C HRESULT WINAPI CreateDXGIFactory2(UINT Flags, REFIID riid, void **ppFactory)
{
	return S_OK;
}

EXTERN_C HRESULT WINAPI DXGIDeclareAdapterRemovalSupport()
{
	return S_OK;
}

EXTERN_C HRESULT WINAPI DXGIGetDebugInterface1(UINT Flags, REFIID riid, void **ppDebug)
{
	return S_OK;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	return TRUE;
}

