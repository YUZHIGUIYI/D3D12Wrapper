//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12ResourceWrapper : ID3D12PageableWrapper
	{
	public:
		ID3D12ResourceWrapper(REFIID riid, IUnknown *object);

		~ID3D12ResourceWrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE Map(
						UINT Subresource,
						const D3D12_RANGE* pReadRange,
						void** ppData);

		virtual void STDMETHODCALLTYPE Unmap(
					UINT Subresource,
					const D3D12_RANGE* pWrittenRange);

		virtual D3D12_RESOURCE_DESC STDMETHODCALLTYPE GetDesc();

		virtual D3D12_GPU_VIRTUAL_ADDRESS STDMETHODCALLTYPE GetGPUVirtualAddress();

		virtual HRESULT STDMETHODCALLTYPE WriteToSubresource(
						UINT DstSubresource,
						const D3D12_BOX* pDstBox,
						const void* pSrcData,
						UINT SrcRowPitch,
						UINT SrcDepthPitch);

		virtual HRESULT STDMETHODCALLTYPE ReadFromSubresource(
						void* pDstData,
						UINT DstRowPitch,
						UINT DstDepthPitch,
						UINT SrcSubresource,
						const D3D12_BOX* pSrcBox);

		virtual HRESULT STDMETHODCALLTYPE GetHeapProperties(
						D3D12_HEAP_PROPERTIES* pHeapProperties,
						D3D12_HEAP_FLAGS* pHeapFlags);
	};

	struct ID3D12Resource1Wrapper : ID3D12ResourceWrapper
	{
	public:
		ID3D12Resource1Wrapper(REFIID riid, IUnknown *object);

		~ID3D12Resource1Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE GetProtectedResourceSession(REFIID riid, void** ppProtectedSession);
	};

	struct ID3D12Resource2Wrapper : ID3D12Resource1Wrapper
	{
	public:
		ID3D12Resource2Wrapper(REFIID riid, IUnknown *object);

		~ID3D12Resource2Wrapper() override = default;

		virtual D3D12_RESOURCE_DESC1 STDMETHODCALLTYPE GetDesc1();
	};
}
