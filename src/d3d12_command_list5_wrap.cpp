#include "d3d12_command_list_wrap.h"
#include "d3d12_command_list5_wrap.h"

namespace gfxshim
{
    ID3D12GraphicsCommandList5Wrapper::ID3D12GraphicsCommandList5Wrapper(const IID &riid, IUnknown *object)
    : ID3D12GraphicsCommandList4Wrapper(riid, object)
    {

    }

    ID3D12GraphicsCommandList5Wrapper::~ID3D12GraphicsCommandList5Wrapper() = default;

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList5Wrapper::RSSetShadingRate(
            D3D12_SHADING_RATE baseShadingRate,
            const D3D12_SHADING_RATE_COMBINER* combiners)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList5>()->RSSetShadingRate(baseShadingRate, combiners);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList5Wrapper::RSSetShadingRateImage(
            ID3D12Resource* shadingRateImage)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList5>()->RSSetShadingRateImage(shadingRateImage);
    }
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::RSSetShadingRate(D3D12_SHADING_RATE baseShadingRate,
                                    const D3D12_SHADING_RATE_COMBINER *combiners)
{
    m_pList5->RSSetShadingRate(baseShadingRate, combiners);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::RSSetShadingRateImage(ID3D12Resource *shadingRateImage)
{
    m_pList5->RSSetShadingRateImage(shadingRateImage);
}

