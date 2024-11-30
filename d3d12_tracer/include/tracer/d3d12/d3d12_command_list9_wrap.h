//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <tracer/d3d12/d3d12_command_list8_wrap.h>

namespace gfxshim
{
    struct ID3D12GraphicsCommandList9Wrapper : ID3D12GraphicsCommandList8Wrapper
    {
    public:
        ID3D12GraphicsCommandList9Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12GraphicsCommandList9Wrapper() override;

		virtual void STDMETHODCALLTYPE RSSetDepthBias(
					FLOAT DepthBias,
					FLOAT DepthBiasClamp,
					FLOAT SlopeScaledDepthBias);

		virtual void STDMETHODCALLTYPE IASetIndexBufferStripCutValue(
					D3D12_INDEX_BUFFER_STRIP_CUT_VALUE IBStripCutValue);
    };
}
