//
// Created by ZZK on 2024/7/20.
//

#include <tracer/d3d12/d3d12_device2_wrap.h>

namespace gfxshim
{
    ID3D12Device2Wrapper::ID3D12Device2Wrapper(const IID &riid, IUnknown *object)
    : ID3D12Device1Wrapper(riid, object)
    {

    }

    ID3D12Device2Wrapper::~ID3D12Device2Wrapper() = default;

    HRESULT STDMETHODCALLTYPE ID3D12Device2Wrapper::CreatePipelineState(
            const D3D12_PIPELINE_STATE_STREAM_DESC* pDesc,
            REFIID riid,
            void** ppPipelineState)
    {
        return GetWrappedObjectAs<ID3D12Device2>()->CreatePipelineState(pDesc, riid, ppPipelineState);
    }
}