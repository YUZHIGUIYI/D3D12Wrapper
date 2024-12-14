//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12VirtualizationGuestDeviceWrapper final : ID3D12VirtualizationGuestDevice
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12VirtualizationGuestDeviceWrapper *> s_d3d12_guest_device_manager{};
		inline static std::mutex s_d3d12_guest_device_mutex{};

	public:
		ID3D12VirtualizationGuestDeviceWrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12VirtualizationGuestDeviceWrapper() = default;

		// ID3D12VirtualizationGuestDeviceWrapper manager
		static void InsertD3D12GuestDevice(void *object_key, ID3D12VirtualizationGuestDeviceWrapper *guest_device)
		{
			std::lock_guard guard{ s_d3d12_guest_device_mutex };
			s_d3d12_guest_device_manager[object_key] = guest_device;
		}

		static ID3D12VirtualizationGuestDeviceWrapper *QueryExistingD3D12GuestDevice(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_guest_device_mutex };
			if (s_d3d12_guest_device_manager.contains(object_key))
			{
				return s_d3d12_guest_device_manager[object_key];
			}
			return nullptr;
		}

		// Helper functions
		REFIID GetRiid() const;

		IUnknown *GetWrappedObject();

		const IUnknown *GetWrappedObject() const;

		template <typename T>
		T *GetWrappedObjectAs()
		{
			return reinterpret_cast<T *>(m_object.GetInterfacePtr());
		}

		template <typename T>
		const T *GetWrappedObjectAs() const
		{
			return reinterpret_cast<const T *>(m_object.GetInterfacePtr());
		}

		uint32_t GetRefCount() const;

		// IUnknown
		HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** object) override;

		ULONG STDMETHODCALLTYPE AddRef() override;

		ULONG STDMETHODCALLTYPE Release() override;

		// ID3D12VirtualizationGuestDevice
		HRESULT STDMETHODCALLTYPE ShareWithHost(ID3D12DeviceChild *pObject, HANDLE *pHandle) override;

		HRESULT STDMETHODCALLTYPE CreateFenceFd(ID3D12Fence *pFence, UINT64 FenceValue, int *pFenceFd) override;
	};
}
