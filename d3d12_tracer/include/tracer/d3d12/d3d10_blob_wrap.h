//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	// New wrapped ID3D10Blob
	struct ID3D10BlobWrapper final : ID3D10Blob
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D10BlobWrapper *> s_d310_blob_manager{};
		inline static std::mutex s_d3d10_blob_mutex{};

	public:
		ID3D10BlobWrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D10BlobWrapper() = default;

		// ID3D10BlobWrapper manager
		static void InsertD3D10Blob(void *object_key, ID3D10BlobWrapper *output)
		{
			std::lock_guard guard{ s_d3d10_blob_mutex };
			s_d310_blob_manager[object_key] = output;
		}

		static ID3D10BlobWrapper *QueryExistingD3D10Blob(void *object_key)
		{
			std::lock_guard guard{ s_d3d10_blob_mutex };
			if (s_d310_blob_manager.contains(object_key))
			{
				return s_d310_blob_manager[object_key];
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

		// ID3D10Blob
		LPVOID STDMETHODCALLTYPE GetBufferPointer() override;

		SIZE_T STDMETHODCALLTYPE GetBufferSize() override;
	};
}
