//
// Created by ZZK on 2024/7/20.
//

#include <tracer/d3d12/d3d12_device3_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
    ID3D12Device3Wrapper::ID3D12Device3Wrapper(const IID &riid, IUnknown *object)
    : ID3D12Device2Wrapper(riid, object)
    {

    }

    ID3D12Device3Wrapper::~ID3D12Device3Wrapper() = default;

    HRESULT STDMETHODCALLTYPE ID3D12Device3Wrapper::OpenExistingHeapFromAddress(
            const void* pAddress,
            REFIID riid,
            void** ppvHeap)
    {
        const auto result = GetWrappedObjectAs<ID3D12Device3>()->OpenExistingHeapFromAddress(pAddress, riid, ppvHeap);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvHeap);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device3Wrapper::OpenExistingHeapFromFileMapping(
            HANDLE hFileMapping,
            REFIID riid,
            void** ppvHeap)
    {
        const auto result = GetWrappedObjectAs<ID3D12Device3>()->OpenExistingHeapFromFileMapping(hFileMapping, riid, ppvHeap);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvHeap);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device3Wrapper::EnqueueMakeResident(
            D3D12_RESIDENCY_FLAGS Flags,
            UINT NumObjects,
            ID3D12Pageable* const* ppObjects,
            ID3D12Fence* pFenceToSignal,
            UINT64 FenceValueToSignal)
    {
		if (NumObjects > 0U && ppObjects != nullptr)
		{
			std::vector<ID3D12Pageable *> unwrap_objects(NumObjects);
			for (uint32_t i = 0U; i < NumObjects; ++i)
			{
				unwrap_objects[i] = ppObjects[i];
			}
			const auto result = GetWrappedObjectAs<ID3D12Device3>()->EnqueueMakeResident(Flags, NumObjects, unwrap_objects.data(),
																							encode::GetWrappedObject<ID3D12Fence>(pFenceToSignal), FenceValueToSignal);
			return result;
		}
        const auto result = GetWrappedObjectAs<ID3D12Device3>()->EnqueueMakeResident(Flags, NumObjects, ppObjects,
																							encode::GetWrappedObject<ID3D12Fence>(pFenceToSignal), FenceValueToSignal);
		return result;
    }
}