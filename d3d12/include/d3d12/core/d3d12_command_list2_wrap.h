//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <d3d12/core/d3d12_command_list1_wrap.h>

namespace gfxshim
{
    class ID3D12GraphicsCommandList2Wrapper : public ID3D12GraphicsCommandList1Wrapper
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