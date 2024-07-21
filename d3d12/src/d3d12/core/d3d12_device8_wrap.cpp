//
// Created by ZZK on 2024/7/20.
//

#include <d3d12/core/d3d12_device8_wrap.h>

namespace gfxshim
{
    ID3D12Device8Wrapper::ID3D12Device8Wrapper(const IID &riid, IUnknown *object)
    : ID3D12Device7Wrapper(riid, object)
    {

    }

    ID3D12Device8Wrapper::~ID3D12Device8Wrapper() = default;

    D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE ID3D12Device8Wrapper::GetResourceAllocationInfo2(
            UINT visibleMask,
            UINT numResourceDescs,
            const D3D12_RESOURCE_DESC1* pResourceDescs,
            D3D12_RESOURCE_ALLOCATION_INFO1* pResourceAllocationInfo1)
    {
        return GetWrappedObjectAs<ID3D12Device8>()->GetResourceAllocationInfo2(visibleMask, numResourceDescs, pResourceDescs, pResourceAllocationInfo1);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device8Wrapper::CreateCommittedResource2(
            const D3D12_HEAP_PROPERTIES* pHeapProperties,
            D3D12_HEAP_FLAGS HeapFlags,
            const D3D12_RESOURCE_DESC1* pDesc,
            D3D12_RESOURCE_STATES InitialResourceState,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            ID3D12ProtectedResourceSession* pProtectedSession,
            REFIID riidResource,
            void** ppvResource)
    {
        return GetWrappedObjectAs<ID3D12Device8>()->CreateCommittedResource2(pHeapProperties, HeapFlags, pDesc, InitialResourceState,
                                                                            pOptimizedClearValue, pProtectedSession, riidResource, ppvResource);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device8Wrapper::CreatePlacedResource1(
            ID3D12Heap* pHeap,
            UINT64 HeapOffset,
            const D3D12_RESOURCE_DESC1* pDesc,
            D3D12_RESOURCE_STATES InitialState,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            REFIID riid,
            void** ppvResource)
    {
        return GetWrappedObjectAs<ID3D12Device8>()->CreatePlacedResource1(pHeap, HeapOffset, pDesc, InitialState,
                                                                            pOptimizedClearValue, riid, ppvResource);
    }

    void STDMETHODCALLTYPE ID3D12Device8Wrapper::CreateSamplerFeedbackUnorderedAccessView(
            ID3D12Resource* pTargetedResource,
            ID3D12Resource* pFeedbackResource,
            D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
    {
        GetWrappedObjectAs<ID3D12Device8>()->CreateSamplerFeedbackUnorderedAccessView(pTargetedResource, pFeedbackResource, DestDescriptor);
    }

    void STDMETHODCALLTYPE ID3D12Device8Wrapper::GetCopyableFootprints1(
            const D3D12_RESOURCE_DESC1* pResourceDesc,
            UINT FirstSubresource,
            UINT NumSubresources,
            UINT64 BaseOffset,
            D3D12_PLACED_SUBRESOURCE_FOOTPRINT* pLayouts,
            UINT* pNumRows,
            UINT64* pRowSizeInBytes,
            UINT64* pTotalBytes)
    {
        GetWrappedObjectAs<ID3D12Device8>()->GetCopyableFootprints1(pResourceDesc, FirstSubresource, NumSubresources, BaseOffset,
                                                                    pLayouts, pNumRows, pRowSizeInBytes, pTotalBytes);
    }
}