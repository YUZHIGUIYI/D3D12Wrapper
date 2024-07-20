//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include "d3d12_command_list6_wrap.h"

namespace gfxshim
{
    class ID3D12GraphicsCommandList7Wrapper : public ID3D12GraphicsCommandList6Wrapper
    {
    public:
        ID3D12GraphicsCommandList7Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12GraphicsCommandList7Wrapper() override;

        virtual void STDMETHODCALLTYPE Barrier(
                UINT32 NumBarrierGroups,
                const D3D12_BARRIER_GROUP* pBarrierGroups);
    };
}
