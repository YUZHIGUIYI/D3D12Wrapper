//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12SharingContractWrapper final : ID3D12SharingContract
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12SharingContractWrapper *> s_d3d12_sharing_contract_manager{};
		inline static std::mutex s_d3d12_sharing_contract_mutex{};

	public:
		ID3D12SharingContractWrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12SharingContractWrapper() = default;

		// ID3D12SharingContractWrapper manager
		static void InsertD3D12SharingContract(void *object_key, ID3D12SharingContractWrapper *sharing_contract)
		{
			std::lock_guard guard{ s_d3d12_sharing_contract_mutex };
			s_d3d12_sharing_contract_manager[object_key] = sharing_contract;
		}

		static ID3D12SharingContractWrapper *QueryExistingD3D12SharingContract(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_sharing_contract_mutex };
			if (s_d3d12_sharing_contract_manager.contains(object_key))
			{
				return s_d3d12_sharing_contract_manager[object_key];
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

		// ID3D12SharingContract
		void STDMETHODCALLTYPE Present(ID3D12Resource *pResource, UINT Subresource, HWND window) override;

		void STDMETHODCALLTYPE SharedFenceSignal(ID3D12Fence *pFence, UINT64 FenceValue) override;

		void STDMETHODCALLTYPE BeginCapturableWork(REFGUID guid) override;

		void STDMETHODCALLTYPE EndCapturableWork(REFGUID guid) override;
	};

	struct ID3D12ManualWriteTrackingResourceWrapper final : ID3D12ManualWriteTrackingResource
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12ManualWriteTrackingResourceWrapper *> s_d3d12_manual_resource_manager{};
		inline static std::mutex s_d3d12_manual_resource_mutex{};

	public:
		ID3D12ManualWriteTrackingResourceWrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12ManualWriteTrackingResourceWrapper() = default;

		// ID3D12ManualWriteTrackingResourceWrapper manager
		static void InsertD3D12ManualResource(void *object_key, ID3D12ManualWriteTrackingResourceWrapper *manual_write_tracking_resource)
		{
			std::lock_guard guard{ s_d3d12_manual_resource_mutex };
			s_d3d12_manual_resource_manager[object_key] = manual_write_tracking_resource;
		}

		static ID3D12ManualWriteTrackingResourceWrapper *QueryExistingD3D12ManualResource(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_manual_resource_mutex };
			if (s_d3d12_manual_resource_manager.contains(object_key))
			{
				return s_d3d12_manual_resource_manager[object_key];
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

		// ID3D12ManualWriteTrackingResource
		void STDMETHODCALLTYPE TrackWrite(UINT Subresource, const D3D12_RANGE *pWrittenRange) override;
	};
}
