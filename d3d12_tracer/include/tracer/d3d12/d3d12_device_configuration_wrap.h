//
// Created by ZZK on 2024/11/30.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12DeviceConfiguration1Wrapper final : ID3D12DeviceConfiguration1
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12DeviceConfiguration1Wrapper *> s_d3d12_device_configuration1_manager{};
		inline static std::mutex s_d3d12_device_configuration1_mutex{};

	public:
		ID3D12DeviceConfiguration1Wrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12DeviceConfiguration1Wrapper() = default;

		// ID3D12DeviceConfiguration1Wrapper manager
		static void InsertD3D12DeviceConfiguration1(void *object_key, ID3D12DeviceConfiguration1Wrapper *device_configuration1)
		{
			std::lock_guard guard{ s_d3d12_device_configuration1_mutex };
			s_d3d12_device_configuration1_manager[object_key] = device_configuration1;
		}

		static ID3D12DeviceConfiguration1Wrapper *QueryExistingD3D12DeviceConfiguration1(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_device_configuration1_mutex };
			if (s_d3d12_device_configuration1_manager.contains(object_key))
			{
				return s_d3d12_device_configuration1_manager[object_key];
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

		// ID3D12DeviceConfiguration
		D3D12_DEVICE_CONFIGURATION_DESC STDMETHODCALLTYPE GetDesc() override;

		HRESULT STDMETHODCALLTYPE GetEnabledExperimentalFeatures(GUID* pGuids, UINT NumGuids) override;

		HRESULT STDMETHODCALLTYPE SerializeVersionedRootSignature(
						const D3D12_VERSIONED_ROOT_SIGNATURE_DESC* pDesc,
						ID3DBlob** ppResult,
						ID3DBlob** ppError) override;

		HRESULT STDMETHODCALLTYPE CreateVersionedRootSignatureDeserializer(
						const void* pBlob,
						SIZE_T Size,
						REFIID riid,
						void** ppvDeserializer) override;

		// ID3D12DeviceConfiguration1
		HRESULT STDMETHODCALLTYPE CreateVersionedRootSignatureDeserializerFromSubobjectInLibrary(
						const void *pLibraryBlob,
						SIZE_T Size,
						LPCWSTR RootSignatureSubobjectName,
						REFIID riid,
						void **ppvDeserializer) override;
	};
}
