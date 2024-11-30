//
// Created by ZZK on 2024/11/25.
//

#include <tracer/d3d12/d3d12_tools_wrap.h>

namespace gfxshim
{
	ID3D12ToolsWrapper::ID3D12ToolsWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	void STDMETHODCALLTYPE ID3D12ToolsWrapper::EnableShaderInstrumentation(BOOL bEnable)
	{
		GetWrappedObjectAs<ID3D12Tools>()->EnableShaderInstrumentation(bEnable);
	}

	BOOL STDMETHODCALLTYPE ID3D12ToolsWrapper::ShaderInstrumentationEnabled()
	{
		const auto result = GetWrappedObjectAs<ID3D12Tools>()->ShaderInstrumentationEnabled();
		return result;
	}

}