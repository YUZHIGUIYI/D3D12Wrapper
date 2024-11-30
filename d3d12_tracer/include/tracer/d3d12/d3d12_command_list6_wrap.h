//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <tracer/d3d12/d3d12_command_list5_wrap.h>

namespace gfxshim
{
    struct ID3D12GraphicsCommandList6Wrapper : ID3D12GraphicsCommandList5Wrapper
    {
    public:
        ID3D12GraphicsCommandList6Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12GraphicsCommandList6Wrapper() override;

        virtual void STDMETHODCALLTYPE DispatchMesh(
                UINT ThreadGroupCountX,
                UINT ThreadGroupCountY,
                UINT ThreadGroupCountZ);
    };
}
