//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <tracer/d3d12/d3d12_command_list7_wrap.h>

namespace gfxshim
{
    struct ID3D12GraphicsCommandList8Wrapper : ID3D12GraphicsCommandList7Wrapper
    {
    public:
        ID3D12GraphicsCommandList8Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12GraphicsCommandList8Wrapper() override;

		virtual void STDMETHODCALLTYPE OMSetFrontAndBackStencilRef(UINT FrontStencilRef, UINT BackStencilRef);
    };
}
