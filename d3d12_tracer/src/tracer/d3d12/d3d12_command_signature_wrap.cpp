//
// Created by ZZK on 2024/11/30.
//

#include <tracer/d3d12/d3d12_command_signature_wrap.h>

namespace gfxshim
{
	ID3D12CommandSignatureWrapper::ID3D12CommandSignatureWrapper(const IID &riid, IUnknown *object)
	: ID3D12PageableWrapper(riid, object)
	{

	}

}