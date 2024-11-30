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
	: ID3D12SDKConfigurationWrapper(riid, object)
	{

	}

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