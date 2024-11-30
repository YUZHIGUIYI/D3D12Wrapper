//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12SwapChainAssistantWrapper : IUnknownWrapper
	{
	public:
		ID3D12SwapChainAssistantWrapper(REFIID riid, IUnknown *object);

		~ID3D12SwapChainAssistantWrapper() override = default;

		virtual LUID STDMETHODCALLTYPE GetLUID();

		virtual HRESULT STDMETHODCALLTYPE GetSwapChainObject(REFIID riid, void** ppv);

		virtual HRESULT STDMETHODCALLTYPE GetCurrentResourceAndCommandQueue(
											REFIID riidResource,
											void** ppvResource,
											REFIID riidQueue,
											void** ppvQueue);

		virtual HRESULT STDMETHODCALLTYPE InsertImplicitSync();
	};
}
