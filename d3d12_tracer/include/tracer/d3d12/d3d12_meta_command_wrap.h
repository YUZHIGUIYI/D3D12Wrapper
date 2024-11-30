//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12MetaCommandWrapper : ID3D12PageableWrapper
	{
	public:
		ID3D12MetaCommandWrapper(REFIID riid, IUnknown *object);

		~ID3D12MetaCommandWrapper() override = default;

		virtual UINT64 STDMETHODCALLTYPE GetRequiredParameterResourceSize(D3D12_META_COMMAND_PARAMETER_STAGE Stage, UINT ParameterIndex);
	};
}
