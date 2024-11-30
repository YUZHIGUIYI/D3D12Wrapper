//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <tracer/d3d12/d3d12_device10_wrap.h>

namespace gfxshim
{
    struct ID3D12Device11Wrapper : ID3D12Device10Wrapper
    {
    public:
        ID3D12Device11Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12Device11Wrapper() override;

		virtual void STDMETHODCALLTYPE CreateSampler2(const D3D12_SAMPLER_DESC2* pDesc, D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor);
    };
}
