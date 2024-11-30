#include <tracer/d3d12/d3d12_command_list_wrap.h>
#include <tracer/d3d12/d3d12_device_wrap.h>
#include <tracer/d3d12/d3d12_command_allocator_wrap.h>
#include <tracer/core/wrapper_creators.h>
#include <tracer/hooks/d3d12_hook_manager.h>

namespace gfxshim
{
    // ID3D12CommandListWrapper
    ID3D12CommandListWrapper::ID3D12CommandListWrapper(const IID &riid, IUnknown *object)
    : ID3D12DeviceChildWrapper(riid, object)
    {

    }

    ID3D12CommandListWrapper::~ID3D12CommandListWrapper() = default;

    D3D12_COMMAND_LIST_TYPE STDMETHODCALLTYPE ID3D12CommandListWrapper::GetType()
    {
        const auto result = GetWrappedObjectAs<ID3D12CommandList>()->GetType();
		return result;
    }

    // ID3D12GraphicsCommandListWrapper
    ID3D12GraphicsCommandListWrapper::ID3D12GraphicsCommandListWrapper(const IID &riid, IUnknown *object)
    : ID3D12CommandListWrapper(riid, object)
    {

    }

    ID3D12GraphicsCommandListWrapper::~ID3D12GraphicsCommandListWrapper() = default;

    HRESULT STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::Close()
    {
		// TODO: trim draw and dispatch
        const auto result = GetWrappedObjectAs<ID3D12GraphicsCommandList>()->Close();
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::Reset(
            ID3D12CommandAllocator* pAllocator,
            ID3D12PipelineState* pInitialState)
    {
		// TODO: trim draw and dispatch
        const auto result = GetWrappedObjectAs<ID3D12GraphicsCommandList>()->Reset(encode::GetWrappedObject<ID3D12CommandAllocator>(pAllocator),
																								encode::GetWrappedObject<ID3D12PipelineState>(pInitialState));
		return result;
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::ClearState(
            ID3D12PipelineState* pPipelineState)
    {
		// TODO: trim draw and dispatch
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->ClearState(encode::GetWrappedObject<ID3D12PipelineState>(pPipelineState));
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::DrawInstanced(
            UINT VertexCountPerInstance,
            UINT InstanceCount,
            UINT StartVertexLocation,
            UINT StartInstanceLocation)
    {
		// TODO: trim draw
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->DrawInstanced(VertexCountPerInstance, InstanceCount, StartInstanceLocation, StartInstanceLocation);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::DrawIndexedInstanced(
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

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::Dispatch(
            UINT ThreadGroupCountX,
            UINT ThreadGroupCountY,
            UINT ThreadGroupCountZ)
    {
		// TODO: trim dispatch
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->Dispatch(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::CopyBufferRegion(
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

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::CopyTextureRegion(
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

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::CopyResource(
            ID3D12Resource* pDstResource,
            ID3D12Resource* pSrcResource)
    {
		// TODO: trim draw and dispatch
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->CopyResource(encode::GetWrappedObject<ID3D12Resource>(pDstResource), encode::GetWrappedObject<ID3D12Resource>(pSrcResource));
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::CopyTiles(
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

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::ResolveSubresource(
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

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::IASetPrimitiveTopology(
            D3D12_PRIMITIVE_TOPOLOGY PrimitiveTopology)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->IASetPrimitiveTopology(PrimitiveTopology);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::RSSetViewports(
            UINT NumViewports,
            const D3D12_VIEWPORT* pViewports)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->RSSetViewports(NumViewports, pViewports);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::RSSetScissorRects(
            UINT NumRects, const D3D12_RECT* pRects)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->RSSetScissorRects(NumRects, pRects);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::OMSetBlendFactor(
            const FLOAT BlendFactor [4])
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->OMSetBlendFactor(BlendFactor);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::OMSetStencilRef(
            UINT StencilRef)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->OMSetStencilRef(StencilRef);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::SetPipelineState(
            ID3D12PipelineState* pPipelineState)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetPipelineState(encode::GetWrappedObject<ID3D12PipelineState>(pPipelineState));
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::ResourceBarrier(
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

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::ExecuteBundle(
            ID3D12GraphicsCommandList* pCommandList)
    {
        // TODO: check
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->ExecuteBundle(encode::GetWrappedObject<ID3D12GraphicsCommandList>(pCommandList));
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::SetDescriptorHeaps(
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

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::SetComputeRootSignature(
            ID3D12RootSignature* pRootSignature)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetComputeRootSignature(encode::GetWrappedObject<ID3D12RootSignature>(pRootSignature));
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::SetGraphicsRootSignature(
            ID3D12RootSignature* pRootSignature)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetGraphicsRootSignature(encode::GetWrappedObject<ID3D12RootSignature>(pRootSignature));
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::SetComputeRootDescriptorTable(
            UINT RootParameterIndex,
            D3D12_GPU_DESCRIPTOR_HANDLE BaseDescriptor)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetComputeRootDescriptorTable(RootParameterIndex, BaseDescriptor);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::SetGraphicsRootDescriptorTable(
            UINT RootParameterIndex,
            D3D12_GPU_DESCRIPTOR_HANDLE BaseDescriptor)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetGraphicsRootDescriptorTable(RootParameterIndex, BaseDescriptor);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::SetComputeRoot32BitConstant(
            UINT RootParameterIndex,
            UINT SrcData,
            UINT DestOffsetIn32BitValues)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetComputeRoot32BitConstant(RootParameterIndex, SrcData, DestOffsetIn32BitValues);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::SetGraphicsRoot32BitConstant(
            UINT RootParameterIndex,
            UINT SrcData,
            UINT DestOffsetIn32BitValues)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetGraphicsRoot32BitConstant(RootParameterIndex, SrcData, DestOffsetIn32BitValues);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::SetComputeRoot32BitConstants(
            UINT RootParameterIndex,
            UINT Num32BitValuesToSet,
            const void* pSrcData,
            UINT DestOffsetIn32BitValues)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetComputeRoot32BitConstants(RootParameterIndex, Num32BitValuesToSet, pSrcData, DestOffsetIn32BitValues);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::SetGraphicsRoot32BitConstants(
            UINT RootParameterIndex,
            UINT Num32BitValuesToSet,
            const void* pSrcData,
            UINT DestOffsetIn32BitValues)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetGraphicsRoot32BitConstants(RootParameterIndex, Num32BitValuesToSet, pSrcData, DestOffsetIn32BitValues);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::SetComputeRootConstantBufferView(
            UINT RootParameterIndex,
            D3D12_GPU_VIRTUAL_ADDRESS BufferLocation)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetComputeRootConstantBufferView(RootParameterIndex, BufferLocation);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::SetGraphicsRootConstantBufferView(
            UINT RootParameterIndex,
            D3D12_GPU_VIRTUAL_ADDRESS BufferLocation)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetGraphicsRootConstantBufferView(RootParameterIndex, BufferLocation);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::SetComputeRootShaderResourceView(
            UINT RootParameterIndex,
            D3D12_GPU_VIRTUAL_ADDRESS BufferLocation)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetComputeRootShaderResourceView(RootParameterIndex, BufferLocation);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::SetGraphicsRootShaderResourceView(
            UINT RootParameterIndex,
            D3D12_GPU_VIRTUAL_ADDRESS BufferLocation)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetGraphicsRootShaderResourceView(RootParameterIndex, BufferLocation);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::SetComputeRootUnorderedAccessView(
            UINT RootParameterIndex,
            D3D12_GPU_VIRTUAL_ADDRESS BufferLocation)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetComputeRootUnorderedAccessView(RootParameterIndex, BufferLocation);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::SetGraphicsRootUnorderedAccessView(
            UINT RootParameterIndex,
            D3D12_GPU_VIRTUAL_ADDRESS BufferLocation)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetGraphicsRootUnorderedAccessView(RootParameterIndex, BufferLocation);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::IASetIndexBuffer(
            const D3D12_INDEX_BUFFER_VIEW* pView)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->IASetIndexBuffer(pView);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::IASetVertexBuffers(
            UINT StartSlot,
            UINT NumViews,
            const D3D12_VERTEX_BUFFER_VIEW* pViews)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->IASetVertexBuffers(StartSlot, NumViews, pViews);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::SOSetTargets(
            UINT StartSlot,
            UINT NumViews,
            const D3D12_STREAM_OUTPUT_BUFFER_VIEW* pViews)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SOSetTargets(StartSlot, NumViews, pViews);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::OMSetRenderTargets(
            UINT NumRenderTargetDescriptors,
            const D3D12_CPU_DESCRIPTOR_HANDLE* pRenderTargetDescriptors,
            BOOL RTsSingleHandleToDescriptorRange,
            const D3D12_CPU_DESCRIPTOR_HANDLE* pDepthStencilDescriptor)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->OMSetRenderTargets(NumRenderTargetDescriptors, pRenderTargetDescriptors, RTsSingleHandleToDescriptorRange, pDepthStencilDescriptor);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::ClearDepthStencilView(
            D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView,
            D3D12_CLEAR_FLAGS ClearFlags,
            FLOAT Depth,
            UINT8 Stencil,
            UINT NumRects,
            const D3D12_RECT* pRects)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->ClearDepthStencilView(DepthStencilView, ClearFlags, Depth, Stencil, NumRects, pRects);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::ClearRenderTargetView(
            D3D12_CPU_DESCRIPTOR_HANDLE RenderTargetView,
            const FLOAT ColorRGBA [4],
            UINT NumRects,
            const D3D12_RECT* pRects)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->ClearRenderTargetView(RenderTargetView, ColorRGBA, NumRects, pRects);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::ClearUnorderedAccessViewUint(
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

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::ClearUnorderedAccessViewFloat(
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

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::DiscardResource(
            ID3D12Resource* pResource,
            const D3D12_DISCARD_REGION* pRegion)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->DiscardResource(encode::GetWrappedObject<ID3D12Resource>(pResource), pRegion);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::BeginQuery(
            ID3D12QueryHeap* pQueryHeap,
            D3D12_QUERY_TYPE Type,
            UINT Index)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->BeginQuery(encode::GetWrappedObject<ID3D12QueryHeap>(pQueryHeap), Type, Index);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::EndQuery(
            ID3D12QueryHeap* pQueryHeap,
            D3D12_QUERY_TYPE Type,
            UINT Index)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->EndQuery(encode::GetWrappedObject<ID3D12QueryHeap>(pQueryHeap), Type, Index);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::ResolveQueryData(
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

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::SetPredication(
            ID3D12Resource* pBuffer,
            UINT64 AlignedBufferOffset,
            D3D12_PREDICATION_OP Operation)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetPredication(encode::GetWrappedObject<ID3D12Resource>(pBuffer), AlignedBufferOffset, Operation);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::SetMarker(
            UINT Metadata,
            const void* pData,
            UINT Size)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->SetMarker(Metadata, pData, Size);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::BeginEvent(
            UINT Metadata,
            const void* pData,
            UINT Size)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->BeginEvent(Metadata, pData, Size);
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::EndEvent()
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList>()->EndEvent();
    }

    void STDMETHODCALLTYPE ID3D12GraphicsCommandListWrapper::ExecuteIndirect(
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
}

WrappedID3D12GraphicsCommandList::WrappedID3D12GraphicsCommandList(ID3D12GraphicsCommandList *real_command_list, WrappedID3D12Device *wrapped_device,
                                                                    WrappedID3D12CommandAllocator *wrapped_command_allocator)
: m_pList(real_command_list), m_wrapped_command_allocator(wrapped_command_allocator), m_wrapped_device(wrapped_device)
{
    if (m_pList)
    {
        m_pList->QueryInterface(__uuidof(ID3D12GraphicsCommandList1), reinterpret_cast<void **>(&m_pList1));
        m_pList->QueryInterface(__uuidof(ID3D12GraphicsCommandList2), reinterpret_cast<void **>(&m_pList2));
        m_pList->QueryInterface(__uuidof(ID3D12GraphicsCommandList3), reinterpret_cast<void **>(&m_pList3));
        m_pList->QueryInterface(__uuidof(ID3D12GraphicsCommandList4), reinterpret_cast<void **>(&m_pList4));
        m_pList->QueryInterface(__uuidof(ID3D12GraphicsCommandList5), reinterpret_cast<void **>(&m_pList5));
        m_pList->QueryInterface(__uuidof(ID3D12GraphicsCommandList6), reinterpret_cast<void **>(&m_pList6));
        m_pList->QueryInterface(__uuidof(ID3D12GraphicsCommandList7), reinterpret_cast<void **>(&m_pList7));
        m_pList->QueryInterface(__uuidof(ID3D12GraphicsCommandList8), reinterpret_cast<void **>(&m_pList8));
        m_pList->QueryInterface(__uuidof(ID3D12GraphicsCommandList9), reinterpret_cast<void **>(&m_pList9));
        m_pList->QueryInterface(__uuidof(ID3D12GraphicsCommandList10), reinterpret_cast<void **>(&m_pList10));

        m_pList->AddRef();
    }
}

WrappedID3D12GraphicsCommandList::~WrappedID3D12GraphicsCommandList() = default;

ID3D12GraphicsCommandList *WrappedID3D12GraphicsCommandList::GetReal() const
{
    return m_pList;
}

ULONG STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::AddRef()
{
    return m_pList->AddRef();
}

ULONG STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::Release()
{
    return m_pList->Release();
}

HRESULT STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::QueryInterface(REFIID riid, void **ppvObject)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    const auto result = m_pList->QueryInterface(riid, ppvObject);
    if (riid == __uuidof(ID3D12CommandList)          || riid == __uuidof(ID3D12GraphicsCommandList)  || riid == __uuidof(ID3D12GraphicsCommandList1) ||
        riid == __uuidof(ID3D12GraphicsCommandList2) || riid == __uuidof(ID3D12GraphicsCommandList3) || riid == __uuidof(ID3D12GraphicsCommandList4) ||
        riid == __uuidof(ID3D12GraphicsCommandList5) || riid == __uuidof(ID3D12GraphicsCommandList6) || riid == __uuidof(ID3D12GraphicsCommandList7) ||
        riid == __uuidof(ID3D12GraphicsCommandList8) || riid == __uuidof(ID3D12GraphicsCommandList9) || riid == __uuidof(ID3D12GraphicsCommandList10))
    {
        *ppvObject = this;
        this->AddRef();
    }
    return result;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::GetPrivateData(REFGUID guid, UINT *pDataSize, void *pData)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pList->GetPrivateData(guid, pDataSize, pData);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetPrivateData(REFGUID guid, UINT DataSize, const void *pData)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pList->SetPrivateData(guid, DataSize, pData);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetPrivateDataInterface(REFGUID guid, const IUnknown *pData)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pList->SetPrivateDataInterface(guid, pData);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetName(LPCWSTR Name)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pList->SetName(Name);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::GetDevice(REFIID riid, _COM_Outptr_opt_ void **ppvDevice)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    HRESULT result = m_wrapped_device->GetDevice(riid, ppvDevice);
    return result;
}

D3D12_COMMAND_LIST_TYPE STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::GetType()
{
    auto command_list_type =  m_pList->GetType();
    return command_list_type;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::Close()
{
    return m_pList->Close();
}

HRESULT STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::Reset(ID3D12CommandAllocator *pAllocator, ID3D12PipelineState *pInitialState)
{
    D3D12_WRAPPER_ASSERT(pAllocator != nullptr, "ID3D12CommandAllocator can not be nullptr");
    ID3D12CommandAllocator *real_command_allocator = pAllocator;
    if (auto *wrapped_command_allocator = dynamic_cast<WrappedID3D12CommandAllocator *>(pAllocator))
    {
        real_command_allocator = wrapped_command_allocator->GetReal();
    }
    return m_pList->Reset(real_command_allocator, pInitialState);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::ClearState(ID3D12PipelineState *pPipelineState)
{
    m_pList->ClearState(pPipelineState);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::DrawInstanced(UINT VertexCountPerInstance, UINT InstanceCount,
                                UINT StartVertexLocation, UINT StartInstanceLocation)
{
    m_pList->DrawInstanced(VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
    gfxshim::D3D12HookManager::GetInstance().CollectStagingResourcePerDraw(m_wrapped_device, m_pList);  // TODO: test deferred per-draw-dump
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount,
                                        UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation)
{
    m_pList->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
    gfxshim::D3D12HookManager::GetInstance().CollectStagingResourcePerDraw(m_wrapped_device, m_pList);  // TODO: test deferred per-draw-dump
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ)
{
    m_pList->Dispatch(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
    gfxshim::D3D12HookManager::GetInstance().CollectStagingResourcePerDispatch(m_wrapped_device, m_pList);  // TODO: test deferred per-dispatch-dump
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::CopyBufferRegion(ID3D12Resource *pDstBuffer, UINT64 DstOffset,
                                    ID3D12Resource *pSrcBuffer, UINT64 SrcOffset, UINT64 NumBytes)
{
    m_pList->CopyBufferRegion(pDstBuffer, DstOffset, pSrcBuffer, SrcOffset, NumBytes);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::CopyTextureRegion(const D3D12_TEXTURE_COPY_LOCATION *pDst, UINT DstX,
                                    UINT DstY, UINT DstZ,
                                    const D3D12_TEXTURE_COPY_LOCATION *pSrc,
                                    const D3D12_BOX *pSrcBox)
{
    m_pList->CopyTextureRegion(pDst, DstX, DstY, DstZ, pSrc, pSrcBox);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::CopyResource(ID3D12Resource *pDstResource, ID3D12Resource *pSrcResource)
{
    m_pList->CopyResource(pDstResource, pSrcResource);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::CopyTiles(ID3D12Resource *pTiledResource,
                            const D3D12_TILED_RESOURCE_COORDINATE *pTileRegionStartCoordinate,
                            const D3D12_TILE_REGION_SIZE *pTileRegionSize,
                            ID3D12Resource *pBuffer, UINT64 BufferStartOffsetInBytes,
                            D3D12_TILE_COPY_FLAGS Flags)
{
    m_pList->CopyTiles(pTiledResource, pTileRegionStartCoordinate, pTileRegionSize, pBuffer, BufferStartOffsetInBytes, Flags);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::ResolveSubresource(ID3D12Resource *pDstResource, UINT DstSubresource,
                                    ID3D12Resource *pSrcResource, UINT SrcSubresource,
                                    DXGI_FORMAT Format)
{
    m_pList->ResolveSubresource(pDstResource, DstSubresource, pSrcResource, SrcSubresource, Format);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::IASetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY PrimitiveTopology)
{
    m_pList->IASetPrimitiveTopology(PrimitiveTopology);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::RSSetViewports(UINT NumViewports, const D3D12_VIEWPORT *pViewports)
{
    m_pList->RSSetViewports(NumViewports, pViewports);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::RSSetScissorRects(UINT NumRects, const D3D12_RECT *pRects)
{
    m_pList->RSSetScissorRects(NumRects, pRects);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::OMSetBlendFactor(const FLOAT BlendFactor[4])
{
    m_pList->OMSetBlendFactor(BlendFactor);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::OMSetStencilRef(UINT StencilRef)
{
    m_pList->OMSetStencilRef(StencilRef);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetPipelineState(ID3D12PipelineState *pPipelineState)
{
    m_pList->SetPipelineState(pPipelineState);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::ResourceBarrier(UINT NumBarriers, const D3D12_RESOURCE_BARRIER *pBarriers)
{
    m_pList->ResourceBarrier(NumBarriers, pBarriers);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::ExecuteBundle(ID3D12GraphicsCommandList *pCommandList)
{
    // TODO: Verify robustness
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    ID3D12GraphicsCommandList *real_command_list = pCommandList;
    if (pCommandList)
    {
        if (auto *wrapped_command_list = dynamic_cast<WrappedID3D12GraphicsCommandList *>(pCommandList))
        {
            real_command_list = wrapped_command_list->GetReal();
        }
    }
    m_pList->ExecuteBundle(real_command_list);
    gfxshim::D3D12HookManager::GetInstance().CollectStagingResourcePerBundle(m_wrapped_device, m_pList, real_command_list);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetDescriptorHeaps(UINT NumDescriptorHeaps,
                                    ID3D12DescriptorHeap *const *ppDescriptorHeaps)
{
    m_pList->SetDescriptorHeaps(NumDescriptorHeaps, ppDescriptorHeaps);
    gfxshim::D3D12HookManager::GetInstance().ResetDescriptorHeaps(m_pList, NumDescriptorHeaps, ppDescriptorHeaps);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetComputeRootSignature(ID3D12RootSignature *pRootSignature)
{
    m_pList->SetComputeRootSignature(pRootSignature);
    gfxshim::D3D12HookManager::GetInstance().ResetComputePipelineRootSignature(m_pList, pRootSignature);  // TODO: enable uav test
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetGraphicsRootSignature(ID3D12RootSignature *pRootSignature)
{
    m_pList->SetGraphicsRootSignature(pRootSignature);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetComputeRootDescriptorTable(UINT RootParameterIndex,
                                                D3D12_GPU_DESCRIPTOR_HANDLE BaseDescriptor)
{
    m_pList->SetComputeRootDescriptorTable(RootParameterIndex, BaseDescriptor);
    gfxshim::D3D12HookManager::GetInstance().UpdateUAVStatePerDispatch(m_pList, RootParameterIndex, BaseDescriptor.ptr);  // TODO: enable uav test
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetGraphicsRootDescriptorTable(UINT RootParameterIndex,
                                                D3D12_GPU_DESCRIPTOR_HANDLE BaseDescriptor)
{
    m_pList->SetGraphicsRootDescriptorTable(RootParameterIndex, BaseDescriptor);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetComputeRoot32BitConstant(UINT RootParameterIndex, UINT SrcData,
                                            UINT DestOffsetIn32BitValues)
{
    m_pList->SetComputeRoot32BitConstant(RootParameterIndex, SrcData, DestOffsetIn32BitValues);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetGraphicsRoot32BitConstant(UINT RootParameterIndex, UINT SrcData,
                                            UINT DestOffsetIn32BitValues)
{
    m_pList->SetGraphicsRoot32BitConstant(RootParameterIndex, SrcData, DestOffsetIn32BitValues);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetComputeRoot32BitConstants(UINT RootParameterIndex,
                                                UINT Num32BitValuesToSet,
                                                const void *pSrcData,
                                                UINT DestOffsetIn32BitValues)
{
    m_pList->SetComputeRoot32BitConstants(RootParameterIndex, Num32BitValuesToSet, pSrcData, DestOffsetIn32BitValues);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetGraphicsRoot32BitConstants(UINT RootParameterIndex,
                                                UINT Num32BitValuesToSet,
                                                const void *pSrcData,
                                                UINT DestOffsetIn32BitValues)
{
    m_pList->SetGraphicsRoot32BitConstants(RootParameterIndex, Num32BitValuesToSet, pSrcData, DestOffsetIn32BitValues);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetComputeRootConstantBufferView(UINT RootParameterIndex,
                                                    D3D12_GPU_VIRTUAL_ADDRESS BufferLocation)
{
    m_pList->SetComputeRootConstantBufferView(RootParameterIndex, BufferLocation);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetGraphicsRootConstantBufferView(UINT RootParameterIndex,
                                                    D3D12_GPU_VIRTUAL_ADDRESS BufferLocation)
{
    m_pList->SetGraphicsRootConstantBufferView(RootParameterIndex, BufferLocation);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetComputeRootShaderResourceView(UINT RootParameterIndex,
                                                    D3D12_GPU_VIRTUAL_ADDRESS BufferLocation)
{
    m_pList->SetComputeRootConstantBufferView(RootParameterIndex, BufferLocation);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetGraphicsRootShaderResourceView(UINT RootParameterIndex,
                                                    D3D12_GPU_VIRTUAL_ADDRESS BufferLocation)
{
    m_pList->SetGraphicsRootShaderResourceView(RootParameterIndex, BufferLocation);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetComputeRootUnorderedAccessView(UINT RootParameterIndex,
                                                    D3D12_GPU_VIRTUAL_ADDRESS BufferLocation)
{
    m_pList->SetComputeRootUnorderedAccessView(RootParameterIndex, BufferLocation);
    gfxshim::D3D12HookManager::GetInstance().UpdateUAVStatePerDispatch(m_pList, BufferLocation);  // TODO: enable uav test
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetGraphicsRootUnorderedAccessView(UINT RootParameterIndex,
                                                    D3D12_GPU_VIRTUAL_ADDRESS BufferLocation)
{
    m_pList->SetGraphicsRootUnorderedAccessView(RootParameterIndex, BufferLocation);
    gfxshim::D3D12HookManager::GetInstance().UpdateUAVStatePerDraw(m_pList, BufferLocation);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::IASetIndexBuffer(const D3D12_INDEX_BUFFER_VIEW *pView)
{
    m_pList->IASetIndexBuffer(pView);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::IASetVertexBuffers(UINT StartSlot, UINT NumViews,
                                    const D3D12_VERTEX_BUFFER_VIEW *pViews)
{
    m_pList->IASetVertexBuffers(StartSlot, NumViews, pViews);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SOSetTargets(UINT StartSlot, UINT NumViews,
                                const D3D12_STREAM_OUTPUT_BUFFER_VIEW *pViews)
{
    m_pList->SOSetTargets(StartSlot, NumViews, pViews);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::OMSetRenderTargets(UINT NumRenderTargetDescriptors,
                                            const D3D12_CPU_DESCRIPTOR_HANDLE *pRenderTargetDescriptors,
                                            BOOL RTsSingleHandleToDescriptorRange,
                                            const D3D12_CPU_DESCRIPTOR_HANDLE *pDepthStencilDescriptor)
{
    m_pList->OMSetRenderTargets(NumRenderTargetDescriptors, pRenderTargetDescriptors, RTsSingleHandleToDescriptorRange, pDepthStencilDescriptor);
    gfxshim::D3D12HookManager::GetInstance().UpdateRTVAndDSVStatesPerDraw(m_pList, NumRenderTargetDescriptors, pRenderTargetDescriptors, pDepthStencilDescriptor);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::ClearDepthStencilView(D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView,
                                        D3D12_CLEAR_FLAGS ClearFlags, FLOAT Depth,
                                        UINT8 Stencil, UINT NumRects,
                                        const D3D12_RECT *pRects)
{
    m_pList->ClearDepthStencilView(DepthStencilView, ClearFlags, Depth, Stencil, NumRects, pRects);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::ClearRenderTargetView(D3D12_CPU_DESCRIPTOR_HANDLE RenderTargetView,
                                        const FLOAT ColorRGBA[4], UINT NumRects,
                                        const D3D12_RECT *pRects)
{
    m_pList->ClearRenderTargetView(RenderTargetView, ColorRGBA, NumRects, pRects);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::ClearUnorderedAccessViewUint(
            D3D12_GPU_DESCRIPTOR_HANDLE ViewGPUHandleInCurrentHeap,
            D3D12_CPU_DESCRIPTOR_HANDLE ViewCPUHandle, ID3D12Resource *pResource, const UINT Values[4],
            UINT NumRects, const D3D12_RECT *pRects)
{
    m_pList->ClearUnorderedAccessViewUint(ViewGPUHandleInCurrentHeap, ViewCPUHandle, pResource, Values, NumRects, pRects);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::ClearUnorderedAccessViewFloat(
            D3D12_GPU_DESCRIPTOR_HANDLE ViewGPUHandleInCurrentHeap,
            D3D12_CPU_DESCRIPTOR_HANDLE ViewCPUHandle, ID3D12Resource *pResource, const FLOAT Values[4],
            UINT NumRects, const D3D12_RECT *pRects)
{
    m_pList->ClearUnorderedAccessViewFloat(ViewGPUHandleInCurrentHeap, ViewCPUHandle, pResource, 
                                        Values, NumRects, pRects);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::DiscardResource(ID3D12Resource *pResource,
                                const D3D12_DISCARD_REGION *pRegion)
{
    m_pList->DiscardResource(pResource, pRegion);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::BeginQuery(ID3D12QueryHeap *pQueryHeap, D3D12_QUERY_TYPE Type, UINT Index)
{
    m_pList->BeginQuery(pQueryHeap, Type, Index);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::EndQuery(ID3D12QueryHeap *pQueryHeap, D3D12_QUERY_TYPE Type, UINT Index)
{
    m_pList->EndQuery(pQueryHeap, Type, Index);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::ResolveQueryData(ID3D12QueryHeap *pQueryHeap, D3D12_QUERY_TYPE Type,
                                    UINT StartIndex, UINT NumQueries,
                                    ID3D12Resource *pDestinationBuffer,
                                    UINT64 AlignedDestinationBufferOffset)
{
    m_pList->ResolveQueryData(pQueryHeap, Type, StartIndex, NumQueries, pDestinationBuffer, AlignedDestinationBufferOffset);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetPredication(ID3D12Resource *pBuffer, UINT64 AlignedBufferOffset,
                                D3D12_PREDICATION_OP Operation)
{
    m_pList->SetPredication(pBuffer, AlignedBufferOffset, Operation);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetMarker(UINT Metadata, const void *pData, UINT Size)
{
    m_pList->SetMarker(Metadata, pData, Size);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::BeginEvent(UINT Metadata, const void *pData, UINT Size)
{
    m_pList->BeginEvent(Metadata, pData, Size);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::EndEvent() 
{
    m_pList->EndEvent();
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::ExecuteIndirect(ID3D12CommandSignature *pCommandSignature,
                                UINT MaxCommandCount, ID3D12Resource *pArgumentBuffer,
                                UINT64 ArgumentBufferOffset, ID3D12Resource *pCountBuffer,
                                UINT64 CountBufferOffset)
{
    m_pList->ExecuteIndirect(pCommandSignature, MaxCommandCount, pArgumentBuffer, ArgumentBufferOffset, pCountBuffer, CountBufferOffset);
    gfxshim::D3D12HookManager::GetInstance().CollectStagingResourcePerIndirect(m_wrapped_device, m_pList, reinterpret_cast<uint64_t>(pCommandSignature));  // TODO: test deferred per-execute-indirect-dump
}
