//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12DeviceRemovedExtendedDataSettingsWrapper : IUnknownWrapper
	{
	public:
		ID3D12DeviceRemovedExtendedDataSettingsWrapper(REFIID riid, IUnknown *object);

		~ID3D12DeviceRemovedExtendedDataSettingsWrapper() override = default;

		virtual void STDMETHODCALLTYPE SetAutoBreadcrumbsEnablement(D3D12_DRED_ENABLEMENT Enablement);

		virtual void STDMETHODCALLTYPE SetPageFaultEnablement(D3D12_DRED_ENABLEMENT Enablement);

		virtual void STDMETHODCALLTYPE SetWatsonDumpEnablement(D3D12_DRED_ENABLEMENT Enablement);
	};

	struct ID3D12DeviceRemovedExtendedDataSettings1Wrapper : ID3D12DeviceRemovedExtendedDataSettingsWrapper
	{
	public:
		ID3D12DeviceRemovedExtendedDataSettings1Wrapper(REFIID riid, IUnknown *object);

		~ID3D12DeviceRemovedExtendedDataSettings1Wrapper() override = default;

		virtual void STDMETHODCALLTYPE SetBreadcrumbContextEnablement(D3D12_DRED_ENABLEMENT Enablement);
	};

	struct ID3D12DeviceRemovedExtendedDataSettings2Wrapper : ID3D12DeviceRemovedExtendedDataSettings1Wrapper
	{
	public:
		ID3D12DeviceRemovedExtendedDataSettings2Wrapper(REFIID riid, IUnknown *object);

		~ID3D12DeviceRemovedExtendedDataSettings2Wrapper() override = default;

		virtual void STDMETHODCALLTYPE UseMarkersOnlyAutoBreadcrumbs(BOOL MarkersOnly);
	};

	struct ID3D12DeviceRemovedExtendedDataWrapper : IUnknownWrapper
	{
	public:
		ID3D12DeviceRemovedExtendedDataWrapper(REFIID riid, IUnknown *object);

		~ID3D12DeviceRemovedExtendedDataWrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE GetAutoBreadcrumbsOutput(D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT* pOutput);

		virtual HRESULT STDMETHODCALLTYPE GetPageFaultAllocationOutput(D3D12_DRED_PAGE_FAULT_OUTPUT* pOutput);
	};

	struct ID3D12DeviceRemovedExtendedData1Wrapper : ID3D12DeviceRemovedExtendedDataWrapper
	{
	public:
		ID3D12DeviceRemovedExtendedData1Wrapper(REFIID riid, IUnknown *object);

		~ID3D12DeviceRemovedExtendedData1Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE GetAutoBreadcrumbsOutput1(D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT1* pOutput);

		virtual HRESULT STDMETHODCALLTYPE GetPageFaultAllocationOutput1(D3D12_DRED_PAGE_FAULT_OUTPUT1* pOutput);
	};

	struct ID3D12DeviceRemovedExtendedData2Wrapper : ID3D12DeviceRemovedExtendedData1Wrapper
	{
	public:
		ID3D12DeviceRemovedExtendedData2Wrapper(REFIID riid, IUnknown *object);

		~ID3D12DeviceRemovedExtendedData2Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE GetPageFaultAllocationOutput2(D3D12_DRED_PAGE_FAULT_OUTPUT2* pOutput);

		virtual D3D12_DRED_DEVICE_STATE STDMETHODCALLTYPE GetDeviceState();
	};
}
