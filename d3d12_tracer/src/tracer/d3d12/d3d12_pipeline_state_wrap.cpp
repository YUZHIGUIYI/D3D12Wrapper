//
// Created by ZZK on 2024/11/24.
//

#include <tracer/d3d12/d3d12_pipeline_state_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	ID3D12PipelineStateWrapper::ID3D12PipelineStateWrapper(const IID &riid, IUnknown *object)
	: ID3D12PageableWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE ID3D12PipelineStateWrapper::GetCachedBlob(ID3DBlob **ppBlob)
	{
		const auto result = GetWrappedObjectAs<ID3D12PipelineState>()->GetCachedBlob(ppBlob);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(__uuidof(ID3D10Blob), reinterpret_cast<void **>(ppBlob));
		}
		return result;
	}

}