//
// Created by ZZK on 2024/8/19.
//

#include <tracer/d3d12/d3d12_command_list_wrap.h>
#include <tracer/d3d12/d3d12_command_list10_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	ID3D12GraphicsCommandList10Wrapper::ID3D12GraphicsCommandList10Wrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12GraphicsCommandList10Wrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12GraphicsCommandList10Wrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12GraphicsCommandList10Wrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12GraphicsCommandList10Wrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12GraphicsCommandList10Wrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12Object
	HRESULT STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::GetPrivateData(const GUID &guid, UINT *pDataSize, void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->GetPrivateData(guid, pDataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetPrivateData(const GUID &guid, UINT DataSize, const void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateData(guid, DataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetPrivateDataInterface(const GUID &guid, const IUnknown *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateDataInterface(guid, encode::GetWrappedObject<IUnknown>(pData));
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetName(LPCWSTR Name)
	{
		return GetWrappedObjectAs<ID3D12Object>()->SetName(Name);
	}

	// ID3D12DeviceChild
	HRESULT STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::GetDevice(const IID &riid, void **ppvDevice)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceChild>()->GetDevice(riid, ppvDevice);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvDevice);
		}
		return result;
	}

	// ID3D12CommandList
	D3D12_COMMAND_LIST_TYPE STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::GetType()
	{
		const auto result = GetWrappedObjectAs<ID3D12CommandList>()->GetType();
		return result;
	}

	// ID3D12GraphicsCommandList
	HRESULT STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::Close()
    {
		// TODO: trim draw and dispatch
        const auto result = GetWrappedObjectAs<ID3D12GraphicsCommandList>()->Close();
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::Reset(
            ID3D12CommandAllocator* pAllocator,
            ID3D12PipelineState* pInitialState)
    {
		// TODO: trim draw and dispatch
        const auto result = GetWrappedObjectAs<ID3D12GraphicsCommandList>()->Reset(encode::GetWrappedObject<ID3D12CommandAllocator>(pAllocator),
																								encode::GetWrappedObject<ID3D12PipelineState>(pInitialState));
		return result;
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::ClearState(
            ID3D12PipelineState* pPipelineState)
    {
		// TODO: trim draw and dispatch
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->ClearState(encode::GetWrappedObject<ID3D12PipelineState>(pPipelineState));
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::DrawInstanced(
            UINT VertexCountPerInstance,
            UINT InstanceCount,
            UINT StartVertexLocation,
            UINT StartInstanceLocation)
    {
		// TODO: trim draw
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->DrawInstanced(VertexCountPerInstance, InstanceCount, StartInstanceLocation, StartInstanceLocation);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::DrawIndexedInstanced(
            UINT IndexCountPerInstance,
            UINT InstanceCount,
            UINT StartIndexLocation,
            INT BaseVertexLocation,
            UINT StartInstanceLocation)
    {
		// TODO: trim draw
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, StartInstanceLocation,
                                                                                BaseVertexLocation, StartInstanceLocation);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::Dispatch(
            UINT ThreadGroupCountX,
            UINT ThreadGroupCountY,
            UINT ThreadGroupCountZ)
    {
		// TODO: trim dispatch
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->Dispatch(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::CopyBufferRegion(
            ID3D12Resource* pDstBuffer,
            UINT64 DstOffset,
            ID3D12Resource* pSrcBuffer,
            UINT64 SrcOffset,
            UINT64 NumBytes)
    {
		// TODO: trim draw and dispatch
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->CopyBufferRegion(encode::GetWrappedObject<ID3D12Resource>(pDstBuffer), DstOffset,
																			encode::GetWrappedObject<ID3D12Resource>(pSrcBuffer), SrcOffset, NumBytes);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::CopyTextureRegion(
            const D3D12_TEXTURE_COPY_LOCATION* pDst,
            UINT DstX,
            UINT DstY,
            UINT DstZ,
            const D3D12_TEXTURE_COPY_LOCATION* pSrc,
            const D3D12_BOX* pSrcBox)
    {
		// TODO: check unwrap copy location, trim draw or dispatch
		D3D12_TEXTURE_COPY_LOCATION dst_copy_location = *pDst;
		D3D12_TEXTURE_COPY_LOCATION src_copy_location = *pSrc;
		dst_copy_location.pResource = encode::GetWrappedObject<ID3D12Resource>(pDst->pResource);
		src_copy_location.pResource = encode::GetWrappedObject<ID3D12Resource>(pSrc->pResource);
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->CopyTextureRegion(&dst_copy_location, DstX, DstY, DstZ, &src_copy_location, pSrcBox);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::CopyResource(
            ID3D12Resource* pDstResource,
            ID3D12Resource* pSrcResource)
    {
		// TODO: trim draw and dispatch
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->CopyResource(encode::GetWrappedObject<ID3D12Resource>(pDstResource), encode::GetWrappedObject<ID3D12Resource>(pSrcResource));
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::CopyTiles(
            ID3D12Resource* pTiledResource,
            const D3D12_TILED_RESOURCE_COORDINATE* pTileRegionStartCoordinate,
            const D3D12_TILE_REGION_SIZE* pTileRegionSize,
            ID3D12Resource* pBuffer,
            UINT64 BufferStartOffsetInBytes,
            D3D12_TILE_COPY_FLAGS Flags)
    {
		// TODO: trim draw and dispatch
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->CopyTiles(encode::GetWrappedObject<ID3D12Resource>(pTiledResource), pTileRegionStartCoordinate, pTileRegionSize,
                                                                    encode::GetWrappedObject<ID3D12Resource>(pBuffer), BufferStartOffsetInBytes, Flags);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::ResolveSubresource(
            ID3D12Resource* pDstResource,
            UINT DstSubresource,
            ID3D12Resource* pSrcResource,
            UINT SrcSubresource,
            DXGI_FORMAT Format)
    {
		// TODO: trim draw
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->ResolveSubresource(encode::GetWrappedObject<ID3D12Resource>(pDstResource), DstSubresource,
																			encode::GetWrappedObject<ID3D12Resource>(pSrcResource), SrcSubresource, Format);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::IASetPrimitiveTopology(
            D3D12_PRIMITIVE_TOPOLOGY PrimitiveTopology)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->IASetPrimitiveTopology(PrimitiveTopology);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::RSSetViewports(
            UINT NumViewports,
            const D3D12_VIEWPORT* pViewports)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->RSSetViewports(NumViewports, pViewports);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::RSSetScissorRects(
            UINT NumRects, const D3D12_RECT* pRects)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->RSSetScissorRects(NumRects, pRects);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::OMSetBlendFactor(
            const FLOAT BlendFactor [4])
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->OMSetBlendFactor(BlendFactor);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::OMSetStencilRef(
            UINT StencilRef)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->OMSetStencilRef(StencilRef);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetPipelineState(
            ID3D12PipelineState* pPipelineState)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetPipelineState(encode::GetWrappedObject<ID3D12PipelineState>(pPipelineState));
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::ResourceBarrier(
            UINT NumBarriers,
            const D3D12_RESOURCE_BARRIER* pBarriers)
    {
		if (NumBarriers > 0U && pBarriers != nullptr)
		{
			std::vector<D3D12_RESOURCE_BARRIER> unwrap_barriers(NumBarriers);
			std::memcpy(unwrap_barriers.data(), pBarriers, sizeof(D3D12_RESOURCE_BARRIER) * NumBarriers);
			for (uint32_t i = 0U; i < NumBarriers; ++i)
			{
				if (pBarriers[i].Type == D3D12_RESOURCE_BARRIER_TYPE_TRANSITION)
				{
					unwrap_barriers[i].Transition.pResource = encode::GetWrappedObject<ID3D12Resource>(pBarriers[i].Transition.pResource);
				} else if (pBarriers[i].Type == D3D12_RESOURCE_BARRIER_TYPE_ALIASING)
				{
					unwrap_barriers[i].Aliasing.pResourceBefore = encode::GetWrappedObject<ID3D12Resource>(pBarriers[i].Aliasing.pResourceBefore);
					unwrap_barriers[i].Aliasing.pResourceAfter = encode::GetWrappedObject<ID3D12Resource>(pBarriers[i].Aliasing.pResourceAfter);
				} else
				{
					unwrap_barriers[i].UAV.pResource = encode::GetWrappedObject<ID3D12Resource>(pBarriers[i].UAV.pResource);
				}
			}
			return GetWrappedObjectAs<ID3D12GraphicsCommandList>()->ResourceBarrier(NumBarriers, unwrap_barriers.data());
		}
        return GetWrappedObjectAs<ID3D12GraphicsCommandList>()->ResourceBarrier(NumBarriers, pBarriers);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::ExecuteBundle(
            ID3D12GraphicsCommandList* pCommandList)
    {
        // TODO: check
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->ExecuteBundle(encode::GetWrappedObject<ID3D12GraphicsCommandList>(pCommandList));
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetDescriptorHeaps(
            UINT NumDescriptorHeaps,
            ID3D12DescriptorHeap* const* ppDescriptorHeaps)
    {
		if (NumDescriptorHeaps > 0U && ppDescriptorHeaps != nullptr)
		{
			std::vector<ID3D12DescriptorHeap *> unwrap_heaps(NumDescriptorHeaps);
			for (uint32_t i = 0U; i < NumDescriptorHeaps; ++i)
			{
				unwrap_heaps[i] = encode::GetWrappedObject<ID3D12DescriptorHeap>(ppDescriptorHeaps[i]);
			}
			return GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetDescriptorHeaps(NumDescriptorHeaps, unwrap_heaps.data());
		}
        return GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetDescriptorHeaps(NumDescriptorHeaps, ppDescriptorHeaps);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetComputeRootSignature(
            ID3D12RootSignature* pRootSignature)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetComputeRootSignature(encode::GetWrappedObject<ID3D12RootSignature>(pRootSignature));
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetGraphicsRootSignature(
            ID3D12RootSignature* pRootSignature)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetGraphicsRootSignature(encode::GetWrappedObject<ID3D12RootSignature>(pRootSignature));
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetComputeRootDescriptorTable(
            UINT RootParameterIndex,
            D3D12_GPU_DESCRIPTOR_HANDLE BaseDescriptor)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetComputeRootDescriptorTable(RootParameterIndex, BaseDescriptor);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetGraphicsRootDescriptorTable(
            UINT RootParameterIndex,
            D3D12_GPU_DESCRIPTOR_HANDLE BaseDescriptor)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetGraphicsRootDescriptorTable(RootParameterIndex, BaseDescriptor);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetComputeRoot32BitConstant(
            UINT RootParameterIndex,
            UINT SrcData,
            UINT DestOffsetIn32BitValues)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetComputeRoot32BitConstant(RootParameterIndex, SrcData, DestOffsetIn32BitValues);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetGraphicsRoot32BitConstant(
            UINT RootParameterIndex,
            UINT SrcData,
            UINT DestOffsetIn32BitValues)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetGraphicsRoot32BitConstant(RootParameterIndex, SrcData, DestOffsetIn32BitValues);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetComputeRoot32BitConstants(
            UINT RootParameterIndex,
            UINT Num32BitValuesToSet,
            const void* pSrcData,
            UINT DestOffsetIn32BitValues)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetComputeRoot32BitConstants(RootParameterIndex, Num32BitValuesToSet, pSrcData, DestOffsetIn32BitValues);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetGraphicsRoot32BitConstants(
            UINT RootParameterIndex,
            UINT Num32BitValuesToSet,
            const void* pSrcData,
            UINT DestOffsetIn32BitValues)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetGraphicsRoot32BitConstants(RootParameterIndex, Num32BitValuesToSet, pSrcData, DestOffsetIn32BitValues);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetComputeRootConstantBufferView(
            UINT RootParameterIndex,
            D3D12_GPU_VIRTUAL_ADDRESS BufferLocation)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetComputeRootConstantBufferView(RootParameterIndex, BufferLocation);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetGraphicsRootConstantBufferView(
            UINT RootParameterIndex,
            D3D12_GPU_VIRTUAL_ADDRESS BufferLocation)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetGraphicsRootConstantBufferView(RootParameterIndex, BufferLocation);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetComputeRootShaderResourceView(
            UINT RootParameterIndex,
            D3D12_GPU_VIRTUAL_ADDRESS BufferLocation)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetComputeRootShaderResourceView(RootParameterIndex, BufferLocation);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetGraphicsRootShaderResourceView(
            UINT RootParameterIndex,
            D3D12_GPU_VIRTUAL_ADDRESS BufferLocation)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetGraphicsRootShaderResourceView(RootParameterIndex, BufferLocation);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetComputeRootUnorderedAccessView(
            UINT RootParameterIndex,
            D3D12_GPU_VIRTUAL_ADDRESS BufferLocation)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetComputeRootUnorderedAccessView(RootParameterIndex, BufferLocation);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetGraphicsRootUnorderedAccessView(
            UINT RootParameterIndex,
            D3D12_GPU_VIRTUAL_ADDRESS BufferLocation)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetGraphicsRootUnorderedAccessView(RootParameterIndex, BufferLocation);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::IASetIndexBuffer(
            const D3D12_INDEX_BUFFER_VIEW* pView)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->IASetIndexBuffer(pView);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::IASetVertexBuffers(
            UINT StartSlot,
            UINT NumViews,
            const D3D12_VERTEX_BUFFER_VIEW* pViews)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->IASetVertexBuffers(StartSlot, NumViews, pViews);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SOSetTargets(
            UINT StartSlot,
            UINT NumViews,
            const D3D12_STREAM_OUTPUT_BUFFER_VIEW* pViews)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SOSetTargets(StartSlot, NumViews, pViews);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::OMSetRenderTargets(
            UINT NumRenderTargetDescriptors,
            const D3D12_CPU_DESCRIPTOR_HANDLE* pRenderTargetDescriptors,
            BOOL RTsSingleHandleToDescriptorRange,
            const D3D12_CPU_DESCRIPTOR_HANDLE* pDepthStencilDescriptor)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->OMSetRenderTargets(NumRenderTargetDescriptors, pRenderTargetDescriptors, RTsSingleHandleToDescriptorRange, pDepthStencilDescriptor);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::ClearDepthStencilView(
            D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView,
            D3D12_CLEAR_FLAGS ClearFlags,
            FLOAT Depth,
            UINT8 Stencil,
            UINT NumRects,
            const D3D12_RECT* pRects)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->ClearDepthStencilView(DepthStencilView, ClearFlags, Depth, Stencil, NumRects, pRects);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::ClearRenderTargetView(
            D3D12_CPU_DESCRIPTOR_HANDLE RenderTargetView,
            const FLOAT ColorRGBA [4],
            UINT NumRects,
            const D3D12_RECT* pRects)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->ClearRenderTargetView(RenderTargetView, ColorRGBA, NumRects, pRects);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::ClearUnorderedAccessViewUint(
            D3D12_GPU_DESCRIPTOR_HANDLE ViewGPUHandleInCurrentHeap,
            D3D12_CPU_DESCRIPTOR_HANDLE ViewCPUHandle,
            ID3D12Resource* pResource,
            const UINT Values [4],
            UINT NumRects,
            const D3D12_RECT* pRects)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->ClearUnorderedAccessViewUint(ViewGPUHandleInCurrentHeap, ViewCPUHandle, encode::GetWrappedObject<ID3D12Resource>(pResource),
                                                                                        Values, NumRects, pRects);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::ClearUnorderedAccessViewFloat(
            D3D12_GPU_DESCRIPTOR_HANDLE ViewGPUHandleInCurrentHeap,
            D3D12_CPU_DESCRIPTOR_HANDLE ViewCPUHandle,
            ID3D12Resource* pResource,
            const FLOAT Values [4],
            UINT NumRects,
            const D3D12_RECT* pRects)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->ClearUnorderedAccessViewFloat(ViewGPUHandleInCurrentHeap, ViewCPUHandle, encode::GetWrappedObject<ID3D12Resource>(pResource),
                                                                                        Values, NumRects, pRects);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::DiscardResource(
            ID3D12Resource* pResource,
            const D3D12_DISCARD_REGION* pRegion)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->DiscardResource(encode::GetWrappedObject<ID3D12Resource>(pResource), pRegion);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::BeginQuery(
            ID3D12QueryHeap* pQueryHeap,
            D3D12_QUERY_TYPE Type,
            UINT Index)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->BeginQuery(encode::GetWrappedObject<ID3D12QueryHeap>(pQueryHeap), Type, Index);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::EndQuery(
            ID3D12QueryHeap* pQueryHeap,
            D3D12_QUERY_TYPE Type,
            UINT Index)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->EndQuery(encode::GetWrappedObject<ID3D12QueryHeap>(pQueryHeap), Type, Index);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::ResolveQueryData(
            ID3D12QueryHeap* pQueryHeap,
            D3D12_QUERY_TYPE Type,
            UINT StartIndex,
            UINT NumQueries,
            ID3D12Resource* pDestinationBuffer,
            UINT64 AlignedDestinationBufferOffset)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->ResolveQueryData(encode::GetWrappedObject<ID3D12QueryHeap>(pQueryHeap), Type, StartIndex, NumQueries,
                                                                        encode::GetWrappedObject<ID3D12Resource>(pDestinationBuffer), AlignedDestinationBufferOffset);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetPredication(
            ID3D12Resource* pBuffer,
            UINT64 AlignedBufferOffset,
            D3D12_PREDICATION_OP Operation)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetPredication(encode::GetWrappedObject<ID3D12Resource>(pBuffer), AlignedBufferOffset, Operation);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetMarker(
            UINT Metadata,
            const void* pData,
            UINT Size)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetMarker(Metadata, pData, Size);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::BeginEvent(
            UINT Metadata,
            const void* pData,
            UINT Size)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->BeginEvent(Metadata, pData, Size);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::EndEvent()
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->EndEvent();
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::ExecuteIndirect(
            ID3D12CommandSignature* pCommandSignature,
            UINT MaxCommandCount,
            ID3D12Resource* pArgumentBuffer,
            UINT64 ArgumentBufferOffset,
            ID3D12Resource* pCountBuffer,
            UINT64 CountBufferOffset)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->ExecuteIndirect(encode::GetWrappedObject<ID3D12CommandSignature>(pCommandSignature), MaxCommandCount, encode::GetWrappedObject<ID3D12Resource>(pArgumentBuffer),
                                                                            ArgumentBufferOffset, encode::GetWrappedObject<ID3D12Resource>(pCountBuffer), CountBufferOffset);
    }

	// ID3D12GraphicsCommandList1
	void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::AtomicCopyBufferUINT(
            ID3D12Resource* pDstBuffer,
            UINT64 DstOffset,
            ID3D12Resource* pSrcBuffer,
            UINT64 SrcOffset,
            UINT Dependencies,
            ID3D12Resource* const* ppDependentResources,
            const D3D12_SUBRESOURCE_RANGE_UINT64* pDependentSubresourceRanges)
    {
		if (Dependencies > 0U && ppDependentResources != nullptr)
		{
			std::vector<ID3D12Resource *> unwrap_resources(Dependencies);
			for (uint32_t i = 0U; i < Dependencies; ++i)
			{
				unwrap_resources[i] = encode::GetWrappedObject<ID3D12Resource>(ppDependentResources[i]);
			}
			return GetWrappedObjectAs<ID3D12GraphicsCommandList1>()->AtomicCopyBufferUINT(encode::GetWrappedObject<ID3D12Resource>(pDstBuffer), DstOffset, encode::GetWrappedObject<ID3D12Resource>(pSrcBuffer), SrcOffset,
																						Dependencies, unwrap_resources.data(), pDependentSubresourceRanges);
		}
        return GetWrappedObjectAs<ID3D12GraphicsCommandList1>()->AtomicCopyBufferUINT(encode::GetWrappedObject<ID3D12Resource>(pDstBuffer), DstOffset, encode::GetWrappedObject<ID3D12Resource>(pSrcBuffer), SrcOffset,
																						Dependencies, ppDependentResources, pDependentSubresourceRanges);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::AtomicCopyBufferUINT64(
            ID3D12Resource* pDstBuffer,
            UINT64 DstOffset,
            ID3D12Resource* pSrcBuffer,
            UINT64 SrcOffset,
            UINT Dependencies,
            ID3D12Resource* const* ppDependentResources,
            const D3D12_SUBRESOURCE_RANGE_UINT64* pDependentSubresourceRanges)
    {
		if (Dependencies > 0U && ppDependentResources != nullptr)
		{
		    std::vector<ID3D12Resource *> unwrap_resources(Dependencies);
		    for (uint32_t i = 0U; i < Dependencies; ++i)
		    {
				unwrap_resources[i] = encode::GetWrappedObject<ID3D12Resource>(ppDependentResources[i]);
		    }
		    return GetWrappedObjectAs<ID3D12GraphicsCommandList1>()->AtomicCopyBufferUINT64(encode::GetWrappedObject<ID3D12Resource>(pDstBuffer), DstOffset, encode::GetWrappedObject<ID3D12Resource>(pSrcBuffer), SrcOffset,
																						Dependencies, unwrap_resources.data(), pDependentSubresourceRanges);
		}
        return GetWrappedObjectAs<ID3D12GraphicsCommandList1>()->AtomicCopyBufferUINT64(encode::GetWrappedObject<ID3D12Resource>(pDstBuffer), DstOffset, encode::GetWrappedObject<ID3D12Resource>(pSrcBuffer), SrcOffset,
																						Dependencies, ppDependentResources, pDependentSubresourceRanges);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::OMSetDepthBounds(
            FLOAT Min,
            FLOAT Max)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList1>()->OMSetDepthBounds(Min, Max);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetSamplePositions(
            UINT NumSamplesPerPixel,
            UINT NumPixels,
            D3D12_SAMPLE_POSITION* pSamplePositions)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList1>()->SetSamplePositions(NumSamplesPerPixel, NumPixels, pSamplePositions);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::ResolveSubresourceRegion(
            ID3D12Resource* pDstResource,
            UINT DstSubresource,
            UINT DstX,
            UINT DstY,
            ID3D12Resource* pSrcResource,
            UINT SrcSubresource,
            D3D12_RECT* pSrcRect,
            DXGI_FORMAT Format,
            D3D12_RESOLVE_MODE ResolveMode)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList1>()->ResolveSubresourceRegion(encode::GetWrappedObject<ID3D12Resource>(pDstResource), DstSubresource, DstX, DstY, encode::GetWrappedObject<ID3D12Resource>(pSrcResource),
                                                                                    SrcSubresource, pSrcRect, Format, ResolveMode);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetViewInstanceMask(UINT Mask)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList1>()->SetViewInstanceMask(Mask);
    }

	// ID3D12GraphicsCommandList2
	void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::WriteBufferImmediate(
			UINT Count,
			const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER* pParams,
			const D3D12_WRITEBUFFERIMMEDIATE_MODE* pModes)
	{
		GetWrappedObjectAs<ID3D12GraphicsCommandList2>()->WriteBufferImmediate(Count, pParams, pModes);
	}

	// ID3D12GraphicsCommandList3
	void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetProtectedResourceSession(
			ID3D12ProtectedResourceSession* pProtectedResourceSession)
	{
		GetWrappedObjectAs<ID3D12GraphicsCommandList3>()->SetProtectedResourceSession(encode::GetWrappedObject<ID3D12ProtectedResourceSession>(pProtectedResourceSession));
	}

	// ID3D12GraphicsCommandList4
	void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::BeginRenderPass(
            UINT NumRenderTargets,
            const D3D12_RENDER_PASS_RENDER_TARGET_DESC* pRenderTargets,
            const D3D12_RENDER_PASS_DEPTH_STENCIL_DESC* pDepthStencil,
            D3D12_RENDER_PASS_FLAGS Flags)
    {
		// TODO: unwrap render target desc and depth stencil desc
        GetWrappedObjectAs<ID3D12GraphicsCommandList4>()->BeginRenderPass(NumRenderTargets, pRenderTargets, pDepthStencil, Flags);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::EndRenderPass()
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList4>()->EndRenderPass();
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::InitializeMetaCommand(
            ID3D12MetaCommand* pMetaCommand,
            const void* pInitializationParametersData,
            SIZE_T InitializationParametersDataSizeInBytes)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList4>()->InitializeMetaCommand(encode::GetWrappedObject<ID3D12MetaCommand>(pMetaCommand), pInitializationParametersData, InitializationParametersDataSizeInBytes);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::ExecuteMetaCommand(
            ID3D12MetaCommand* pMetaCommand,
            const void* pExecutionParametersData,
            SIZE_T ExecutionParametersDataSizeInBytes)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList4>()->ExecuteMetaCommand(encode::GetWrappedObject<ID3D12MetaCommand>(pMetaCommand), pExecutionParametersData, ExecutionParametersDataSizeInBytes);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::BuildRaytracingAccelerationStructure(
            const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC* pDesc,
            UINT NumPostbuildInfoDescs,
            const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC* pPostbuildInfoDescs)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList4>()->BuildRaytracingAccelerationStructure(pDesc, NumPostbuildInfoDescs, pPostbuildInfoDescs);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::EmitRaytracingAccelerationStructurePostbuildInfo(
            const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC* pDesc,
            UINT NumSourceAccelerationStructures,
            const D3D12_GPU_VIRTUAL_ADDRESS* pSourceAccelerationStructureData)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList4>()->EmitRaytracingAccelerationStructurePostbuildInfo(pDesc, NumSourceAccelerationStructures, pSourceAccelerationStructureData);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::CopyRaytracingAccelerationStructure(
            D3D12_GPU_VIRTUAL_ADDRESS DestAccelerationStructureData,
            D3D12_GPU_VIRTUAL_ADDRESS SourceAccelerationStructureData,
            D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE Mode)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList4>()->CopyRaytracingAccelerationStructure(DestAccelerationStructureData, SourceAccelerationStructureData, Mode);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetPipelineState1(
            ID3D12StateObject* pStateObject)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList4>()->SetPipelineState1(encode::GetWrappedObject<ID3D12StateObject>(pStateObject));
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::DispatchRays(
            const D3D12_DISPATCH_RAYS_DESC* pDesc)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList4>()->DispatchRays(pDesc);
    }

	// ID3D12GraphicsCommandList5
	void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::RSSetShadingRate(
			D3D12_SHADING_RATE baseShadingRate,
			const D3D12_SHADING_RATE_COMBINER* combiners)
	{
		GetWrappedObjectAs<ID3D12GraphicsCommandList5>()->RSSetShadingRate(baseShadingRate, combiners);
	}

	void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::RSSetShadingRateImage(
			ID3D12Resource* shadingRateImage)
	{
		GetWrappedObjectAs<ID3D12GraphicsCommandList5>()->RSSetShadingRateImage(encode::GetWrappedObject<ID3D12Resource>(shadingRateImage));
	}

	// ID3D12GraphicsCommandList6
	void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::DispatchMesh(
			UINT ThreadGroupCountX,
			UINT ThreadGroupCountY,
			UINT ThreadGroupCountZ)
	{
		GetWrappedObjectAs<ID3D12GraphicsCommandList6>()->DispatchMesh(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
	}

	// ID3D12GraphicsCommandList7
	void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::Barrier(
            UINT32 NumBarrierGroups,
            const D3D12_BARRIER_GROUP* pBarrierGroups)
    {
		// TODO: check unwrap structs
		if (NumBarrierGroups > 0U && pBarrierGroups != nullptr)
		{
			std::vector<D3D12_BARRIER_GROUP> unwrap_barrier_groups(NumBarrierGroups);
			std::vector<D3D12_TEXTURE_BARRIER> texture_barriers{};
			std::vector<D3D12_BUFFER_BARRIER> buffer_barriers{};
			std::memcpy(unwrap_barrier_groups.data(), pBarrierGroups, sizeof(D3D12_BARRIER_GROUP) * NumBarrierGroups);
			for (uint32_t i = 0U; i < NumBarrierGroups; ++i)
			{
				auto &&barrier_group = pBarrierGroups[i];
				if (barrier_group.Type == D3D12_BARRIER_TYPE_TEXTURE && barrier_group.NumBarriers > 0U)
				{
					texture_barriers.resize(barrier_group.NumBarriers);
					std::memcpy(texture_barriers.data(), barrier_group.pTextureBarriers, barrier_group.NumBarriers * sizeof(D3D12_TEXTURE_BARRIER));
					for (uint32_t j = 0U; j < barrier_group.NumBarriers; ++j)
					{
						texture_barriers[j].pResource = encode::GetWrappedObject<ID3D12Resource>(barrier_group.pTextureBarriers[j].pResource);
					}
					unwrap_barrier_groups[i].pTextureBarriers = texture_barriers.data();
				} else if (barrier_group.Type == D3D12_BARRIER_TYPE_BUFFER && barrier_group.NumBarriers > 0U)
				{
					buffer_barriers.resize(barrier_group.NumBarriers);
					std::memcpy(buffer_barriers.data(), barrier_group.pBufferBarriers, barrier_group.NumBarriers * sizeof(D3D12_BUFFER_BARRIER));
					for (uint32_t j = 0U; j < barrier_group.NumBarriers; ++j)
					{
						buffer_barriers[j].pResource = encode::GetWrappedObject<ID3D12Resource>(barrier_group.pBufferBarriers[j].pResource);
					}
					unwrap_barrier_groups[i].pBufferBarriers = buffer_barriers.data();
				}
			}
			return GetWrappedObjectAs<ID3D12GraphicsCommandList7>()->Barrier(NumBarrierGroups, unwrap_barrier_groups.data());
		}
        return GetWrappedObjectAs<ID3D12GraphicsCommandList7>()->Barrier(NumBarrierGroups, pBarrierGroups);
    }

	// ID3D12GraphicsCommandList8
	void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::OMSetFrontAndBackStencilRef(UINT FrontStencilRef, UINT BackStencilRef)
	{
		GetWrappedObjectAs<ID3D12GraphicsCommandList8>()->OMSetFrontAndBackStencilRef(FrontStencilRef, BackStencilRef);
	}

	// ID3D12GraphicsCommandList9
	void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::RSSetDepthBias(FLOAT DepthBias, FLOAT DepthBiasClamp,
																			FLOAT SlopeScaledDepthBias)
	{
		GetWrappedObjectAs<ID3D12GraphicsCommandList9>()->RSSetDepthBias(DepthBias, DepthBiasClamp, SlopeScaledDepthBias);
	}

	void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::IASetIndexBufferStripCutValue(D3D12_INDEX_BUFFER_STRIP_CUT_VALUE IBStripCutValue)
	{
		GetWrappedObjectAs<ID3D12GraphicsCommandList9>()->IASetIndexBufferStripCutValue(IBStripCutValue);
	}

	// ID3D12GraphicsCommandList10
	void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::SetProgram(const D3D12_SET_PROGRAM_DESC *pDesc)
	{
		// TODO: check
		GetWrappedObjectAs<ID3D12GraphicsCommandList10>()->SetProgram(pDesc);
	}

	void STDMETHODCALLTYPE ID3D12GraphicsCommandList10Wrapper::DispatchGraph(const D3D12_DISPATCH_GRAPH_DESC *pDesc)
	{
		// TODO: check
		GetWrappedObjectAs<ID3D12GraphicsCommandList10>()->DispatchGraph(pDesc);
	}
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetProgram(
        _In_  const D3D12_SET_PROGRAM_DESC *pDesc)
{
    m_pList10->SetProgram(pDesc);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::DispatchGraph(
        _In_  const D3D12_DISPATCH_GRAPH_DESC *pDesc)
{
    m_pList10->DispatchGraph(pDesc);
}