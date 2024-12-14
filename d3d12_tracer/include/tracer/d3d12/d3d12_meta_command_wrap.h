//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12MetaCommandWrapper final : ID3D12MetaCommand
	{
		private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12MetaCommandWrapper *> s_d3d12_meta_command_manager{};
		inline static std::mutex s_d3d12_meta_command_mutex{};

	public:
		ID3D12MetaCommandWrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12MetaCommandWrapper() = default;

		// ID3D12MetaCommandWrapper manager
		static void InsertD3D12MetaCommand(void *object_key, ID3D12MetaCommandWrapper *meta_command)
		{
			std::lock_guard guard{ s_d3d12_meta_command_mutex };
			s_d3d12_meta_command_manager[object_key] = meta_command;
		}

		static ID3D12MetaCommandWrapper *QueryExistingD3D12MetaCommand(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_meta_command_mutex };
			if (s_d3d12_meta_command_manager.contains(object_key))
			{
				return s_d3d12_meta_command_manager[object_key];
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

		// ID3D12MetaCommand
		virtual UINT64 STDMETHODCALLTYPE GetRequiredParameterResourceSize(D3D12_META_COMMAND_PARAMETER_STAGE Stage, UINT ParameterIndex);
	};
}