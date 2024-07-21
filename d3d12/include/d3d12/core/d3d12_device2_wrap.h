//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <d3d12/core/d3d12_device1_wrap.h>

namespace gfxshim
{
    class ID3D12Device2Wrapper : public ID3D12Device1Wrapper
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
