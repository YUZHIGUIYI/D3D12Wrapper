//
// Created by ZZK on 2024/7/20.
//

#include <d3d12/core/d3d12_device11_wrap.h>

namespace gfxshim
{
    ID3D12Device11Wrapper::ID3D12Device11Wrapper(const IID &riid, IUnknown *object)
    : ID3D12Device10Wrapper(riid, object)
    {

    }

    ID3D12Device11Wrapper::~ID3D12Device11Wrapper() = default;
}