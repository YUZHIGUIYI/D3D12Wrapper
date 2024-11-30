//
// Created by ZZK on 2024/11/26.
//

#include <tracer/d3d12/d3d12_protected_session_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	// Wrap ID3D12ProtectedSession
	ID3D12ProtectedSessionWrapper::ID3D12ProtectedSessionWrapper(const IID &riid, IUnknown *object)
	: ID3D12DeviceChildWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE ID3D12ProtectedSessionWrapper::GetStatusFence(const IID &riid, void **ppFence)
	{
		const auto result = GetWrappedObjectAs<ID3D12ProtectedSession>()->GetStatusFence(riid, ppFence);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppFence);
		}
		return result;
	}

	D3D12_PROTECTED_SESSION_STATUS STDMETHODCALLTYPE ID3D12ProtectedSessionWrapper::GetSessionStatus()
	{
		const auto result = GetWrappedObjectAs<ID3D12ProtectedSession>()->GetSessionStatus();
		return result;
	}

	// Wrap ID3D12ProtectedResourceSession
	ID3D12ProtectedResourceSessionWrapper::ID3D12ProtectedResourceSessionWrapper(const IID &riid, IUnknown *object)
	: ID3D12ProtectedSessionWrapper(riid, object)
	{

	}

	D3D12_PROTECTED_RESOURCE_SESSION_DESC STDMETHODCALLTYPE ID3D12ProtectedResourceSessionWrapper::GetDesc()
	{
		const auto result = GetWrappedObjectAs<ID3D12ProtectedResourceSession>()->GetDesc();
		return result;
	}

	// Wrap ID3D12ProtectedResourceSession1
	ID3D12ProtectedResourceSession1Wrapper::ID3D12ProtectedResourceSession1Wrapper(const IID &riid, IUnknown *object)
	: ID3D12ProtectedResourceSessionWrapper(riid, object)
	{

	}

	D3D12_PROTECTED_RESOURCE_SESSION_DESC1 STDMETHODCALLTYPE ID3D12ProtectedResourceSession1Wrapper::GetDesc1()
	{
		const auto result = GetWrappedObjectAs<ID3D12ProtectedResourceSession1>()->GetDesc1();
		return result;
	}

}