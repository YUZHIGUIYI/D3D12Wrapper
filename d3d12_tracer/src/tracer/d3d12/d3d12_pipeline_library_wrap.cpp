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
	: ID3D12PipelineLibraryWrapper(riid, object)
	{

	}

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