//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12HeapWrapper : ID3D12PageableWrapper
	{
	public:
		ID3D12HeapWrapper(REFIID riid, IUnknown *object);

		~ID3D12HeapWrapper() override = default;

		virtual D3D12_HEAP_DESC STDMETHODCALLTYPE GetDesc();
	};

	struct ID3D12Heap1Wrapper : ID3D12HeapWrapper
	{
	public:
		ID3D12Heap1Wrapper(REFIID riid, IUnknown *object);

		~ID3D12Heap1Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE GetProtectedResourceSession(REFIID riid, void** ppProtectedSession);
	};

	struct ID3D12DescriptorHeapWrapper : ID3D12PageableWrapper
	{
	public:
		ID3D12DescriptorHeapWrapper(REFIID riid, IUnknown *object);

		~ID3D12DescriptorHeapWrapper() override = default;

		virtual D3D12_DESCRIPTOR_HEAP_DESC STDMETHODCALLTYPE GetDesc();

		virtual D3D12_CPU_DESCRIPTOR_HANDLE STDMETHODCALLTYPE GetCPUDescriptorHandleForHeapStart();

		virtual D3D12_GPU_DESCRIPTOR_HANDLE STDMETHODCALLTYPE GetGPUDescriptorHandleForHeapStart();
	};

	struct ID3D12QueryHeapWrapper : ID3D12PageableWrapper
	{
	public:
		ID3D12QueryHeapWrapper(REFIID riid, IUnknown *object);

		~ID3D12QueryHeapWrapper() override = default;
	};
}
