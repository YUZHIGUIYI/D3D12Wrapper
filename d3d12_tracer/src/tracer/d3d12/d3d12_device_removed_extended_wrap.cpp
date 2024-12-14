//
// Created by ZZK on 2024/11/30.
//

#include <tracer/core/wrapper_creators.h>
#include <tracer/d3d12/d3d12_device_removed_extended_wrap.h>

namespace gfxshim
{
	// Wrap ID3D12DeviceRemovedExtendedDataSettings
	ID3D12DeviceRemovedExtendedDataSettingsWrapper::ID3D12DeviceRemovedExtendedDataSettingsWrapper(const IID& riid, IUnknown* object)
	: IUnknownWrapper(riid, object)
	{

	}

	void STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedDataSettingsWrapper::SetAutoBreadcrumbsEnablement(D3D12_DRED_ENABLEMENT Enablement)
	{
		GetWrappedObjectAs<ID3D12DeviceRemovedExtendedDataSettings>()->SetAutoBreadcrumbsEnablement(Enablement);
	}

	void STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedDataSettingsWrapper::SetPageFaultEnablement(D3D12_DRED_ENABLEMENT Enablement)
	{
		GetWrappedObjectAs<ID3D12DeviceRemovedExtendedDataSettings>()->SetPageFaultEnablement(Enablement);
	}

	void STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedDataSettingsWrapper::SetWatsonDumpEnablement(D3D12_DRED_ENABLEMENT Enablement)
	{
		GetWrappedObjectAs<ID3D12DeviceRemovedExtendedDataSettings>()->SetWatsonDumpEnablement(Enablement);
	}

	// Wrap ID3D12DeviceRemovedExtendedDataSettings1
	ID3D12DeviceRemovedExtendedDataSettings1Wrapper::ID3D12DeviceRemovedExtendedDataSettings1Wrapper(const IID &riid, IUnknown *object)
	: ID3D12DeviceRemovedExtendedDataSettingsWrapper(riid, object)
	{

	}

	void STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedDataSettings1Wrapper::SetBreadcrumbContextEnablement(D3D12_DRED_ENABLEMENT Enablement)
	{
		GetWrappedObjectAs<ID3D12DeviceRemovedExtendedDataSettings1>()->SetBreadcrumbContextEnablement(Enablement);
	}

	// Wrap ID3D12DeviceRemovedExtendedDataSettings2
	ID3D12DeviceRemovedExtendedDataSettings2Wrapper::ID3D12DeviceRemovedExtendedDataSettings2Wrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12DeviceRemovedExtendedDataSettings2Wrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12DeviceRemovedExtendedDataSettings2Wrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12DeviceRemovedExtendedDataSettings2Wrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12DeviceRemovedExtendedDataSettings2Wrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedDataSettings2Wrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			D3D12_WRAPPER_DEBUG("Invoke ID3D12DeviceRemovedExtendedDataSettings2Wrapper::QueryInterface, get unknown object");
			return S_OK;
		} else
		{
			encode::WrapObject(riid, object);
			D3D12_WRAPPER_DEBUG("Invoke ID3D12DeviceRemovedExtendedDataSettings2Wrapper::QueryInterface, get wrapped object");
		}
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedDataSettings2Wrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedDataSettings2Wrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12DeviceRemovedExtendedDataSettings
	void STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedDataSettings2Wrapper::SetAutoBreadcrumbsEnablement(D3D12_DRED_ENABLEMENT Enablement)
	{
		GetWrappedObjectAs<ID3D12DeviceRemovedExtendedDataSettings>()->SetAutoBreadcrumbsEnablement(Enablement);
	}

	void STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedDataSettings2Wrapper::SetPageFaultEnablement(D3D12_DRED_ENABLEMENT Enablement)
	{
		GetWrappedObjectAs<ID3D12DeviceRemovedExtendedDataSettings>()->SetPageFaultEnablement(Enablement);
	}

	void STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedDataSettings2Wrapper::SetWatsonDumpEnablement(D3D12_DRED_ENABLEMENT Enablement)
	{
		GetWrappedObjectAs<ID3D12DeviceRemovedExtendedDataSettings>()->SetWatsonDumpEnablement(Enablement);
	}

	// ID3D12DeviceRemovedExtendedDataSettings1
	void STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedDataSettings2Wrapper::SetBreadcrumbContextEnablement(D3D12_DRED_ENABLEMENT Enablement)
	{
		GetWrappedObjectAs<ID3D12DeviceRemovedExtendedDataSettings1>()->SetBreadcrumbContextEnablement(Enablement);
	}

	// ID3D12DeviceRemovedExtendedDataSettings2
	void STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedDataSettings2Wrapper::UseMarkersOnlyAutoBreadcrumbs(BOOL MarkersOnly)
	{
		GetWrappedObjectAs<ID3D12DeviceRemovedExtendedDataSettings2>()->UseMarkersOnlyAutoBreadcrumbs(MarkersOnly);
	}

	// ID3D12DeviceRemovedExtendedData
	ID3D12DeviceRemovedExtendedDataWrapper::ID3D12DeviceRemovedExtendedDataWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedDataWrapper::GetAutoBreadcrumbsOutput(D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT *pOutput)
	{
		// TODO: check wrap, fix
		const auto result = GetWrappedObjectAs<ID3D12DeviceRemovedExtendedData>()->GetAutoBreadcrumbsOutput(pOutput);
		if (SUCCEEDED(result))
		{
			if (pOutput->pHeadAutoBreadcrumbNode != nullptr)
			{
				if (pOutput->pHeadAutoBreadcrumbNode->pCommandList != nullptr)
				{
					encode::WrapObject(__uuidof(ID3D12GraphicsCommandList), reinterpret_cast<void **>(pOutput->pHeadAutoBreadcrumbNode->pCommandList));
				}
				if (pOutput->pHeadAutoBreadcrumbNode->pCommandQueue != nullptr)
				{
					encode::WrapObject(__uuidof(ID3D12CommandQueue), reinterpret_cast<void **>(pOutput->pHeadAutoBreadcrumbNode->pCommandQueue));
				}
			}
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedDataWrapper::GetPageFaultAllocationOutput(D3D12_DRED_PAGE_FAULT_OUTPUT *pOutput)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceRemovedExtendedData>()->GetPageFaultAllocationOutput(pOutput);
		return result;
	}

	// Wrap ID3D12DeviceRemovedExtendedData1
	ID3D12DeviceRemovedExtendedData1Wrapper::ID3D12DeviceRemovedExtendedData1Wrapper(const IID &riid, IUnknown *object)
	: ID3D12DeviceRemovedExtendedDataWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedData1Wrapper::GetAutoBreadcrumbsOutput1(D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT1 *pOutput)
	{
		// TODO: check wrap, fix
		const auto result = GetWrappedObjectAs<ID3D12DeviceRemovedExtendedData1>()->GetAutoBreadcrumbsOutput1(pOutput);
		if (SUCCEEDED(result))
		{
			if (pOutput->pHeadAutoBreadcrumbNode != nullptr)
			{
				if (pOutput->pHeadAutoBreadcrumbNode->pCommandList != nullptr)
				{
					encode::WrapObject(__uuidof(ID3D12GraphicsCommandList), reinterpret_cast<void **>(pOutput->pHeadAutoBreadcrumbNode->pCommandList));
				}
				if (pOutput->pHeadAutoBreadcrumbNode->pCommandQueue != nullptr)
				{
					encode::WrapObject(__uuidof(ID3D12CommandQueue), reinterpret_cast<void **>(pOutput->pHeadAutoBreadcrumbNode->pCommandQueue));
				}
			}
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedData1Wrapper::GetPageFaultAllocationOutput1(D3D12_DRED_PAGE_FAULT_OUTPUT1 *pOutput)
	{
		// TODO: check wrap, fix
		const auto result = GetWrappedObjectAs<ID3D12DeviceRemovedExtendedData1>()->GetPageFaultAllocationOutput1(pOutput);
		if (SUCCEEDED(result))
		{
			if (pOutput->pHeadExistingAllocationNode != nullptr)
			{
				if (pOutput->pHeadExistingAllocationNode->pObject != nullptr)
				{
					encode::WrapObject(__uuidof(IUnknown), reinterpret_cast<void **>(const_cast<IUnknown *>(pOutput->pHeadExistingAllocationNode->pObject)));
				}
			}
			if (pOutput->pHeadRecentFreedAllocationNode != nullptr)
			{
				if (pOutput->pHeadRecentFreedAllocationNode->pObject != nullptr)
				{
					encode::WrapObject(__uuidof(IUnknown), reinterpret_cast<void **>(const_cast<IUnknown *>(pOutput->pHeadRecentFreedAllocationNode->pObject)));
				}
			}
		}
		return result;
	}

	// Wrap ID3D12DeviceRemovedExtendedData2
	ID3D12DeviceRemovedExtendedData2Wrapper::ID3D12DeviceRemovedExtendedData2Wrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12DeviceRemovedExtendedData2Wrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12DeviceRemovedExtendedData2Wrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12DeviceRemovedExtendedData2Wrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12DeviceRemovedExtendedData2Wrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedData2Wrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			D3D12_WRAPPER_DEBUG("Invoke ID3D12DeviceRemovedExtendedData2Wrapper::QueryInterface, get unknown object");
			return S_OK;
		} else
		{
			encode::WrapObject(riid, object);
			D3D12_WRAPPER_DEBUG("Invoke ID3D12DeviceRemovedExtendedData2Wrapper::QueryInterface, get wrapped object");
		}
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedData2Wrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedData2Wrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12DeviceRemovedExtendedData
	HRESULT STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedData2Wrapper::GetAutoBreadcrumbsOutput(D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT *pOutput)
	{
		// TODO: check wrap, fix
		const auto result = GetWrappedObjectAs<ID3D12DeviceRemovedExtendedData>()->GetAutoBreadcrumbsOutput(pOutput);
		if (SUCCEEDED(result))
		{
			if (pOutput->pHeadAutoBreadcrumbNode != nullptr)
			{
				if (pOutput->pHeadAutoBreadcrumbNode->pCommandList != nullptr)
				{
					encode::WrapObject(__uuidof(ID3D12GraphicsCommandList), reinterpret_cast<void **>(pOutput->pHeadAutoBreadcrumbNode->pCommandList));
				}
				if (pOutput->pHeadAutoBreadcrumbNode->pCommandQueue != nullptr)
				{
					encode::WrapObject(__uuidof(ID3D12CommandQueue), reinterpret_cast<void **>(pOutput->pHeadAutoBreadcrumbNode->pCommandQueue));
				}
			}
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedData2Wrapper::GetPageFaultAllocationOutput(D3D12_DRED_PAGE_FAULT_OUTPUT *pOutput)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceRemovedExtendedData>()->GetPageFaultAllocationOutput(pOutput);
		return result;
	}

	// ID3D12DeviceRemovedExtendedData1
	HRESULT STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedData2Wrapper::GetAutoBreadcrumbsOutput1(D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT1 *pOutput)
	{
		// TODO: check wrap, fix
		const auto result = GetWrappedObjectAs<ID3D12DeviceRemovedExtendedData1>()->GetAutoBreadcrumbsOutput1(pOutput);
		if (SUCCEEDED(result))
		{
			if (pOutput->pHeadAutoBreadcrumbNode != nullptr)
			{
				if (pOutput->pHeadAutoBreadcrumbNode->pCommandList != nullptr)
				{
					encode::WrapObject(__uuidof(ID3D12GraphicsCommandList), reinterpret_cast<void **>(pOutput->pHeadAutoBreadcrumbNode->pCommandList));
				}
				if (pOutput->pHeadAutoBreadcrumbNode->pCommandQueue != nullptr)
				{
					encode::WrapObject(__uuidof(ID3D12CommandQueue), reinterpret_cast<void **>(pOutput->pHeadAutoBreadcrumbNode->pCommandQueue));
				}
			}
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedData2Wrapper::GetPageFaultAllocationOutput1(D3D12_DRED_PAGE_FAULT_OUTPUT1 *pOutput)
	{
		// TODO: check wrap, fix
		const auto result = GetWrappedObjectAs<ID3D12DeviceRemovedExtendedData1>()->GetPageFaultAllocationOutput1(pOutput);
		if (SUCCEEDED(result))
		{
			if (pOutput->pHeadExistingAllocationNode != nullptr)
			{
				if (pOutput->pHeadExistingAllocationNode->pObject != nullptr)
				{
					encode::WrapObject(__uuidof(IUnknown), reinterpret_cast<void **>(const_cast<IUnknown *>(pOutput->pHeadExistingAllocationNode->pObject)));
				}
			}
			if (pOutput->pHeadRecentFreedAllocationNode != nullptr)
			{
				if (pOutput->pHeadRecentFreedAllocationNode->pObject != nullptr)
				{
					encode::WrapObject(__uuidof(IUnknown), reinterpret_cast<void **>(const_cast<IUnknown *>(pOutput->pHeadRecentFreedAllocationNode->pObject)));
				}
			}
		}
		return result;
	}

	// ID3D12DeviceRemovedExtendedData2
	HRESULT STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedData2Wrapper::GetPageFaultAllocationOutput2(D3D12_DRED_PAGE_FAULT_OUTPUT2 *pOutput)
	{
		// TODO: check wrap, fix
		const auto result = GetWrappedObjectAs<ID3D12DeviceRemovedExtendedData2>()->GetPageFaultAllocationOutput2(pOutput);
		if (SUCCEEDED(result))
		{
			if (pOutput->pHeadRecentFreedAllocationNode != nullptr)
			{
				if (pOutput->pHeadExistingAllocationNode->pObject != nullptr)
				{
					encode::WrapObject(__uuidof(IUnknown), reinterpret_cast<void **>(const_cast<IUnknown *>(pOutput->pHeadExistingAllocationNode->pObject)));
				}
			}
			if (pOutput->pHeadRecentFreedAllocationNode->pObject != nullptr)
			{
				if (pOutput->pHeadRecentFreedAllocationNode->pObject != nullptr)
				{
					encode::WrapObject(__uuidof(IUnknown), reinterpret_cast<void **>(const_cast<IUnknown *>(pOutput->pHeadRecentFreedAllocationNode->pObject)));
				}
			}
		}
		return result;
	}

	D3D12_DRED_DEVICE_STATE STDMETHODCALLTYPE ID3D12DeviceRemovedExtendedData2Wrapper::GetDeviceState()
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceRemovedExtendedData2>()->GetDeviceState();
		return result;
	}
}