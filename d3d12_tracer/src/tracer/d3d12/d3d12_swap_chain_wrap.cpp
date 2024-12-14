//
// Created by ZZK on 2024/11/25.
//

#include <tracer/d3d12/d3d12_swap_chain_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	ID3D12SwapChainAssistantWrapper::ID3D12SwapChainAssistantWrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12SwapChainAssistantWrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12SwapChainAssistantWrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12SwapChainAssistantWrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12SwapChainAssistantWrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12SwapChainAssistantWrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12SwapChainAssistantWrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12SwapChainAssistantWrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12SwapChainAssistantWrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12SwapChainAssistant
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