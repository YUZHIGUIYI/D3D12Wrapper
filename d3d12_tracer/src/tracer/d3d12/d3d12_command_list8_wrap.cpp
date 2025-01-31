//
// Created by ZZK on 2024/7/20.
//

#include <tracer/d3d12/d3d12_command_list_wrap.h>

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::OMSetFrontAndBackStencilRef(
        _In_  UINT FrontStencilRef,
        _In_  UINT BackStencilRef)
{
    m_pList8->OMSetFrontAndBackStencilRef(FrontStencilRef, BackStencilRef);
}