//
// Created by ZZK on 2024/7/20.
//

#include <tracer/d3d12/d3d12_device10_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
    ID3D12Device10Wrapper::ID3D12Device10Wrapper(const IID &riid, IUnknown *object)
    : ID3D12Device9Wrapper(riid, object)
    {

    }

    ID3D12Device10Wrapper::~ID3D12Device10Wrapper() = default;

    HRESULT STDMETHODCALLTYPE ID3D12Device10Wrapper::CreateCommittedResource3(
            const D3D12_HEAP_PROPERTIES* pHeapProperties,
            D3D12_HEAP_FLAGS HeapFlags,
            const D3D12_RESOURCE_DESC1* pDesc,
            D3D12_BARRIER_LAYOUT InitialLayout,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            ID3D12ProtectedResourceSession* pProtectedSession,
            UINT32 NumCastableFormats,
            DXGI_FORMAT* pCastableFormats,
            REFIID riidResource,
            void** ppvResource)
    {
		// TODO: check wrap
        const auto result = GetWrappedObjectAs<ID3D12Device10>()->CreateCommittedResource3(pHeapProperties, HeapFlags, pDesc, InitialLayout,
                                                            pOptimizedClearValue, encode::GetWrappedObject<ID3D12ProtectedResourceSession>(pProtectedSession), NumCastableFormats, pCastableFormats, riidResource, ppvResource);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riidResource, ppvResource);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device10Wrapper::CreatePlacedResource2(
            ID3D12Heap* pHeap,
            UINT64 HeapOffset,
            const D3D12_RESOURCE_DESC1* pDesc,
            D3D12_BARRIER_LAYOUT InitialLayout,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            UINT32 NumCastableFormats,
            DXGI_FORMAT* pCastableFormats,
            REFIID riid,
            void** ppvResource)
    {
        const auto result = GetWrappedObjectAs<ID3D12Device10>()->CreatePlacedResource2(encode::GetWrappedObject<ID3D12Heap>(pHeap), HeapOffset, pDesc, InitialLayout, pOptimizedClearValue,
                                                                            NumCastableFormats, pCastableFormats, riid, ppvResource);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvResource);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device10Wrapper::CreateReservedResource2(
            const D3D12_RESOURCE_DESC* pDesc,
            D3D12_BARRIER_LAYOUT InitialLayout,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            ID3D12ProtectedResourceSession* pProtectedSession,
            UINT32 NumCastableFormats,
            DXGI_FORMAT* pCastableFormats,
            REFIID riid,
            void** ppvResource)
    {
        const auto result = GetWrappedObjectAs<ID3D12Device10>()->CreateReservedResource2(pDesc, InitialLayout, pOptimizedClearValue, encode::GetWrappedObject<ID3D12ProtectedResourceSession>(pProtectedSession),
                                                                            NumCastableFormats, pCastableFormats, riid, ppvResource);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvResource);
		}
		return result;
    }
}