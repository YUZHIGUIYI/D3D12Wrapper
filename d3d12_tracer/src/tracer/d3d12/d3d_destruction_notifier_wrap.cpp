//
// Created by ZZK on 2024/11/30.
//

#include <tracer/d3d12/d3d_destruction_notifier_wrap.h>

namespace gfxshim
{
	ID3DDestructionNotifierWrapper::ID3DDestructionNotifierWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE ID3DDestructionNotifierWrapper::RegisterDestructionCallback(PFN_DESTRUCTION_CALLBACK callbackFn, void *pData, UINT *pCallbackID)
	{
		const auto result = GetWrappedObjectAs<ID3DDestructionNotifier>()->RegisterDestructionCallback(callbackFn, pData, pCallbackID);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3DDestructionNotifierWrapper::UnregisterDestructionCallback(UINT callbackID)
	{
		const auto result = GetWrappedObjectAs<ID3DDestructionNotifier>()->UnregisterDestructionCallback(callbackID);
		return result;
	}

}