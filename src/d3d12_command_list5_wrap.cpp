#include "d3d12_command_list.h"

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::RSSetShadingRate(D3D12_SHADING_RATE baseShadingRate,
                                    const D3D12_SHADING_RATE_COMBINER *combiners)
{
    m_pList5->RSSetShadingRate(baseShadingRate, combiners);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::RSSetShadingRateImage(ID3D12Resource *shadingRateImage)
{
    m_pList5->RSSetShadingRateImage(shadingRateImage);
}

