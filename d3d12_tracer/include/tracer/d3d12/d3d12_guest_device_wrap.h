//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12VirtualizationGuestDeviceWrapper : IUnknownWrapper
	{
	public:
		ID3D12VirtualizationGuestDeviceWrapper(REFIID riid, IUnknown *object);

		~ID3D12VirtualizationGuestDeviceWrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE ShareWithHost(ID3D12DeviceChild* pObject, HANDLE* pHandle);

		virtual HRESULT STDMETHODCALLTYPE CreateFenceFd(ID3D12Fence* pFence, UINT64 FenceValue, int* pFenceFd);
	};
}
