//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12FenceWrapper : ID3D12PageableWrapper
	{
	public:
		ID3D12FenceWrapper(REFIID riid, IUnknown *object);

		~ID3D12FenceWrapper() override = default;

		virtual UINT64 STDMETHODCALLTYPE GetCompletedValue();

		virtual HRESULT STDMETHODCALLTYPE SetEventOnCompletion(UINT64 Value, HANDLE hEvent);

		virtual HRESULT STDMETHODCALLTYPE Signal(UINT64 Value);
	};

	struct ID3D12Fence1Wrapper : ID3D12FenceWrapper
	{
	public:
		ID3D12Fence1Wrapper(REFIID riid, IUnknown *object);

		~ID3D12Fence1Wrapper() override = default;

		virtual D3D12_FENCE_FLAGS STDMETHODCALLTYPE GetCreationFlags();
	};
}
