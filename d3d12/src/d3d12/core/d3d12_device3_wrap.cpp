//
// Created by ZZK on 2024/7/20.
//

#include <d3d12/core/d3d12_device3_wrap.h>

namespace gfxshim
{
    ID3D12Device3Wrapper::ID3D12Device3Wrapper(const IID &riid, IUnknown *object)
    : ID3D12Device2Wrapper(riid, object)
    {

    }

    ID3D12Device3Wrapper::~ID3D12Device3Wrapper() = default;

    HRESULT STDMETHODCALLTYPE ID3D12Device3Wrapper::OpenExistingHeapFromAddress(
            const void* pAddress,
            REFIID riid,
            void** ppvHeap)
    {
        return GetWrappedObjectAs<ID3D12Device3>()->OpenExistingHeapFromAddress(pAddress, riid, ppvHeap);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device3Wrapper::OpenExistingHeapFromFileMapping(
            HANDLE hFileMapping,
            REFIID riid,
            void** ppvHeap)
    {
        return GetWrappedObjectAs<ID3D12Device3>()->OpenExistingHeapFromFileMapping(hFileMapping, riid, ppvHeap);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device3Wrapper::EnqueueMakeResident(
            D3D12_RESIDENCY_FLAGS Flags,
            UINT NumObjects,
            ID3D12Pageable* const* ppObjects,
            ID3D12Fence* pFenceToSignal,
            UINT64 FenceValueToSignal)
    {
        return GetWrappedObjectAs<ID3D12Device3>()->EnqueueMakeResident(Flags, NumObjects, ppObjects, pFenceToSignal, FenceValueToSignal);
    }
}