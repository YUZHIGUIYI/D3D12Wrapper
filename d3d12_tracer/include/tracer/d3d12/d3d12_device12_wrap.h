//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <tracer/d3d12/d3d12_device11_wrap.h>

namespace gfxshim
{
    struct ID3D12Device12Wrapper : ID3D12Device11Wrapper
    {
    public:
        ID3D12Device12Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12Device12Wrapper() override;

		virtual D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE GetResourceAllocationInfo3(
												UINT visibleMask,
												UINT numResourceDescs,
												const D3D12_RESOURCE_DESC1* pResourceDescs,
												const UINT32* pNumCastableFormats,
												const DXGI_FORMAT* const* ppCastableFormats,
												D3D12_RESOURCE_ALLOCATION_INFO1* pResourceAllocationInfo1);
    };
}