//
// Created by ZZK on 2024/11/30.
//

#include <tracer/d3d12/d3d12_meta_command_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	ID3D12MetaCommandWrapper::ID3D12MetaCommandWrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12MetaCommandWrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12MetaCommandWrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12MetaCommandWrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12MetaCommandWrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12MetaCommandWrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12MetaCommandWrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12MetaCommandWrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12MetaCommandWrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12Object
	HRESULT STDMETHODCALLTYPE ID3D12MetaCommandWrapper::GetPrivateData(const GUID &guid, UINT *pDataSize, void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->GetPrivateData(guid, pDataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12MetaCommandWrapper::SetPrivateData(const GUID &guid, UINT DataSize, const void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateData(guid, DataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12MetaCommandWrapper::SetPrivateDataInterface(const GUID &guid, const IUnknown *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateDataInterface(guid, encode::GetWrappedObject<IUnknown>(pData));
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12MetaCommandWrapper::SetName(LPCWSTR Name)
	{
		return GetWrappedObjectAs<ID3D12Object>()->SetName(Name);
	}

	// ID3D12DeviceChild
	HRESULT STDMETHODCALLTYPE ID3D12MetaCommandWrapper::GetDevice(const IID &riid, void **ppvDevice)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceChild>()->GetDevice(riid, ppvDevice);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvDevice);
		}
		return result;
	}

	// ID3D12MetaCommand
	UINT64 STDMETHODCALLTYPE ID3D12MetaCommandWrapper::GetRequiredParameterResourceSize(D3D12_META_COMMAND_PARAMETER_STAGE Stage, UINT ParameterIndex)
	{
		const auto result = GetWrappedObjectAs<ID3D12MetaCommand>()->GetRequiredParameterResourceSize(Stage, ParameterIndex);
		return result;
	}

}