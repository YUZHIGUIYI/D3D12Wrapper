//
// Created by ZZK on 2024/7/20.
//

#include <tracer/d3d12/d3d12_device11_wrap.h>

namespace gfxshim
{
    ID3D12Device11Wrapper::ID3D12Device11Wrapper(const IID &riid, IUnknown *object)
    : ID3D12Device10Wrapper(riid, object)
    {

    }

    ID3D12Device11Wrapper::~ID3D12Device11Wrapper() = default;
}