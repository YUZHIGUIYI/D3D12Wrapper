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

	struct ID3D12InfoQueue1Wrapper : ID3D12InfoQueueWrapper
	{
	public:
		ID3D12InfoQueue1Wrapper(REFIID riid, IUnknown *object);

		~ID3D12InfoQueue1Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE RegisterMessageCallback(
						D3D12MessageFunc CallbackFunc,
						D3D12_MESSAGE_CALLBACK_FLAGS CallbackFilterFlags,
						void* pContext,
						DWORD* pCallbackCookie);

		virtual HRESULT STDMETHODCALLTYPE UnregisterMessageCallback(DWORD CallbackCookie);
	};
}
