//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <tracer/d3d12/d3d12_device11_wrap.h>

namespace gfxshim
{
    class ID3D12Device12Wrapper : public ID3D12Device11Wrapper
    {
    public:
        ID3D12Device12Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12Device12Wrapper() override;

        // TODO: implement GetResourceAllocationInfo3
    };
}