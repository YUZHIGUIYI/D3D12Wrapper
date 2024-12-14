//
// Created by ZZK on 2024/11/24.
//

#include <tracer/d3d12/d3d12_debug_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	// Wrap ID3D12Debug
	ID3D12DebugWrapper::ID3D12DebugWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	void STDMETHODCALLTYPE ID3D12DebugWrapper::EnableDebugLayer()
	{
		GetWrappedObjectAs<ID3D12Debug>()->EnableDebugLayer();
	}

	// Wrap ID3D12Debug1
	ID3D12Debug1Wrapper::ID3D12Debug1Wrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12Debug1Wrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12Debug1Wrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12Debug1Wrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12Debug1Wrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12Debug1Wrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12Debug1Wrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12Debug1Wrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12Debug1Wrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12Debug1
	void STDMETHODCALLTYPE ID3D12Debug1Wrapper::EnableDebugLayer()
	{
		GetWrappedObjectAs<ID3D12Debug1>()->EnableDebugLayer();
	}

	void STDMETHODCALLTYPE ID3D12Debug1Wrapper::SetEnableGPUBasedValidation(BOOL Enable)
	{
		GetWrappedObjectAs<ID3D12Debug1>()->SetEnableGPUBasedValidation(Enable);
	}

	void STDMETHODCALLTYPE ID3D12Debug1Wrapper::SetEnableSynchronizedCommandQueueValidation(BOOL Enable)
	{
		GetWrappedObjectAs<ID3D12Debug1>()->SetEnableSynchronizedCommandQueueValidation(Enable);
	}

	// Wrap ID3D12Debug2
	ID3D12Debug2Wrapper::ID3D12Debug2Wrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12Debug2Wrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12Debug2Wrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12Debug2Wrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12Debug2Wrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12Debug2Wrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12Debug2Wrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12Debug2Wrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12Debug2Wrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12Debug2
	void STDMETHODCALLTYPE ID3D12Debug2Wrapper::SetGPUBasedValidationFlags(D3D12_GPU_BASED_VALIDATION_FLAGS Flags) \
	{
		GetWrappedObjectAs<ID3D12Debug2>()->SetGPUBasedValidationFlags(Flags);
	}

	// Wrap ID3D12Debug3
	ID3D12Debug3Wrapper::ID3D12Debug3Wrapper(const IID &riid, IUnknown *object)
	: ID3D12DebugWrapper(riid, object)
	{

	}

	void STDMETHODCALLTYPE ID3D12Debug3Wrapper::SetEnableGPUBasedValidation(BOOL Enable)
	{
		GetWrappedObjectAs<ID3D12Debug3>()->SetEnableGPUBasedValidation(Enable);
	}

	void STDMETHODCALLTYPE ID3D12Debug3Wrapper::SetEnableSynchronizedCommandQueueValidation(BOOL Enable)
	{
		GetWrappedObjectAs<ID3D12Debug3>()->SetEnableSynchronizedCommandQueueValidation(Enable);
	}

	void STDMETHODCALLTYPE ID3D12Debug3Wrapper::SetGPUBasedValidationFlags(D3D12_GPU_BASED_VALIDATION_FLAGS Flags)
	{
		GetWrappedObjectAs<ID3D12Debug3>()->SetGPUBasedValidationFlags(Flags);
	}

	// Wrap ID3D12Debug4
	ID3D12Debug4Wrapper::ID3D12Debug4Wrapper(const IID &riid, IUnknown *object)
	: ID3D12Debug3Wrapper(riid, object)
	{

	}

	void STDMETHODCALLTYPE ID3D12Debug4Wrapper::DisableDebugLayer()
	{
		GetWrappedObjectAs<ID3D12Debug4>()->DisableDebugLayer();
	}

	// Wrap ID3D12Debug5
	ID3D12Debug5Wrapper::ID3D12Debug5Wrapper(const IID &riid, IUnknown *object)
	: ID3D12Debug4Wrapper(riid, object)
	{

	}

	void STDMETHODCALLTYPE ID3D12Debug5Wrapper::SetEnableAutoName(BOOL Enable)
	{
		GetWrappedObjectAs<ID3D12Debug5>()->SetEnableAutoName(Enable);
	}

	// Wrap ID3D12Debug6
	ID3D12Debug6Wrapper::ID3D12Debug6Wrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12Debug6Wrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12Debug6Wrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12Debug6Wrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12Debug6Wrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12Debug6Wrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12Debug6Wrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12Debug6Wrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12Debug6Wrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12Debug
	void STDMETHODCALLTYPE ID3D12Debug6Wrapper::EnableDebugLayer()
	{
		GetWrappedObjectAs<ID3D12Debug>()->EnableDebugLayer();
	}

	// ID3D12Debug3
	void STDMETHODCALLTYPE ID3D12Debug6Wrapper::SetEnableGPUBasedValidation(BOOL Enable)
	{
		GetWrappedObjectAs<ID3D12Debug3>()->SetEnableGPUBasedValidation(Enable);
	}

	void STDMETHODCALLTYPE ID3D12Debug6Wrapper::SetEnableSynchronizedCommandQueueValidation(BOOL Enable)
	{
		GetWrappedObjectAs<ID3D12Debug3>()->SetEnableSynchronizedCommandQueueValidation(Enable);
	}

	void STDMETHODCALLTYPE ID3D12Debug6Wrapper::SetGPUBasedValidationFlags(D3D12_GPU_BASED_VALIDATION_FLAGS Flags)
	{
		GetWrappedObjectAs<ID3D12Debug3>()->SetGPUBasedValidationFlags(Flags);
	}

	// ID3D12Debug4
	void STDMETHODCALLTYPE ID3D12Debug6Wrapper::DisableDebugLayer()
	{
		GetWrappedObjectAs<ID3D12Debug4>()->DisableDebugLayer();
	}

	// ID3D12Debug5
	void STDMETHODCALLTYPE ID3D12Debug6Wrapper::SetEnableAutoName(BOOL Enable)
	{
		GetWrappedObjectAs<ID3D12Debug5>()->SetEnableAutoName(Enable);
	}

	// ID3D12Debug6
	void STDMETHODCALLTYPE ID3D12Debug6Wrapper::SetForceLegacyBarrierValidation(BOOL Enable)
	{
		GetWrappedObjectAs<ID3D12Debug6>()->SetForceLegacyBarrierValidation(Enable);
	}

	// Wrap ID3D12DebugDevice
	ID3D12DebugDeviceWrapper::ID3D12DebugDeviceWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE ID3D12DebugDeviceWrapper::SetFeatureMask(D3D12_DEBUG_FEATURE Mask)
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugDevice>()->SetFeatureMask(Mask);
		return result;
	}

	D3D12_DEBUG_FEATURE STDMETHODCALLTYPE ID3D12DebugDeviceWrapper::GetFeatureMask()
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugDevice>()->GetFeatureMask();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DebugDeviceWrapper::ReportLiveDeviceObjects(D3D12_RLDO_FLAGS Flags)
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugDevice>()->ReportLiveDeviceObjects(Flags);
		return result;
	}

	// Wrap ID3D12DebugDevice1
	ID3D12DebugDevice1Wrapper::ID3D12DebugDevice1Wrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12DebugDevice1Wrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12DebugDevice1Wrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12DebugDevice1Wrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12DebugDevice1Wrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12DebugDevice1Wrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12DebugDevice1Wrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12DebugDevice1Wrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12DebugDevice1Wrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12DebugDevice1
	HRESULT STDMETHODCALLTYPE ID3D12DebugDevice1Wrapper::SetDebugParameter(D3D12_DEBUG_DEVICE_PARAMETER_TYPE Type, const void *pData,
																			UINT DataSize)
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugDevice1>()->SetDebugParameter(Type, pData, DataSize);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DebugDevice1Wrapper::GetDebugParameter(D3D12_DEBUG_DEVICE_PARAMETER_TYPE Type, void *pData,
																			UINT DataSize)
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugDevice1>()->GetDebugParameter(Type, pData, DataSize);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DebugDevice1Wrapper::ReportLiveDeviceObjects(D3D12_RLDO_FLAGS Flags)
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugDevice1>()->ReportLiveDeviceObjects(Flags);
		return result;
	}

	// Wrap ID3D12DebugDevice2
	ID3D12DebugDevice2Wrapper::ID3D12DebugDevice2Wrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12DebugDevice2Wrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12DebugDevice2Wrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12DebugDevice2Wrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12DebugDevice2Wrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12DebugDevice2Wrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12DebugDevice2Wrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12DebugDevice2Wrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12DebugDevice2Wrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12DebugDevice
	HRESULT STDMETHODCALLTYPE ID3D12DebugDevice2Wrapper::SetFeatureMask(D3D12_DEBUG_FEATURE Mask)
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugDevice>()->SetFeatureMask(Mask);
		return result;
	}

	D3D12_DEBUG_FEATURE STDMETHODCALLTYPE ID3D12DebugDevice2Wrapper::GetFeatureMask()
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugDevice>()->GetFeatureMask();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DebugDevice2Wrapper::ReportLiveDeviceObjects(D3D12_RLDO_FLAGS Flags)
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugDevice>()->ReportLiveDeviceObjects(Flags);
		return result;
	}

	// ID3D12DebugDevice2
	HRESULT STDMETHODCALLTYPE ID3D12DebugDevice2Wrapper::SetDebugParameter(D3D12_DEBUG_DEVICE_PARAMETER_TYPE Type, const void *pData,
																			UINT DataSize)
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugDevice2>()->SetDebugParameter(Type, pData, DataSize);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DebugDevice2Wrapper::GetDebugParameter(D3D12_DEBUG_DEVICE_PARAMETER_TYPE Type, void *pData,
																			UINT DataSize)
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugDevice2>()->GetDebugParameter(Type, pData, DataSize);
		return result;
	}

	// Wrap ID3D12DebugCommandQueue
	ID3D12DebugCommandQueueWrapper::ID3D12DebugCommandQueueWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	BOOL STDMETHODCALLTYPE ID3D12DebugCommandQueueWrapper::AssertResourceState(ID3D12Resource *pResource, UINT Subresource, UINT State)
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugCommandQueue>()->AssertResourceState(encode::GetWrappedObject<ID3D12Resource>(pResource), Subresource, State);
		return result;
	}

	// Wrap ID3D12DebugCommandQueue1
	ID3D12DebugCommandQueue1Wrapper::ID3D12DebugCommandQueue1Wrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12DebugCommandQueue1Wrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12DebugCommandQueue1Wrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12DebugCommandQueue1Wrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12DebugCommandQueue1Wrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12DebugCommandQueue1Wrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12DebugCommandQueue1Wrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12DebugCommandQueue1Wrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12DebugCommandQueue1Wrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12DebugCommandQueue
	BOOL STDMETHODCALLTYPE ID3D12DebugCommandQueue1Wrapper::AssertResourceState(ID3D12Resource *pResource, UINT Subresource, UINT State)
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugCommandQueue>()->AssertResourceState(encode::GetWrappedObject<ID3D12Resource>(pResource), Subresource, State);
		return result;
	}

	// ID3D12DebugCommandQueue1
	void STDMETHODCALLTYPE ID3D12DebugCommandQueue1Wrapper::AssertResourceAccess(ID3D12Resource *pResource, UINT Subresource,
																				D3D12_BARRIER_ACCESS Access)
	{
		GetWrappedObjectAs<ID3D12DebugCommandQueue1>()->AssertResourceAccess(encode::GetWrappedObject<ID3D12Resource>(pResource), Subresource, Access);
	}

	void STDMETHODCALLTYPE ID3D12DebugCommandQueue1Wrapper::AssertTextureLayout(ID3D12Resource *pResource, UINT Subresource,
																				D3D12_BARRIER_LAYOUT Layout)
	{
		GetWrappedObjectAs<ID3D12DebugCommandQueue1>()->AssertTextureLayout(encode::GetWrappedObject<ID3D12Resource>(pResource), Subresource, Layout);
	}

	// Wrap ID3D12DebugCommandList
	ID3D12DebugCommandListWrapper::ID3D12DebugCommandListWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	BOOL STDMETHODCALLTYPE ID3D12DebugCommandListWrapper::AssertResourceState(ID3D12Resource *pResource, UINT Subresource, UINT State)
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugCommandList>()->AssertResourceState(encode::GetWrappedObject<ID3D12Resource>(pResource), Subresource, State);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DebugCommandListWrapper::SetFeatureMask(D3D12_DEBUG_FEATURE Mask)
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugCommandList>()->SetFeatureMask(Mask);
		return result;
	}

	D3D12_DEBUG_FEATURE STDMETHODCALLTYPE ID3D12DebugCommandListWrapper::GetFeatureMask()
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugCommandList>()->GetFeatureMask();
		return result;
	}

	// Wrap ID3D12DebugCommandList1
	ID3D12DebugCommandList1Wrapper::ID3D12DebugCommandList1Wrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12DebugCommandList1Wrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12DebugCommandList1Wrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12DebugCommandList1Wrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12DebugCommandList1Wrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12DebugCommandList1Wrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12DebugCommandList1Wrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12DebugCommandList1Wrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12DebugCommandList1Wrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12DebugCommandList1
	BOOL STDMETHODCALLTYPE ID3D12DebugCommandList1Wrapper::AssertResourceState(ID3D12Resource *pResource, UINT Subresource, UINT State)
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugCommandList1>()->AssertResourceState(encode::GetWrappedObject<ID3D12Resource>(pResource), Subresource, State);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DebugCommandList1Wrapper::SetDebugParameter(D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
																				const void *pData, UINT DataSize)
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugCommandList1>()->SetDebugParameter(Type, pData, DataSize);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DebugCommandList1Wrapper::GetDebugParameter(D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type, void *pData, UINT DataSize)
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugCommandList1>()->GetDebugParameter(Type, pData, DataSize);
		return result;
	}

	// Wrap ID3D12DebugCommandList2
	ID3D12DebugCommandList2Wrapper::ID3D12DebugCommandList2Wrapper(const IID &riid, IUnknown *object)
	: ID3D12DebugCommandListWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE ID3D12DebugCommandList2Wrapper::SetDebugParameter(D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
																				const void *pData, UINT DataSize)
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugCommandList2>()->SetDebugParameter(Type, pData, DataSize);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DebugCommandList2Wrapper::GetDebugParameter(D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type, void *pData, UINT DataSize)
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugCommandList2>()->GetDebugParameter(Type, pData, DataSize);
		return result;
	}

	// Wrap ID3D12DebugCommandList3
	ID3D12DebugCommandList3Wrapper::ID3D12DebugCommandList3Wrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12DebugCommandList3Wrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12DebugCommandList3Wrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12DebugCommandList3Wrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12DebugCommandList3Wrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12DebugCommandList3Wrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12DebugCommandList3Wrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12DebugCommandList3Wrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12DebugCommandList3Wrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12DebugCommandList
	BOOL STDMETHODCALLTYPE ID3D12DebugCommandList3Wrapper::AssertResourceState(ID3D12Resource *pResource, UINT Subresource, UINT State)
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugCommandList>()->AssertResourceState(encode::GetWrappedObject<ID3D12Resource>(pResource), Subresource, State);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DebugCommandList3Wrapper::SetFeatureMask(D3D12_DEBUG_FEATURE Mask)
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugCommandList>()->SetFeatureMask(Mask);
		return result;
	}

	D3D12_DEBUG_FEATURE STDMETHODCALLTYPE ID3D12DebugCommandList3Wrapper::GetFeatureMask()
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugCommandList>()->GetFeatureMask();
		return result;
	}

	// ID3D12DebugCommandList2
	HRESULT STDMETHODCALLTYPE ID3D12DebugCommandList3Wrapper::SetDebugParameter(D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
																				const void *pData, UINT DataSize)
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugCommandList2>()->SetDebugParameter(Type, pData, DataSize);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DebugCommandList3Wrapper::GetDebugParameter(D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type, void *pData, UINT DataSize)
	{
		const auto result = GetWrappedObjectAs<ID3D12DebugCommandList2>()->GetDebugParameter(Type, pData, DataSize);
		return result;
	}

	// ID3D12DebugCommandList3
	void STDMETHODCALLTYPE ID3D12DebugCommandList3Wrapper::AssertResourceAccess(ID3D12Resource *pResource, UINT Subresource, D3D12_BARRIER_ACCESS Access)
	{
		GetWrappedObjectAs<ID3D12DebugCommandList3>()->AssertResourceAccess(encode::GetWrappedObject<ID3D12Resource>(pResource), Subresource, Access);
	}

	void STDMETHODCALLTYPE ID3D12DebugCommandList3Wrapper::AssertTextureLayout(ID3D12Resource *pResource, UINT Subresource,
															 D3D12_BARRIER_LAYOUT Layout)
	{
		GetWrappedObjectAs<ID3D12DebugCommandList3>()->AssertTextureLayout(encode::GetWrappedObject<ID3D12Resource>(pResource), Subresource, Layout);
	}

}