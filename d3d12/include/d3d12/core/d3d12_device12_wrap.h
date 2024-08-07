//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <d3d12/core/d3d12_device11_wrap.h>

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