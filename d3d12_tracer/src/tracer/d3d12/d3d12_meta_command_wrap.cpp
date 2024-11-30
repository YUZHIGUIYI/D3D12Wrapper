//
// Created by ZZK on 2024/11/30.
//

#include <tracer/d3d12/d3d12_meta_command_wrap.h>

namespace gfxshim
{
	ID3D12MetaCommandWrapper::ID3D12MetaCommandWrapper(const IID &riid, IUnknown *object)
	: ID3D12PageableWrapper(riid, object)
	{

	}

	UINT64 STDMETHODCALLTYPE ID3D12MetaCommandWrapper::GetRequiredParameterResourceSize(D3D12_META_COMMAND_PARAMETER_STAGE Stage, UINT ParameterIndex)
	{
		const auto result = GetWrappedObjectAs<ID3D12MetaCommand>()->GetRequiredParameterResourceSize(Stage, ParameterIndex);
		return result;
	}

}