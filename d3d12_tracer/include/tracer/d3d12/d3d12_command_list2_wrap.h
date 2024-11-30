//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <tracer/d3d12/d3d12_command_list1_wrap.h>

namespace gfxshim
{
    struct ID3D12GraphicsCommandList2Wrapper : ID3D12GraphicsCommandList1Wrapper
    {
    public:
        ID3D12GraphicsCommandList2Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12GraphicsCommandList2Wrapper() override;

        virtual void STDMETHODCALLTYPE WriteBufferImmediate(
                UINT Count,
                const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER* pParams,
                const D3D12_WRITEBUFFERIMMEDIATE_MODE* pModes);
    };
}