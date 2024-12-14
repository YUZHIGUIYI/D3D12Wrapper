//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12InfoQueueWrapper : IUnknownWrapper
	{
	public:
		ID3D12InfoQueueWrapper(REFIID riid, IUnknown *object);

		~ID3D12InfoQueueWrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE SetMessageCountLimit(UINT64 MessageCountLimit);

		virtual void STDMETHODCALLTYPE ClearStoredMessages();

		virtual HRESULT STDMETHODCALLTYPE GetMessage(
										UINT64 MessageIndex,
										D3D12_MESSAGE* pMessage,
										SIZE_T* pMessageByteLength);

		virtual UINT64 STDMETHODCALLTYPE GetNumMessagesAllowedByStorageFilter();

		virtual UINT64 STDMETHODCALLTYPE GetNumMessagesDeniedByStorageFilter();

		virtual UINT64 STDMETHODCALLTYPE GetNumStoredMessages();

		virtual UINT64 STDMETHODCALLTYPE GetNumStoredMessagesAllowedByRetrievalFilter();

		virtual UINT64 STDMETHODCALLTYPE GetNumMessagesDiscardedByMessageCountLimit();

		virtual UINT64 STDMETHODCALLTYPE GetMessageCountLimit();

		virtual HRESULT STDMETHODCALLTYPE AddStorageFilterEntries(D3D12_INFO_QUEUE_FILTER* pFilter);

		virtual HRESULT STDMETHODCALLTYPE GetStorageFilter(D3D12_INFO_QUEUE_FILTER* pFilter, SIZE_T* pFilterByteLength);

		virtual void STDMETHODCALLTYPE ClearStorageFilter();

		virtual HRESULT STDMETHODCALLTYPE PushEmptyStorageFilter();

		virtual HRESULT STDMETHODCALLTYPE PushCopyOfStorageFilter();

		virtual HRESULT STDMETHODCALLTYPE PushStorageFilter(D3D12_INFO_QUEUE_FILTER* pFilter);

		virtual void STDMETHODCALLTYPE PopStorageFilter();

		virtual UINT STDMETHODCALLTYPE GetStorageFilterStackSize();

		virtual HRESULT STDMETHODCALLTYPE AddRetrievalFilterEntries(D3D12_INFO_QUEUE_FILTER* pFilter);

		virtual HRESULT STDMETHODCALLTYPE GetRetrievalFilter(D3D12_INFO_QUEUE_FILTER* pFilter, SIZE_T* pFilterByteLength);

		virtual void STDMETHODCALLTYPE ClearRetrievalFilter();

		virtual HRESULT STDMETHODCALLTYPE PushEmptyRetrievalFilter();

		virtual HRESULT STDMETHODCALLTYPE PushCopyOfRetrievalFilter();

		virtual HRESULT STDMETHODCALLTYPE PushRetrievalFilter(D3D12_INFO_QUEUE_FILTER* pFilter);

		virtual void STDMETHODCALLTYPE PopRetrievalFilter();

		virtual UINT STDMETHODCALLTYPE GetRetrievalFilterStackSize();

		virtual HRESULT STDMETHODCALLTYPE AddMessage(
								D3D12_MESSAGE_CATEGORY Category,
								D3D12_MESSAGE_SEVERITY Severity,
								D3D12_MESSAGE_ID ID,
								LPCSTR pDescription);

		virtual HRESULT STDMETHODCALLTYPE AddApplicationMessage(
						D3D12_MESSAGE_SEVERITY Severity,
						LPCSTR pDescription);

		virtual HRESULT STDMETHODCALLTYPE SetBreakOnCategory(
						D3D12_MESSAGE_CATEGORY Category,
						BOOL bEnable);

		virtual HRESULT STDMETHODCALLTYPE SetBreakOnSeverity(
						D3D12_MESSAGE_SEVERITY Severity,
						BOOL bEnable);

		virtual HRESULT STDMETHODCALLTYPE SetBreakOnID(
						D3D12_MESSAGE_ID ID,
						BOOL bEnable);

		virtual BOOL STDMETHODCALLTYPE GetBreakOnCategory(D3D12_MESSAGE_CATEGORY Category);

		virtual BOOL STDMETHODCALLTYPE GetBreakOnSeverity(D3D12_MESSAGE_SEVERITY Severity);

		virtual BOOL STDMETHODCALLTYPE GetBreakOnID(D3D12_MESSAGE_ID ID);

		virtual void STDMETHODCALLTYPE SetMuteDebugOutput(BOOL bMute);

		virtual BOOL STDMETHODCALLTYPE GetMuteDebugOutput();
	};

	struct ID3D12InfoQueue1Wrapper final : ID3D12InfoQueue1
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12InfoQueue1Wrapper *> s_d3d12_info_queue1_manager{};
		inline static std::mutex s_d3d12_info_queue1_mutex{};

	public:
		ID3D12InfoQueue1Wrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12InfoQueue1Wrapper() = default;

		// ID3D12InfoQueue1Wrapper manager
		static void InsertD3D12InfoQueue1(void *object_key, ID3D12InfoQueue1Wrapper *info_queue1)
		{
			std::lock_guard guard{ s_d3d12_info_queue1_mutex };
			s_d3d12_info_queue1_manager[object_key] = info_queue1;
		}

		static ID3D12InfoQueue1Wrapper *QueryExistingD3D12InfoQueue1(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_info_queue1_mutex };
			if (s_d3d12_info_queue1_manager.contains(object_key))
			{
				return s_d3d12_info_queue1_manager[object_key];
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

		// ID3D12InfoQueue
		HRESULT STDMETHODCALLTYPE SetMessageCountLimit(UINT64 MessageCountLimit) override;

		void STDMETHODCALLTYPE ClearStoredMessages() override;

		HRESULT STDMETHODCALLTYPE GetMessage(UINT64 MessageIndex,
											D3D12_MESSAGE* pMessage,
											SIZE_T* pMessageByteLength) override;

		UINT64 STDMETHODCALLTYPE GetNumMessagesAllowedByStorageFilter() override;

		UINT64 STDMETHODCALLTYPE GetNumMessagesDeniedByStorageFilter() override;

		UINT64 STDMETHODCALLTYPE GetNumStoredMessages() override;

		UINT64 STDMETHODCALLTYPE GetNumStoredMessagesAllowedByRetrievalFilter() override;

		UINT64 STDMETHODCALLTYPE GetNumMessagesDiscardedByMessageCountLimit() override;

		UINT64 STDMETHODCALLTYPE GetMessageCountLimit() override;

		HRESULT STDMETHODCALLTYPE AddStorageFilterEntries(D3D12_INFO_QUEUE_FILTER* pFilter) override;

		HRESULT STDMETHODCALLTYPE GetStorageFilter(D3D12_INFO_QUEUE_FILTER* pFilter, SIZE_T* pFilterByteLength) override;

		void STDMETHODCALLTYPE ClearStorageFilter() override;

		HRESULT STDMETHODCALLTYPE PushEmptyStorageFilter() override;

		HRESULT STDMETHODCALLTYPE PushCopyOfStorageFilter() override;

		HRESULT STDMETHODCALLTYPE PushStorageFilter(D3D12_INFO_QUEUE_FILTER* pFilter) override;

		void STDMETHODCALLTYPE PopStorageFilter() override;

		UINT STDMETHODCALLTYPE GetStorageFilterStackSize() override;

		HRESULT STDMETHODCALLTYPE AddRetrievalFilterEntries(D3D12_INFO_QUEUE_FILTER* pFilter) override;

		HRESULT STDMETHODCALLTYPE GetRetrievalFilter(D3D12_INFO_QUEUE_FILTER* pFilter, SIZE_T* pFilterByteLength) override;

		void STDMETHODCALLTYPE ClearRetrievalFilter() override;

		HRESULT STDMETHODCALLTYPE PushEmptyRetrievalFilter() override;

		HRESULT STDMETHODCALLTYPE PushCopyOfRetrievalFilter() override;

		HRESULT STDMETHODCALLTYPE PushRetrievalFilter(D3D12_INFO_QUEUE_FILTER* pFilter) override;

		void STDMETHODCALLTYPE PopRetrievalFilter() override;

		UINT STDMETHODCALLTYPE GetRetrievalFilterStackSize() override;

		HRESULT STDMETHODCALLTYPE AddMessage(
								D3D12_MESSAGE_CATEGORY Category,
								D3D12_MESSAGE_SEVERITY Severity,
								D3D12_MESSAGE_ID ID,
								LPCSTR pDescription) override;

		HRESULT STDMETHODCALLTYPE AddApplicationMessage(
						D3D12_MESSAGE_SEVERITY Severity,
						LPCSTR pDescription) override;

		HRESULT STDMETHODCALLTYPE SetBreakOnCategory(
						D3D12_MESSAGE_CATEGORY Category,
						BOOL bEnable) override;

		HRESULT STDMETHODCALLTYPE SetBreakOnSeverity(
						D3D12_MESSAGE_SEVERITY Severity,
						BOOL bEnable) override;

		HRESULT STDMETHODCALLTYPE SetBreakOnID(
						D3D12_MESSAGE_ID ID,
						BOOL bEnable) override;

		BOOL STDMETHODCALLTYPE GetBreakOnCategory(D3D12_MESSAGE_CATEGORY Category) override;

		BOOL STDMETHODCALLTYPE GetBreakOnSeverity(D3D12_MESSAGE_SEVERITY Severity) override;

		BOOL STDMETHODCALLTYPE GetBreakOnID(D3D12_MESSAGE_ID ID) override;

		void STDMETHODCALLTYPE SetMuteDebugOutput(BOOL bMute) override;

		BOOL STDMETHODCALLTYPE GetMuteDebugOutput() override;

		// ID3D12InfoQueue1
		HRESULT STDMETHODCALLTYPE RegisterMessageCallback(D3D12MessageFunc CallbackFunc,
														  D3D12_MESSAGE_CALLBACK_FLAGS CallbackFilterFlags,
														  void *pContext, DWORD *pCallbackCookie) override;

		HRESULT STDMETHODCALLTYPE UnregisterMessageCallback(DWORD CallbackCookie) override;
	};
}
