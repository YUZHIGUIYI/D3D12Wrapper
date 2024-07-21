//
// Created by ZZK on 2024/7/20.
//

#include <d3d12/core/d3d12_command_list9_wrap.h>

namespace gfxshim
{
    ID3D12GraphicsCommandList9Wrapper::ID3D12GraphicsCommandList9Wrapper(const IID &riid, IUnknown *object)
    : ID3D12GraphicsCommandList8Wrapper(riid, object)
    {

    }

    ID3D12GraphicsCommandList9Wrapper::~ID3D12GraphicsCommandList9Wrapper() = default;
}