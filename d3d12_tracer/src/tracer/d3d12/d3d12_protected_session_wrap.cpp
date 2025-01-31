//
// Created by ZZK on 2024/11/26.
//

#include <tracer/d3d12/d3d12_protected_session_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	// Wrap ID3D12ProtectedResourceSession1
	ID3D12ProtectedResourceSession1Wrapper::ID3D12ProtectedResourceSession1Wrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12ProtectedResourceSession1Wrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12ProtectedResourceSession1Wrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12ProtectedResourceSession1Wrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12ProtectedResourceSession1Wrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12ProtectedResourceSession1Wrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12ProtectedResourceSession1Wrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12ProtectedResourceSession1Wrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12ProtectedResourceSession1Wrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12Object
	HRESULT STDMETHODCALLTYPE ID3D12ProtectedResourceSession1Wrapper::GetPrivateData(const GUID &guid, UINT *pDataSize, void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->GetPrivateData(guid, pDataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12ProtectedResourceSession1Wrapper::SetPrivateData(const GUID &guid, UINT DataSize, const void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateData(guid, DataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12ProtectedResourceSession1Wrapper::SetPrivateDataInterface(const GUID &guid, const IUnknown *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateDataInterface(guid, encode::GetWrappedObject<IUnknown>(pData));
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12ProtectedResourceSession1Wrapper::SetName(LPCWSTR Name)
	{
		return GetWrappedObjectAs<ID3D12Object>()->SetName(Name);
	}

	// ID3D12DeviceChild
	HRESULT STDMETHODCALLTYPE ID3D12ProtectedResourceSession1Wrapper::GetDevice(const IID &riid, void **ppvDevice)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceChild>()->GetDevice(riid, ppvDevice);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvDevice);
		}
		return result;
	}

	// ID3D12ProtectedSession
	HRESULT STDMETHODCALLTYPE ID3D12ProtectedResourceSession1Wrapper::GetStatusFence(const IID &riid, void **ppFence)
	{
		const auto result = GetWrappedObjectAs<ID3D12ProtectedSession>()->GetStatusFence(riid, ppFence);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppFence);
		}
		return result;
	}

	D3D12_PROTECTED_SESSION_STATUS STDMETHODCALLTYPE ID3D12ProtectedResourceSession1Wrapper::GetSessionStatus()
	{
		const auto result = GetWrappedObjectAs<ID3D12ProtectedSession>()->GetSessionStatus();
		return result;
	}

	// ID3D12ProtectedResourceSession
	D3D12_PROTECTED_RESOURCE_SESSION_DESC STDMETHODCALLTYPE ID3D12ProtectedResourceSession1Wrapper::GetDesc()
	{
		const auto result = GetWrappedObjectAs<ID3D12ProtectedResourceSession>()->GetDesc();
		return result;
	}

	// ID3D12ProtectedResourceSession1
	D3D12_PROTECTED_RESOURCE_SESSION_DESC1 STDMETHODCALLTYPE ID3D12ProtectedResourceSession1Wrapper::GetDesc1()
	{
		const auto result = GetWrappedObjectAs<ID3D12ProtectedResourceSession1>()->GetDesc1();
		return result;
	}

}