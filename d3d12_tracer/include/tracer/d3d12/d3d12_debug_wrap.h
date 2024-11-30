//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12DebugWrapper : IUnknownWrapper
	{
	public:
		ID3D12DebugWrapper(REFIID riid, IUnknown *object);

		~ID3D12DebugWrapper() override = default;

		virtual void STDMETHODCALLTYPE EnableDebugLayer();
	};

	struct ID3D12Debug1Wrapper : IUnknownWrapper
	{
	public:
		ID3D12Debug1Wrapper(REFIID riid, IUnknown *object);

		~ID3D12Debug1Wrapper() override = default;

		virtual void STDMETHODCALLTYPE EnableDebugLayer();

		virtual void STDMETHODCALLTYPE SetEnableGPUBasedValidation(BOOL Enable);

		virtual void STDMETHODCALLTYPE SetEnableSynchronizedCommandQueueValidation(BOOL Enable);
	};

	struct ID3D12Debug2Wrapper : IUnknownWrapper
	{
	public:
		ID3D12Debug2Wrapper(REFIID riid, IUnknown *object);

		~ID3D12Debug2Wrapper() override = default;

		virtual void STDMETHODCALLTYPE SetGPUBasedValidationFlags(D3D12_GPU_BASED_VALIDATION_FLAGS Flags);
	};

	struct ID3D12Debug3Wrapper : ID3D12DebugWrapper
	{
	public:
		ID3D12Debug3Wrapper(REFIID riid, IUnknown *object);

		~ID3D12Debug3Wrapper() override = default;

		virtual void STDMETHODCALLTYPE SetEnableGPUBasedValidation(BOOL Enable);

		virtual void STDMETHODCALLTYPE SetEnableSynchronizedCommandQueueValidation(BOOL Enable);

		virtual void STDMETHODCALLTYPE SetGPUBasedValidationFlags(D3D12_GPU_BASED_VALIDATION_FLAGS Flags);
	};

	struct ID3D12Debug4Wrapper : ID3D12Debug3Wrapper
	{
	public:
		ID3D12Debug4Wrapper(REFIID riid, IUnknown *object);

		~ID3D12Debug4Wrapper() override = default;

		virtual void STDMETHODCALLTYPE DisableDebugLayer();
	};

	struct ID3D12Debug5Wrapper : ID3D12Debug4Wrapper
	{
	public:
		ID3D12Debug5Wrapper(REFIID riid, IUnknown *object);

		~ID3D12Debug5Wrapper() override = default;

		virtual void STDMETHODCALLTYPE SetEnableAutoName(BOOL Enable);
	};

	struct ID3D12Debug6Wrapper : ID3D12Debug5Wrapper
	{
	public:
		ID3D12Debug6Wrapper(REFIID riid, IUnknown *object);

		virtual void STDMETHODCALLTYPE SetForceLegacyBarrierValidation(BOOL Enable);
	};

	struct ID3D12DebugDeviceWrapper : IUnknownWrapper
	{
	public:
		ID3D12DebugDeviceWrapper(REFIID riid, IUnknown *object);

		~ID3D12DebugDeviceWrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE SetFeatureMask(D3D12_DEBUG_FEATURE Mask);

		virtual D3D12_DEBUG_FEATURE STDMETHODCALLTYPE GetFeatureMask();

		virtual HRESULT STDMETHODCALLTYPE ReportLiveDeviceObjects(D3D12_RLDO_FLAGS Flags);
	};

	struct ID3D12DebugDevice1Wrapper : IUnknownWrapper
	{
	public:
		ID3D12DebugDevice1Wrapper(REFIID riid, IUnknown *object);

		~ID3D12DebugDevice1Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE SetDebugParameter(D3D12_DEBUG_DEVICE_PARAMETER_TYPE Type, const void* pData, UINT DataSize);

		virtual HRESULT STDMETHODCALLTYPE GetDebugParameter(D3D12_DEBUG_DEVICE_PARAMETER_TYPE Type, void* pData, UINT DataSize);

		virtual HRESULT STDMETHODCALLTYPE ReportLiveDeviceObjects(D3D12_RLDO_FLAGS Flags);
	};

	struct ID3D12DebugDevice2Wrapper : ID3D12DebugDeviceWrapper
	{
	public:
		ID3D12DebugDevice2Wrapper(REFIID riid, IUnknown *object);

		~ID3D12DebugDevice2Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE SetDebugParameter(D3D12_DEBUG_DEVICE_PARAMETER_TYPE Type, const void* pData, UINT DataSize);

		virtual HRESULT STDMETHODCALLTYPE GetDebugParameter(D3D12_DEBUG_DEVICE_PARAMETER_TYPE Type, void* pData, UINT DataSize);
	};

	struct ID3D12DebugCommandQueueWrapper : IUnknownWrapper
	{
	public:
		ID3D12DebugCommandQueueWrapper(REFIID riid, IUnknown *object);

		~ID3D12DebugCommandQueueWrapper() override = default;

		virtual BOOL STDMETHODCALLTYPE AssertResourceState(ID3D12Resource* pResource, UINT Subresource, UINT State);
	};

	struct ID3D12DebugCommandQueue1Wrapper : ID3D12DebugCommandQueueWrapper
	{
	public:
		ID3D12DebugCommandQueue1Wrapper(REFIID riid, IUnknown *object);

		~ID3D12DebugCommandQueue1Wrapper() override = default;

		virtual void STDMETHODCALLTYPE AssertResourceAccess(ID3D12Resource* pResource, UINT Subresource, D3D12_BARRIER_ACCESS Access);

		virtual void STDMETHODCALLTYPE AssertTextureLayout(ID3D12Resource* pResource, UINT Subresource, D3D12_BARRIER_LAYOUT Layout);
	};

	struct ID3D12DebugCommandListWrapper : IUnknownWrapper
	{
	public:
		ID3D12DebugCommandListWrapper(REFIID riid, IUnknown *object);

		~ID3D12DebugCommandListWrapper() override = default;

		virtual BOOL STDMETHODCALLTYPE AssertResourceState(ID3D12Resource* pResource, UINT Subresource, UINT State);

		virtual HRESULT STDMETHODCALLTYPE SetFeatureMask(D3D12_DEBUG_FEATURE Mask);

		virtual D3D12_DEBUG_FEATURE STDMETHODCALLTYPE GetFeatureMask();
	};

	struct ID3D12DebugCommandList1Wrapper : IUnknownWrapper
	{
	public:
		ID3D12DebugCommandList1Wrapper(REFIID riid, IUnknown *object);

		~ID3D12DebugCommandList1Wrapper() override = default;

		virtual BOOL STDMETHODCALLTYPE AssertResourceState(ID3D12Resource* pResource, UINT Subresource, UINT State);

		virtual HRESULT STDMETHODCALLTYPE SetDebugParameter(
						D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
						const void* pData,
						UINT DataSize);

		virtual HRESULT STDMETHODCALLTYPE GetDebugParameter(
						D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
						void* pData,
						UINT DataSize);
	};

	struct ID3D12DebugCommandList2Wrapper : ID3D12DebugCommandListWrapper
	{
	public:
		ID3D12DebugCommandList2Wrapper(REFIID riid, IUnknown *object);

		~ID3D12DebugCommandList2Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE SetDebugParameter(
						D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
						const void* pData,
						UINT DataSize);

		virtual HRESULT STDMETHODCALLTYPE GetDebugParameter(
						D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
						void* pData,
						UINT DataSize);
	};

	struct ID3D12DebugCommandList3Wrapper : ID3D12DebugCommandList2Wrapper
	{
	public:
		ID3D12DebugCommandList3Wrapper(REFIID riid, IUnknown *object);

		~ID3D12DebugCommandList3Wrapper() override = default;

		virtual void STDMETHODCALLTYPE AssertResourceAccess(
						ID3D12Resource* pResource,
						UINT Subresource,
						D3D12_BARRIER_ACCESS Access);

		virtual void STDMETHODCALLTYPE AssertTextureLayout(
						ID3D12Resource* pResource,
						UINT Subresource,
						D3D12_BARRIER_LAYOUT Layout);
	};
}
