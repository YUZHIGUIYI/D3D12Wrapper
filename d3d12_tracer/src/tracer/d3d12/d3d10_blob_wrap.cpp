//
// Created by ZZK on 2024/11/24.
//

#include <tracer/d3d12/d3d10_blob_wrap.h>

namespace gfxshim
{
	ID3D10BlobWrapper::ID3D10BlobWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	LPVOID STDMETHODCALLTYPE ID3D10BlobWrapper::GetBufferPointer()
	{
		const auto result = GetWrappedObjectAs<ID3D10Blob>()->GetBufferPointer();
		return result;
	}

	SIZE_T STDMETHODCALLTYPE ID3D10BlobWrapper::GetBufferSize()
	{
		const auto result = GetWrappedObjectAs<ID3D10Blob>()->GetBufferSize();
		return result;
	}

}