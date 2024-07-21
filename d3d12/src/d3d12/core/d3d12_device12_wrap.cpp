//
// Created by ZZK on 2024/7/20.
//

#include <d3d12/core/d3d12_device12_wrap.h>

namespace gfxshim
{
    ID3D12Device12Wrapper::ID3D12Device12Wrapper(const IID &riid, IUnknown *object)
    : ID3D12Device11Wrapper(riid, object)
    {

    }

    ID3D12Device12Wrapper::~ID3D12Device12Wrapper() = default;
}