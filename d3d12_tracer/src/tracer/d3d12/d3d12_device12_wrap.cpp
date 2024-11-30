//
// Created by ZZK on 2024/7/20.
//

#include <tracer/d3d12/d3d12_device12_wrap.h>

namespace gfxshim
{
    ID3D12Device12Wrapper::ID3D12Device12Wrapper(const IID &riid, IUnknown *object)
    : ID3D12Device11Wrapper(riid, object)
    {

    }

    ID3D12Device12Wrapper::~ID3D12Device12Wrapper() = default;

	D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE ID3D12Device12Wrapper::GetResourceAllocationInfo3(
			UINT visibleMask, UINT numResourceDescs, const D3D12_RESOURCE_DESC1 *pResourceDescs,
			const UINT32 *pNumCastableFormats, const DXGI_FORMAT *const *ppCastableFormats,
			D3D12_RESOURCE_ALLOCATION_INFO1 *pResourceAllocationInfo1)
	{
		const auto result = GetWrappedObjectAs<ID3D12Device12>()->GetResourceAllocationInfo3(visibleMask, numResourceDescs, pResourceDescs, pNumCastableFormats,
																								ppCastableFormats, pResourceAllocationInfo1);
		return result;
	}

}