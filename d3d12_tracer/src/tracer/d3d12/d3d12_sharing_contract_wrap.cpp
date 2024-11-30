//
// Created by ZZK on 2024/11/26.
//

#include <tracer/d3d12/d3d12_sharing_contract_wrap.h>

namespace gfxshim
{
	// Wrap ID3D12SharingContract
	ID3D12SharingContractWrapper::ID3D12SharingContractWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	void STDMETHODCALLTYPE ID3D12SharingContractWrapper::Present(ID3D12Resource *pResource, UINT Subresource, HWND window)
	{
		GetWrappedObjectAs<ID3D12SharingContract>()->Present(encode::GetWrappedObject<ID3D12Resource>(pResource), Subresource, window);
	}

	void STDMETHODCALLTYPE ID3D12SharingContractWrapper::SharedFenceSignal(ID3D12Fence *pFence, UINT64 FenceValue)
	{
		GetWrappedObjectAs<ID3D12SharingContract>()->SharedFenceSignal(encode::GetWrappedObject<ID3D12Fence>(pFence), FenceValue);
	}

	void STDMETHODCALLTYPE ID3D12SharingContractWrapper::BeginCapturableWork(const GUID &guid)
	{
		GetWrappedObjectAs<ID3D12SharingContract>()->BeginCapturableWork(guid);
	}

	void STDMETHODCALLTYPE ID3D12SharingContractWrapper::EndCapturableWork(const GUID &guid)
	{
		GetWrappedObjectAs<ID3D12SharingContract>()->EndCapturableWork(guid);
	}

	// Wrap
	ID3D12ManualWriteTrackingResourceWrapper::ID3D12ManualWriteTrackingResourceWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	void STDMETHODCALLTYPE ID3D12ManualWriteTrackingResourceWrapper::TrackWrite(UINT Subresource, const D3D12_RANGE *pWrittenRange)
	{
		GetWrappedObjectAs<ID3D12ManualWriteTrackingResource>()->TrackWrite(Subresource, pWrittenRange);
	}
}