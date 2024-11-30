//
// Created by ZZK on 2024/11/30.
//

#include <tracer/d3d12/d3d12_device_configuration_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	ID3D12DeviceConfigurationWrapper::ID3D12DeviceConfigurationWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	D3D12_DEVICE_CONFIGURATION_DESC STDMETHODCALLTYPE ID3D12DeviceConfigurationWrapper::GetDesc()
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceConfiguration>()->GetDesc();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DeviceConfigurationWrapper::GetEnabledExperimentalFeatures(GUID *pGuids, UINT NumGuids)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceConfiguration>()->GetEnabledExperimentalFeatures(pGuids, NumGuids);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DeviceConfigurationWrapper::SerializeVersionedRootSignature(const D3D12_VERSIONED_ROOT_SIGNATURE_DESC *pDesc,
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

	HRESULT STDMETHODCALLTYPE ID3D12DeviceConfigurationWrapper::CreateVersionedRootSignatureDeserializer(const void *pBlob, SIZE_T Size,
																										const IID &riid, void **ppvDeserializer)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceConfiguration>()->CreateVersionedRootSignatureDeserializer(pBlob, Size, riid, ppvDeserializer);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvDeserializer);
		}
		return result;
	}

}