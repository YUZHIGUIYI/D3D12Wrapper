//
// Created by ZZK on 2024/11/24.
//

#include <tracer/d3d12/d3d12_info_queue_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	ID3D12InfoQueueWrapper::ID3D12InfoQueueWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueueWrapper::SetMessageCountLimit(UINT64 MessageCountLimit)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->SetMessageCountLimit(MessageCountLimit);
		return result;
	}

	void STDMETHODCALLTYPE ID3D12InfoQueueWrapper::ClearStoredMessages()
	{
		GetWrappedObjectAs<ID3D12InfoQueue>()->ClearStoredMessages();
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueueWrapper::GetMessage(UINT64 MessageIndex, D3D12_MESSAGE *pMessage, SIZE_T *pMessageByteLength)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetMessage(MessageIndex, pMessage, pMessageByteLength);
		return result;
	}

	UINT64 STDMETHODCALLTYPE ID3D12InfoQueueWrapper::GetNumMessagesAllowedByStorageFilter()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetNumMessagesAllowedByStorageFilter();
		return result;
	}

	UINT64 STDMETHODCALLTYPE ID3D12InfoQueueWrapper::GetNumMessagesDeniedByStorageFilter()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetNumMessagesDeniedByStorageFilter();
		return result;
	}

	UINT64 STDMETHODCALLTYPE ID3D12InfoQueueWrapper::GetNumStoredMessages()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetNumStoredMessages();
		return result;
	}

	UINT64 STDMETHODCALLTYPE ID3D12InfoQueueWrapper::GetNumStoredMessagesAllowedByRetrievalFilter()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetNumStoredMessagesAllowedByRetrievalFilter();
		return result;
	}

	UINT64 STDMETHODCALLTYPE ID3D12InfoQueueWrapper::GetNumMessagesDiscardedByMessageCountLimit()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetNumMessagesDiscardedByMessageCountLimit();
		return result;
	}

	UINT64 STDMETHODCALLTYPE ID3D12InfoQueueWrapper::GetMessageCountLimit()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetMessageCountLimit();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueueWrapper::AddStorageFilterEntries(D3D12_INFO_QUEUE_FILTER *pFilter)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->AddStorageFilterEntries(pFilter);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueueWrapper::GetStorageFilter(D3D12_INFO_QUEUE_FILTER *pFilter, SIZE_T *pFilterByteLength)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetStorageFilter(pFilter, pFilterByteLength);
		return result;
	}

	void STDMETHODCALLTYPE ID3D12InfoQueueWrapper::ClearStorageFilter()
	{
		GetWrappedObjectAs<ID3D12InfoQueue>()->ClearStorageFilter();
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueueWrapper::PushEmptyStorageFilter()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->PushEmptyStorageFilter();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueueWrapper::PushCopyOfStorageFilter()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->PushCopyOfStorageFilter();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueueWrapper::PushStorageFilter(D3D12_INFO_QUEUE_FILTER *pFilter)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->PushStorageFilter(pFilter);
		return result;
	}

	void STDMETHODCALLTYPE ID3D12InfoQueueWrapper::PopStorageFilter()
	{
		GetWrappedObjectAs<ID3D12InfoQueue>()->PopStorageFilter();
	}

	UINT STDMETHODCALLTYPE ID3D12InfoQueueWrapper::GetStorageFilterStackSize()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetStorageFilterStackSize();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueueWrapper::AddRetrievalFilterEntries(D3D12_INFO_QUEUE_FILTER *pFilter)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->AddRetrievalFilterEntries(pFilter);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueueWrapper::GetRetrievalFilter(D3D12_INFO_QUEUE_FILTER *pFilter, SIZE_T *pFilterByteLength)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetRetrievalFilter(pFilter, pFilterByteLength);
		return result;
	}

	void STDMETHODCALLTYPE ID3D12InfoQueueWrapper::ClearRetrievalFilter()
	{
		GetWrappedObjectAs<ID3D12InfoQueue>()->ClearRetrievalFilter();
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueueWrapper::PushEmptyRetrievalFilter()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->PushEmptyRetrievalFilter();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueueWrapper::PushCopyOfRetrievalFilter()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->PushCopyOfRetrievalFilter();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueueWrapper::PushRetrievalFilter(D3D12_INFO_QUEUE_FILTER *pFilter)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->PushRetrievalFilter(pFilter);
		return result;
	}

	void STDMETHODCALLTYPE ID3D12InfoQueueWrapper::PopRetrievalFilter()
	{
		GetWrappedObjectAs<ID3D12InfoQueue>()->PopRetrievalFilter();
	}

	UINT STDMETHODCALLTYPE ID3D12InfoQueueWrapper::GetRetrievalFilterStackSize()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetRetrievalFilterStackSize();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueueWrapper::AddMessage(D3D12_MESSAGE_CATEGORY Category, D3D12_MESSAGE_SEVERITY Severity,
																D3D12_MESSAGE_ID ID, LPCSTR pDescription)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->AddMessage(Category, Severity, ID, pDescription);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueueWrapper::AddApplicationMessage(D3D12_MESSAGE_SEVERITY Severity, LPCSTR pDescription)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->AddApplicationMessage(Severity, pDescription);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueueWrapper::SetBreakOnCategory(D3D12_MESSAGE_CATEGORY Category, BOOL bEnable)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->SetBreakOnCategory(Category, bEnable);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueueWrapper::SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY Severity, BOOL bEnable)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->SetBreakOnSeverity(Severity, bEnable);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueueWrapper::SetBreakOnID(D3D12_MESSAGE_ID ID, BOOL bEnable)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->SetBreakOnID(ID, bEnable);
		return result;
	}

	BOOL STDMETHODCALLTYPE ID3D12InfoQueueWrapper::GetBreakOnCategory(D3D12_MESSAGE_CATEGORY Category)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetBreakOnCategory(Category);
		return result;
	}

	BOOL STDMETHODCALLTYPE ID3D12InfoQueueWrapper::GetBreakOnSeverity(D3D12_MESSAGE_SEVERITY Severity)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetBreakOnSeverity(Severity);
		return result;
	}

	BOOL STDMETHODCALLTYPE ID3D12InfoQueueWrapper::GetBreakOnID(D3D12_MESSAGE_ID ID)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetBreakOnID(ID);
		return result;
	}

	void STDMETHODCALLTYPE ID3D12InfoQueueWrapper::SetMuteDebugOutput(BOOL bMute)
	{
		GetWrappedObjectAs<ID3D12InfoQueue>()->SetMuteDebugOutput(bMute);
	}

	BOOL STDMETHODCALLTYPE ID3D12InfoQueueWrapper::GetMuteDebugOutput()
	{
		return GetWrappedObjectAs<ID3D12InfoQueue>()->GetMuteDebugOutput();
	}

	// New wrapped ID3D12InfoQueue1
	ID3D12InfoQueue1Wrapper::ID3D12InfoQueue1Wrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12InfoQueue1Wrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12InfoQueue1Wrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12InfoQueue1Wrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12InfoQueue1Wrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12InfoQueue1Wrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12InfoQueue
	HRESULT STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::SetMessageCountLimit(UINT64 MessageCountLimit)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->SetMessageCountLimit(MessageCountLimit);
		return result;
	}

	void STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::ClearStoredMessages()
	{
		GetWrappedObjectAs<ID3D12InfoQueue>()->ClearStoredMessages();
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::GetMessage(UINT64 MessageIndex, D3D12_MESSAGE *pMessage, SIZE_T *pMessageByteLength)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetMessage(MessageIndex, pMessage, pMessageByteLength);
		return result;
	}

	UINT64 STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::GetNumMessagesAllowedByStorageFilter()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetNumMessagesAllowedByStorageFilter();
		return result;
	}

	UINT64 STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::GetNumMessagesDeniedByStorageFilter()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetNumMessagesDeniedByStorageFilter();
		return result;
	}

	UINT64 STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::GetNumStoredMessages()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetNumStoredMessages();
		return result;
	}

	UINT64 STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::GetNumStoredMessagesAllowedByRetrievalFilter()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetNumStoredMessagesAllowedByRetrievalFilter();
		return result;
	}

	UINT64 STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::GetNumMessagesDiscardedByMessageCountLimit()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetNumMessagesDiscardedByMessageCountLimit();
		return result;
	}

	UINT64 STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::GetMessageCountLimit()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetMessageCountLimit();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::AddStorageFilterEntries(D3D12_INFO_QUEUE_FILTER *pFilter)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->AddStorageFilterEntries(pFilter);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::GetStorageFilter(D3D12_INFO_QUEUE_FILTER *pFilter, SIZE_T *pFilterByteLength)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetStorageFilter(pFilter, pFilterByteLength);
		return result;
	}

	void STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::ClearStorageFilter()
	{
		GetWrappedObjectAs<ID3D12InfoQueue>()->ClearStorageFilter();
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::PushEmptyStorageFilter()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->PushEmptyStorageFilter();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::PushCopyOfStorageFilter()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->PushCopyOfStorageFilter();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::PushStorageFilter(D3D12_INFO_QUEUE_FILTER *pFilter)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->PushStorageFilter(pFilter);
		return result;
	}

	void STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::PopStorageFilter()
	{
		GetWrappedObjectAs<ID3D12InfoQueue>()->PopStorageFilter();
	}

	UINT STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::GetStorageFilterStackSize()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetStorageFilterStackSize();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::AddRetrievalFilterEntries(D3D12_INFO_QUEUE_FILTER *pFilter)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->AddRetrievalFilterEntries(pFilter);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::GetRetrievalFilter(D3D12_INFO_QUEUE_FILTER *pFilter, SIZE_T *pFilterByteLength)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetRetrievalFilter(pFilter, pFilterByteLength);
		return result;
	}

	void STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::ClearRetrievalFilter()
	{
		GetWrappedObjectAs<ID3D12InfoQueue>()->ClearRetrievalFilter();
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::PushEmptyRetrievalFilter()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->PushEmptyRetrievalFilter();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::PushCopyOfRetrievalFilter()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->PushCopyOfRetrievalFilter();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::PushRetrievalFilter(D3D12_INFO_QUEUE_FILTER *pFilter)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->PushRetrievalFilter(pFilter);
		return result;
	}

	void STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::PopRetrievalFilter()
	{
		GetWrappedObjectAs<ID3D12InfoQueue>()->PopRetrievalFilter();
	}

	UINT STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::GetRetrievalFilterStackSize()
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetRetrievalFilterStackSize();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::AddMessage(D3D12_MESSAGE_CATEGORY Category, D3D12_MESSAGE_SEVERITY Severity,
																D3D12_MESSAGE_ID ID, LPCSTR pDescription)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->AddMessage(Category, Severity, ID, pDescription);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::AddApplicationMessage(D3D12_MESSAGE_SEVERITY Severity, LPCSTR pDescription)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->AddApplicationMessage(Severity, pDescription);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::SetBreakOnCategory(D3D12_MESSAGE_CATEGORY Category, BOOL bEnable)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->SetBreakOnCategory(Category, bEnable);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY Severity, BOOL bEnable)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->SetBreakOnSeverity(Severity, bEnable);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::SetBreakOnID(D3D12_MESSAGE_ID ID, BOOL bEnable)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->SetBreakOnID(ID, bEnable);
		return result;
	}

	BOOL STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::GetBreakOnCategory(D3D12_MESSAGE_CATEGORY Category)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetBreakOnCategory(Category);
		return result;
	}

	BOOL STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::GetBreakOnSeverity(D3D12_MESSAGE_SEVERITY Severity)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetBreakOnSeverity(Severity);
		return result;
	}

	BOOL STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::GetBreakOnID(D3D12_MESSAGE_ID ID)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue>()->GetBreakOnID(ID);
		return result;
	}

	void STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::SetMuteDebugOutput(BOOL bMute)
	{
		GetWrappedObjectAs<ID3D12InfoQueue>()->SetMuteDebugOutput(bMute);
	}

	BOOL STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::GetMuteDebugOutput()
	{
		return GetWrappedObjectAs<ID3D12InfoQueue>()->GetMuteDebugOutput();
	}

	// ID3D12InfoQueue1
	HRESULT STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::RegisterMessageCallback(D3D12MessageFunc CallbackFunc,
																				D3D12_MESSAGE_CALLBACK_FLAGS CallbackFilterFlags,
																				void *pContext, DWORD *pCallbackCookie)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue1>()->RegisterMessageCallback(CallbackFunc, CallbackFilterFlags, pContext, pCallbackCookie);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12InfoQueue1Wrapper::UnregisterMessageCallback(DWORD CallbackCookie)
	{
		const auto result = GetWrappedObjectAs<ID3D12InfoQueue1>()->UnregisterMessageCallback(CallbackCookie);
		return result;
	}

}