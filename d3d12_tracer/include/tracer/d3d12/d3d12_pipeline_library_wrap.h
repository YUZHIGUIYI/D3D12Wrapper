//
// Created by ZZK on 2024/11/24.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12PipelineLibraryWrapper : ID3D12DeviceChildWrapper
	{
	public:
		ID3D12PipelineLibraryWrapper(REFIID riid, IUnknown *object);

		~ID3D12PipelineLibraryWrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE StorePipeline(LPCWSTR pName, ID3D12PipelineState *pPipeline);

		virtual HRESULT STDMETHODCALLTYPE LoadGraphicsPipeline(
						LPCWSTR pName,
						const D3D12_GRAPHICS_PIPELINE_STATE_DESC* pDesc,
						REFIID riid,
						void** ppPipelineState);

		virtual HRESULT STDMETHODCALLTYPE LoadComputePipeline(
						LPCWSTR pName,
						const D3D12_COMPUTE_PIPELINE_STATE_DESC* pDesc,
						REFIID riid,
						void** ppPipelineState);

		virtual SIZE_T STDMETHODCALLTYPE GetSerializedSize();

		virtual HRESULT STDMETHODCALLTYPE Serialize(
						void* pData,
						SIZE_T DataSizeInBytes);
	};

	struct ID3D12PipelineLibrary1Wrapper : ID3D12PipelineLibraryWrapper
	{
	public:
		ID3D12PipelineLibrary1Wrapper(REFIID riid, IUnknown *object);

		~ID3D12PipelineLibrary1Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE LoadPipeline(
						LPCWSTR pName,
						const D3D12_PIPELINE_STATE_STREAM_DESC* pDesc,
						REFIID riid,
						void** ppPipelineState);
	};
}
