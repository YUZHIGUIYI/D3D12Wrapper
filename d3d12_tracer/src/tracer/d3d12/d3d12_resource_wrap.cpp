//
// Created by ZZK on 2024/11/24.
//

#include <tracer/d3d12/d3d12_resource_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	// Wrap ID3D12Resource
	ID3D12ResourceWrapper::ID3D12ResourceWrapper(const IID &riid, IUnknown *object)
	: ID3D12PageableWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE ID3D12ResourceWrapper::Map(UINT Subresource, const D3D12_RANGE *pReadRange, void **ppData)
	{
		// TODO: map trace
		const auto result = GetWrappedObjectAs<ID3D12Resource>()->Map(Subresource, pReadRange, ppData);
		return result;
	}

	void STDMETHODCALLTYPE ID3D12ResourceWrapper::Unmap(UINT Subresource, const D3D12_RANGE *pWrittenRange)
	{
		// TODO: unmap trace
		GetWrappedObjectAs<ID3D12Resource>()->Unmap(Subresource, pWrittenRange);
	}

	D3D12_RESOURCE_DESC STDMETHODCALLTYPE ID3D12ResourceWrapper::GetDesc()
	{
		const auto result = GetWrappedObjectAs<ID3D12Resource>()->GetDesc();
		return result;
	}

	D3D12_GPU_VIRTUAL_ADDRESS STDMETHODCALLTYPE ID3D12ResourceWrapper::GetGPUVirtualAddress()
	{
		const auto result = GetWrappedObjectAs<ID3D12Resource>()->GetGPUVirtualAddress();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12ResourceWrapper::WriteToSubresource(UINT DstSubresource, const D3D12_BOX *pDstBox,
																		const void *pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch)
	{
		const auto result = GetWrappedObjectAs<ID3D12Resource>()->WriteToSubresource(DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12ResourceWrapper::ReadFromSubresource(void *pDstData, UINT DstRowPitch, UINT DstDepthPitch,
																		UINT SrcSubresource, const D3D12_BOX *pSrcBox)
	{
		const auto result = GetWrappedObjectAs<ID3D12Resource>()->ReadFromSubresource(pDstData, DstRowPitch, DstDepthPitch, SrcSubresource, pSrcBox);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12ResourceWrapper::GetHeapProperties(D3D12_HEAP_PROPERTIES *pHeapProperties,
																		D3D12_HEAP_FLAGS *pHeapFlags)
	{
		const auto result = GetWrappedObjectAs<ID3D12Resource>()->GetHeapProperties(pHeapProperties, pHeapFlags);
		return result;
	}

	// Wrap ID3D12Resource1
	ID3D12Resource1Wrapper::ID3D12Resource1Wrapper(const IID &riid, IUnknown *object)
	: ID3D12ResourceWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE ID3D12Resource1Wrapper::GetProtectedResourceSession(const IID &riid, void **ppProtectedSession)
	{
		const auto result = GetWrappedObjectAs<ID3D12Resource1>()->GetProtectedResourceSession(riid, ppProtectedSession);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppProtectedSession);
		}
		return result;
	}

	// Wrap ID3D12Resource2
	ID3D12Resource2Wrapper::ID3D12Resource2Wrapper(const IID &riid, IUnknown *object)
	: ID3D12Resource1Wrapper(riid, object)
	{

	}

	D3D12_RESOURCE_DESC1 STDMETHODCALLTYPE ID3D12Resource2Wrapper::GetDesc1()
	{
		const auto result = GetWrappedObjectAs<ID3D12Resource2>()->GetDesc1();
		return result;
	}
}