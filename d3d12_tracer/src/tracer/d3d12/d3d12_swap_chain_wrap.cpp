//
// Created by ZZK on 2024/11/25.
//

#include <tracer/d3d12/d3d12_swap_chain_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	ID3D12SwapChainAssistantWrapper::ID3D12SwapChainAssistantWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	LUID STDMETHODCALLTYPE ID3D12SwapChainAssistantWrapper::GetLUID()
	{
		const auto result = GetWrappedObjectAs<ID3D12SwapChainAssistant>()->GetLUID();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12SwapChainAssistantWrapper::GetSwapChainObject(const IID &riid, void **ppv)
	{
		const auto result = GetWrappedObjectAs<ID3D12SwapChainAssistant>()->GetSwapChainObject(riid, ppv);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppv);
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12SwapChainAssistantWrapper::GetCurrentResourceAndCommandQueue(const IID &riidResource, void **ppvResource,
																								const IID &riidQueue, void **ppvQueue)
	{
		const auto result = GetWrappedObjectAs<ID3D12SwapChainAssistant>()->GetCurrentResourceAndCommandQueue(riidResource, ppvResource, riidQueue, ppvQueue);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riidResource, ppvResource);
			encode::WrapObject(riidQueue, ppvQueue);
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12SwapChainAssistantWrapper::InsertImplicitSync()
	{
		const auto result = GetWrappedObjectAs<ID3D12SwapChainAssistant>()->InsertImplicitSync();
		return result;
	}

}