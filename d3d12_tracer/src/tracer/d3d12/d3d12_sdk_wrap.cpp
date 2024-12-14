//
// Created by ZZK on 2024/11/30.
//

#include <tracer/d3d12/d3d12_sdk_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	// Wrap ID3D12SDKConfiguration
	ID3D12SDKConfigurationWrapper::ID3D12SDKConfigurationWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE ID3D12SDKConfigurationWrapper::SetSDKVersion(UINT SDKVersion, LPCSTR SDKPath)
	{
		const auto result = GetWrappedObjectAs<ID3D12SDKConfiguration>()->SetSDKVersion(SDKVersion, SDKPath);
		return result;
	}

	// Wrap ID3D12SDKConfiguration1
	ID3D12SDKConfiguration1Wrapper::ID3D12SDKConfiguration1Wrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12SDKConfiguration1Wrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12SDKConfiguration1Wrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12SDKConfiguration1Wrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12SDKConfiguration1Wrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12SDKConfiguration1Wrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12SDKConfiguration1Wrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12SDKConfiguration1Wrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12SDKConfiguration1Wrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12SDKConfiguration
	HRESULT STDMETHODCALLTYPE ID3D12SDKConfiguration1Wrapper::SetSDKVersion(UINT SDKVersion, LPCSTR SDKPath)
	{
		const auto result = GetWrappedObjectAs<ID3D12SDKConfiguration>()->SetSDKVersion(SDKVersion, SDKPath);
		return result;
	}

	// ID3D12SDKConfiguration1
	HRESULT STDMETHODCALLTYPE ID3D12SDKConfiguration1Wrapper::CreateDeviceFactory(UINT SDKVersion, LPCSTR SDKPath, const IID &riid, void **ppvFactory)
	{
		const auto result = GetWrappedObjectAs<ID3D12SDKConfiguration1>()->CreateDeviceFactory(SDKVersion, SDKPath, riid, ppvFactory);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvFactory);
		}
		return result;
	}

	void STDMETHODCALLTYPE ID3D12SDKConfiguration1Wrapper::FreeUnusedSDKs()
	{
		GetWrappedObjectAs<ID3D12SDKConfiguration1>()->FreeUnusedSDKs();
	}

}