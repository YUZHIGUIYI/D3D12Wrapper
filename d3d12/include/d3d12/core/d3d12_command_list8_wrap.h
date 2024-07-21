//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <d3d12/core/d3d12_command_list7_wrap.h>

namespace gfxshim
{
    class ID3D12GraphicsCommandList8Wrapper : public ID3D12GraphicsCommandList7Wrapper
    {
    public:
        ID3D12GraphicsCommandList8Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12GraphicsCommandList8Wrapper() override;

        // TODO: implement OMSetFrontAndBackStencilRef
    };
}
