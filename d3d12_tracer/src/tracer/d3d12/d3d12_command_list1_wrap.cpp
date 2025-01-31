#include <tracer/d3d12/d3d12_command_list_wrap.h>

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::AtomicCopyBufferUINT(ID3D12Resource *pDstBuffer, UINT64 DstOffset,
                                        ID3D12Resource *pSrcBuffer, UINT64 SrcOffset,
                                        UINT Dependencies,
                                        ID3D12Resource *const *ppDependentResources,
                                        const D3D12_SUBRESOURCE_RANGE_UINT64 *
                                        pDependentSubresourceRanges)
{
    m_pList1->AtomicCopyBufferUINT(pDstBuffer, DstOffset, pSrcBuffer, SrcOffset, Dependencies, ppDependentResources, pDependentSubresourceRanges);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::AtomicCopyBufferUINT64(ID3D12Resource *pDstBuffer, UINT64 DstOffset,
                                        ID3D12Resource *pSrcBuffer, UINT64 SrcOffset,
                                        UINT Dependencies,
                                        ID3D12Resource *const *ppDependentResources,
                                        const D3D12_SUBRESOURCE_RANGE_UINT64 *
                                        pDependentSubresourceRanges)
{
    m_pList1->AtomicCopyBufferUINT64(pDstBuffer, DstOffset, pSrcBuffer, SrcOffset, Dependencies, ppDependentResources, pDependentSubresourceRanges);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::OMSetDepthBounds(FLOAT Min, FLOAT Max)
{
    m_pList1->OMSetDepthBounds(Min, Max);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetSamplePositions(UINT NumSamplesPerPixel, UINT NumPixels,
                                    D3D12_SAMPLE_POSITION *pSamplePositions)
{
    m_pList1->SetSamplePositions(NumSamplesPerPixel, NumPixels, pSamplePositions);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::ResolveSubresourceRegion(ID3D12Resource *pDstResource, UINT DstSubresource,
                                            UINT DstX, UINT DstY,
                                            ID3D12Resource *pSrcResource, UINT SrcSubresource,
                                            D3D12_RECT *pSrcRect, DXGI_FORMAT Format,
                                            D3D12_RESOLVE_MODE ResolveMode)
{
    m_pList1->ResolveSubresourceRegion(pDstResource, DstSubresource, DstX, DstY, pSrcResource, SrcSubresource, pSrcRect, Format, ResolveMode);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetViewInstanceMask(UINT Mask)
{
    m_pList1->SetViewInstanceMask(Mask);
}

