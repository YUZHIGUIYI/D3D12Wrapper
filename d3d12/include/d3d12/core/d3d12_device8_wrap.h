//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <d3d12/core/d3d12_device7_wrap.h>

namespace gfxshim
{
    class ID3D12Device8Wrapper : public ID3D12Device7Wrapper
    {
    public:
        ID3D12Device8Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12Device8Wrapper() override;

        virtual D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE GetResourceAllocationInfo2(
                UINT visibleMask,
                UINT numResourceDescs,
                const D3D12_RESOURCE_DESC1* pResourceDescs,
                D3D12_RESOURCE_ALLOCATION_INFO1* pResourceAllocationInfo1);

        virtual HRESULT STDMETHODCALLTYPE CreateCommittedResource2(
                const D3D12_HEAP_PROPERTIES* pHeapProperties,
                D3D12_HEAP_FLAGS HeapFlags,
                const D3D12_RESOURCE_DESC1* pDesc,
                D3D12_RESOURCE_STATES InitialResourceState,
                const D3D12_CLEAR_VALUE* pOptimizedClearValue,
                ID3D12ProtectedResourceSession* pProtectedSession,
                REFIID riidResource,
                void** ppvResource);

        virtual HRESULT STDMETHODCALLTYPE CreatePlacedResource1(
                ID3D12Heap* pHeap,
                UINT64 HeapOffset,
                const D3D12_RESOURCE_DESC1* pDesc,
                D3D12_RESOURCE_STATES InitialState,
                const D3D12_CLEAR_VALUE* pOptimizedClearValue,
                REFIID riid,
                void** ppvResource);

        virtual void STDMETHODCALLTYPE CreateSamplerFeedbackUnorderedAccessView(
                ID3D12Resource* pTargetedResource,
                ID3D12Resource* pFeedbackResource,
                D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor);

        virtual void STDMETHODCALLTYPE GetCopyableFootprints1(
                const D3D12_RESOURCE_DESC1* pResourceDesc,
                UINT FirstSubresource,
                UINT NumSubresources,
                UINT64 BaseOffset,
                D3D12_PLACED_SUBRESOURCE_FOOTPRINT* pLayouts,
                UINT* pNumRows,
                UINT64* pRowSizeInBytes,
                UINT64* pTotalBytes);
    };
}
