//
// Created by ZZK on 2024/11/25.
//

#include <tracer/d3d12/d3d12_guest_device_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	ID3D12VirtualizationGuestDeviceWrapper::ID3D12VirtualizationGuestDeviceWrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12VirtualizationGuestDeviceWrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12VirtualizationGuestDeviceWrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12VirtualizationGuestDeviceWrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12VirtualizationGuestDeviceWrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12VirtualizationGuestDeviceWrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12VirtualizationGuestDeviceWrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12VirtualizationGuestDeviceWrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12VirtualizationGuestDeviceWrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12VirtualizationGuestDevice
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