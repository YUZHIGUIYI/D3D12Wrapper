//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12SwapChainAssistantWrapper final : ID3D12SwapChainAssistant
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12SwapChainAssistantWrapper *> s_d3d12_swap_chain_assistant_manager{};
		inline static std::mutex s_d3d12_swap_chain_assistant_mutex{};

	public:
		ID3D12SwapChainAssistantWrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12SwapChainAssistantWrapper() = default;

		// ID3D12SwapChainAssistantWrapper manager
		static void InsertD3D12SwapChainAssistant(void *object_key, ID3D12SwapChainAssistantWrapper *swap_chain_assistant)
		{
			std::lock_guard guard{ s_d3d12_swap_chain_assistant_mutex };
			s_d3d12_swap_chain_assistant_manager[object_key] = swap_chain_assistant;
		}

		static ID3D12SwapChainAssistantWrapper *QueryExistingD3D12SwapChainAssistant(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_swap_chain_assistant_mutex };
			if (s_d3d12_swap_chain_assistant_manager.contains(object_key))
			{
				return s_d3d12_swap_chain_assistant_manager[object_key];
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

		// ID3D12SwapChainAssistant
		LUID STDMETHODCALLTYPE GetLUID() override;

		HRESULT STDMETHODCALLTYPE GetSwapChainObject(REFIID riid, void **ppv) override;

		HRESULT STDMETHODCALLTYPE GetCurrentResourceAndCommandQueue(REFIID riidResource, void **ppvResource,
																	REFIID riidQueue, void **ppvQueue) override;

		HRESULT STDMETHODCALLTYPE InsertImplicitSync() override;
	};
}
