//
// Created by ZZK on 2024/7/20.
//

#include <tracer/d3d12/d3d12_device14_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	ID3D12Device14Wrapper::ID3D12Device14Wrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12Device14Wrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12Device14Wrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12Device14Wrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12Device14Wrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		if (IsEqualIID(riid, IID_Device_11_On_12))
		{
			D3D12_WRAPPER_DEBUG("Invoke ID3D12Device14Wrapper::QueryInterface, equal riid");
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12Device14Wrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12Device14Wrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12Device14Wrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12Object
	HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::GetPrivateData(const GUID &guid, UINT *pDataSize, void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->GetPrivateData(guid, pDataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::SetPrivateData(const GUID &guid, UINT DataSize, const void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateData(guid, DataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::SetPrivateDataInterface(const GUID &guid, const IUnknown *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateDataInterface(guid, encode::GetWrappedObject<IUnknown>(pData));
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::SetName(LPCWSTR Name)
	{
		return GetWrappedObjectAs<ID3D12Object>()->SetName(Name);
	}

	// ID3D12Device
	UINT STDMETHODCALLTYPE ID3D12Device14Wrapper::GetNodeCount()
    {
        return GetWrappedObjectAs<ID3D12Device>()->GetNodeCount();
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateCommandQueue(
            const D3D12_COMMAND_QUEUE_DESC* pDesc,
            REFIID riid,
            void** ppCommandQueue)
    {
        const HRESULT result = GetWrappedObjectAs<ID3D12Device>()->CreateCommandQueue(pDesc, riid, ppCommandQueue);
        if (SUCCEEDED(result))
        {
			encode::WrapObject(riid, ppCommandQueue);
        }
        return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateCommandAllocator(
            D3D12_COMMAND_LIST_TYPE type,
            REFIID riid,
            void** ppCommandAllocator)
    {
		const auto result = GetWrappedObjectAs<ID3D12Device>()->CreateCommandAllocator(type, riid, ppCommandAllocator);
		if (SUCCEEDED(result))
		{
		    encode::WrapObject(riid, ppCommandAllocator);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateGraphicsPipelineState(
            const D3D12_GRAPHICS_PIPELINE_STATE_DESC* pDesc,
            REFIID riid,
            void** ppPipelineState)
    {
		// TODO: check creation and wrap, attention root signature
		D3D12_GRAPHICS_PIPELINE_STATE_DESC pipeline_state_desc = *pDesc;
		if (pipeline_state_desc.pRootSignature != nullptr)
		{
		    pipeline_state_desc.pRootSignature = encode::GetWrappedObject<ID3D12RootSignature>(pipeline_state_desc.pRootSignature);
		}
		const auto result = GetWrappedObjectAs<ID3D12Device>()->CreateGraphicsPipelineState(&pipeline_state_desc, riid, ppPipelineState);
		if (SUCCEEDED(result))
		{
		    encode::WrapObject(riid, ppPipelineState);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateComputePipelineState(
            const D3D12_COMPUTE_PIPELINE_STATE_DESC* pDesc,
            REFIID riid,
            void** ppPipelineState)
    {
		// TODO: check creation and wrap, attention root signature
		D3D12_COMPUTE_PIPELINE_STATE_DESC pipeline_state_desc = *pDesc;
		if (pipeline_state_desc.pRootSignature != nullptr)
		{
		    pipeline_state_desc.pRootSignature = encode::GetWrappedObject<ID3D12RootSignature>(pipeline_state_desc.pRootSignature);
		}
		const auto result = GetWrappedObjectAs<ID3D12Device>()->CreateComputePipelineState(&pipeline_state_desc, riid, ppPipelineState);
		if (SUCCEEDED(result))
		{
		    encode::WrapObject(riid, ppPipelineState);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateCommandList(
            UINT nodeMask,
            D3D12_COMMAND_LIST_TYPE type,
            ID3D12CommandAllocator* pCommandAllocator,
            ID3D12PipelineState* pInitialState,
            REFIID riid,
            void** ppCommandList)
    {
		const auto result = GetWrappedObjectAs<ID3D12Device>()->CreateCommandList(nodeMask, type, encode::GetWrappedObject<ID3D12CommandAllocator>(pCommandAllocator),
																						encode::GetWrappedObject<ID3D12PipelineState>(pInitialState), riid, ppCommandList);
		if (SUCCEEDED(result))
		{
		    encode::WrapObject(riid, ppCommandList);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CheckFeatureSupport(
            D3D12_FEATURE Feature,
            void* pFeatureSupportData,
            UINT FeatureSupportDataSize)
    {
		const auto result = GetWrappedObjectAs<ID3D12Device>()->CheckFeatureSupport(Feature, pFeatureSupportData, FeatureSupportDataSize);
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateDescriptorHeap(
            const D3D12_DESCRIPTOR_HEAP_DESC* pDescriptorHeapDesc,
            REFIID riid,
            void** ppvHeap)
    {
		const auto result = GetWrappedObjectAs<ID3D12Device>()->CreateDescriptorHeap(pDescriptorHeapDesc, riid, ppvHeap);
		if (SUCCEEDED(result))
		{
		    encode::WrapObject(riid, ppvHeap);
		}
		return result;
    }

    UINT STDMETHODCALLTYPE ID3D12Device14Wrapper::GetDescriptorHandleIncrementSize(
            D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapType)
    {
		const auto result = GetWrappedObjectAs<ID3D12Device>()->GetDescriptorHandleIncrementSize(DescriptorHeapType);
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateRootSignature(
            UINT nodeMask,
            const void* pBlobWithRootSignature,
            SIZE_T blobLengthInBytes,
            REFIID riid,
            void** ppvRootSignature)
    {
		const auto result = GetWrappedObjectAs<ID3D12Device>()->CreateRootSignature(nodeMask, pBlobWithRootSignature, blobLengthInBytes, riid, ppvRootSignature);
		if (SUCCEEDED(result))
		{
		    encode::WrapObject(riid, ppvRootSignature);
		}
		return result;
    }

    void STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateConstantBufferView(
            const D3D12_CONSTANT_BUFFER_VIEW_DESC* pDesc,
            D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
    {
        GetWrappedObjectAs<ID3D12Device>()->CreateConstantBufferView(pDesc, DestDescriptor);
    }

    void STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateShaderResourceView(
            ID3D12Resource* pResource,
            const D3D12_SHADER_RESOURCE_VIEW_DESC* pDesc,
            D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
    {
        GetWrappedObjectAs<ID3D12Device>()->CreateShaderResourceView(encode::GetWrappedObject<ID3D12Resource>(pResource), pDesc, DestDescriptor);
    }

    void STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateUnorderedAccessView(
            ID3D12Resource* pResource,
            ID3D12Resource* pCounterResource,
            const D3D12_UNORDERED_ACCESS_VIEW_DESC* pDesc,
            D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
    {
		GetWrappedObjectAs<ID3D12Device>()->CreateUnorderedAccessView(encode::GetWrappedObject<ID3D12Resource>(pResource), encode::GetWrappedObject<ID3D12Resource>(pCounterResource),
																	pDesc, DestDescriptor);
    }

    void STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateRenderTargetView(
            ID3D12Resource* pResource,
            const D3D12_RENDER_TARGET_VIEW_DESC* pDesc,
            D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
    {
        GetWrappedObjectAs<ID3D12Device>()->CreateRenderTargetView(encode::GetWrappedObject<ID3D12Resource>(pResource), pDesc, DestDescriptor);
    }

    void STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateDepthStencilView(
            ID3D12Resource* pResource,
            const D3D12_DEPTH_STENCIL_VIEW_DESC* pDesc,
            D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
    {
        GetWrappedObjectAs<ID3D12Device>()->CreateDepthStencilView(encode::GetWrappedObject<ID3D12Resource>(pResource), pDesc, DestDescriptor);
    }

    void STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateSampler(
            const D3D12_SAMPLER_DESC* pDesc,
            D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
    {
        GetWrappedObjectAs<ID3D12Device>()->CreateSampler(pDesc, DestDescriptor);
    }

    void STDMETHODCALLTYPE ID3D12Device14Wrapper::CopyDescriptors(
            UINT NumDestDescriptorRanges,
            const D3D12_CPU_DESCRIPTOR_HANDLE* pDestDescriptorRangeStarts,
            const UINT* pDestDescriptorRangeSizes,
            UINT NumSrcDescriptorRanges,
            const D3D12_CPU_DESCRIPTOR_HANDLE* pSrcDescriptorRangeStarts,
            const UINT* pSrcDescriptorRangeSizes,
            D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapsType)
    {
        GetWrappedObjectAs<ID3D12Device>()->CopyDescriptors(NumDestDescriptorRanges, pDestDescriptorRangeStarts, pDestDescriptorRangeSizes, NumSrcDescriptorRanges,
                                                            pSrcDescriptorRangeStarts, pSrcDescriptorRangeSizes, DescriptorHeapsType);
    }

    void STDMETHODCALLTYPE ID3D12Device14Wrapper::CopyDescriptorsSimple(
            UINT NumDescriptors,
            D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptorRangeStart,
            D3D12_CPU_DESCRIPTOR_HANDLE SrcDescriptorRangeStart,
            D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapsType)
    {
        GetWrappedObjectAs<ID3D12Device>()->CopyDescriptorsSimple(NumDescriptors, DestDescriptorRangeStart, SrcDescriptorRangeStart, DescriptorHeapsType);
    }

    D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE ID3D12Device14Wrapper::GetResourceAllocationInfo(
            UINT visibleMask,
            UINT numResourceDescs,
            const D3D12_RESOURCE_DESC* pResourceDescs)
    {
        return GetWrappedObjectAs<ID3D12Device>()->GetResourceAllocationInfo(visibleMask, numResourceDescs, pResourceDescs);
    }

    D3D12_HEAP_PROPERTIES STDMETHODCALLTYPE ID3D12Device14Wrapper::GetCustomHeapProperties(
            UINT nodeMask,
            D3D12_HEAP_TYPE heapType)
    {
        return GetWrappedObjectAs<ID3D12Device>()->GetCustomHeapProperties(nodeMask, heapType);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateCommittedResource(
            const D3D12_HEAP_PROPERTIES* pHeapProperties,
            D3D12_HEAP_FLAGS HeapFlags,
            const D3D12_RESOURCE_DESC* pDesc,
            D3D12_RESOURCE_STATES InitialResourceState,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            REFIID riidResource,
            void** ppvResource)
    {
		// TODO: add write watch
		const auto result = GetWrappedObjectAs<ID3D12Device>()->CreateCommittedResource(pHeapProperties, HeapFlags, pDesc, InitialResourceState,
		                                                                   pOptimizedClearValue, riidResource, ppvResource);
		if (SUCCEEDED(result))
		{
		    encode::WrapObject(riidResource, ppvResource);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateHeap(
            const D3D12_HEAP_DESC* pDesc,
            REFIID riid,
            void** ppvHeap)
    {
		// TODO: add write watch
		const auto result = GetWrappedObjectAs<ID3D12Device>()->CreateHeap(pDesc, riid, ppvHeap);
		if (SUCCEEDED(result))
		{
		    encode::WrapObject(riid, ppvHeap);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreatePlacedResource(
            ID3D12Heap* pHeap,
            UINT64 HeapOffset,
            const D3D12_RESOURCE_DESC* pDesc,
            D3D12_RESOURCE_STATES InitialState,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            REFIID riid,
            void** ppvResource)
    {
		const auto result = GetWrappedObjectAs<ID3D12Device>()->CreatePlacedResource(encode::GetWrappedObject<ID3D12Heap>(pHeap), HeapOffset, pDesc, InitialState,
		                                                                pOptimizedClearValue, riid, ppvResource);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvResource);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateReservedResource(
            const D3D12_RESOURCE_DESC* pDesc,
            D3D12_RESOURCE_STATES InitialState,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            REFIID riid,
            void** ppvResource)
    {
		const auto result = GetWrappedObjectAs<ID3D12Device>()->CreateReservedResource(pDesc, InitialState, pOptimizedClearValue, riid, ppvResource);
		if (SUCCEEDED(result))
		{
		    encode::WrapObject(riid, ppvResource);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateSharedHandle(
            ID3D12DeviceChild* pObject,
            const SECURITY_ATTRIBUTES* pAttributes,
            DWORD Access,
            LPCWSTR Name,
            HANDLE* pHandle)
    {
		const auto result = GetWrappedObjectAs<ID3D12Device>()->CreateSharedHandle(encode::GetWrappedObject<ID3D12DeviceChild>(pObject), pAttributes, Access, Name, pHandle);
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::OpenSharedHandle(
            HANDLE NTHandle,
            REFIID riid,
            void** ppvObj)
    {
		const auto result = GetWrappedObjectAs<ID3D12Device>()->OpenSharedHandle(NTHandle, riid, ppvObj);
		if (SUCCEEDED(result))
		{
		    encode::WrapObject(riid, ppvObj);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::OpenSharedHandleByName(
            LPCWSTR Name,
            DWORD Access,
            HANDLE* pNTHandle)
    {
        return GetWrappedObjectAs<ID3D12Device>()->OpenSharedHandleByName(Name, Access, pNTHandle);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::MakeResident(
            UINT NumObjects,
            ID3D12Pageable* const* ppObjects)
    {
		if (NumObjects > 0U && ppObjects != nullptr)
		{
			std::vector<ID3D12Pageable *> pageable_objects(NumObjects);
		    for (uint32_t i = 0U; i < NumObjects; ++i)
		    {
				pageable_objects[i] = encode::GetWrappedObject<ID3D12Pageable>(ppObjects[i]);
		    }
		    const auto result = GetWrappedObjectAs<ID3D12Device>()->MakeResident(NumObjects, pageable_objects.data());
		    return result;
		}
		return GetWrappedObjectAs<ID3D12Device>()->MakeResident(NumObjects, ppObjects);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::Evict(
            UINT NumObjects,
            ID3D12Pageable* const* ppObjects)
    {
		if (NumObjects > 0U && ppObjects != nullptr)
		{
		    std::vector<ID3D12Pageable *> pageable_objects(NumObjects);
		    for (uint32_t i = 0U; i < NumObjects; ++i)
		    {
				pageable_objects[i] = encode::GetWrappedObject<ID3D12Pageable>(ppObjects[i]);
		    }
		    const auto result = GetWrappedObjectAs<ID3D12Device>()->Evict(NumObjects, pageable_objects.data());
		    return result;
		}
		return GetWrappedObjectAs<ID3D12Device>()->Evict(NumObjects, ppObjects);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateFence(
            UINT64 InitialValue,
            D3D12_FENCE_FLAGS Flags,
            REFIID riid,
            void** ppFence)
    {
		const auto result = GetWrappedObjectAs<ID3D12Device>()->CreateFence(InitialValue, Flags, riid, ppFence);
		if (SUCCEEDED(result))
		{
		    encode::WrapObject(riid, ppFence);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::GetDeviceRemovedReason()
    {
        return GetWrappedObjectAs<ID3D12Device>()->GetDeviceRemovedReason();
    }

    void STDMETHODCALLTYPE ID3D12Device14Wrapper::GetCopyableFootprints(
            const D3D12_RESOURCE_DESC* pResourceDesc,
            UINT FirstSubresource,
            UINT NumSubresources,
            UINT64 BaseOffset,
            D3D12_PLACED_SUBRESOURCE_FOOTPRINT* pLayouts,
            UINT* pNumRows,
            UINT64* pRowSizeInBytes,
            UINT64* pTotalBytes)
    {
        GetWrappedObjectAs<ID3D12Device>()->GetCopyableFootprints(pResourceDesc, FirstSubresource, NumSubresources, BaseOffset,
                                                                  pLayouts, pNumRows, pRowSizeInBytes, pTotalBytes);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateQueryHeap(
            const D3D12_QUERY_HEAP_DESC* pDesc,
            REFIID riid,
            void** ppvHeap)
    {
		const auto result = GetWrappedObjectAs<ID3D12Device>()->CreateQueryHeap(pDesc, riid, ppvHeap);
		if (SUCCEEDED(result))
		{
		    encode::WrapObject(riid, ppvHeap);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::SetStablePowerState(BOOL Enable)
    {
        return GetWrappedObjectAs<ID3D12Device>()->SetStablePowerState(Enable);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateCommandSignature(
            const D3D12_COMMAND_SIGNATURE_DESC* pDesc,
            ID3D12RootSignature* pRootSignature,
            REFIID riid,
            void** ppvCommandSignature)
    {
		const auto result = GetWrappedObjectAs<ID3D12Device>()->CreateCommandSignature(pDesc, encode::GetWrappedObject<ID3D12RootSignature>(pRootSignature), riid, ppvCommandSignature);
		if (SUCCEEDED(result))
		{
		    encode::WrapObject(riid, ppvCommandSignature);
		}
		return result;
    }

    void STDMETHODCALLTYPE ID3D12Device14Wrapper::GetResourceTiling(
            ID3D12Resource* pTiledResource,
            UINT* pNumTilesForEntireResource,
            D3D12_PACKED_MIP_INFO* pPackedMipDesc,
            D3D12_TILE_SHAPE* pStandardTileShapeForNonPackedMips,
            UINT* pNumSubresourceTilings,
            UINT FirstSubresourceTilingToGet,
            D3D12_SUBRESOURCE_TILING* pSubresourceTilingsForNonPackedMips)
    {
        GetWrappedObjectAs<ID3D12Device>()->GetResourceTiling(encode::GetWrappedObject<ID3D12Resource>(pTiledResource), pNumTilesForEntireResource, pPackedMipDesc, pStandardTileShapeForNonPackedMips,
                                                              pNumSubresourceTilings, FirstSubresourceTilingToGet, pSubresourceTilingsForNonPackedMips);
    }

    LUID STDMETHODCALLTYPE ID3D12Device14Wrapper::GetAdapterLuid()
    {
        return GetWrappedObjectAs<ID3D12Device>()->GetAdapterLuid();
    }

	// ID3D12Device1
	HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreatePipelineLibrary(
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

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::SetEventOnMultipleFenceCompletion(
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

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::SetResidencyPriority(
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

	// ID3D12Device2
	HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreatePipelineState(
            const D3D12_PIPELINE_STATE_STREAM_DESC* pDesc,
            REFIID riid,
            void** ppPipelineState)
    {
		// TODO: check unwrap state stream desc
		if (pDesc != nullptr && pDesc->SizeInBytes > 0U && pDesc->pPipelineStateSubobjectStream != nullptr)
		{
			D3D12_PIPELINE_STATE_STREAM_DESC unwrap_pipeline_state_stream_desc{};
			std::vector<uint8_t> pipeline_state_stream(pDesc->SizeInBytes);
			std::memcpy(pipeline_state_stream.data(), pDesc->pPipelineStateSubobjectStream, pDesc->SizeInBytes);
			unwrap_pipeline_state_stream_desc.SizeInBytes = pDesc->SizeInBytes;
			unwrap_pipeline_state_stream_desc.pPipelineStateSubobjectStream = pipeline_state_stream.data();
			auto start = pipeline_state_stream.data();
			size_t offset = 0U;
			while (offset < pDesc->SizeInBytes)
			{
				auto current = start + offset;
				const auto sub_object_type = *reinterpret_cast<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE *>(current);
				// Only the root signature sub-object requires object unwrapping, the rest of the sub-objects only require an offset increment
				if (sub_object_type == D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_ROOT_SIGNATURE)
				{
					auto sub_object = reinterpret_cast<Dx12SignatureSubObject *>(current);
					sub_object->value = encode::GetWrappedObject<ID3D12RootSignature>(sub_object->value);
					offset += sizeof(Dx12SignatureSubObject);
					break;
				}
				switch (sub_object_type)
				{
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_VS:
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_PS:
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_DS:
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_HS:
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_GS:
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_CS:
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_AS:
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_MS:
					    offset += sizeof(Dx12ShaderBytecodeSubObject);
					    break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_STREAM_OUTPUT:
						offset += sizeof(Dx12StreamOutputSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_BLEND:
						offset += sizeof(Dx12BlendSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_SAMPLE_MASK:
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_NODE_MASK:
						offset += sizeof(Dx12UintSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_RASTERIZER:
						offset += sizeof(Dx12RasterizerSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL:
						offset += sizeof(Dx12DepthStencilSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_INPUT_LAYOUT:
						offset += sizeof(Dx12InputLayoutSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_IB_STRIP_CUT_VALUE:
						offset += sizeof(Dx12StripCutSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_PRIMITIVE_TOPOLOGY:
						offset += sizeof(Dx12PrimitiveTopologySubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_RENDER_TARGET_FORMATS:
						offset += sizeof(Dx12RenderTargetFormatsSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL_FORMAT:
						offset += sizeof(Dx12FormatSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_SAMPLE_DESC:
						offset += sizeof(Dx12SampleDescSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_CACHED_PSO:
						offset += sizeof(Dx12CachedPSOSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_FLAGS:
						offset += sizeof(Dx12TypeFlagsSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL1:
						offset += sizeof(Dx12DepthStencil1SubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_VIEW_INSTANCING:
						offset += sizeof(Dx12ViewInstancingSubObject);
						break;
					default:
						 // Type is unrecognized. Write an invalid enum value so the decoder know the data is incomplete,
						offset = pDesc->SizeInBytes;
						break;
				}
			}

			const auto result = GetWrappedObjectAs<ID3D12Device2>()->CreatePipelineState(&unwrap_pipeline_state_stream_desc, riid, ppPipelineState);
			if (SUCCEEDED(result))
			{
				encode::WrapObject(riid, ppPipelineState);
			}
			return result;
		}
		const auto result = GetWrappedObjectAs<ID3D12Device2>()->CreatePipelineState(pDesc, riid, ppPipelineState);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppPipelineState);
		}
		return result;
    }

	// ID3D12Device3
	HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::OpenExistingHeapFromAddress(
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

	HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::OpenExistingHeapFromFileMapping(
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

	HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::EnqueueMakeResident(
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

	// ID3D12Device4
	HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateCommandList1(
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

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateProtectedResourceSession(
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

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateCommittedResource1(
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

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateHeap1(
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

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateReservedResource1(
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

    D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE ID3D12Device14Wrapper::GetResourceAllocationInfo1(
            UINT visibleMask,
            UINT numResourceDescs,
            const D3D12_RESOURCE_DESC* pResourceDescs,
            D3D12_RESOURCE_ALLOCATION_INFO1* pResourceAllocationInfo1)
    {
		const auto result = GetWrappedObjectAs<ID3D12Device4>()->GetResourceAllocationInfo1(visibleMask, numResourceDescs, pResourceDescs, pResourceAllocationInfo1);
		return result;
    }

	// ID3D12Device5
	HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateLifetimeTracker(
            ID3D12LifetimeOwner* pOwner,
            REFIID riid,
            void** ppvTracker)
    {
        const auto result = GetWrappedObjectAs<ID3D12Device5>()->CreateLifetimeTracker(encode::GetWrappedObject<ID3D12LifetimeOwner>(pOwner), riid, ppvTracker);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvTracker);
		}
		return result;
    }

    void STDMETHODCALLTYPE ID3D12Device14Wrapper::RemoveDevice()
    {
        GetWrappedObjectAs<ID3D12Device5>()->RemoveDevice();
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::EnumerateMetaCommands(
            UINT* pNumMetaCommands,
            D3D12_META_COMMAND_DESC* pDescs)
    {
        return GetWrappedObjectAs<ID3D12Device5>()->EnumerateMetaCommands(pNumMetaCommands, pDescs);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::EnumerateMetaCommandParameters(
            REFGUID CommandId,
            D3D12_META_COMMAND_PARAMETER_STAGE Stage,
            UINT* pTotalStructureSizeInBytes,
            UINT* pParameterCount,
            D3D12_META_COMMAND_PARAMETER_DESC* pParameterDescs)
    {
        return GetWrappedObjectAs<ID3D12Device5>()->EnumerateMetaCommandParameters(CommandId, Stage, pTotalStructureSizeInBytes, pParameterCount, pParameterDescs);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateMetaCommand(
            REFGUID CommandId,
            UINT NodeMask,
            const void* pCreationParametersData,
            SIZE_T CreationParametersDataSizeInBytes,
            REFIID riid,
            void** ppMetaCommand)
    {
        const auto result = GetWrappedObjectAs<ID3D12Device5>()->CreateMetaCommand(CommandId, NodeMask, pCreationParametersData,
                                                                        CreationParametersDataSizeInBytes, riid, ppMetaCommand);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppMetaCommand);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateStateObject(
            const D3D12_STATE_OBJECT_DESC* pDesc,
            REFIID riid,
            void** ppStateObject)
    {
		// TODO: unwrap state object desc
		D3D12_WRAPPER_ERROR("Currently do not unwrap D3D12_STATE_OBJECT_DESC, DXR is not supported");
		if (pDesc != nullptr && pDesc->NumSubobjects > 0U && pDesc->pSubobjects != nullptr)
		{
			D3D12_STATE_OBJECT_DESC unwrapped_state_object_desc = *pDesc;
			std::vector<D3D12_STATE_SUBOBJECT> unwrapped_state_sub_objects(pDesc->NumSubobjects);
			std::memcpy(unwrapped_state_sub_objects.data(), pDesc->pSubobjects, sizeof(D3D12_STATE_SUBOBJECT) * pDesc->NumSubobjects);
			encode::UnwrapStructObjects(unwrapped_state_sub_objects, std::span{ pDesc->pSubobjects, pDesc->NumSubobjects });
			unwrapped_state_object_desc.pSubobjects = unwrapped_state_sub_objects.data();
			const auto result = GetWrappedObjectAs<ID3D12Device5>()->CreateStateObject(&unwrapped_state_object_desc, riid, ppStateObject);
			if (SUCCEEDED(result))
			{
				encode::WrapObject(riid, ppStateObject);
			}
			return result;
		}

        const auto result = GetWrappedObjectAs<ID3D12Device5>()->CreateStateObject(pDesc, riid, ppStateObject);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppStateObject);
		}
		return result;
    }

    void STDMETHODCALLTYPE ID3D12Device14Wrapper::GetRaytracingAccelerationStructurePrebuildInfo(
            const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS* pDesc,
            D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO* pInfo)
    {
        GetWrappedObjectAs<ID3D12Device5>()->GetRaytracingAccelerationStructurePrebuildInfo(pDesc, pInfo);
    }

    D3D12_DRIVER_MATCHING_IDENTIFIER_STATUS STDMETHODCALLTYPE ID3D12Device14Wrapper::CheckDriverMatchingIdentifier(
            D3D12_SERIALIZED_DATA_TYPE SerializedDataType,
            const D3D12_SERIALIZED_DATA_DRIVER_MATCHING_IDENTIFIER* pIdentifierToCheck)
    {
        return GetWrappedObjectAs<ID3D12Device5>()->CheckDriverMatchingIdentifier(SerializedDataType, pIdentifierToCheck);
    }

	// ID3D12Device6
	HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::SetBackgroundProcessingMode(
			D3D12_BACKGROUND_PROCESSING_MODE Mode,
			D3D12_MEASUREMENTS_ACTION MeasurementsAction,
			HANDLE hEventToSignalUponCompletion,
			BOOL* pbFurtherMeasurementsDesired)
	{
		return GetWrappedObjectAs<ID3D12Device6>()->SetBackgroundProcessingMode(Mode, MeasurementsAction, hEventToSignalUponCompletion, pbFurtherMeasurementsDesired);
	}

	// ID3D12Device7
	HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::AddToStateObject(
            const D3D12_STATE_OBJECT_DESC* pAddition,
            ID3D12StateObject* pStateObjectToGrowFrom,
            REFIID riid,
            void** ppNewStateObject)
    {
		// TODO: unwrap state object desc
		D3D12_WRAPPER_ERROR("Currently do not unwrap D3D12_STATE_OBJECT_DESC, DXR is not supported");
		if (pAddition != nullptr && pAddition->NumSubobjects > 0U && pAddition->pSubobjects != nullptr)
		{
		    D3D12_STATE_OBJECT_DESC unwrapped_state_object_desc = *pAddition;
		    std::vector<D3D12_STATE_SUBOBJECT> unwrapped_state_sub_objects(pAddition->NumSubobjects);
		    std::memcpy(unwrapped_state_sub_objects.data(), pAddition->pSubobjects, sizeof(D3D12_STATE_SUBOBJECT) * pAddition->NumSubobjects);
		    encode::UnwrapStructObjects(unwrapped_state_sub_objects, std::span{ pAddition->pSubobjects, pAddition->NumSubobjects });
		    unwrapped_state_object_desc.pSubobjects = unwrapped_state_sub_objects.data();
			const auto result = GetWrappedObjectAs<ID3D12Device7>()->AddToStateObject(&unwrapped_state_object_desc, encode::GetWrappedObject<ID3D12StateObject>(pStateObjectToGrowFrom),
																							riid, ppNewStateObject);
		    if (SUCCEEDED(result))
		    {
				encode::WrapObject(riid, ppNewStateObject);
		    }
		    return result;
		}

        const auto result = GetWrappedObjectAs<ID3D12Device7>()->AddToStateObject(pAddition, encode::GetWrappedObject<ID3D12StateObject>(pStateObjectToGrowFrom),
																							riid, ppNewStateObject);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppNewStateObject);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateProtectedResourceSession1(
            const D3D12_PROTECTED_RESOURCE_SESSION_DESC1* pDesc,
            REFIID riid,
            void** ppSession)
    {
        const auto result = GetWrappedObjectAs<ID3D12Device7>()->CreateProtectedResourceSession1(pDesc, riid, ppSession);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppSession);
		}
		return result;
    }

	// ID3D12Device8
	D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE ID3D12Device14Wrapper::GetResourceAllocationInfo2(
            UINT visibleMask,
            UINT numResourceDescs,
            const D3D12_RESOURCE_DESC1* pResourceDescs,
            D3D12_RESOURCE_ALLOCATION_INFO1* pResourceAllocationInfo1)
    {
        const auto result = GetWrappedObjectAs<ID3D12Device8>()->GetResourceAllocationInfo2(visibleMask, numResourceDescs, pResourceDescs, pResourceAllocationInfo1);
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateCommittedResource2(
            const D3D12_HEAP_PROPERTIES* pHeapProperties,
            D3D12_HEAP_FLAGS HeapFlags,
            const D3D12_RESOURCE_DESC1* pDesc,
            D3D12_RESOURCE_STATES InitialResourceState,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            ID3D12ProtectedResourceSession* pProtectedSession,
            REFIID riidResource,
            void** ppvResource)
    {
        const auto result = GetWrappedObjectAs<ID3D12Device8>()->CreateCommittedResource2(pHeapProperties, HeapFlags, pDesc, InitialResourceState,
                                                                            pOptimizedClearValue, encode::GetWrappedObject<ID3D12ProtectedResourceSession>(pProtectedSession), riidResource, ppvResource);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riidResource, ppvResource);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreatePlacedResource1(
            ID3D12Heap* pHeap,
            UINT64 HeapOffset,
            const D3D12_RESOURCE_DESC1* pDesc,
            D3D12_RESOURCE_STATES InitialState,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            REFIID riid,
            void** ppvResource)
    {
        const auto result = GetWrappedObjectAs<ID3D12Device8>()->CreatePlacedResource1(encode::GetWrappedObject<ID3D12Heap>(pHeap), HeapOffset, pDesc, InitialState,
                                                                            pOptimizedClearValue, riid, ppvResource);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvResource);
		}
		return result;
    }

    void STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateSamplerFeedbackUnorderedAccessView(
            ID3D12Resource* pTargetedResource,
            ID3D12Resource* pFeedbackResource,
            D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
    {
		// TODO: wrap descriptor
        GetWrappedObjectAs<ID3D12Device8>()->CreateSamplerFeedbackUnorderedAccessView(encode::GetWrappedObject<ID3D12Resource>(pTargetedResource),
																					encode::GetWrappedObject<ID3D12Resource>(pFeedbackResource), DestDescriptor);
    }

    void STDMETHODCALLTYPE ID3D12Device14Wrapper::GetCopyableFootprints1(
            const D3D12_RESOURCE_DESC1* pResourceDesc,
            UINT FirstSubresource,
            UINT NumSubresources,
            UINT64 BaseOffset,
            D3D12_PLACED_SUBRESOURCE_FOOTPRINT* pLayouts,
            UINT* pNumRows,
            UINT64* pRowSizeInBytes,
            UINT64* pTotalBytes)
    {
        GetWrappedObjectAs<ID3D12Device8>()->GetCopyableFootprints1(pResourceDesc, FirstSubresource, NumSubresources, BaseOffset,
                                                                    pLayouts, pNumRows, pRowSizeInBytes, pTotalBytes);
    }

	// ID3D12Device9
	HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateShaderCacheSession(
			const D3D12_SHADER_CACHE_SESSION_DESC* pDesc,
			REFIID riid,
			void** ppvSession)
	{
		const auto result = GetWrappedObjectAs<ID3D12Device9>()->CreateShaderCacheSession(pDesc, riid, ppvSession);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvSession);
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::ShaderCacheControl(
			D3D12_SHADER_CACHE_KIND_FLAGS Kinds,
			D3D12_SHADER_CACHE_CONTROL_FLAGS Control)
	{
		const auto result = GetWrappedObjectAs<ID3D12Device9>()->ShaderCacheControl(Kinds, Control);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateCommandQueue1(
			const D3D12_COMMAND_QUEUE_DESC* pDesc,
			REFIID CreatorID,
			REFIID riid,
			void** ppCommandQueue)
	{
		// TODO: implement
		const auto result = GetWrappedObjectAs<ID3D12Device9>()->CreateCommandQueue1(pDesc, CreatorID, riid, ppCommandQueue);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppCommandQueue);
		}
		return result;
	}

	// ID3D12Device10
	HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateCommittedResource3(
            const D3D12_HEAP_PROPERTIES* pHeapProperties,
            D3D12_HEAP_FLAGS HeapFlags,
            const D3D12_RESOURCE_DESC1* pDesc,
            D3D12_BARRIER_LAYOUT InitialLayout,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            ID3D12ProtectedResourceSession* pProtectedSession,
            UINT32 NumCastableFormats,
            const DXGI_FORMAT* pCastableFormats,
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

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreatePlacedResource2(
            ID3D12Heap* pHeap,
            UINT64 HeapOffset,
            const D3D12_RESOURCE_DESC1* pDesc,
            D3D12_BARRIER_LAYOUT InitialLayout,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            UINT32 NumCastableFormats,
            const DXGI_FORMAT* pCastableFormats,
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

    HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateReservedResource2(
            const D3D12_RESOURCE_DESC* pDesc,
            D3D12_BARRIER_LAYOUT InitialLayout,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            ID3D12ProtectedResourceSession* pProtectedSession,
            UINT32 NumCastableFormats,
            const DXGI_FORMAT* pCastableFormats,
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

	// ID3D12Device11
	void STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateSampler2(const D3D12_SAMPLER_DESC2 *pDesc,
																D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
	{
		// TODO: unwrap destination descriptor
		GetWrappedObjectAs<ID3D12Device11>()->CreateSampler2(pDesc, DestDescriptor);
	}

	// ID3D12Device12
	D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE ID3D12Device14Wrapper::GetResourceAllocationInfo3(
			UINT visibleMask, UINT numResourceDescs, const D3D12_RESOURCE_DESC1 *pResourceDescs,
			const UINT32 *pNumCastableFormats, const DXGI_FORMAT *const *ppCastableFormats,
			D3D12_RESOURCE_ALLOCATION_INFO1 *pResourceAllocationInfo1)
	{
		const auto result = GetWrappedObjectAs<ID3D12Device12>()->GetResourceAllocationInfo3(visibleMask, numResourceDescs, pResourceDescs, pNumCastableFormats,
																								ppCastableFormats, pResourceAllocationInfo1);
		return result;
	}

	// ID3D12Device13
	HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::OpenExistingHeapFromAddress1(
		_In_  const void *pAddress,
		SIZE_T size,
		REFIID riid,
		_COM_Outptr_  void **ppvHeap)
	{
		const auto result = GetWrappedObjectAs<ID3D12Device13>()->OpenExistingHeapFromAddress1(pAddress, size, riid, ppvHeap);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvHeap);
		}
		return result;
	}

	// ID3D12Device14
	HRESULT STDMETHODCALLTYPE ID3D12Device14Wrapper::CreateRootSignatureFromSubobjectInLibrary(
			_In_  UINT nodeMask,
			_In_reads_(blobLengthInBytes)  const void *pLibraryBlob,
			_In_  SIZE_T blobLengthInBytes,
			_In_opt_  LPCWSTR subobjectName,
			REFIID riid,
			_COM_Outptr_  void **ppvRootSignature)
	{
		// TODO: check wrap and unwrap
		const auto result = GetWrappedObjectAs<ID3D12Device14>()->CreateRootSignatureFromSubobjectInLibrary(nodeMask, pLibraryBlob, blobLengthInBytes, subobjectName, riid, ppvRootSignature);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvRootSignature);
		}
		return result;
	}
}