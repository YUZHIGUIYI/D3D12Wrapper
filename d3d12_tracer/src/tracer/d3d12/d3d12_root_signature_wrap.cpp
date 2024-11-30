//
// Created by ZZK on 2024/11/24.
//

#include <tracer/d3d12/d3d12_root_signature_wrap.h>

namespace gfxshim
{
	ID3D12RootSignatureWrapper::ID3D12RootSignatureWrapper(const IID &riid, IUnknown *object)
	: ID3D12DeviceChildWrapper(riid, object)
	{

	}

	ID3D12RootSignatureDeserializerWrapper::ID3D12RootSignatureDeserializerWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	const D3D12_ROOT_SIGNATURE_DESC *STDMETHODCALLTYPE ID3D12RootSignatureDeserializerWrapper::GetRootSignatureDesc()
	{
		const auto result = GetWrappedObjectAs<ID3D12RootSignatureDeserializer>()->GetRootSignatureDesc();
		return result;
	}

	ID3D12VersionedRootSignatureDeserializerWrapper::ID3D12VersionedRootSignatureDeserializerWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	const D3D12_VERSIONED_ROOT_SIGNATURE_DESC *STDMETHODCALLTYPE ID3D12VersionedRootSignatureDeserializerWrapper::GetUnconvertedRootSignatureDesc()
	{
		const auto result = GetWrappedObjectAs<ID3D12VersionedRootSignatureDeserializer>()->GetUnconvertedRootSignatureDesc();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12VersionedRootSignatureDeserializerWrapper::GetRootSignatureDescAtVersion(
								D3D_ROOT_SIGNATURE_VERSION convertToVersion, const D3D12_VERSIONED_ROOT_SIGNATURE_DESC **ppDesc)
	{
		const auto result = GetWrappedObjectAs<ID3D12VersionedRootSignatureDeserializer>()->GetRootSignatureDescAtVersion(convertToVersion, ppDesc);
		return result;
	}


}