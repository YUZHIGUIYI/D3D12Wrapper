//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D10BlobWrapper : IUnknownWrapper
	{
	public:
		ID3D10BlobWrapper(REFIID riid, IUnknown *object);

		~ID3D10BlobWrapper() override = default;

		virtual LPVOID STDMETHODCALLTYPE GetBufferPointer();

		virtual SIZE_T STDMETHODCALLTYPE GetBufferSize();
	};
}
