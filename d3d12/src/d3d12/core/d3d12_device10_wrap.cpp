//
// Created by ZZK on 2024/7/20.
//

#include <d3d12/core/d3d12_device10_wrap.h>

namespace gfxshim
{
    ID3D12Device10Wrapper::ID3D12Device10Wrapper(const IID &riid, IUnknown *object)
    : ID3D12Device9Wrapper(riid, object)
    {

    }

    ID3D12Device10Wrapper::~ID3D12Device10Wrapper() = default;

    HRESULT STDMETHODCALLTYPE ID3D12Device10Wrapper::CreateCommittedResource3(
            const D3D12_HEAP_PROPERTIES* pHeapProperties,
            D3D12_HEAP_FLAGS HeapFlags,
            const D3D12_RESOURCE_DESC1* pDesc,
            D3D12_BARRIER_LAYOUT InitialLayout,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            ID3D12ProtectedResourceSession* pProtectedSession,
            UINT32 NumCastableFormats,
            DXGI_FORMAT* pCastableFormats,
            REFIID riidResource,
            void** ppvResource)
    {
        return GetWrappedObjectAs<ID3D12Device10>()->CreateCommittedResource3(pHeapProperties, HeapFlags, pDesc, InitialLayout,
                                                            pOptimizedClearValue, pProtectedSession, NumCastableFormats, pCastableFormats, riidResource, ppvResource);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device10Wrapper::CreatePlacedResource2(
            ID3D12Heap* pHeap,
            UINT64 HeapOffset,
            const D3D12_RESOURCE_DESC1* pDesc,
            D3D12_BARRIER_LAYOUT InitialLayout,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            UINT32 NumCastableFormats,
            DXGI_FORMAT* pCastableFormats,
            REFIID riid,
            void** ppvResource)
    {
        return GetWrappedObjectAs<ID3D12Device10>()->CreatePlacedResource2(pHeap, HeapOffset, pDesc, InitialLayout, pOptimizedClearValue,
                                                                            NumCastableFormats, pCastableFormats, riid, ppvResource);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device10Wrapper::CreateReservedResource2(
            const D3D12_RESOURCE_DESC* pDesc,
            D3D12_BARRIER_LAYOUT InitialLayout,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            ID3D12ProtectedResourceSession* pProtectedSession,
            UINT32 NumCastableFormats,
            DXGI_FORMAT* pCastableFormats,
            REFIID riid,
            void** ppvResource)
    {
        return GetWrappedObjectAs<ID3D12Device10>()->CreateReservedResource2(pDesc, InitialLayout, pOptimizedClearValue, pProtectedSession,
                                                                            NumCastableFormats, pCastableFormats, riid, ppvResource);
    }
}