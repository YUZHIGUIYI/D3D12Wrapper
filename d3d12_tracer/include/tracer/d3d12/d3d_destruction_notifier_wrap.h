//
// Created by ZZK on 2024/11/30.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3DDestructionNotifierWrapper : IUnknownWrapper
	{
	public:
		ID3DDestructionNotifierWrapper(REFIID riid, IUnknown *object);

		~ID3DDestructionNotifierWrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE RegisterDestructionCallback(
						PFN_DESTRUCTION_CALLBACK callbackFn,
						void* pData,
						UINT* pCallbackID);

		virtual HRESULT STDMETHODCALLTYPE UnregisterDestructionCallback(UINT callbackID);
	};
}
