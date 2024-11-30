//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12RootSignatureWrapper : ID3D12DeviceChildWrapper
	{
	public:
		ID3D12RootSignatureWrapper(REFIID riid, IUnknown *object);

		~ID3D12RootSignatureWrapper() override = default;
	};

	struct ID3D12RootSignatureDeserializerWrapper : IUnknownWrapper
	{
	public:
		ID3D12RootSignatureDeserializerWrapper(REFIID riid, IUnknown *object);

		~ID3D12RootSignatureDeserializerWrapper() override = default;

		virtual const D3D12_ROOT_SIGNATURE_DESC *STDMETHODCALLTYPE GetRootSignatureDesc();
	};

	struct ID3D12VersionedRootSignatureDeserializerWrapper : IUnknownWrapper
	{
	public:
		ID3D12VersionedRootSignatureDeserializerWrapper(REFIID riid, IUnknown *object);

		~ID3D12VersionedRootSignatureDeserializerWrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE GetRootSignatureDescAtVersion(D3D_ROOT_SIGNATURE_VERSION convertToVersion,
																		const D3D12_VERSIONED_ROOT_SIGNATURE_DESC** ppDesc);

		virtual const D3D12_VERSIONED_ROOT_SIGNATURE_DESC *STDMETHODCALLTYPE GetUnconvertedRootSignatureDesc();
	};
}
