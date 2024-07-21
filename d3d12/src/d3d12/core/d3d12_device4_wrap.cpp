//
// Created by ZZK on 2024/7/20.
//

#include <d3d12/core/d3d12_device4_wrap.h>

namespace gfxshim
{
    ID3D12Device4Wrapper::ID3D12Device4Wrapper(const IID &riid, IUnknown *object)
    : ID3D12Device3Wrapper(riid, object)
    {

    }

    ID3D12Device4Wrapper::~ID3D12Device4Wrapper() = default;

    HRESULT STDMETHODCALLTYPE ID3D12Device4Wrapper::CreateCommandList1(
            UINT nodeMask,
            D3D12_COMMAND_LIST_TYPE type,
            D3D12_COMMAND_LIST_FLAGS flags,
            REFIID riid,
            void** ppCommandList)
    {
        return GetWrappedObjectAs<ID3D12Device4>()->CreateCommandList1(nodeMask, type, flags, riid, ppCommandList);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device4Wrapper::CreateProtectedResourceSession(
            const D3D12_PROTECTED_RESOURCE_SESSION_DESC* pDesc,
            REFIID riid,
            void** ppSession)
    {
        return GetWrappedObjectAs<ID3D12Device4>()->CreateProtectedResourceSession(pDesc, riid, ppSession);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device4Wrapper::CreateCommittedResource1(
            const D3D12_HEAP_PROPERTIES* pHeapProperties,
            D3D12_HEAP_FLAGS HeapFlags,
            const D3D12_RESOURCE_DESC* pDesc,
            D3D12_RESOURCE_STATES InitialResourceState,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            ID3D12ProtectedResourceSession* pProtectedSession,
            REFIID riidResource,
            void** ppvResource)
    {
        return GetWrappedObjectAs<ID3D12Device4>()->CreateCommittedResource1(pHeapProperties, HeapFlags, pDesc, InitialResourceState,
                                                                            pOptimizedClearValue, pProtectedSession, riidResource, ppvResource);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device4Wrapper::CreateHeap1(
            const D3D12_HEAP_DESC* pDesc,
            ID3D12ProtectedResourceSession* pProtectedSession,
            REFIID riid,
            void** ppvHeap)
    {
        return GetWrappedObjectAs<ID3D12Device4>()->CreateHeap1(pDesc, pProtectedSession, riid, ppvHeap);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device4Wrapper::CreateReservedResource1(
            const D3D12_RESOURCE_DESC* pDesc,
            D3D12_RESOURCE_STATES InitialState,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            ID3D12ProtectedResourceSession* pProtectedSession,
            REFIID riid,
            void** ppvResource)
    {
        return GetWrappedObjectAs<ID3D12Device4>()->CreateReservedResource1(pDesc, InitialState, pOptimizedClearValue,
                                                                            pProtectedSession, riid, ppvResource);
    }

    D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE ID3D12Device4Wrapper::GetResourceAllocationInfo1(
            UINT visibleMask,
            UINT numResourceDescs,
            const D3D12_RESOURCE_DESC* pResourceDescs,
            D3D12_RESOURCE_ALLOCATION_INFO1* pResourceAllocationInfo1)
    {
        return GetWrappedObjectAs<ID3D12Device4>()->GetResourceAllocationInfo1(visibleMask, numResourceDescs, pResourceDescs, pResourceAllocationInfo1);
    }
}