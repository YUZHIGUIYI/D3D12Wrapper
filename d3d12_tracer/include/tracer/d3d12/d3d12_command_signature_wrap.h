//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12CommandSignatureWrapper : ID3D12PageableWrapper
	{
	public:
		ID3D12CommandSignatureWrapper(REFIID riid, IUnknown *object);

		~ID3D12CommandSignatureWrapper() override = default;
	};
}
