//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12LifetimeOwnerWrapper final : ID3D12LifetimeOwner
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12LifetimeOwnerWrapper *> s_d3d12_lifetime_owner_manager{};
		inline static std::mutex s_d3d12_lifetime_owner_mutex{};

	public:
		ID3D12LifetimeOwnerWrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12LifetimeOwnerWrapper() = default;

		// ID3D12LifetimeOwnerWrapper manager
		static void InsertD3D12LifetimeOwner(void *object_key, ID3D12LifetimeOwnerWrapper *lifetime_owner)
		{
			std::lock_guard guard{ s_d3d12_lifetime_owner_mutex };
			s_d3d12_lifetime_owner_manager[object_key] = lifetime_owner;
		}

		static ID3D12LifetimeOwnerWrapper *QueryExistingD3D12LifetimeOwner(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_lifetime_owner_mutex };
			if (s_d3d12_lifetime_owner_manager.contains(object_key))
			{
				return s_d3d12_lifetime_owner_manager[object_key];
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

		// ID3D12LifetimeOwner
		virtual void STDMETHODCALLTYPE LifetimeStateUpdated(D3D12_LIFETIME_STATE NewState);
	};

	struct ID3D12LifetimeTrackerWrapper final : ID3D12LifetimeTracker
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12LifetimeTrackerWrapper *> s_d3d12_lifetime_tracer_manager{};
		inline static std::mutex s_d3d12_lifetime_tracer_mutex{};

	public:
		ID3D12LifetimeTrackerWrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12LifetimeTrackerWrapper() = default;

		// ID3D12LifetimeTrackerWrapper manager
		static void InsertD3D12LifetimeTracer(void *object_key, ID3D12LifetimeTrackerWrapper *lifetime_tracker)
		{
			std::lock_guard guard{ s_d3d12_lifetime_tracer_mutex };
			s_d3d12_lifetime_tracer_manager[object_key] = lifetime_tracker;
		}

		static ID3D12LifetimeTrackerWrapper *QueryExistingD3D12LifetimeTracer(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_lifetime_tracer_mutex };
			if (s_d3d12_lifetime_tracer_manager.contains(object_key))
			{
				return s_d3d12_lifetime_tracer_manager[object_key];
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

		// ID3D12Object
		HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID guid, UINT* pDataSize, void* pData) override;

		HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID guid, UINT DataSize, const void* pData) override;

		HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID guid, const IUnknown* pData) override;

		HRESULT STDMETHODCALLTYPE SetName(LPCWSTR Name) override;

		// ID3D12DeviceChild
		HRESULT STDMETHODCALLTYPE GetDevice(REFIID riid, void** ppvDevice) override;

		// ID3D12LifetimeTracker
		virtual HRESULT STDMETHODCALLTYPE DestroyOwnedObject(ID3D12DeviceChild* pObject);
	};
}
