//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include "d3d12_command_list2_wrap.h"

namespace gfxshim
{
    class ID3D12GraphicsCommandList3Wrapper : public ID3D12GraphicsCommandList2Wrapper
    {
    public:
        ID3D12GraphicsCommandList3Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12GraphicsCommandList3Wrapper() override;

        virtual void STDMETHODCALLTYPE SetProtectedResourceSession(
                ID3D12ProtectedResourceSession* pProtectedResourceSession);
    };
}
