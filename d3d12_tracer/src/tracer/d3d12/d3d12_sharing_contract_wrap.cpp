//
// Created by ZZK on 2024/11/26.
//

#include <tracer/d3d12/d3d12_sharing_contract_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	// Wrap ID3D12SharingContract
	ID3D12SharingContractWrapper::ID3D12SharingContractWrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12SharingContractWrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12SharingContractWrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12SharingContractWrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12SharingContractWrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12SharingContractWrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12SharingContractWrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12SharingContractWrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12SharingContractWrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12SharingContract
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

	// Wrap ID3D12ManualWriteTrackingResource
	ID3D12ManualWriteTrackingResourceWrapper::ID3D12ManualWriteTrackingResourceWrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12ManualWriteTrackingResourceWrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12ManualWriteTrackingResourceWrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12ManualWriteTrackingResourceWrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12ManualWriteTrackingResourceWrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12ManualWriteTrackingResourceWrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12ManualWriteTrackingResourceWrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12ManualWriteTrackingResourceWrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12ManualWriteTrackingResourceWrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12ManualWriteTrackingResource
	void STDMETHODCALLTYPE ID3D12ManualWriteTrackingResourceWrapper::TrackWrite(UINT Subresource, const D3D12_RANGE *pWrittenRange)
	{
		GetWrappedObjectAs<ID3D12ManualWriteTrackingResource>()->TrackWrite(Subresource, pWrittenRange);
	}
}