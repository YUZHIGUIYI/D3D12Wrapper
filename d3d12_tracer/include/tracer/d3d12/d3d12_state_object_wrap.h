//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12StateObjectWrapper final : ID3D12StateObject
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12StateObjectWrapper *> s_d3d12_state_object_manager{};
		inline static std::mutex s_d3d12_state_object_mutex{};

	public:
		ID3D12StateObjectWrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12StateObjectWrapper() = default;

		// ID3D12StateObjectWrapper manager
		static void InsertD3D12StateObject(void *object_key, ID3D12StateObjectWrapper *state_object)
		{
			std::lock_guard guard{ s_d3d12_state_object_mutex };
			s_d3d12_state_object_manager[object_key] = state_object;
		}

		static ID3D12StateObjectWrapper *QueryExistingD3D12StateObject(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_state_object_mutex };
			if (s_d3d12_state_object_manager.contains(object_key))
			{
				return s_d3d12_state_object_manager[object_key];
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

	struct ID3D12StateObjectProperties1Wrapper final : ID3D12StateObjectProperties1
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12StateObjectProperties1Wrapper *> s_d3d12_state_object_properties1_manager{};
		inline static std::mutex s_d3d12_state_object_properties1_mutex{};

	public:
		ID3D12StateObjectProperties1Wrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12StateObjectProperties1Wrapper() = default;

		// ID3D12StateObjectProperties1Wrapper manager
		static void InsertD3D12StateObjectProperties1(void *object_key, ID3D12StateObjectProperties1Wrapper *state_object_properties1)
		{
			std::lock_guard guard{ s_d3d12_state_object_properties1_mutex };
			s_d3d12_state_object_properties1_manager[object_key] = state_object_properties1;
		}

		static ID3D12StateObjectProperties1Wrapper *QueryExistingD3D12StateObjectProperties1(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_state_object_properties1_mutex };
			if (s_d3d12_state_object_properties1_manager.contains(object_key))
			{
				return s_d3d12_state_object_properties1_manager[object_key];
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

		// ID3D12StateObjectProperties
		void* STDMETHODCALLTYPE GetShaderIdentifier(LPCWSTR pExportName) override;

		UINT64 STDMETHODCALLTYPE GetShaderStackSize(LPCWSTR pExportName) override;

		UINT64 STDMETHODCALLTYPE GetPipelineStackSize() override;

		void STDMETHODCALLTYPE SetPipelineStackSize(UINT64 PipelineStackSizeInBytes) override;

		// ID3D12StateObjectProperties1
		D3D12_PROGRAM_IDENTIFIER STDMETHODCALLTYPE GetProgramIdentifier(LPCWSTR pProgramName) override;
	};
}
