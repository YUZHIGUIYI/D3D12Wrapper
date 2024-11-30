//
// Created by ZZK on 2024/7/20.
//

#include <tracer/d3d12/d3d12_device8_wrap.h>
#include <tracer/core/wrapper_creators.h>

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
        const auto result = GetWrappedObjectAs<ID3D12Device8>()->GetResourceAllocationInfo2(visibleMask, numResourceDescs, pResourceDescs, pResourceAllocationInfo1);
		return result;
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
        const auto result = GetWrappedObjectAs<ID3D12Device8>()->CreateCommittedResource2(pHeapProperties, HeapFlags, pDesc, InitialResourceState,
                                                                            pOptimizedClearValue, encode::GetWrappedObject<ID3D12ProtectedResourceSession>(pProtectedSession), riidResource, ppvResource);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riidResource, ppvResource);
		}
		return result;
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
        const auto result = GetWrappedObjectAs<ID3D12Device8>()->CreatePlacedResource1(encode::GetWrappedObject<ID3D12Heap>(pHeap), HeapOffset, pDesc, InitialState,
                                                                            pOptimizedClearValue, riid, ppvResource);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvResource);
		}
		return result;
    }

    void STDMETHODCALLTYPE ID3D12Device8Wrapper::CreateSamplerFeedbackUnorderedAccessView(
            ID3D12Resource* pTargetedResource,
            ID3D12Resource* pFeedbackResource,
            D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
    {
		// TODO: wrap descriptor
        GetWrappedObjectAs<ID3D12Device8>()->CreateSamplerFeedbackUnorderedAccessView(encode::GetWrappedObject<ID3D12Resource>(pTargetedResource),
																					encode::GetWrappedObject<ID3D12Resource>(pFeedbackResource), DestDescriptor);
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