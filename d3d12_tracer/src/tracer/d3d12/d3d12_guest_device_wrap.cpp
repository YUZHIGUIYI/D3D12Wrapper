//
// Created by ZZK on 2024/11/25.
//

#include <tracer/d3d12/d3d12_guest_device_wrap.h>

namespace gfxshim
{
	ID3D12VirtualizationGuestDeviceWrapper::ID3D12VirtualizationGuestDeviceWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE ID3D12VirtualizationGuestDeviceWrapper::ShareWithHost(ID3D12DeviceChild *pObject, HANDLE *pHandle)
	{
		const auto result = GetWrappedObjectAs<ID3D12VirtualizationGuestDevice>()->ShareWithHost(encode::GetWrappedObject<ID3D12DeviceChild>(pObject), pHandle);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12VirtualizationGuestDeviceWrapper::CreateFenceFd(ID3D12Fence *pFence, UINT64 FenceValue, int *pFenceFd)
	{
		const auto result = GetWrappedObjectAs<ID3D12VirtualizationGuestDevice>()->CreateFenceFd(encode::GetWrappedObject<ID3D12Fence>(pFence), FenceValue, pFenceFd);
		return result;
	}

}