//
// Created by ZZK on 2024/11/11.
//

#include <d3d12.h>
#include <dxgi.h>
#include <dxgi1_3.h>
#include <dxgi1_6.h>
#include <Windows.h>

EXTERN_C bool WINAPI InitializeD3D12Tracer()
{
	return true;
}

EXTERN_C bool WINAPI InitializeDXGITracer()
{
	return true;
}

EXTERN_C void WINAPI ReleaseD3D12Tracer()
{

}

EXTERN_C void WINAPI ReleaseDXGITracer()
{

}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	return TRUE;
}