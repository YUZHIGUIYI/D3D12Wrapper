//
// Created by ZZK on 2024/11/24.
//

#include <tracer/d3d12/d3d12_root_signature_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	// ID3D12RootSignatureWrapper
	ID3D12RootSignatureWrapper::ID3D12RootSignatureWrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12RootSignatureWrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12RootSignatureWrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12RootSignatureWrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12RootSignatureWrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12RootSignatureWrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12RootSignatureWrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12RootSignatureWrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12RootSignatureWrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12Object
	HRESULT STDMETHODCALLTYPE ID3D12RootSignatureWrapper::GetPrivateData(const GUID &guid, UINT *pDataSize, void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->GetPrivateData(guid, pDataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12RootSignatureWrapper::SetPrivateData(const GUID &guid, UINT DataSize, const void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateData(guid, DataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12RootSignatureWrapper::SetPrivateDataInterface(const GUID &guid, const IUnknown *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateDataInterface(guid, encode::GetWrappedObject<IUnknown>(pData));
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12RootSignatureWrapper::SetName(LPCWSTR Name)
	{
		return GetWrappedObjectAs<ID3D12Object>()->SetName(Name);
	}

	// ID3D12DeviceChild
	HRESULT STDMETHODCALLTYPE ID3D12RootSignatureWrapper::GetDevice(const IID &riid, void **ppvDevice)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceChild>()->GetDevice(riid, ppvDevice);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvDevice);
		}
		return result;
	}

	// ID3D12RootSignatureDeserializerWrapper
	ID3D12RootSignatureDeserializerWrapper::ID3D12RootSignatureDeserializerWrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12RootSignatureDeserializerWrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12RootSignatureDeserializerWrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12RootSignatureDeserializerWrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12RootSignatureDeserializerWrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12RootSignatureDeserializerWrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12RootSignatureDeserializerWrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12RootSignatureDeserializerWrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12RootSignatureDeserializerWrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12RootSignatureDeserializer
	const D3D12_ROOT_SIGNATURE_DESC *STDMETHODCALLTYPE ID3D12RootSignatureDeserializerWrapper::GetRootSignatureDesc()
	{
		const auto result = GetWrappedObjectAs<ID3D12RootSignatureDeserializer>()->GetRootSignatureDesc();
		return result;
	}

	// ID3D12VersionedRootSignatureDeserializerWrapper
	ID3D12VersionedRootSignatureDeserializerWrapper::ID3D12VersionedRootSignatureDeserializerWrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12VersionedRootSignatureDeserializerWrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12VersionedRootSignatureDeserializerWrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12VersionedRootSignatureDeserializerWrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12VersionedRootSignatureDeserializerWrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12VersionedRootSignatureDeserializerWrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG(
				"Invoke ID3D12VersionedRootSignatureDeserializerWrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12VersionedRootSignatureDeserializerWrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12VersionedRootSignatureDeserializerWrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12VersionedRootSignatureDeserializer
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