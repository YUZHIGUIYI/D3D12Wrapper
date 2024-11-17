//
// Created by ZZK on 2024/7/20.
//

#include <tracer/d3d12/d3d12_command_list8_wrap.h>

namespace gfxshim
{
    ID3D12GraphicsCommandList8Wrapper::ID3D12GraphicsCommandList8Wrapper(const IID &riid, IUnknown *object)
    : ID3D12GraphicsCommandList7Wrapper(riid, object)
    {

    }

    ID3D12GraphicsCommandList8Wrapper::~ID3D12GraphicsCommandList8Wrapper() = default;
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::OMSetFrontAndBackStencilRef(
        _In_  UINT FrontStencilRef,
        _In_  UINT BackStencilRef)
{
    m_pList8->OMSetFrontAndBackStencilRef(FrontStencilRef, BackStencilRef);
}