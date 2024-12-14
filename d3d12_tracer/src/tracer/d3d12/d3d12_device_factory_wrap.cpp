//
// Created by ZZK on 2024/11/24.
//

#include <tracer/d3d12/d3d12_device_factory_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	ID3D12DeviceFactoryWrapper::ID3D12DeviceFactoryWrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12DeviceFactoryWrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12DeviceFactoryWrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12DeviceFactoryWrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12DeviceFactoryWrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12DeviceFactoryWrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12DeviceFactoryWrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12DeviceFactoryWrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12DeviceFactoryWrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12DeviceFactory
	HRESULT STDMETHODCALLTYPE ID3D12DeviceFactoryWrapper::InitializeFromGlobalState()
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceFactory>()->InitializeFromGlobalState();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DeviceFactoryWrapper::ApplyToGlobalState()
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceFactory>()->ApplyToGlobalState();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DeviceFactoryWrapper::SetFlags(D3D12_DEVICE_FACTORY_FLAGS flags)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceFactory>()->SetFlags(flags);
		return result;
	}

	D3D12_DEVICE_FACTORY_FLAGS STDMETHODCALLTYPE ID3D12DeviceFactoryWrapper::GetFlags()
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceFactory>()->GetFlags();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DeviceFactoryWrapper::GetConfigurationInterface(const IID &clsid, const IID &iid, void **ppv)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceFactory>()->GetConfigurationInterface(clsid, iid, ppv);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(iid, ppv);
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DeviceFactoryWrapper::EnableExperimentalFeatures(UINT NumFeatures, const IID *pIIDs,
																					void *pConfigurationStructs,
																					UINT *pConfigurationStructSizes)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceFactory>()->EnableExperimentalFeatures(NumFeatures, pIIDs, pConfigurationStructs, pConfigurationStructSizes);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DeviceFactoryWrapper::CreateDevice(IUnknown *adapter, D3D_FEATURE_LEVEL FeatureLevel, const IID &riid,
																		void **ppvDevice)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceFactory>()->CreateDevice(encode::GetWrappedObject<IUnknown>(adapter), FeatureLevel, riid, ppvDevice);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvDevice);
		}
		return result;
	}

}