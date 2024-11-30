//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12ToolsWrapper : IUnknownWrapper
	{
	public:
		ID3D12ToolsWrapper(REFIID riid, IUnknown *object);

		~ID3D12ToolsWrapper() override = default;

		virtual void STDMETHODCALLTYPE EnableShaderInstrumentation(BOOL bEnable);

		virtual BOOL STDMETHODCALLTYPE ShaderInstrumentationEnabled();
	};
}
