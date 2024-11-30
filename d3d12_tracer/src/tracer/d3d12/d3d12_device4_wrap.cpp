//
// Created by ZZK on 2024/7/20.
//

#include <tracer/d3d12/d3d12_device4_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
    ID3D12Device4Wrapper::ID3D12Device4Wrapper(const IID &riid, IUnknown *object)
    : ID3D12Device3Wrapper(riid, object)
    {

    }

    ID3D12Device4Wrapper::~ID3D12Device4Wrapper() = default;

    HRESULT STDMETHODCALLTYPE ID3D12Device4Wrapper::CreateCommandList1(
            UINT nodeMask,
            D3D12_COMMAND_LIST_TYPE type,
            D3D12_COMMAND_LIST_FLAGS flags,
            REFIID riid,
            void** ppCommandList)
    {
        const auto result = GetWrappedObjectAs<ID3D12Device4>()->CreateCommandList1(nodeMask, type, flags, riid, ppCommandList);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppCommandList);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device4Wrapper::CreateProtectedResourceSession(
            const D3D12_PROTECTED_RESOURCE_SESSION_DESC* pDesc,
            REFIID riid,
            void** ppSession)
    {
        const auto result = GetWrappedObjectAs<ID3D12Device4>()->CreateProtectedResourceSession(pDesc, riid, ppSession);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppSession);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device4Wrapper::CreateCommittedResource1(
            const D3D12_HEAP_PROPERTIES* pHeapProperties,
            D3D12_HEAP_FLAGS HeapFlags,
            const D3D12_RESOURCE_DESC* pDesc,
            D3D12_RESOURCE_STATES InitialResourceState,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            ID3D12ProtectedResourceSession* pProtectedSession,
            REFIID riidResource,
            void** ppvResource)
    {
		// TODO: check unwrap
        const auto result = GetWrappedObjectAs<ID3D12Device4>()->CreateCommittedResource1(pHeapProperties, HeapFlags, pDesc, InitialResourceState,
																								pOptimizedClearValue, encode::GetWrappedObject<ID3D12ProtectedResourceSession>(pProtectedSession),
																								riidResource, ppvResource);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riidResource, ppvResource);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device4Wrapper::CreateHeap1(
            const D3D12_HEAP_DESC* pDesc,
            ID3D12ProtectedResourceSession* pProtectedSession,
            REFIID riid,
            void** ppvHeap)
    {
		// TODO: check unwrap
        const auto result = GetWrappedObjectAs<ID3D12Device4>()->CreateHeap1(pDesc, encode::GetWrappedObject<ID3D12ProtectedResourceSession>(pProtectedSession), riid, ppvHeap);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvHeap);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device4Wrapper::CreateReservedResource1(
            const D3D12_RESOURCE_DESC* pDesc,
            D3D12_RESOURCE_STATES InitialState,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            ID3D12ProtectedResourceSession* pProtectedSession,
            REFIID riid,
            void** ppvResource)
    {
		// TODO: check unwrap
        const auto result = GetWrappedObjectAs<ID3D12Device4>()->CreateReservedResource1(pDesc, InitialState, pOptimizedClearValue,
                                                                            encode::GetWrappedObject<ID3D12ProtectedResourceSession>(pProtectedSession), riid, ppvResource);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvResource);
		}
		return result;
    }

    D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE ID3D12Device4Wrapper::GetResourceAllocationInfo1(
            UINT visibleMask,
            UINT numResourceDescs,
            const D3D12_RESOURCE_DESC* pResourceDescs,
            D3D12_RESOURCE_ALLOCATION_INFO1* pResourceAllocationInfo1)
    {
		const auto result = GetWrappedObjectAs<ID3D12Device4>()->GetResourceAllocationInfo1(visibleMask, numResourceDescs, pResourceDescs, pResourceAllocationInfo1);
		return result;
    }
}