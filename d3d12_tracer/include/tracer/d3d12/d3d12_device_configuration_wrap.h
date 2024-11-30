//
// Created by ZZK on 2024/11/30.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12DeviceConfigurationWrapper : IUnknownWrapper
	{
	public:
		ID3D12DeviceConfigurationWrapper(REFIID riid, IUnknown *object);

		~ID3D12DeviceConfigurationWrapper() override = default;

		virtual D3D12_DEVICE_CONFIGURATION_DESC STDMETHODCALLTYPE GetDesc();

		virtual HRESULT STDMETHODCALLTYPE GetEnabledExperimentalFeatures(GUID* pGuids, UINT NumGuids);

		virtual HRESULT STDMETHODCALLTYPE SerializeVersionedRootSignature(
						const D3D12_VERSIONED_ROOT_SIGNATURE_DESC* pDesc,
						ID3DBlob** ppResult,
						ID3DBlob** ppError);

		virtual HRESULT STDMETHODCALLTYPE CreateVersionedRootSignatureDeserializer(
						const void* pBlob,
						SIZE_T Size,
						REFIID riid,
						void** ppvDeserializer);
	};
}
