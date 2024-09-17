#pragma once

#include <d3d12/common/d3d12_wrap_common.h>

namespace gfxshim
{
    class ID3D12CommandListWrapper : public ID3D12DeviceChildWrapper
    {
    private:
        inline static std::unordered_map<IUnknown *, ID3D12CommandListWrapper *> m_command_list_wrapper_map;
        inline static std::mutex m_command_list_wrapper_lock;

    public:
        ID3D12CommandListWrapper(REFIID riid, IUnknown *object);

        ~ID3D12CommandListWrapper() override;

        virtual D3D12_COMMAND_LIST_TYPE STDMETHODCALLTYPE GetType();
    };

    class ID3D12GraphicsCommandListWrapper : public ID3D12CommandListWrapper
    {
    public:
        ID3D12GraphicsCommandListWrapper(REFIID riid, IUnknown *object);

        ~ID3D12GraphicsCommandListWrapper() override;

        virtual HRESULT STDMETHODCALLTYPE Close();

        virtual HRESULT STDMETHODCALLTYPE Reset(
                ID3D12CommandAllocator* pAllocator,
                ID3D12PipelineState* pInitialState);

        virtual void STDMETHODCALLTYPE ClearState(
                ID3D12PipelineState* pPipelineState);

        virtual void STDMETHODCALLTYPE DrawInstanced(
                UINT VertexCountPerInstance,
                UINT InstanceCount,
                UINT StartVertexLocation,
                UINT StartInstanceLocation);

        virtual void STDMETHODCALLTYPE DrawIndexedInstanced(
                UINT IndexCountPerInstance,
                UINT InstanceCount,
                UINT StartIndexLocation,
                INT BaseVertexLocation,
                UINT StartInstanceLocation);

        virtual void STDMETHODCALLTYPE Dispatch(
                UINT ThreadGroupCountX,
                UINT ThreadGroupCountY,
                UINT ThreadGroupCountZ);

        virtual void STDMETHODCALLTYPE CopyBufferRegion(
                ID3D12Resource* pDstBuffer,
                UINT64 DstOffset,
                ID3D12Resource* pSrcBuffer,
                UINT64 SrcOffset,
                UINT64 NumBytes);

        virtual void STDMETHODCALLTYPE CopyTextureRegion(
                const D3D12_TEXTURE_COPY_LOCATION* pDst,
                UINT DstX,
                UINT DstY,
                UINT DstZ,
                const D3D12_TEXTURE_COPY_LOCATION* pSrc,
                const D3D12_BOX* pSrcBox);

        virtual void STDMETHODCALLTYPE CopyResource(
                ID3D12Resource* pDstResource,
                ID3D12Resource* pSrcResource);

        virtual void STDMETHODCALLTYPE CopyTiles(
                ID3D12Resource* pTiledResource,
                const D3D12_TILED_RESOURCE_COORDINATE* pTileRegionStartCoordinate,
                const D3D12_TILE_REGION_SIZE* pTileRegionSize,
                ID3D12Resource* pBuffer,
                UINT64 BufferStartOffsetInBytes,
                D3D12_TILE_COPY_FLAGS Flags);

        virtual void STDMETHODCALLTYPE ResolveSubresource(
                ID3D12Resource* pDstResource,
                UINT DstSubresource,
                ID3D12Resource* pSrcResource,
                UINT SrcSubresource,
                DXGI_FORMAT Format);

        virtual void STDMETHODCALLTYPE IASetPrimitiveTopology(
                D3D12_PRIMITIVE_TOPOLOGY PrimitiveTopology);

        virtual void STDMETHODCALLTYPE RSSetViewports(
                UINT NumViewports,
                const D3D12_VIEWPORT* pViewports);

        virtual void STDMETHODCALLTYPE RSSetScissorRects(
                UINT NumRects,
                const D3D12_RECT* pRects);

        virtual void STDMETHODCALLTYPE OMSetBlendFactor(
                const FLOAT BlendFactor [4]);

        virtual void STDMETHODCALLTYPE OMSetStencilRef(
                UINT StencilRef);

        virtual void STDMETHODCALLTYPE SetPipelineState(
                ID3D12PipelineState* pPipelineState);

        virtual void STDMETHODCALLTYPE ResourceBarrier(
                UINT NumBarriers,
                const D3D12_RESOURCE_BARRIER* pBarriers);

        virtual void STDMETHODCALLTYPE ExecuteBundle(
                ID3D12GraphicsCommandList* pCommandList);

        virtual void STDMETHODCALLTYPE SetDescriptorHeaps(
                UINT NumDescriptorHeaps,
                ID3D12DescriptorHeap* const* ppDescriptorHeaps);

        virtual void STDMETHODCALLTYPE SetComputeRootSignature(
                ID3D12RootSignature* pRootSignature);

        virtual void STDMETHODCALLTYPE SetGraphicsRootSignature(
                ID3D12RootSignature* pRootSignature);

        virtual void STDMETHODCALLTYPE SetComputeRootDescriptorTable(
                UINT RootParameterIndex,
                D3D12_GPU_DESCRIPTOR_HANDLE BaseDescriptor);

        virtual void STDMETHODCALLTYPE SetGraphicsRootDescriptorTable(
                UINT RootParameterIndex,
                D3D12_GPU_DESCRIPTOR_HANDLE BaseDescriptor);

        virtual void STDMETHODCALLTYPE SetComputeRoot32BitConstant(
                UINT RootParameterIndex,
                UINT SrcData,
                UINT DestOffsetIn32BitValues);

        virtual void STDMETHODCALLTYPE SetGraphicsRoot32BitConstant(
                UINT RootParameterIndex,
                UINT SrcData,
                UINT DestOffsetIn32BitValues);

        virtual void STDMETHODCALLTYPE SetComputeRoot32BitConstants(
                UINT RootParameterIndex,
                UINT Num32BitValuesToSet,
                const void* pSrcData,
                UINT DestOffsetIn32BitValues);

        virtual void STDMETHODCALLTYPE SetGraphicsRoot32BitConstants(
                UINT RootParameterIndex,
                UINT Num32BitValuesToSet,
                const void* pSrcData,
                UINT DestOffsetIn32BitValues);

        virtual void STDMETHODCALLTYPE SetComputeRootConstantBufferView(
                UINT RootParameterIndex,
                D3D12_GPU_VIRTUAL_ADDRESS BufferLocation);

        virtual void STDMETHODCALLTYPE SetGraphicsRootConstantBufferView(
                UINT RootParameterIndex,
                D3D12_GPU_VIRTUAL_ADDRESS BufferLocation);

        virtual void STDMETHODCALLTYPE SetComputeRootShaderResourceView(
                UINT RootParameterIndex,
                D3D12_GPU_VIRTUAL_ADDRESS BufferLocation);

        virtual void STDMETHODCALLTYPE SetGraphicsRootShaderResourceView(
                UINT RootParameterIndex,
                D3D12_GPU_VIRTUAL_ADDRESS BufferLocation);

        virtual void STDMETHODCALLTYPE SetComputeRootUnorderedAccessView(
                UINT RootParameterIndex,
                D3D12_GPU_VIRTUAL_ADDRESS BufferLocation);

        virtual void STDMETHODCALLTYPE SetGraphicsRootUnorderedAccessView(
                UINT RootParameterIndex,
                D3D12_GPU_VIRTUAL_ADDRESS BufferLocation);

        virtual void STDMETHODCALLTYPE IASetIndexBuffer(
                const D3D12_INDEX_BUFFER_VIEW* pView);

        virtual void STDMETHODCALLTYPE IASetVertexBuffers(
                UINT StartSlot,
                UINT NumViews,
                const D3D12_VERTEX_BUFFER_VIEW* pViews);

        virtual void STDMETHODCALLTYPE SOSetTargets(
                UINT StartSlot,
                UINT NumViews,
                const D3D12_STREAM_OUTPUT_BUFFER_VIEW* pViews);

        virtual void STDMETHODCALLTYPE OMSetRenderTargets(
                UINT NumRenderTargetDescriptors,
                const D3D12_CPU_DESCRIPTOR_HANDLE* pRenderTargetDescriptors,
                BOOL RTsSingleHandleToDescriptorRange,
                const D3D12_CPU_DESCRIPTOR_HANDLE* pDepthStencilDescriptor);

        virtual void STDMETHODCALLTYPE ClearDepthStencilView(
                D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView,
                D3D12_CLEAR_FLAGS ClearFlags,
                FLOAT Depth,
                UINT8 Stencil,
                UINT NumRects,
                const D3D12_RECT* pRects);

        virtual void STDMETHODCALLTYPE ClearRenderTargetView(
                D3D12_CPU_DESCRIPTOR_HANDLE RenderTargetView,
                const FLOAT ColorRGBA [4],
                UINT NumRects,
                const D3D12_RECT* pRects);

        virtual void STDMETHODCALLTYPE ClearUnorderedAccessViewUint(
                D3D12_GPU_DESCRIPTOR_HANDLE ViewGPUHandleInCurrentHeap,
                D3D12_CPU_DESCRIPTOR_HANDLE ViewCPUHandle,
                ID3D12Resource* pResource,
                const UINT Values [4],
                UINT NumRects,
                const D3D12_RECT* pRects);

        virtual void STDMETHODCALLTYPE ClearUnorderedAccessViewFloat(
                D3D12_GPU_DESCRIPTOR_HANDLE ViewGPUHandleInCurrentHeap,
                D3D12_CPU_DESCRIPTOR_HANDLE ViewCPUHandle,
                ID3D12Resource* pResource,
                const FLOAT Values [4],
                UINT NumRects,
                const D3D12_RECT* pRects);

        virtual void STDMETHODCALLTYPE DiscardResource(
                ID3D12Resource* pResource,
                const D3D12_DISCARD_REGION* pRegion);

        virtual void STDMETHODCALLTYPE BeginQuery(
                ID3D12QueryHeap* pQueryHeap,
                D3D12_QUERY_TYPE Type,
                UINT Index);

        virtual void STDMETHODCALLTYPE EndQuery(
                ID3D12QueryHeap* pQueryHeap,
                D3D12_QUERY_TYPE Type,
                UINT Index);

        virtual void STDMETHODCALLTYPE ResolveQueryData(
                ID3D12QueryHeap* pQueryHeap,
                D3D12_QUERY_TYPE Type,
                UINT StartIndex,
                UINT NumQueries,
                ID3D12Resource* pDestinationBuffer,
                UINT64 AlignedDestinationBufferOffset);

        virtual void STDMETHODCALLTYPE SetPredication(
                ID3D12Resource* pBuffer,
                UINT64 AlignedBufferOffset,
                D3D12_PREDICATION_OP Operation);

        virtual void STDMETHODCALLTYPE SetMarker(
                UINT Metadata,
                const void* pData,
                UINT Size);

        virtual void STDMETHODCALLTYPE BeginEvent(
                UINT Metadata,
                const void* pData,
                UINT Size);

        virtual void STDMETHODCALLTYPE EndEvent();

        virtual void STDMETHODCALLTYPE ExecuteIndirect(
                ID3D12CommandSignature* pCommandSignature,
                UINT MaxCommandCount,
                ID3D12Resource* pArgumentBuffer,
                UINT64 ArgumentBufferOffset,
                ID3D12Resource* pCountBuffer,
                UINT64 CountBufferOffset);
    };
}

class WrappedID3D12Device;

class WrappedID3D12GraphicsCommandList;

class WrappedID3D12CommandAllocator;

class WrappedID3D12DebugCommandList : public ID3D12DebugCommandList2
{
private:
    ID3D12DebugCommandList *m_pDebugList      = nullptr;
    ID3D12DebugCommandList1 *m_pDebugList1    = nullptr;
    ID3D12DebugCommandList2 *m_pDebugList2    = nullptr;

public:
    explicit WrappedID3D12DebugCommandList(ID3D12DebugCommandList *real_command_list);

    ~WrappedID3D12DebugCommandList();

    // Implement IUnknown
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) final;

    ULONG STDMETHODCALLTYPE AddRef() final;

    ULONG STDMETHODCALLTYPE Release() final;

    // Implement ID3D12DebugCommandList
    BOOL STDMETHODCALLTYPE AssertResourceState(ID3D12Resource *pResource, UINT Subresource, UINT State) final;

    HRESULT STDMETHODCALLTYPE SetFeatureMask(D3D12_DEBUG_FEATURE Mask) final;

    D3D12_DEBUG_FEATURE STDMETHODCALLTYPE GetFeatureMask() final;

    // Implement ID3D12DebugCommandList1 / ID3D12DebugCommandList2
    HRESULT STDMETHODCALLTYPE SetDebugParameter(D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
                                                const void *pData, UINT DataSize) final;

    HRESULT STDMETHODCALLTYPE GetDebugParameter(D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
                                                void *pData, UINT DataSize) final;
};

class WrappedID3D12GraphicsCommandList final : public ID3D12GraphicsCommandList10
{
private:
    ID3D12GraphicsCommandList   *m_pList   = nullptr;
    ID3D12GraphicsCommandList1  *m_pList1  = nullptr;
    ID3D12GraphicsCommandList2  *m_pList2  = nullptr;
    ID3D12GraphicsCommandList3  *m_pList3  = nullptr;
    ID3D12GraphicsCommandList4  *m_pList4  = nullptr;
    ID3D12GraphicsCommandList5  *m_pList5  = nullptr;
    ID3D12GraphicsCommandList6  *m_pList6  = nullptr;
    ID3D12GraphicsCommandList7  *m_pList7  = nullptr;
    ID3D12GraphicsCommandList8  *m_pList8  = nullptr;
    ID3D12GraphicsCommandList9  *m_pList9  = nullptr;
    ID3D12GraphicsCommandList10 *m_pList10 = nullptr;

    WrappedID3D12CommandAllocator *m_wrapped_command_allocator = nullptr;
    WrappedID3D12Device *m_wrapped_device = nullptr;

public:
    WrappedID3D12GraphicsCommandList(ID3D12GraphicsCommandList *real_command_list, WrappedID3D12Device *wrapped_device, WrappedID3D12CommandAllocator *wrapped_command_allocator);

    ~WrappedID3D12GraphicsCommandList();

    [[nodiscard]] ID3D12GraphicsCommandList *GetReal() const;

public:
    // Implement IUnknown
    ULONG STDMETHODCALLTYPE AddRef() final;
    
    ULONG STDMETHODCALLTYPE Release() final;

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) final;

    // Implement ID3D12Object
    HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID guid, UINT *pDataSize, void *pData) final;

    HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID guid, UINT DataSize, const void *pData) final;

    HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID guid, const IUnknown *pData) final;

    HRESULT STDMETHODCALLTYPE SetName(LPCWSTR Name) final;

    // Implement ID3D12DeviceChild
    HRESULT STDMETHODCALLTYPE GetDevice(REFIID riid, _COM_Outptr_opt_ void **ppvDevice) final;

    // Implement ID3D12CommandList
    D3D12_COMMAND_LIST_TYPE STDMETHODCALLTYPE GetType() final;

    // Implement ID3D12GraphicsCommandList
    HRESULT STDMETHODCALLTYPE Close() final;

    HRESULT STDMETHODCALLTYPE Reset(ID3D12CommandAllocator *pAllocator, ID3D12PipelineState *pInitialState) final;

    void STDMETHODCALLTYPE ClearState(ID3D12PipelineState *pPipelineState) final;

    void STDMETHODCALLTYPE DrawInstanced(UINT VertexCountPerInstance, UINT InstanceCount,
                                UINT StartVertexLocation, UINT StartInstanceLocation) final;

    void STDMETHODCALLTYPE DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount,
                                        UINT StartIndexLocation, INT BaseVertexLocation,
                                        UINT StartInstanceLocation) final;

    void STDMETHODCALLTYPE Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY,
                            UINT ThreadGroupCountZ) final;

    void STDMETHODCALLTYPE CopyBufferRegion(ID3D12Resource *pDstBuffer, UINT64 DstOffset,
                                    ID3D12Resource *pSrcBuffer, UINT64 SrcOffset,
                                    UINT64 NumBytes) final;

    void STDMETHODCALLTYPE CopyTextureRegion(const D3D12_TEXTURE_COPY_LOCATION *pDst, UINT DstX,
                                    UINT DstY, UINT DstZ,
                                    const D3D12_TEXTURE_COPY_LOCATION *pSrc,
                                    const D3D12_BOX *pSrcBox) final;

    void STDMETHODCALLTYPE CopyResource(ID3D12Resource *pDstResource, ID3D12Resource *pSrcResource) final;

    void STDMETHODCALLTYPE CopyTiles(ID3D12Resource *pTiledResource,
                            const D3D12_TILED_RESOURCE_COORDINATE *pTileRegionStartCoordinate,
                            const D3D12_TILE_REGION_SIZE *pTileRegionSize,
                            ID3D12Resource *pBuffer, UINT64 BufferStartOffsetInBytes,
                            D3D12_TILE_COPY_FLAGS Flags) final;

    void STDMETHODCALLTYPE ResolveSubresource(ID3D12Resource *pDstResource, UINT DstSubresource,
                                    ID3D12Resource *pSrcResource, UINT SrcSubresource,
                                    DXGI_FORMAT Format) final;

    void STDMETHODCALLTYPE IASetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY PrimitiveTopology) final;

    void STDMETHODCALLTYPE RSSetViewports(UINT NumViewports, const D3D12_VIEWPORT *pViewports) final;

    void STDMETHODCALLTYPE RSSetScissorRects(UINT NumRects, const D3D12_RECT *pRects) final;

    void STDMETHODCALLTYPE OMSetBlendFactor(const FLOAT BlendFactor[4]) final;

    void STDMETHODCALLTYPE OMSetStencilRef(UINT StencilRef) final;

    void STDMETHODCALLTYPE SetPipelineState(ID3D12PipelineState *pPipelineState) final;

    void STDMETHODCALLTYPE ResourceBarrier(UINT NumBarriers, const D3D12_RESOURCE_BARRIER *pBarriers) final;

    void STDMETHODCALLTYPE ExecuteBundle(ID3D12GraphicsCommandList *pCommandList) final;

    void STDMETHODCALLTYPE SetDescriptorHeaps(UINT NumDescriptorHeaps,
                                    ID3D12DescriptorHeap *const *ppDescriptorHeaps) final;

    void STDMETHODCALLTYPE SetComputeRootSignature(ID3D12RootSignature *pRootSignature) final;

    void STDMETHODCALLTYPE SetGraphicsRootSignature(ID3D12RootSignature *pRootSignature) final;

    void STDMETHODCALLTYPE SetComputeRootDescriptorTable(UINT RootParameterIndex,
                                                D3D12_GPU_DESCRIPTOR_HANDLE BaseDescriptor) final;

    void STDMETHODCALLTYPE SetGraphicsRootDescriptorTable(UINT RootParameterIndex,
                                                D3D12_GPU_DESCRIPTOR_HANDLE BaseDescriptor) final;

    void STDMETHODCALLTYPE SetComputeRoot32BitConstant(UINT RootParameterIndex, UINT SrcData,
                                            UINT DestOffsetIn32BitValues) final;

    void STDMETHODCALLTYPE SetGraphicsRoot32BitConstant(UINT RootParameterIndex, UINT SrcData,
                                            UINT DestOffsetIn32BitValues) final;

    void STDMETHODCALLTYPE SetComputeRoot32BitConstants(UINT RootParameterIndex,
                                                UINT Num32BitValuesToSet,
                                                const void *pSrcData,
                                                UINT DestOffsetIn32BitValues) final;

    void STDMETHODCALLTYPE SetGraphicsRoot32BitConstants(UINT RootParameterIndex,
                                                UINT Num32BitValuesToSet,
                                                const void *pSrcData,
                                                UINT DestOffsetIn32BitValues) final;

    void STDMETHODCALLTYPE SetComputeRootConstantBufferView(UINT RootParameterIndex,
                                                    D3D12_GPU_VIRTUAL_ADDRESS BufferLocation) final;

    void STDMETHODCALLTYPE SetGraphicsRootConstantBufferView(UINT RootParameterIndex,
                                                    D3D12_GPU_VIRTUAL_ADDRESS BufferLocation) final;

    void STDMETHODCALLTYPE SetComputeRootShaderResourceView(UINT RootParameterIndex,
                                                    D3D12_GPU_VIRTUAL_ADDRESS BufferLocation) final;

    void STDMETHODCALLTYPE SetGraphicsRootShaderResourceView(UINT RootParameterIndex,
                                                    D3D12_GPU_VIRTUAL_ADDRESS BufferLocation) final;

    void STDMETHODCALLTYPE SetComputeRootUnorderedAccessView(UINT RootParameterIndex,
                                                    D3D12_GPU_VIRTUAL_ADDRESS BufferLocation) final;

    void STDMETHODCALLTYPE SetGraphicsRootUnorderedAccessView(UINT RootParameterIndex,
                                                    D3D12_GPU_VIRTUAL_ADDRESS BufferLocation) final;

    void STDMETHODCALLTYPE IASetIndexBuffer(const D3D12_INDEX_BUFFER_VIEW *pView) final;

    void STDMETHODCALLTYPE IASetVertexBuffers(UINT StartSlot, UINT NumViews,
                                    const D3D12_VERTEX_BUFFER_VIEW *pViews) final;

    void STDMETHODCALLTYPE SOSetTargets(UINT StartSlot, UINT NumViews,
                                const D3D12_STREAM_OUTPUT_BUFFER_VIEW *pViews) final;

    void STDMETHODCALLTYPE OMSetRenderTargets(UINT NumRenderTargetDescriptors,
                                            const D3D12_CPU_DESCRIPTOR_HANDLE *
                                            pRenderTargetDescriptors,
                                            BOOL RTsSingleHandleToDescriptorRange,
                                            const D3D12_CPU_DESCRIPTOR_HANDLE *
                                            pDepthStencilDescriptor) final;

    void STDMETHODCALLTYPE ClearDepthStencilView(D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView,
                                        D3D12_CLEAR_FLAGS ClearFlags, FLOAT Depth,
                                        UINT8 Stencil, UINT NumRects,
                                        const D3D12_RECT *pRects) final;

    void STDMETHODCALLTYPE ClearRenderTargetView(D3D12_CPU_DESCRIPTOR_HANDLE RenderTargetView,
                                        const FLOAT ColorRGBA[4], UINT NumRects,
                                        const D3D12_RECT *pRects) final;

    void STDMETHODCALLTYPE ClearUnorderedAccessViewUint(
            D3D12_GPU_DESCRIPTOR_HANDLE ViewGPUHandleInCurrentHeap,
            D3D12_CPU_DESCRIPTOR_HANDLE ViewCPUHandle, ID3D12Resource *pResource, const UINT Values[4],
            UINT NumRects, const D3D12_RECT *pRects) final;

    void STDMETHODCALLTYPE ClearUnorderedAccessViewFloat(
            D3D12_GPU_DESCRIPTOR_HANDLE ViewGPUHandleInCurrentHeap,
            D3D12_CPU_DESCRIPTOR_HANDLE ViewCPUHandle, ID3D12Resource *pResource, const FLOAT Values[4],
            UINT NumRects, const D3D12_RECT *pRects) final;

    void STDMETHODCALLTYPE DiscardResource(ID3D12Resource *pResource,
                                const D3D12_DISCARD_REGION *pRegion) final;

    void STDMETHODCALLTYPE BeginQuery(ID3D12QueryHeap *pQueryHeap, D3D12_QUERY_TYPE Type, UINT Index) final;

    void STDMETHODCALLTYPE EndQuery(ID3D12QueryHeap *pQueryHeap, D3D12_QUERY_TYPE Type, UINT Index) final;

    void STDMETHODCALLTYPE ResolveQueryData(ID3D12QueryHeap *pQueryHeap, D3D12_QUERY_TYPE Type,
                                    UINT StartIndex, UINT NumQueries,
                                    ID3D12Resource *pDestinationBuffer,
                                    UINT64 AlignedDestinationBufferOffset) final;

    void STDMETHODCALLTYPE SetPredication(ID3D12Resource *pBuffer, UINT64 AlignedBufferOffset,
                                D3D12_PREDICATION_OP Operation) final;

    void STDMETHODCALLTYPE SetMarker(UINT Metadata, const void *pData, UINT Size) final;

    void STDMETHODCALLTYPE BeginEvent(UINT Metadata, const void *pData, UINT Size) final;

    void STDMETHODCALLTYPE EndEvent() final;

    void STDMETHODCALLTYPE ExecuteIndirect(ID3D12CommandSignature *pCommandSignature,
                                UINT MaxCommandCount, ID3D12Resource *pArgumentBuffer,
                                UINT64 ArgumentBufferOffset, ID3D12Resource *pCountBuffer,
                                UINT64 CountBufferOffset) final;

    // Implement ID3D12GraphicsCommandList1
    void STDMETHODCALLTYPE AtomicCopyBufferUINT(ID3D12Resource *pDstBuffer, UINT64 DstOffset,
                                        ID3D12Resource *pSrcBuffer, UINT64 SrcOffset,
                                        UINT Dependencies,
                                        ID3D12Resource *const *ppDependentResources,
                                        const D3D12_SUBRESOURCE_RANGE_UINT64 *
                                        pDependentSubresourceRanges) final;

    void STDMETHODCALLTYPE AtomicCopyBufferUINT64(ID3D12Resource *pDstBuffer, UINT64 DstOffset,
                                        ID3D12Resource *pSrcBuffer, UINT64 SrcOffset,
                                        UINT Dependencies,
                                        ID3D12Resource *const *ppDependentResources,
                                        const D3D12_SUBRESOURCE_RANGE_UINT64 *
                                        pDependentSubresourceRanges) final;

    void STDMETHODCALLTYPE OMSetDepthBounds(FLOAT Min, FLOAT Max) final;

    void STDMETHODCALLTYPE SetSamplePositions(UINT NumSamplesPerPixel, UINT NumPixels,
                                    D3D12_SAMPLE_POSITION *pSamplePositions) final;

    void STDMETHODCALLTYPE ResolveSubresourceRegion(ID3D12Resource *pDstResource, UINT DstSubresource,
                                            UINT DstX, UINT DstY,
                                            ID3D12Resource *pSrcResource, UINT SrcSubresource,
                                            D3D12_RECT *pSrcRect, DXGI_FORMAT Format,
                                            D3D12_RESOLVE_MODE ResolveMode) final;

    void STDMETHODCALLTYPE SetViewInstanceMask(UINT Mask) final;

    // Implement ID3D12GraphicsCommandList2
    void STDMETHODCALLTYPE WriteBufferImmediate(UINT Count,
                                        const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER *pParams,
                                        const D3D12_WRITEBUFFERIMMEDIATE_MODE *pModes) final;

    // Implement ID3D12GraphicsCommandList3
    void STDMETHODCALLTYPE SetProtectedResourceSession(ID3D12ProtectedResourceSession *pProtectedResourceSession) final;

    // Implement ID3D12GraphicsCommandList4
    void STDMETHODCALLTYPE BeginRenderPass(UINT NumRenderTargets,
                                const D3D12_RENDER_PASS_RENDER_TARGET_DESC *pRenderTargets,
                                const D3D12_RENDER_PASS_DEPTH_STENCIL_DESC *pDepthStencil,
                                D3D12_RENDER_PASS_FLAGS Flags) final;

    void STDMETHODCALLTYPE EndRenderPass() final;

    void STDMETHODCALLTYPE InitializeMetaCommand(ID3D12MetaCommand *pMetaCommand,
                                        const void *pInitializationParametersData,
                                        SIZE_T InitializationParametersDataSizeInBytes) final;

    void STDMETHODCALLTYPE ExecuteMetaCommand(ID3D12MetaCommand *pMetaCommand,
                                    const void *pExecutionParametersData,
                                    SIZE_T ExecutionParametersDataSizeInBytes) final;

    void STDMETHODCALLTYPE BuildRaytracingAccelerationStructure(
            const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC *pDesc, UINT NumPostbuildInfoDescs,
            const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC *pPostbuildInfoDescs) final;

    void STDMETHODCALLTYPE EmitRaytracingAccelerationStructurePostbuildInfo(
            const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC *pDesc,
            UINT NumSourceAccelerationStructures,
            const D3D12_GPU_VIRTUAL_ADDRESS *pSourceAccelerationStructureData) final;

    void STDMETHODCALLTYPE CopyRaytracingAccelerationStructure(
            D3D12_GPU_VIRTUAL_ADDRESS DestAccelerationStructureData,
            D3D12_GPU_VIRTUAL_ADDRESS SourceAccelerationStructureData,
            D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE Mode) final;

    void STDMETHODCALLTYPE SetPipelineState1(ID3D12StateObject *pStateObject) final;

    void STDMETHODCALLTYPE DispatchRays(const D3D12_DISPATCH_RAYS_DESC *pDesc) final;

    // Implement ID3D12GraphicsCommandList5
    void STDMETHODCALLTYPE RSSetShadingRate(D3D12_SHADING_RATE baseShadingRate,
                                    const D3D12_SHADING_RATE_COMBINER *combiners) final;

    void STDMETHODCALLTYPE RSSetShadingRateImage(ID3D12Resource *shadingRateImage) final;

    // Implement ID3D12GraphicsCommandList6
    void STDMETHODCALLTYPE DispatchMesh(UINT ThreadGroupCountX, UINT ThreadGroupCountY,
                                UINT ThreadGroupCountZ) final;

    // Implement ID3D12GraphicsCommandList7
    void STDMETHODCALLTYPE Barrier(UINT32 NumBarrierGroups,
                        const D3D12_BARRIER_GROUP *pBarrierGroups) final;

    // Implement ID3D12GraphicsCommandList8
    void STDMETHODCALLTYPE OMSetFrontAndBackStencilRef(
            _In_  UINT FrontStencilRef,
            _In_  UINT BackStencilRef) final;

    // Implement ID3D12GraphicsCommandList9
    void STDMETHODCALLTYPE RSSetDepthBias(
            _In_  FLOAT DepthBias,
            _In_  FLOAT DepthBiasClamp,
            _In_  FLOAT SlopeScaledDepthBias) final;

    void STDMETHODCALLTYPE IASetIndexBufferStripCutValue(
            _In_  D3D12_INDEX_BUFFER_STRIP_CUT_VALUE IBStripCutValue) final;

    // Implement ID3D12GraphicsCommandList10
    void STDMETHODCALLTYPE SetProgram(
            _In_  const D3D12_SET_PROGRAM_DESC *pDesc) final;

    void STDMETHODCALLTYPE DispatchGraph(
            _In_  const D3D12_DISPATCH_GRAPH_DESC *pDesc) final;
};