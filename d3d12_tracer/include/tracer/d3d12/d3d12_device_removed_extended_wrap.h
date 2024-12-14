//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12DeviceRemovedExtendedDataSettingsWrapper : IUnknownWrapper
	{
	public:
		ID3D12DeviceRemovedExtendedDataSettingsWrapper(REFIID riid, IUnknown *object);

		~ID3D12DeviceRemovedExtendedDataSettingsWrapper() override = default;

		virtual void STDMETHODCALLTYPE SetAutoBreadcrumbsEnablement(D3D12_DRED_ENABLEMENT Enablement);

		virtual void STDMETHODCALLTYPE SetPageFaultEnablement(D3D12_DRED_ENABLEMENT Enablement);

		virtual void STDMETHODCALLTYPE SetWatsonDumpEnablement(D3D12_DRED_ENABLEMENT Enablement);
	};

	struct ID3D12DeviceRemovedExtendedDataSettings1Wrapper : ID3D12DeviceRemovedExtendedDataSettingsWrapper
	{
	public:
		ID3D12DeviceRemovedExtendedDataSettings1Wrapper(REFIID riid, IUnknown *object);

		~ID3D12DeviceRemovedExtendedDataSettings1Wrapper() override = default;

		virtual void STDMETHODCALLTYPE SetBreadcrumbContextEnablement(D3D12_DRED_ENABLEMENT Enablement);
	};

	struct ID3D12DeviceRemovedExtendedDataSettings2Wrapper final : ID3D12DeviceRemovedExtendedDataSettings2
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12DeviceRemovedExtendedDataSettings2Wrapper *> s_d3d12_device_removed_settings2_manager{};
		inline static std::mutex s_d3d12_device_removed_settings2_mutex{};

	public:
		ID3D12DeviceRemovedExtendedDataSettings2Wrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12DeviceRemovedExtendedDataSettings2Wrapper() = default;

		// ID3D12DeviceRemovedExtendedDataSettings2Wrapper manager
		static void InsertD3D12DeviceRemovedSettings2(void *object_key, ID3D12DeviceRemovedExtendedDataSettings2Wrapper *device_removed_settings2)
		{
			std::lock_guard guard{ s_d3d12_device_removed_settings2_mutex };
			s_d3d12_device_removed_settings2_manager[object_key] = device_removed_settings2;
		}

		static ID3D12DeviceRemovedExtendedDataSettings2Wrapper *QueryExistingD3D12DeviceRemovedSettings2(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_device_removed_settings2_mutex };
			if (s_d3d12_device_removed_settings2_manager.contains(object_key))
			{
				return s_d3d12_device_removed_settings2_manager[object_key];
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

		// ID3D12DeviceRemovedExtendedDataSettings
		void STDMETHODCALLTYPE SetAutoBreadcrumbsEnablement(D3D12_DRED_ENABLEMENT Enablement) override;

		void STDMETHODCALLTYPE SetPageFaultEnablement(D3D12_DRED_ENABLEMENT Enablement) override;

		void STDMETHODCALLTYPE SetWatsonDumpEnablement(D3D12_DRED_ENABLEMENT Enablement) override;

		// ID3D12DeviceRemovedExtendedDataSettings1
		void STDMETHODCALLTYPE SetBreadcrumbContextEnablement(D3D12_DRED_ENABLEMENT Enablement) override;

		// ID3D12DeviceRemovedExtendedDataSettings2
		void STDMETHODCALLTYPE UseMarkersOnlyAutoBreadcrumbs(BOOL MarkersOnly) override;
	};

	struct ID3D12DeviceRemovedExtendedDataWrapper : IUnknownWrapper
	{
	public:
		ID3D12DeviceRemovedExtendedDataWrapper(REFIID riid, IUnknown *object);

		~ID3D12DeviceRemovedExtendedDataWrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE GetAutoBreadcrumbsOutput(D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT* pOutput);

		virtual HRESULT STDMETHODCALLTYPE GetPageFaultAllocationOutput(D3D12_DRED_PAGE_FAULT_OUTPUT* pOutput);
	};

	struct ID3D12DeviceRemovedExtendedData1Wrapper : ID3D12DeviceRemovedExtendedDataWrapper
	{
	public:
		ID3D12DeviceRemovedExtendedData1Wrapper(REFIID riid, IUnknown *object);

		~ID3D12DeviceRemovedExtendedData1Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE GetAutoBreadcrumbsOutput1(D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT1* pOutput);

		virtual HRESULT STDMETHODCALLTYPE GetPageFaultAllocationOutput1(D3D12_DRED_PAGE_FAULT_OUTPUT1* pOutput);
	};

	struct ID3D12DeviceRemovedExtendedData2Wrapper final : ID3D12DeviceRemovedExtendedData2
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12DeviceRemovedExtendedData2Wrapper *> s_d3d12_device_removed_data2_manager{};
		inline static std::mutex s_d3d12_device_removed_data2_mutex{};

	public:
		ID3D12DeviceRemovedExtendedData2Wrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12DeviceRemovedExtendedData2Wrapper() = default;

		// ID3D12DeviceRemovedExtendedData2Wrapper manager
		static void InsertD3D12DeviceRemovedData2(void *object_key, ID3D12DeviceRemovedExtendedData2Wrapper *device_removed_data2)
		{
			std::lock_guard guard{ s_d3d12_device_removed_data2_mutex };
			s_d3d12_device_removed_data2_manager[object_key] = device_removed_data2;
		}

		static ID3D12DeviceRemovedExtendedData2Wrapper *QueryExistingD3D12DeviceRemovedData2(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_device_removed_data2_mutex };
			if (s_d3d12_device_removed_data2_manager.contains(object_key))
			{
				return s_d3d12_device_removed_data2_manager[object_key];
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

		// ID3D12DeviceRemovedExtendedData
		HRESULT STDMETHODCALLTYPE GetAutoBreadcrumbsOutput(D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT* pOutput) override;

		HRESULT STDMETHODCALLTYPE GetPageFaultAllocationOutput(D3D12_DRED_PAGE_FAULT_OUTPUT* pOutput) override;

		// ID3D12DeviceRemovedExtendedData1
		HRESULT STDMETHODCALLTYPE GetAutoBreadcrumbsOutput1(D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT1* pOutput) override;

		HRESULT STDMETHODCALLTYPE GetPageFaultAllocationOutput1(D3D12_DRED_PAGE_FAULT_OUTPUT1* pOutput) override;

		// ID3D12DeviceRemovedExtendedData2
		HRESULT STDMETHODCALLTYPE GetPageFaultAllocationOutput2(D3D12_DRED_PAGE_FAULT_OUTPUT2* pOutput) override;

		D3D12_DRED_DEVICE_STATE STDMETHODCALLTYPE GetDeviceState() override;
	};
}
