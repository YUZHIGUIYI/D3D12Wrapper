//
// Created by ZZK on 2024/11/24.
//

#include <tracer/d3d12/d3d12_fence_wrap.h>

namespace gfxshim
{
	// Wrap ID3D12Fence
	ID3D12FenceWrapper::ID3D12FenceWrapper(const IID &riid, IUnknown *object)
	: ID3D12PageableWrapper(riid, object)
	{

	}

	UINT64 STDMETHODCALLTYPE ID3D12FenceWrapper::GetCompletedValue()
	{
		const auto result = GetWrappedObjectAs<ID3D12Fence>()->GetCompletedValue();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12FenceWrapper::SetEventOnCompletion(UINT64 Value, HANDLE hEvent)
	{
		const auto result = GetWrappedObjectAs<ID3D12Fence>()->SetEventOnCompletion(Value, hEvent);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12FenceWrapper::Signal(UINT64 Value)
	{
		const auto result = GetWrappedObjectAs<ID3D12Fence>()->Signal(Value);
		return result;
	}

	// Wrap ID3D12Fence1
	ID3D12Fence1Wrapper::ID3D12Fence1Wrapper(const IID &riid, IUnknown *object)
	: ID3D12FenceWrapper(riid, object)
	{

	}

	D3D12_FENCE_FLAGS STDMETHODCALLTYPE ID3D12Fence1Wrapper::GetCreationFlags()
	{
		const auto result = GetWrappedObjectAs<ID3D12Fence1>()->GetCreationFlags();
		return result;
	}

}