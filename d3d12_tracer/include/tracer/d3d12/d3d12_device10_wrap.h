//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <tracer/d3d12/d3d12_device9_wrap.h>

namespace gfxshim
{
    struct ID3D12Device10Wrapper : ID3D12Device9Wrapper
    {
    public:
        ID3D12Device10Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12Device10Wrapper() override;

        virtual HRESULT STDMETHODCALLTYPE CreateCommittedResource3(
                const D3D12_HEAP_PROPERTIES* pHeapProperties,
                D3D12_HEAP_FLAGS HeapFlags,
                const D3D12_RESOURCE_DESC1* pDesc,
                D3D12_BARRIER_LAYOUT InitialLayout,
                const D3D12_CLEAR_VALUE* pOptimizedClearValue,
                ID3D12ProtectedResourceSession* pProtectedSession,
                UINT32 NumCastableFormats,
                DXGI_FORMAT* pCastableFormats,
                REFIID riidResource,
                void** ppvResource);

        virtual HRESULT STDMETHODCALLTYPE CreatePlacedResource2(
                ID3D12Heap* pHeap,
                UINT64 HeapOffset,
                const D3D12_RESOURCE_DESC1* pDesc,
                D3D12_BARRIER_LAYOUT InitialLayout,
                const D3D12_CLEAR_VALUE* pOptimizedClearValue,
                UINT32 NumCastableFormats,
                DXGI_FORMAT* pCastableFormats,
                REFIID riid,
                void** ppvResource);

        virtual HRESULT STDMETHODCALLTYPE CreateReservedResource2(
                const D3D12_RESOURCE_DESC* pDesc,
                D3D12_BARRIER_LAYOUT InitialLayout,
                const D3D12_CLEAR_VALUE* pOptimizedClearValue,
                ID3D12ProtectedResourceSession* pProtectedSession,
                UINT32 NumCastableFormats,
                DXGI_FORMAT* pCastableFormats,
                REFIID riid,
                void** ppvResource);
    };
}
