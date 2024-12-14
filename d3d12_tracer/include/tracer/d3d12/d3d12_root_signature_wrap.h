//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12RootSignatureWrapper final : ID3D12RootSignature
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12RootSignatureWrapper *> s_d3d12_root_signature_manager{};
		inline static std::mutex s_d3d12_root_signature_mutex{};

	public:
		ID3D12RootSignatureWrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12RootSignatureWrapper() = default;

		// ID3D12RootSignatureWrapper manager
		static void InsertD3D12RootSignature(void *object_key, ID3D12RootSignatureWrapper *root_signature)
		{
			std::lock_guard guard{ s_d3d12_root_signature_mutex };
			s_d3d12_root_signature_manager[object_key] = root_signature;
		}

		static ID3D12RootSignatureWrapper *QueryExistingD3D12RootSignature(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_root_signature_mutex };
			if (s_d3d12_root_signature_manager.contains(object_key))
			{
				return s_d3d12_root_signature_manager[object_key];
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
	};

	struct ID3D12RootSignatureDeserializerWrapper final : ID3D12RootSignatureDeserializer
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12RootSignatureDeserializerWrapper *> s_d3d12_root_signature_deserializer_manager{};
		inline static std::mutex s_d3d12_root_signature_deserializer_mutex{};

	public:
		ID3D12RootSignatureDeserializerWrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12RootSignatureDeserializerWrapper() = default;

		// ID3D12RootSignatureDeserializerWrapper manager
		static void InsertD3D12RootSignatureDeserializer(void *object_key, ID3D12RootSignatureDeserializerWrapper *root_signature_deserializer)
		{
			std::lock_guard guard{ s_d3d12_root_signature_deserializer_mutex };
			s_d3d12_root_signature_deserializer_manager[object_key] = root_signature_deserializer;
		}

		static ID3D12RootSignatureDeserializerWrapper *QueryExistingD3D12RootSignatureDeserializer(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_root_signature_deserializer_mutex };
			if (s_d3d12_root_signature_deserializer_manager.contains(object_key))
			{
				return s_d3d12_root_signature_deserializer_manager[object_key];
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

		// ID3D12RootSignatureDeserializer
		const D3D12_ROOT_SIGNATURE_DESC *STDMETHODCALLTYPE GetRootSignatureDesc() override;
	};

	struct ID3D12VersionedRootSignatureDeserializerWrapper final : ID3D12VersionedRootSignatureDeserializer
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12VersionedRootSignatureDeserializerWrapper *> s_d3d12_versioned_root_signature_deserializer_manager{};
		inline static std::mutex s_d3d12_versioned_root_signature_deserializer_mutex{};

	public:
		ID3D12VersionedRootSignatureDeserializerWrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12VersionedRootSignatureDeserializerWrapper() = default;

		// ID3D12VersionedRootSignatureDeserializerWrapper manager
		static void InsertD3D12VersionedRootSignatureDeserializer(void *object_key, ID3D12VersionedRootSignatureDeserializerWrapper *root_signature_deserializer)
		{
			std::lock_guard guard{ s_d3d12_versioned_root_signature_deserializer_mutex };
			s_d3d12_versioned_root_signature_deserializer_manager[object_key] = root_signature_deserializer;
		}

		static ID3D12VersionedRootSignatureDeserializerWrapper *QueryExistingD3D12VersionedRootSignatureDeserializer(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_versioned_root_signature_deserializer_mutex };
			if (s_d3d12_versioned_root_signature_deserializer_manager.contains(object_key))
			{
				return s_d3d12_versioned_root_signature_deserializer_manager[object_key];
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

		// ID3D12VersionedRootSignatureDeserializer
		HRESULT STDMETHODCALLTYPE GetRootSignatureDescAtVersion(D3D_ROOT_SIGNATURE_VERSION convertToVersion,
																		const D3D12_VERSIONED_ROOT_SIGNATURE_DESC** ppDesc) override;

		const D3D12_VERSIONED_ROOT_SIGNATURE_DESC *STDMETHODCALLTYPE GetUnconvertedRootSignatureDesc() override;
	};
}
