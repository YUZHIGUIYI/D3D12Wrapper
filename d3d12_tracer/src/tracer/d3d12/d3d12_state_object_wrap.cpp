//
// Created by ZZK on 2024/11/25.
//

#include <tracer/d3d12/d3d12_state_object_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	// Wrap ID3D12StateObject
	ID3D12StateObjectWrapper::ID3D12StateObjectWrapper(REFIID riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12StateObjectWrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12StateObjectWrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12StateObjectWrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12StateObjectWrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12StateObjectWrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12StateObjectWrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12StateObjectWrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12StateObjectWrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12Object
	HRESULT STDMETHODCALLTYPE ID3D12StateObjectWrapper::GetPrivateData(const GUID &guid, UINT *pDataSize, void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->GetPrivateData(guid, pDataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12StateObjectWrapper::SetPrivateData(const GUID &guid, UINT DataSize, const void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateData(guid, DataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12StateObjectWrapper::SetPrivateDataInterface(const GUID &guid, const IUnknown *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateDataInterface(guid, encode::GetWrappedObject<IUnknown>(pData));
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12StateObjectWrapper::SetName(LPCWSTR Name)
	{
		return GetWrappedObjectAs<ID3D12Object>()->SetName(Name);
	}

	// ID3D12DeviceChild
	HRESULT STDMETHODCALLTYPE ID3D12StateObjectWrapper::GetDevice(const IID &riid, void **ppvDevice)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceChild>()->GetDevice(riid, ppvDevice);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvDevice);
		}
		return result;
	}

	// Wrap ID3D12StateObjectProperties
	ID3D12StateObjectProperties1Wrapper::ID3D12StateObjectProperties1Wrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12StateObjectProperties1Wrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12StateObjectProperties1Wrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12StateObjectProperties1Wrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12StateObjectProperties1Wrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12StateObjectProperties1Wrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12StateObjectProperties1Wrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12StateObjectProperties1Wrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12StateObjectProperties1Wrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12StateObjectProperties
	void *STDMETHODCALLTYPE ID3D12StateObjectProperties1Wrapper::GetShaderIdentifier(LPCWSTR pExportName)
	{
		auto *result = GetWrappedObjectAs<ID3D12StateObjectProperties>()->GetShaderIdentifier(pExportName);
		return result;
	}

	UINT64 STDMETHODCALLTYPE ID3D12StateObjectProperties1Wrapper::GetShaderStackSize(LPCWSTR pExportName)
	{
		const auto result = GetWrappedObjectAs<ID3D12StateObjectProperties>()->GetShaderStackSize(pExportName);
		return result;
	}

	UINT64 STDMETHODCALLTYPE ID3D12StateObjectProperties1Wrapper::GetPipelineStackSize()
	{
		const auto result = GetWrappedObjectAs<ID3D12StateObjectProperties>()->GetPipelineStackSize();
		return result;
	}

	void STDMETHODCALLTYPE ID3D12StateObjectProperties1Wrapper::SetPipelineStackSize(UINT64 PipelineStackSizeInBytes)
	{
		GetWrappedObjectAs<ID3D12StateObjectProperties>()->SetPipelineStackSize(PipelineStackSizeInBytes);
	}

	// ID3D12StateObjectProperties1
	D3D12_PROGRAM_IDENTIFIER ID3D12StateObjectProperties1Wrapper::GetProgramIdentifier(LPCWSTR pProgramName)
	{
		const auto result = GetWrappedObjectAs<ID3D12StateObjectProperties1>()->GetProgramIdentifier(pProgramName);
		return result;
	}

}