//
// Created by ZZK on 2024/11/30.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3DDestructionNotifierWrapper final : ID3DDestructionNotifier
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3DDestructionNotifierWrapper *> s_d3d12_destruction_notifier_manager{};
		inline static std::mutex s_d3d12_destruction_notifier_mutex{};

	public:
		ID3DDestructionNotifierWrapper(REFIID riid, IUnknown *object);

		virtual ~ID3DDestructionNotifierWrapper() = default;

		// ID3DDestructionNotifierWrapper manager
		static void InsertD3D12DestructionNotifier(void *object_key, ID3DDestructionNotifierWrapper *destruction_notifier)
		{
			std::lock_guard guard{ s_d3d12_destruction_notifier_mutex };
			s_d3d12_destruction_notifier_manager[object_key] = destruction_notifier;
		}

		static ID3DDestructionNotifierWrapper *QueryExistingD3D12DestructionNotifier(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_destruction_notifier_mutex };
			if (s_d3d12_destruction_notifier_manager.contains(object_key))
			{
				return s_d3d12_destruction_notifier_manager[object_key];
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

		// ID3DDestructionNotifier
		HRESULT STDMETHODCALLTYPE RegisterDestructionCallback(PFN_DESTRUCTION_CALLBACK callbackFn, void *pData,
															  UINT *pCallbackID) override;

		HRESULT STDMETHODCALLTYPE UnregisterDestructionCallback(UINT callbackID) override;
	};
}
