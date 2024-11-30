//
// Created by ZZK on 2024/11/24.
//

#include <tracer/d3d12/d3d12_heap_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	// Wrap ID3D12Heap
	ID3D12HeapWrapper::ID3D12HeapWrapper(const IID &riid, IUnknown *object)
	: ID3D12PageableWrapper(riid, object)
	{

	}

	D3D12_HEAP_DESC STDMETHODCALLTYPE ID3D12HeapWrapper::GetDesc()
	{
		const auto result = GetWrappedObjectAs<ID3D12Heap>()->GetDesc();
		return result;
	}

	// Wrap ID3D12Heap1
	ID3D12Heap1Wrapper::ID3D12Heap1Wrapper(const IID &riid, IUnknown *object)
	: ID3D12HeapWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE ID3D12Heap1Wrapper::GetProtectedResourceSession(const IID &riid, void **ppProtectedSession)
	{
		const auto result = GetWrappedObjectAs<ID3D12Heap1>()->GetProtectedResourceSession(riid, ppProtectedSession);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppProtectedSession);
		}
		return result;
	}

	// Wrap ID3D12DescriptorHeap
	ID3D12DescriptorHeapWrapper::ID3D12DescriptorHeapWrapper(const IID &riid, IUnknown *object)
	: ID3D12PageableWrapper(riid, object)
	{

	}

	D3D12_DESCRIPTOR_HEAP_DESC STDMETHODCALLTYPE ID3D12DescriptorHeapWrapper::GetDesc()
	{
		const auto result = GetWrappedObjectAs<ID3D12DescriptorHeap>()->GetDesc();
		return result;
	}

	D3D12_CPU_DESCRIPTOR_HANDLE STDMETHODCALLTYPE ID3D12DescriptorHeapWrapper::GetCPUDescriptorHandleForHeapStart()
	{
		// TODO: wrap cpu address
		const auto result = GetWrappedObjectAs<ID3D12DescriptorHeap>()->GetCPUDescriptorHandleForHeapStart();
		return result;
	}

	D3D12_GPU_DESCRIPTOR_HANDLE STDMETHODCALLTYPE ID3D12DescriptorHeapWrapper::GetGPUDescriptorHandleForHeapStart()
	{
		const auto result = GetWrappedObjectAs<ID3D12DescriptorHeap>()->GetGPUDescriptorHandleForHeapStart();
		return result;
	}

	// Wrap ID3D12QueryHeap
	ID3D12QueryHeapWrapper::ID3D12QueryHeapWrapper(const IID &riid, IUnknown *object)
	: ID3D12PageableWrapper(riid, object)
	{

	}

}