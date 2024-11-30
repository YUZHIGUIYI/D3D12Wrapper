//
// Created by ZZK on 2024/11/26.
//

#include <tracer/d3d12/d3d12_lifetime_wrap.h>

namespace gfxshim
{
	// Wrap ID3D12LifetimeOwner
	ID3D12LifetimeOwnerWrapper::ID3D12LifetimeOwnerWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	void STDMETHODCALLTYPE ID3D12LifetimeOwnerWrapper::LifetimeStateUpdated(D3D12_LIFETIME_STATE NewState)
	{
		GetWrappedObjectAs<ID3D12LifetimeOwner>()->LifetimeStateUpdated(NewState);
	}

	// Wrap
	ID3D12LifetimeTrackerWrapper::ID3D12LifetimeTrackerWrapper(const IID &riid, IUnknown *object)
	: ID3D12DeviceChildWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE ID3D12LifetimeTrackerWrapper::DestroyOwnedObject(ID3D12DeviceChild *pObject)
	{
		const auto result = GetWrappedObjectAs<ID3D12LifetimeTracker>()->DestroyOwnedObject(encode::GetWrappedObject<ID3D12DeviceChild>(pObject));
		return result;
	}

}