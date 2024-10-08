//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <d3d12/core/d3d12_device2_wrap.h>

namespace gfxshim
{
    class ID3D12Device3Wrapper : public ID3D12Device2Wrapper
    {
    public:
        ID3D12Device3Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12Device3Wrapper() override;

        virtual HRESULT STDMETHODCALLTYPE OpenExistingHeapFromAddress(
                const void* pAddress,
                REFIID riid,
                void** ppvHeap);

        virtual HRESULT STDMETHODCALLTYPE OpenExistingHeapFromFileMapping(
                HANDLE hFileMapping,
                REFIID riid,
                void** ppvHeap);

        virtual HRESULT STDMETHODCALLTYPE EnqueueMakeResident(
                D3D12_RESIDENCY_FLAGS Flags,
                UINT NumObjects,
                ID3D12Pageable* const* ppObjects,
                ID3D12Fence* pFenceToSignal,
                UINT64 FenceValueToSignal);
    };
}
