//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <d3d12/core/d3d12_device6_wrap.h>

namespace gfxshim
{
    class ID3D12Device7Wrapper : public ID3D12Device6Wrapper
    {
    public:
        ID3D12Device7Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12Device7Wrapper() override;

        virtual HRESULT STDMETHODCALLTYPE AddToStateObject(
                const D3D12_STATE_OBJECT_DESC* pAddition,
                ID3D12StateObject* pStateObjectToGrowFrom,
                REFIID riid,
                void** ppNewStateObject);

        virtual HRESULT STDMETHODCALLTYPE CreateProtectedResourceSession1(
                const D3D12_PROTECTED_RESOURCE_SESSION_DESC1* pDesc,
                REFIID riid,
                void** ppSession);
    };
}
