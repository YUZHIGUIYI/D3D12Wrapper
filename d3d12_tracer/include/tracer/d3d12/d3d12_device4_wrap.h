//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <tracer/d3d12/d3d12_device3_wrap.h>

namespace gfxshim
{
    struct ID3D12Device4Wrapper : ID3D12Device3Wrapper
    {
    public:
        ID3D12Device4Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12Device4Wrapper() override;

        virtual HRESULT STDMETHODCALLTYPE CreateCommandList1(
                UINT nodeMask,
                D3D12_COMMAND_LIST_TYPE type,
                D3D12_COMMAND_LIST_FLAGS flags,
                REFIID riid,
                void** ppCommandList);

        virtual HRESULT STDMETHODCALLTYPE CreateProtectedResourceSession(
                const D3D12_PROTECTED_RESOURCE_SESSION_DESC* pDesc,
                REFIID riid,
                void** ppSession);

        virtual HRESULT STDMETHODCALLTYPE CreateCommittedResource1(
                const D3D12_HEAP_PROPERTIES* pHeapProperties,
                D3D12_HEAP_FLAGS HeapFlags,
                const D3D12_RESOURCE_DESC* pDesc,
                D3D12_RESOURCE_STATES InitialResourceState,
                const D3D12_CLEAR_VALUE* pOptimizedClearValue,
                ID3D12ProtectedResourceSession* pProtectedSession,
                REFIID riidResource,
                void** ppvResource);

        virtual HRESULT STDMETHODCALLTYPE CreateHeap1(
                const D3D12_HEAP_DESC* pDesc,
                ID3D12ProtectedResourceSession* pProtectedSession,
                REFIID riid,
                void** ppvHeap);

        virtual HRESULT STDMETHODCALLTYPE CreateReservedResource1(
                const D3D12_RESOURCE_DESC* pDesc,
                D3D12_RESOURCE_STATES InitialState,
                const D3D12_CLEAR_VALUE* pOptimizedClearValue,
                ID3D12ProtectedResourceSession* pProtectedSession,
                REFIID riid,
                void** ppvResource);

        virtual D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE GetResourceAllocationInfo1(
                UINT visibleMask,
                UINT numResourceDescs,
                const D3D12_RESOURCE_DESC* pResourceDescs,
                D3D12_RESOURCE_ALLOCATION_INFO1* pResourceAllocationInfo1);
    };
}
