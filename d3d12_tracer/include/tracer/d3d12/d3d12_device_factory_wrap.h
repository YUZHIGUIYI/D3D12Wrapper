//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12DeviceFactoryWrapper final : ID3D12DeviceFactory
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12DeviceFactoryWrapper *> s_d3d12_device_factory_manager{};
		inline static std::mutex s_d3d12_device_factory_mutex{};

	public:
		ID3D12DeviceFactoryWrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12DeviceFactoryWrapper() = default;

		// ID3D12DeviceFactoryWrapper manager
		static void InsertD3D12DeviceFactory(void *object_key, ID3D12DeviceFactoryWrapper *device_factory)
		{
			std::lock_guard guard{ s_d3d12_device_factory_mutex };
			s_d3d12_device_factory_manager[object_key] = device_factory;
		}

		static ID3D12DeviceFactoryWrapper *QueryExistingD3D12DeviceFactory(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_device_factory_mutex };
			if (s_d3d12_device_factory_manager.contains(object_key))
			{
				return s_d3d12_device_factory_manager[object_key];
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

		// ID3D12DeviceFactory
		HRESULT STDMETHODCALLTYPE InitializeFromGlobalState() override;

		HRESULT STDMETHODCALLTYPE ApplyToGlobalState() override;

		HRESULT STDMETHODCALLTYPE SetFlags(D3D12_DEVICE_FACTORY_FLAGS flags) override;

		D3D12_DEVICE_FACTORY_FLAGS STDMETHODCALLTYPE GetFlags() override;

		HRESULT STDMETHODCALLTYPE GetConfigurationInterface(REFCLSID clsid, REFIID iid, void** ppv) override;

		HRESULT STDMETHODCALLTYPE EnableExperimentalFeatures(
											UINT NumFeatures,
											const IID* pIIDs,
											void* pConfigurationStructs,
											UINT* pConfigurationStructSizes) override;

		HRESULT STDMETHODCALLTYPE CreateDevice(
											IUnknown* adapter,
											D3D_FEATURE_LEVEL FeatureLevel,
											REFIID riid,
											void** ppvDevice) override;
	};
}
