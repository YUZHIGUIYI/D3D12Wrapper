//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12SDKConfigurationWrapper : IUnknownWrapper
	{
	public:
		ID3D12SDKConfigurationWrapper(REFIID riid, IUnknown *object);

		~ID3D12SDKConfigurationWrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE SetSDKVersion(UINT SDKVersion, LPCSTR SDKPath);
	};

	struct ID3D12SDKConfiguration1Wrapper : ID3D12SDKConfigurationWrapper
	{
	public:
		ID3D12SDKConfiguration1Wrapper(REFIID riid, IUnknown *object);

		~ID3D12SDKConfiguration1Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE CreateDeviceFactory(UINT SDKVersion, LPCSTR SDKPath, REFIID riid, void** ppvFactory);

		virtual void STDMETHODCALLTYPE FreeUnusedSDKs();
	};
}
