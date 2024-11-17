//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <tracer/d3d12/d3d12_device10_wrap.h>

namespace gfxshim
{
    class ID3D12Device11Wrapper : public ID3D12Device10Wrapper
    {
    public:
        ID3D12Device11Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12Device11Wrapper() override;

        // TODO: implement CreateSampler2
    };
}
