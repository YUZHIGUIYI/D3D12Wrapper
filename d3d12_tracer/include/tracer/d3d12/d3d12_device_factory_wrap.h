//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12DeviceFactoryWrapper : IUnknownWrapper
	{
	public:
		ID3D12DeviceFactoryWrapper(REFIID riid, IUnknown *object);

		~ID3D12DeviceFactoryWrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE InitializeFromGlobalState();

		virtual HRESULT STDMETHODCALLTYPE ApplyToGlobalState();

		virtual HRESULT STDMETHODCALLTYPE SetFlags(D3D12_DEVICE_FACTORY_FLAGS flags);

		virtual D3D12_DEVICE_FACTORY_FLAGS STDMETHODCALLTYPE GetFlags();

		virtual HRESULT STDMETHODCALLTYPE GetConfigurationInterface(REFCLSID clsid, REFIID iid, void** ppv);

		virtual HRESULT STDMETHODCALLTYPE EnableExperimentalFeatures(
											UINT NumFeatures,
											const IID* pIIDs,
											void* pConfigurationStructs,
											UINT* pConfigurationStructSizes);

		virtual HRESULT STDMETHODCALLTYPE CreateDevice(
											IUnknown* adapter,
											D3D_FEATURE_LEVEL FeatureLevel,
											REFIID riid,
											void** ppvDevice);
	};
}
