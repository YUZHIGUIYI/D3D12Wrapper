//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <d3d12/core/d3d12_command_list5_wrap.h>

namespace gfxshim
{
    class ID3D12GraphicsCommandList6Wrapper : public ID3D12GraphicsCommandList5Wrapper
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
