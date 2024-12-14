//
// Created by ZZK on 2024/11/30.
//

#include <tracer/d3d12/d3d12_device_configuration_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	ID3D12DeviceConfiguration1Wrapper::ID3D12DeviceConfiguration1Wrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12DeviceConfiguration1Wrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12DeviceConfiguration1Wrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12DeviceConfiguration1Wrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12DeviceConfiguration1Wrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12DeviceConfiguration1Wrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12DeviceConfiguration1Wrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12DeviceConfiguration1Wrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12DeviceConfiguration1Wrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12DeviceConfiguration
	D3D12_DEVICE_CONFIGURATION_DESC STDMETHODCALLTYPE ID3D12DeviceConfiguration1Wrapper::GetDesc()
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceConfiguration>()->GetDesc();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DeviceConfiguration1Wrapper::GetEnabledExperimentalFeatures(GUID *pGuids, UINT NumGuids)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceConfiguration>()->GetEnabledExperimentalFeatures(pGuids, NumGuids);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DeviceConfiguration1Wrapper::SerializeVersionedRootSignature(const D3D12_VERSIONED_ROOT_SIGNATURE_DESC *pDesc,
																								ID3DBlob **ppResult, ID3DBlob **ppError)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceConfiguration>()->SerializeVersionedRootSignature(pDesc, ppResult, ppError);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(__uuidof(ID3D10Blob), reinterpret_cast<void **>(ppResult));
			encode::WrapObject(__uuidof(ID3D10Blob), reinterpret_cast<void **>(ppError));
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DeviceConfiguration1Wrapper::CreateVersionedRootSignatureDeserializer(const void *pBlob, SIZE_T Size,
																										const IID &riid, void **ppvDeserializer)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceConfiguration>()->CreateVersionedRootSignatureDeserializer(pBlob, Size, riid, ppvDeserializer);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvDeserializer);
		}
		return result;
	}

	// ID3D12DeviceConfiguration1
	HRESULT ID3D12DeviceConfiguration1Wrapper::CreateVersionedRootSignatureDeserializerFromSubobjectInLibrary(const void *pLibraryBlob, SIZE_T Size, LPCWSTR RootSignatureSubobjectName,
																											const IID &riid, void **ppvDeserializer)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceConfiguration1>()->CreateVersionedRootSignatureDeserializerFromSubobjectInLibrary(pLibraryBlob, Size, RootSignatureSubobjectName, riid, ppvDeserializer);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvDeserializer);
		}
		return result;
	}

}