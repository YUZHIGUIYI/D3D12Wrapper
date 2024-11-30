//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <tracer/d3d12/d3d12_device1_wrap.h>

namespace gfxshim
{
    struct ID3D12Device2Wrapper : ID3D12Device1Wrapper
    {
    public:
        ID3D12Device2Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12Device2Wrapper() override;

        virtual HRESULT STDMETHODCALLTYPE CreatePipelineState(
                const D3D12_PIPELINE_STATE_STREAM_DESC* pDesc,
                REFIID riid,
                void** ppPipelineState);
    };
}
