//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include "d3d12_command_list8_wrap.h"

namespace gfxshim
{
    class ID3D12GraphicsCommandList9Wrapper : public ID3D12GraphicsCommandList8Wrapper
    {
    public:
        ID3D12GraphicsCommandList9Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12GraphicsCommandList9Wrapper() override;

        // TODO: implement RSSetDepthBias and IASetIndexBufferStripCutValue
    };
}
