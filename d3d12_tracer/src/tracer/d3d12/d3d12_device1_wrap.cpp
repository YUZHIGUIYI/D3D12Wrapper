//
// Created by ZZK on 2024/7/20.
//

#include <tracer/d3d12/d3d12_device1_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
    ID3D12Device1Wrapper::ID3D12Device1Wrapper(const IID &riid, IUnknown *object)
    : ID3D12DeviceWrapper(riid, object)
    {

    }

    ID3D12Device1Wrapper::~ID3D12Device1Wrapper() = default;

    HRESULT STDMETHODCALLTYPE ID3D12Device1Wrapper::CreatePipelineLibrary(
            const void* pLibraryBlob,
            SIZE_T BlobLength,
            REFIID riid,
            void** ppPipelineLibrary)
    {
		// TODO: check wrap
        const auto result = GetWrappedObjectAs<ID3D12Device1>()->CreatePipelineLibrary(pLibraryBlob, BlobLength, riid, ppPipelineLibrary);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppPipelineLibrary);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device1Wrapper::SetEventOnMultipleFenceCompletion(
            ID3D12Fence* const* ppFences,
            const UINT64* pFenceValues,
            UINT NumFences,
            D3D12_MULTIPLE_FENCE_WAIT_FLAGS Flags,
            HANDLE hEvent)
    {
		if (NumFences > 0U && ppFences != nullptr)
		{
			std::vector<ID3D12Fence *> unwrap_fences(NumFences);
			for (uint32_t i = 0U; i < NumFences; ++i)
			{
				unwrap_fences[i] = encode::GetWrappedObject<ID3D12Fence>(ppFences[i]);
			}
			const auto result = GetWrappedObjectAs<ID3D12Device1>()->SetEventOnMultipleFenceCompletion(unwrap_fences.data(), pFenceValues, NumFences, Flags, hEvent);
			return result;
		}
        const auto result = GetWrappedObjectAs<ID3D12Device1>()->SetEventOnMultipleFenceCompletion(ppFences, pFenceValues, NumFences, Flags, hEvent);
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device1Wrapper::SetResidencyPriority(
            UINT NumObjects,
            ID3D12Pageable* const* ppObjects,
            const D3D12_RESIDENCY_PRIORITY* pPriorities)
    {
		if (NumObjects > 0U && ppObjects != nullptr)
		{
			std::vector<ID3D12Pageable *> unwrap_objects(NumObjects);
			for (uint32_t i = 0U; i < NumObjects; ++i)
			{
				unwrap_objects[i] = encode::GetWrappedObject<ID3D12Pageable>(ppObjects[i]);
			}
			const auto result = GetWrappedObjectAs<ID3D12Device1>()->SetResidencyPriority(NumObjects, unwrap_objects.data(), pPriorities);
			return result;
		}
		const auto result = GetWrappedObjectAs<ID3D12Device1>()->SetResidencyPriority(NumObjects, ppObjects, pPriorities);
		return result;
    }
}