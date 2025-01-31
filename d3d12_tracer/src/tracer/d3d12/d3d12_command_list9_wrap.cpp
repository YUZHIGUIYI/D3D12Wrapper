//
// Created by ZZK on 2024/7/20.
//

#include <tracer/d3d12/d3d12_command_list_wrap.h>

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::RSSetDepthBias(
        _In_  FLOAT DepthBias,
        _In_  FLOAT DepthBiasClamp,
        _In_  FLOAT SlopeScaledDepthBias)
{
    m_pList9->RSSetDepthBias(DepthBias, DepthBiasClamp, SlopeScaledDepthBias);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::IASetIndexBufferStripCutValue(
        _In_  D3D12_INDEX_BUFFER_STRIP_CUT_VALUE IBStripCutValue)
{
    m_pList9->IASetIndexBufferStripCutValue(IBStripCutValue);
}