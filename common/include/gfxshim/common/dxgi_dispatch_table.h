//
// Created by ZZK on 2024/11/16.
//

#pragma once

#include <gfxshim/common/base.h>

namespace gfxshim
{
	struct DXGIDispatchTable
	{
		// Note: There is no typedef in dxgi.h for the following functions.
		using PFN_DXGI_CREATE_FACTORY                  = HRESULT(WINAPI *)(REFIID, void **);
		using PFN_DXGI_CREATE_FACTORY1                 = HRESULT(WINAPI *)(REFIID, void **);
		using PFN_DXGI_CREATE_FACTORY2                 = HRESULT(WINAPI *)(UINT, REFIID, void **);
		using PFN_DXGI_DECLARE_ADAPTER_REMOVAL_SUPPORT = HRESULT(WINAPI *)();
		using PFN_DXGI_GET_DEBUG_INTERFACE1            = HRESULT(WINAPI *)(UINT, REFIID, void **);
		// Functions processed for capture. These are the DXGI functions exported by dxgi.dll and documented on MSDN.
		PFN_DXGI_CREATE_FACTORY  DXGICreateFactory  = nullptr;
		PFN_DXGI_CREATE_FACTORY1 DXGICreateFactory1 = nullptr;
		PFN_DXGI_CREATE_FACTORY2 DXGICreateFactory2 = nullptr;
		PFN_DXGI_DECLARE_ADAPTER_REMOVAL_SUPPORT DXGIDeclareAdapterRemovalSupport = nullptr;
		PFN_DXGI_GET_DEBUG_INTERFACE1 DXGIGetDebugInterface1 = nullptr;
	};
}
