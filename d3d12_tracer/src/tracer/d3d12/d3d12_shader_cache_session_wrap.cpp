//
// Created by ZZK on 2024/11/24.
//

#include <tracer/d3d12/d3d12_shader_cache_session_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	ID3D12ShaderCacheSessionWrapper::ID3D12ShaderCacheSessionWrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12ShaderCacheSessionWrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12ShaderCacheSessionWrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12ShaderCacheSessionWrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12ShaderCacheSessionWrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12ShaderCacheSessionWrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12ShaderCacheSessionWrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12ShaderCacheSessionWrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12ShaderCacheSessionWrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12Object
	HRESULT STDMETHODCALLTYPE ID3D12ShaderCacheSessionWrapper::GetPrivateData(const GUID &guid, UINT *pDataSize, void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->GetPrivateData(guid, pDataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12ShaderCacheSessionWrapper::SetPrivateData(const GUID &guid, UINT DataSize, const void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateData(guid, DataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12ShaderCacheSessionWrapper::SetPrivateDataInterface(const GUID &guid, const IUnknown *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateDataInterface(guid, encode::GetWrappedObject<IUnknown>(pData));
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12ShaderCacheSessionWrapper::SetName(LPCWSTR Name)
	{
		return GetWrappedObjectAs<ID3D12Object>()->SetName(Name);
	}

	// ID3D12DeviceChild
	HRESULT STDMETHODCALLTYPE ID3D12ShaderCacheSessionWrapper::GetDevice(const IID &riid, void **ppvDevice)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceChild>()->GetDevice(riid, ppvDevice);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvDevice);
		}
		return result;
	}

	// ID3D12ShaderCacheSession
	HRESULT STDMETHODCALLTYPE ID3D12ShaderCacheSessionWrapper::FindValue(const void *pKey, UINT KeySize, void *pValue, UINT *pValueSize)
	{
		const auto result = GetWrappedObjectAs<ID3D12ShaderCacheSession>()->FindValue(pKey, KeySize, pValue, pValueSize);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12ShaderCacheSessionWrapper::StoreValue(const void *pKey, UINT KeySize, const void *pValue, UINT ValueSize)
	{
		const auto result = GetWrappedObjectAs<ID3D12ShaderCacheSession>()->StoreValue(pKey, KeySize, pValue, ValueSize);
		return result;
	}

	void STDMETHODCALLTYPE ID3D12ShaderCacheSessionWrapper::SetDeleteOnDestroy()
	{
		GetWrappedObjectAs<ID3D12ShaderCacheSession>()->SetDeleteOnDestroy();
	}

	D3D12_SHADER_CACHE_SESSION_DESC STDMETHODCALLTYPE ID3D12ShaderCacheSessionWrapper::GetDesc()
	{
		const auto result = GetWrappedObjectAs<ID3D12ShaderCacheSession>()->GetDesc();
		return result;
	}

}