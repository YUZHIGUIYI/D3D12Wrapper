//
// Created by ZZK on 2024/7/20.
//

#include <d3d12/core/d3d12_device1_wrap.h>

namespace gfxshim
{
    ID3D12Device1Wrapper::ID3D12Device1Wrapper(const IID &riid, IUnknown *object)
    : ID3D12DeviceWrapper(riid, object)
    {

    }

    ID3D12Device1Wrapper::~ID3D12Device1Wrapper() = default;

    HRESULT STDMETHODCALLTYPE ID3D12Device1Wrapper::CreatePipelineLibrary(
            const void* pLibraryBlob,
            SIZE_T BlobLength,
            REFIID riid,
            void** ppPipelineLibrary)
    {
        return GetWrappedObjectAs<ID3D12Device1>()->CreatePipelineLibrary(pLibraryBlob, BlobLength, riid,
                                                                            ppPipelineLibrary);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device1Wrapper::SetEventOnMultipleFenceCompletion(
            ID3D12Fence* const* ppFences,
            const UINT64* pFenceValues,
            UINT NumFences,
            D3D12_MULTIPLE_FENCE_WAIT_FLAGS Flags,
            HANDLE hEvent)
    {
        return GetWrappedObjectAs<ID3D12Device1>()->SetEventOnMultipleFenceCompletion(ppFences, pFenceValues, NumFences, Flags, hEvent);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device1Wrapper::SetResidencyPriority(
            UINT NumObjects,
            ID3D12Pageable* const* ppObjects,
            const D3D12_RESIDENCY_PRIORITY* pPriorities)
    {
        return GetWrappedObjectAs<ID3D12Device1>()->SetResidencyPriority(NumObjects, ppObjects, pPriorities);
    }
}