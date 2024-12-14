//
// Created by ZZK on 2024/11/30.
//

#include <tracer/d3d12/d3d_destruction_notifier_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	ID3DDestructionNotifierWrapper::ID3DDestructionNotifierWrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3DDestructionNotifierWrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3DDestructionNotifierWrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3DDestructionNotifierWrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3DDestructionNotifierWrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3DDestructionNotifierWrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3DDestructionNotifierWrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3DDestructionNotifierWrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3DDestructionNotifierWrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3DDestructionNotifier
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