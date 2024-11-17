//
// Created by ZZK on 2024/8/19.
//

#include <tracer/d3d12/d3d12_command_list_wrap.h>

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetProgram(
        _In_  const D3D12_SET_PROGRAM_DESC *pDesc)
{
    m_pList10->SetProgram(pDesc);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::DispatchGraph(
        _In_  const D3D12_DISPATCH_GRAPH_DESC *pDesc)
{
    m_pList10->DispatchGraph(pDesc);
}