//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <tracer/d3d12/d3d12_command_list_wrap.h>

namespace gfxshim
{
    struct ID3D12GraphicsCommandList1Wrapper : ID3D12CommandListWrapper
    {
    public:
        ID3D12GraphicsCommandList1Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12GraphicsCommandList1Wrapper() override;

        virtual void STDMETHODCALLTYPE AtomicCopyBufferUINT(
                ID3D12Resource* pDstBuffer,
                UINT64 DstOffset,
                ID3D12Resource* pSrcBuffer,
                UINT64 SrcOffset,
                UINT Dependencies,
                ID3D12Resource* const* ppDependentResources,
                const D3D12_SUBRESOURCE_RANGE_UINT64* pDependentSubresourceRanges);

        virtual void STDMETHODCALLTYPE AtomicCopyBufferUINT64(
                ID3D12Resource* pDstBuffer,
                UINT64 DstOffset,
                ID3D12Resource* pSrcBuffer,
                UINT64 SrcOffset,
                UINT Dependencies,
                ID3D12Resource* const* ppDependentResources,
                const D3D12_SUBRESOURCE_RANGE_UINT64* pDependentSubresourceRanges);

        virtual void STDMETHODCALLTYPE OMSetDepthBounds(
                FLOAT Min,
                FLOAT Max);

        virtual void STDMETHODCALLTYPE SetSamplePositions(
                UINT NumSamplesPerPixel,
                UINT NumPixels,
                D3D12_SAMPLE_POSITION* pSamplePositions);

        virtual void STDMETHODCALLTYPE ResolveSubresourceRegion(
                ID3D12Resource* pDstResource,
                UINT DstSubresource,
                UINT DstX,
                UINT DstY,
                ID3D12Resource* pSrcResource,
                UINT SrcSubresource,
                D3D12_RECT* pSrcRect,
                DXGI_FORMAT Format,
                D3D12_RESOLVE_MODE ResolveMode);

        virtual void STDMETHODCALLTYPE SetViewInstanceMask(
                UINT Mask);
    };
}
