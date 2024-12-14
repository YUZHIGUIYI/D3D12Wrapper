//
// Created by ZZK on 2024/11/24.
//

#include <tracer/d3d12/d3d12_pipeline_library_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	// Wrap ID3D12PipelineLibrary
	ID3D12PipelineLibraryWrapper::ID3D12PipelineLibraryWrapper(const IID &riid, IUnknown *object)
	: ID3D12DeviceChildWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE ID3D12PipelineLibraryWrapper::StorePipeline(LPCWSTR pName, ID3D12PipelineState *pPipeline)
	{
		const auto result = GetWrappedObjectAs<ID3D12PipelineLibrary>()->StorePipeline(pName, encode::GetWrappedObject<ID3D12PipelineState>(pPipeline));
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12PipelineLibraryWrapper::LoadGraphicsPipeline(LPCWSTR pName,
																				const D3D12_GRAPHICS_PIPELINE_STATE_DESC *pDesc,
																				const IID &riid, void **ppPipelineState)
	{
		const auto result = GetWrappedObjectAs<ID3D12PipelineLibrary>()->LoadGraphicsPipeline(pName, pDesc, riid, ppPipelineState);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppPipelineState);
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12PipelineLibraryWrapper::LoadComputePipeline(LPCWSTR pName,
																				const D3D12_COMPUTE_PIPELINE_STATE_DESC *pDesc,
																				const IID &riid, void **ppPipelineState)
	{
		const auto result = GetWrappedObjectAs<ID3D12PipelineLibrary>()->LoadComputePipeline(pName, pDesc, riid, ppPipelineState);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppPipelineState);
		}
		return result;
	}

	SIZE_T STDMETHODCALLTYPE ID3D12PipelineLibraryWrapper::GetSerializedSize()
	{
		const auto result = GetWrappedObjectAs<ID3D12PipelineLibrary>()->GetSerializedSize();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12PipelineLibraryWrapper::Serialize(void *pData, SIZE_T DataSizeInBytes)
	{
		const auto result = GetWrappedObjectAs<ID3D12PipelineLibrary>()->Serialize(pData, DataSizeInBytes);
		return result;
	}

	// Wrap ID3D12PipelineLibrary1
	ID3D12PipelineLibrary1Wrapper::ID3D12PipelineLibrary1Wrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12PipelineLibrary1Wrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12PipelineLibrary1Wrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12PipelineLibrary1Wrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12PipelineLibrary1Wrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12PipelineLibrary1Wrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12PipelineLibrary1Wrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12PipelineLibrary1Wrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12PipelineLibrary1Wrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12Object
	HRESULT STDMETHODCALLTYPE ID3D12PipelineLibrary1Wrapper::GetPrivateData(const GUID &guid, UINT *pDataSize, void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->GetPrivateData(guid, pDataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12PipelineLibrary1Wrapper::SetPrivateData(const GUID &guid, UINT DataSize, const void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateData(guid, DataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12PipelineLibrary1Wrapper::SetPrivateDataInterface(const GUID &guid, const IUnknown *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateDataInterface(guid, encode::GetWrappedObject<IUnknown>(pData));
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12PipelineLibrary1Wrapper::SetName(LPCWSTR Name)
	{
		return GetWrappedObjectAs<ID3D12Object>()->SetName(Name);
	}

	// ID3D12DeviceChild
	HRESULT STDMETHODCALLTYPE ID3D12PipelineLibrary1Wrapper::GetDevice(const IID &riid, void **ppvDevice)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceChild>()->GetDevice(riid, ppvDevice);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvDevice);
		}
		return result;
	}

	// ID3D12PipelineLibrary
	HRESULT STDMETHODCALLTYPE ID3D12PipelineLibrary1Wrapper::StorePipeline(LPCWSTR pName, ID3D12PipelineState *pPipeline)
	{
		const auto result = GetWrappedObjectAs<ID3D12PipelineLibrary>()->StorePipeline(pName, encode::GetWrappedObject<ID3D12PipelineState>(pPipeline));
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12PipelineLibrary1Wrapper::LoadGraphicsPipeline(LPCWSTR pName,
																				const D3D12_GRAPHICS_PIPELINE_STATE_DESC *pDesc,
																				const IID &riid, void **ppPipelineState)
	{
		const auto result = GetWrappedObjectAs<ID3D12PipelineLibrary>()->LoadGraphicsPipeline(pName, pDesc, riid, ppPipelineState);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppPipelineState);
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12PipelineLibrary1Wrapper::LoadComputePipeline(LPCWSTR pName,
																				const D3D12_COMPUTE_PIPELINE_STATE_DESC *pDesc,
																				const IID &riid, void **ppPipelineState)
	{
		const auto result = GetWrappedObjectAs<ID3D12PipelineLibrary>()->LoadComputePipeline(pName, pDesc, riid, ppPipelineState);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppPipelineState);
		}
		return result;
	}

	SIZE_T STDMETHODCALLTYPE ID3D12PipelineLibrary1Wrapper::GetSerializedSize()
	{
		const auto result = GetWrappedObjectAs<ID3D12PipelineLibrary>()->GetSerializedSize();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12PipelineLibrary1Wrapper::Serialize(void *pData, SIZE_T DataSizeInBytes)
	{
		const auto result = GetWrappedObjectAs<ID3D12PipelineLibrary>()->Serialize(pData, DataSizeInBytes);
		return result;
	}

	// ID3D12PipelineLibrary1
	HRESULT STDMETHODCALLTYPE ID3D12PipelineLibrary1Wrapper::LoadPipeline(LPCWSTR pName, const D3D12_PIPELINE_STATE_STREAM_DESC *pDesc,
																		const IID &riid, void **ppPipelineState)
	{
		const auto result = GetWrappedObjectAs<ID3D12PipelineLibrary1>()->LoadPipeline(pName, pDesc, riid, ppPipelineState);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppPipelineState);
		}
		return result;
	}


}