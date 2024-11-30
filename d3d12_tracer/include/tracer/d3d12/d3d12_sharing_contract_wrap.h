//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12SharingContractWrapper : IUnknownWrapper
	{
	public:
		ID3D12SharingContractWrapper(REFIID riid, IUnknown *object);

		~ID3D12SharingContractWrapper() override = default;

		virtual void STDMETHODCALLTYPE Present(ID3D12Resource* pResource, UINT Subresource, HWND window);

		virtual void STDMETHODCALLTYPE SharedFenceSignal(ID3D12Fence* pFence, UINT64 FenceValue);

		virtual void STDMETHODCALLTYPE BeginCapturableWork(REFGUID guid);

		virtual void STDMETHODCALLTYPE EndCapturableWork(REFGUID guid);
	};

	struct ID3D12ManualWriteTrackingResourceWrapper : IUnknownWrapper
	{
	public:
		ID3D12ManualWriteTrackingResourceWrapper(REFIID riid, IUnknown *object);

		~ID3D12ManualWriteTrackingResourceWrapper() override = default;

		virtual void STDMETHODCALLTYPE TrackWrite(UINT Subresource, const D3D12_RANGE* pWrittenRange);
	};
}
