//
// Created by ZZK on 2024/11/26.
//

#include <tracer/d3d12/d3d12_lifetime_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	// Wrap ID3D12LifetimeOwner
	ID3D12LifetimeOwnerWrapper::ID3D12LifetimeOwnerWrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12LifetimeOwnerWrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12LifetimeOwnerWrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12LifetimeOwnerWrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12LifetimeOwnerWrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12LifetimeOwnerWrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12LifetimeOwnerWrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12LifetimeOwnerWrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12LifetimeOwnerWrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12LifetimeOwner
	void STDMETHODCALLTYPE ID3D12LifetimeOwnerWrapper::LifetimeStateUpdated(D3D12_LIFETIME_STATE NewState)
	{
		GetWrappedObjectAs<ID3D12LifetimeOwner>()->LifetimeStateUpdated(NewState);
	}

	// Wrap ID3D12LifetimeTracker
	ID3D12LifetimeTrackerWrapper::ID3D12LifetimeTrackerWrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12LifetimeTrackerWrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12LifetimeTrackerWrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12LifetimeTrackerWrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12LifetimeTrackerWrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12LifetimeTrackerWrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12LifetimeTrackerWrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12LifetimeTrackerWrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12LifetimeTrackerWrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12Object
	HRESULT STDMETHODCALLTYPE ID3D12LifetimeTrackerWrapper::GetPrivateData(const GUID &guid, UINT *pDataSize, void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->GetPrivateData(guid, pDataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12LifetimeTrackerWrapper::SetPrivateData(const GUID &guid, UINT DataSize, const void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateData(guid, DataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12LifetimeTrackerWrapper::SetPrivateDataInterface(const GUID &guid, const IUnknown *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateDataInterface(guid, encode::GetWrappedObject<IUnknown>(pData));
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12LifetimeTrackerWrapper::SetName(LPCWSTR Name)
	{
		return GetWrappedObjectAs<ID3D12Object>()->SetName(Name);
	}

	// ID3D12DeviceChild
	HRESULT STDMETHODCALLTYPE ID3D12LifetimeTrackerWrapper::GetDevice(const IID &riid, void **ppvDevice)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceChild>()->GetDevice(riid, ppvDevice);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvDevice);
		}
		return result;
	}

	// ID3D12LifetimeTracker
	HRESULT STDMETHODCALLTYPE ID3D12LifetimeTrackerWrapper::DestroyOwnedObject(ID3D12DeviceChild *pObject)
	{
		const auto result = GetWrappedObjectAs<ID3D12LifetimeTracker>()->DestroyOwnedObject(encode::GetWrappedObject<ID3D12DeviceChild>(pObject));
		return result;
	}

}