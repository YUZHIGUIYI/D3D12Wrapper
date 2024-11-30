//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <tracer/d3d12/d3d12_command_list4_wrap.h>

namespace gfxshim
{
    struct ID3D12GraphicsCommandList5Wrapper : ID3D12GraphicsCommandList4Wrapper
    {
    public:
        ID3D12GraphicsCommandList5Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12GraphicsCommandList5Wrapper() override;

        virtual void STDMETHODCALLTYPE RSSetShadingRate(
                D3D12_SHADING_RATE baseShadingRate,
                const D3D12_SHADING_RATE_COMBINER* combiners);

        virtual void STDMETHODCALLTYPE RSSetShadingRateImage(
                ID3D12Resource* shadingRateImage);
    };
}
