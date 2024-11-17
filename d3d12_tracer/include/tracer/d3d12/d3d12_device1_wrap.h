//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <tracer/d3d12/d3d12_device_wrap.h>

namespace gfxshim
{
    class ID3D12Device1Wrapper : public ID3D12DeviceWrapper
    {
    public:
        ID3D12Device1Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12Device1Wrapper() override;

        virtual HRESULT STDMETHODCALLTYPE CreatePipelineLibrary(
                const void* pLibraryBlob,
                SIZE_T BlobLength,
                REFIID riid,
                void** ppPipelineLibrary);

        virtual HRESULT STDMETHODCALLTYPE SetEventOnMultipleFenceCompletion(
                ID3D12Fence* const* ppFences,
                const UINT64* pFenceValues,
                UINT NumFences,
                D3D12_MULTIPLE_FENCE_WAIT_FLAGS Flags,
                HANDLE hEvent);

        virtual HRESULT STDMETHODCALLTYPE SetResidencyPriority(
                UINT NumObjects,
                ID3D12Pageable* const* ppObjects,
                const D3D12_RESIDENCY_PRIORITY* pPriorities);
    };
}
















