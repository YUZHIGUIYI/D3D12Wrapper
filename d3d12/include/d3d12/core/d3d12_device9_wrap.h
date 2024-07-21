//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <d3d12/core/d3d12_device8_wrap.h>

namespace gfxshim
{
    class ID3D12Device9Wrapper : public ID3D12Device8Wrapper
    {
    public:
        ID3D12Device9Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12Device9Wrapper() override;

        virtual HRESULT STDMETHODCALLTYPE CreateShaderCacheSession(
                const D3D12_SHADER_CACHE_SESSION_DESC* pDesc,
                REFIID riid,
                void** ppvSession);

        virtual HRESULT STDMETHODCALLTYPE ShaderCacheControl(
                D3D12_SHADER_CACHE_KIND_FLAGS Kinds,
                D3D12_SHADER_CACHE_CONTROL_FLAGS Control);

        virtual HRESULT STDMETHODCALLTYPE CreateCommandQueue1(
                const D3D12_COMMAND_QUEUE_DESC* pDesc,
                REFIID CreatorID,
                REFIID riid,
                void** ppCommandQueue);
    };
}
