//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12LifetimeOwnerWrapper : IUnknownWrapper
	{
	public:
		ID3D12LifetimeOwnerWrapper(REFIID riid, IUnknown *object);

		~ID3D12LifetimeOwnerWrapper() override = default;

		virtual void STDMETHODCALLTYPE LifetimeStateUpdated(D3D12_LIFETIME_STATE NewState);
	};

	struct ID3D12LifetimeTrackerWrapper : ID3D12DeviceChildWrapper
	{
	public:
		ID3D12LifetimeTrackerWrapper(REFIID riid, IUnknown *object);

		~ID3D12LifetimeTrackerWrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE DestroyOwnedObject(ID3D12DeviceChild* pObject);
	};
}
