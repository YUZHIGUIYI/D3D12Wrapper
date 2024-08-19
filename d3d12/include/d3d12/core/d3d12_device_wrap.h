#pragma once

#include <d3d12/common/d3d12_wrap_common.h>
#include <unordered_map>
#include <mutex>

namespace gfxshim
{
    class ID3D12DeviceWrapper : public ID3D12ObjectWrapper
    {
    private:
        static std::unordered_map<IUnknown *, ID3D12DeviceWrapper *> m_device_wrapper_map;
        static std::mutex m_device_wrapper_lock;

    public:
        ID3D12DeviceWrapper(REFIID riid, IUnknown *object);

        ~ID3D12DeviceWrapper() override;

        virtual UINT STDMETHODCALLTYPE GetNodeCount();

        virtual HRESULT STDMETHODCALLTYPE CreateCommandQueue(
                const D3D12_COMMAND_QUEUE_DESC* pDesc,
                REFIID riid,
                void** ppCommandQueue);

        virtual HRESULT STDMETHODCALLTYPE CreateCommandAllocator(
                D3D12_COMMAND_LIST_TYPE type,
                REFIID riid,
                void** ppCommandAllocator);

        virtual HRESULT STDMETHODCALLTYPE CreateGraphicsPipelineState(
                const D3D12_GRAPHICS_PIPELINE_STATE_DESC* pDesc,
                REFIID riid,
                void** ppPipelineState);

        virtual HRESULT STDMETHODCALLTYPE CreateComputePipelineState(
                const D3D12_COMPUTE_PIPELINE_STATE_DESC* pDesc,
                REFIID riid,
                void** ppPipelineState);

        virtual HRESULT STDMETHODCALLTYPE CreateCommandList(
                UINT nodeMask,
                D3D12_COMMAND_LIST_TYPE type,
                ID3D12CommandAllocator* pCommandAllocator,
                ID3D12PipelineState* pInitialState,
                REFIID riid,
                void** ppCommandList);

        virtual HRESULT STDMETHODCALLTYPE CheckFeatureSupport(
                D3D12_FEATURE Feature,
                void* pFeatureSupportData,
                UINT FeatureSupportDataSize);

        virtual HRESULT STDMETHODCALLTYPE CreateDescriptorHeap(
                const D3D12_DESCRIPTOR_HEAP_DESC* pDescriptorHeapDesc,
                REFIID riid,
                void** ppvHeap);

        virtual UINT STDMETHODCALLTYPE GetDescriptorHandleIncrementSize(
                D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapType);

        virtual HRESULT STDMETHODCALLTYPE CreateRootSignature(
                UINT nodeMask,
                const void* pBlobWithRootSignature,
                SIZE_T blobLengthInBytes,
                REFIID riid,
                void** ppvRootSignature);

        virtual void STDMETHODCALLTYPE CreateConstantBufferView(
                const D3D12_CONSTANT_BUFFER_VIEW_DESC* pDesc,
                D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor);

        virtual void STDMETHODCALLTYPE CreateShaderResourceView(
                ID3D12Resource* pResource,
                const D3D12_SHADER_RESOURCE_VIEW_DESC* pDesc,
                D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor);

        virtual void STDMETHODCALLTYPE CreateUnorderedAccessView(
                ID3D12Resource* pResource,
                ID3D12Resource* pCounterResource,
                const D3D12_UNORDERED_ACCESS_VIEW_DESC* pDesc,
                D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor);

        virtual void STDMETHODCALLTYPE CreateRenderTargetView(
                ID3D12Resource* pResource,
                const D3D12_RENDER_TARGET_VIEW_DESC* pDesc,
                D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor);

        virtual void STDMETHODCALLTYPE CreateDepthStencilView(
                ID3D12Resource* pResource,
                const D3D12_DEPTH_STENCIL_VIEW_DESC* pDesc,
                D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor);

        virtual void STDMETHODCALLTYPE CreateSampler(
                const D3D12_SAMPLER_DESC* pDesc,
                D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor);

        virtual void STDMETHODCALLTYPE CopyDescriptors(
                UINT NumDestDescriptorRanges,
                const D3D12_CPU_DESCRIPTOR_HANDLE* pDestDescriptorRangeStarts,
                const UINT* pDestDescriptorRangeSizes,
                UINT NumSrcDescriptorRanges,
                const D3D12_CPU_DESCRIPTOR_HANDLE* pSrcDescriptorRangeStarts,
                const UINT* pSrcDescriptorRangeSizes,
                D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapsType);

        virtual void STDMETHODCALLTYPE CopyDescriptorsSimple(
                UINT NumDescriptors,
                D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptorRangeStart,
                D3D12_CPU_DESCRIPTOR_HANDLE SrcDescriptorRangeStart,
                D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapsType);

        virtual D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE GetResourceAllocationInfo(
                UINT visibleMask,
                UINT numResourceDescs,
                const D3D12_RESOURCE_DESC* pResourceDescs);

        virtual D3D12_HEAP_PROPERTIES STDMETHODCALLTYPE GetCustomHeapProperties(
                UINT nodeMask,
                D3D12_HEAP_TYPE heapType);

        virtual HRESULT STDMETHODCALLTYPE CreateCommittedResource(
                const D3D12_HEAP_PROPERTIES* pHeapProperties,
                D3D12_HEAP_FLAGS HeapFlags,
                const D3D12_RESOURCE_DESC* pDesc,
                D3D12_RESOURCE_STATES InitialResourceState,
                const D3D12_CLEAR_VALUE* pOptimizedClearValue,
                REFIID riidResource,
                void** ppvResource);

        virtual HRESULT STDMETHODCALLTYPE CreateHeap(
                const D3D12_HEAP_DESC* pDesc,
                REFIID riid,
                void** ppvHeap);

        virtual HRESULT STDMETHODCALLTYPE CreatePlacedResource(
                ID3D12Heap* pHeap,
                UINT64 HeapOffset,
                const D3D12_RESOURCE_DESC* pDesc,
                D3D12_RESOURCE_STATES InitialState,
                const D3D12_CLEAR_VALUE* pOptimizedClearValue,
                REFIID riid,
                void** ppvResource);

        virtual HRESULT STDMETHODCALLTYPE CreateReservedResource(
                const D3D12_RESOURCE_DESC* pDesc,
                D3D12_RESOURCE_STATES InitialState,
                const D3D12_CLEAR_VALUE* pOptimizedClearValue,
                REFIID riid,
                void** ppvResource);

        virtual HRESULT STDMETHODCALLTYPE CreateSharedHandle(
                ID3D12DeviceChild* pObject,
                const SECURITY_ATTRIBUTES* pAttributes,
                DWORD Access,
                LPCWSTR Name,
                HANDLE* pHandle);

        virtual HRESULT STDMETHODCALLTYPE OpenSharedHandle(
                HANDLE NTHandle,
                REFIID riid,
                void** ppvObj);

        virtual HRESULT STDMETHODCALLTYPE OpenSharedHandleByName(
                LPCWSTR Name,
                DWORD Access,
                HANDLE* pNTHandle);

        virtual HRESULT STDMETHODCALLTYPE MakeResident(
                UINT NumObjects,
                ID3D12Pageable* const* ppObjects);

        virtual HRESULT STDMETHODCALLTYPE Evict(
                UINT NumObjects,
                ID3D12Pageable* const* ppObjects);

        virtual HRESULT STDMETHODCALLTYPE CreateFence(
                UINT64 InitialValue,
                D3D12_FENCE_FLAGS Flags,
                REFIID riid,
                void** ppFence);

        virtual HRESULT STDMETHODCALLTYPE GetDeviceRemovedReason();

        virtual void STDMETHODCALLTYPE GetCopyableFootprints(
                const D3D12_RESOURCE_DESC* pResourceDesc,
                UINT FirstSubresource,
                UINT NumSubresources,
                UINT64 BaseOffset,
                D3D12_PLACED_SUBRESOURCE_FOOTPRINT* pLayouts,
                UINT* pNumRows,
                UINT64* pRowSizeInBytes,
                UINT64* pTotalBytes);

        virtual HRESULT STDMETHODCALLTYPE CreateQueryHeap(
                const D3D12_QUERY_HEAP_DESC* pDesc,
                REFIID riid,
                void** ppvHeap);

        virtual HRESULT STDMETHODCALLTYPE SetStablePowerState(
                BOOL Enable);

        virtual HRESULT STDMETHODCALLTYPE CreateCommandSignature(
                const D3D12_COMMAND_SIGNATURE_DESC* pDesc,
                ID3D12RootSignature* pRootSignature,
                REFIID riid,
                void** ppvCommandSignature);

        virtual void STDMETHODCALLTYPE GetResourceTiling(
                ID3D12Resource* pTiledResource,
                UINT* pNumTilesForEntireResource,
                D3D12_PACKED_MIP_INFO* pPackedMipDesc,
                D3D12_TILE_SHAPE* pStandardTileShapeForNonPackedMips,
                UINT* pNumSubresourceTilings,
                UINT FirstSubresourceTilingToGet,
                D3D12_SUBRESOURCE_TILING* pSubresourceTilingsForNonPackedMips);

        virtual LUID STDMETHODCALLTYPE GetAdapterLuid();

        ULONG STDMETHODCALLTYPE Release() override;
    };
}

class WrappedID3D12Device : public ID3D12Device14
{
private:
    ID3D12Device   *m_pDevice   = nullptr;
    ID3D12Device1  *m_pDevice1  = nullptr;
    ID3D12Device2  *m_pDevice2  = nullptr;
    ID3D12Device3  *m_pDevice3  = nullptr;
    ID3D12Device4  *m_pDevice4  = nullptr;
    ID3D12Device5  *m_pDevice5  = nullptr;
    ID3D12Device6  *m_pDevice6  = nullptr;
    ID3D12Device7  *m_pDevice7  = nullptr;
    ID3D12Device8  *m_pDevice8  = nullptr;
    ID3D12Device9  *m_pDevice9  = nullptr;
    ID3D12Device10 *m_pDevice10 = nullptr;
    ID3D12Device11 *m_pDevice11 = nullptr;
    ID3D12Device12 *m_pDevice12 = nullptr;
    ID3D12Device13 *m_pDevice13 = nullptr;
    ID3D12Device14 *m_pDevice14 = nullptr;

public:
    explicit WrappedID3D12Device(ID3D12Device *real_device);

    ~WrappedID3D12Device();

public:
    // Helper for ID3D12DeviceChild implementation to use
    HRESULT GetDevice(REFIID riid, void **ppvDevice);

    // Implement IUnknown
    ULONG STDMETHODCALLTYPE AddRef() override;

    ULONG STDMETHODCALLTYPE Release() override;

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) override;

    // Implement ID3D12Object
    HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID guid, UINT *pDataSize, void *pData) override;

    HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID guid, UINT DataSize, const void *pData) override;

    HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID guid, const IUnknown *pData) override;

    HRESULT STDMETHODCALLTYPE SetName(LPCWSTR Name) override;

    // Implement ID3D12Device
    UINT STDMETHODCALLTYPE GetNodeCount() override;

    LUID STDMETHODCALLTYPE GetAdapterLuid() override;

    HRESULT STDMETHODCALLTYPE CreateCommandQueue(const D3D12_COMMAND_QUEUE_DESC *pDesc, const IID &riid, void **ppCommandQueue) override;

    HRESULT STDMETHODCALLTYPE CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE type, const IID &riid,
                                            void **ppCommandAllocator) override;

    HRESULT STDMETHODCALLTYPE CreateGraphicsPipelineState(const D3D12_GRAPHICS_PIPELINE_STATE_DESC *pDesc, const IID &riid, void **ppPipelineState) override;

    HRESULT STDMETHODCALLTYPE CreateComputePipelineState(const D3D12_COMPUTE_PIPELINE_STATE_DESC *pDesc, const IID &riid, void **ppPipelineState) override;

    HRESULT STDMETHODCALLTYPE CreateCommandList(UINT nodeMask, D3D12_COMMAND_LIST_TYPE type,
                                                ID3D12CommandAllocator *pCommandAllocator,
                                                ID3D12PipelineState *pInitialState, const IID &riid,
                                                void **ppCommandList) override;

    HRESULT STDMETHODCALLTYPE CheckFeatureSupport(D3D12_FEATURE Feature, void *pFeatureSupportData, UINT FeatureSupportDataSize) override;

    HRESULT STDMETHODCALLTYPE CreateDescriptorHeap(const D3D12_DESCRIPTOR_HEAP_DESC *pDescriptorHeapDesc, const IID &riid, void **ppvHeap) override;

    UINT STDMETHODCALLTYPE GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapType) override;

    HRESULT STDMETHODCALLTYPE CreateRootSignature(UINT nodeMask, const void *pBlobWithRootSignature,
                                                SIZE_T blobLengthInBytes, const IID &riid,
                                                void **ppvRootSignature) override;

    void STDMETHODCALLTYPE CreateConstantBufferView(const D3D12_CONSTANT_BUFFER_VIEW_DESC *pDesc, D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) override;

    void STDMETHODCALLTYPE CreateShaderResourceView(ID3D12Resource *pResource,
                                                    const D3D12_SHADER_RESOURCE_VIEW_DESC *pDesc,
                                                    D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) override;
    
    void STDMETHODCALLTYPE CreateUnorderedAccessView(ID3D12Resource *pResource,
                                                    ID3D12Resource *pCounterResource,
                                                    const D3D12_UNORDERED_ACCESS_VIEW_DESC *pDesc,
                                                    D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) override;

    void STDMETHODCALLTYPE CreateRenderTargetView(ID3D12Resource *pResource,
                                                const D3D12_RENDER_TARGET_VIEW_DESC *pDesc,
                                                D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) override;

    void STDMETHODCALLTYPE CreateDepthStencilView(ID3D12Resource *pResource,
                                                const D3D12_DEPTH_STENCIL_VIEW_DESC *pDesc,
                                                D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) override;

    void STDMETHODCALLTYPE CreateSampler(const D3D12_SAMPLER_DESC *pDesc, D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) override;

    void STDMETHODCALLTYPE CopyDescriptors(UINT NumDestDescriptorRanges,
                                            const D3D12_CPU_DESCRIPTOR_HANDLE *pDestDescriptorRangeStarts,
                                            const UINT *pDestDescriptorRangeSizes,
                                            UINT NumSrcDescriptorRanges,
                                            const D3D12_CPU_DESCRIPTOR_HANDLE *pSrcDescriptorRangeStarts,
                                            const UINT *pSrcDescriptorRangeSizes,
                                            D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapsType) override;

    void STDMETHODCALLTYPE CopyDescriptorsSimple(UINT NumDescriptors,
                                                D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptorRangeStart,
                                                D3D12_CPU_DESCRIPTOR_HANDLE SrcDescriptorRangeStart,
                                                D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapsType) override;

    D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE GetResourceAllocationInfo(UINT visibleMask, UINT numResourceDescs, const D3D12_RESOURCE_DESC *pResourceDescs) override;

    D3D12_HEAP_PROPERTIES STDMETHODCALLTYPE GetCustomHeapProperties(UINT nodeMask, D3D12_HEAP_TYPE heapType) override;

    HRESULT STDMETHODCALLTYPE CreateCommittedResource(const D3D12_HEAP_PROPERTIES *pHeapProperties,
                                                    D3D12_HEAP_FLAGS HeapFlags,
                                                    const D3D12_RESOURCE_DESC *pDesc,
                                                    D3D12_RESOURCE_STATES InitialResourceState,
                                                    const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                    const IID &riidResource, void **ppvResource) override;

    HRESULT STDMETHODCALLTYPE CreateHeap(const D3D12_HEAP_DESC *pDesc, const IID &riid, void **ppvHeap) override;

    HRESULT STDMETHODCALLTYPE CreatePlacedResource(ID3D12Heap *pHeap, UINT64 HeapOffset,
                                                    const D3D12_RESOURCE_DESC *pDesc,
                                                    D3D12_RESOURCE_STATES InitialState,
                                                    const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                    const IID &riid, void **ppvResource) override;

    HRESULT STDMETHODCALLTYPE CreateReservedResource(const D3D12_RESOURCE_DESC *pDesc,
                                                    D3D12_RESOURCE_STATES InitialState,
                                                    const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                    const IID &riid, void **ppvResource) override;

    HRESULT STDMETHODCALLTYPE CreateSharedHandle(ID3D12DeviceChild *pObject,
                                                const SECURITY_ATTRIBUTES *pAttributes, DWORD Access,
                                                LPCWSTR Name, HANDLE *pHandle) override;

    HRESULT STDMETHODCALLTYPE OpenSharedHandle(HANDLE NTHandle, const IID &riid, void **ppvObj) override;

    HRESULT STDMETHODCALLTYPE OpenSharedHandleByName(LPCWSTR Name, DWORD Access, HANDLE *pNTHandle) override;

    HRESULT STDMETHODCALLTYPE MakeResident(UINT NumObjects, ID3D12Pageable *const *ppObjects) override;

    HRESULT STDMETHODCALLTYPE Evict(UINT NumObjects, ID3D12Pageable *const *ppObjects) override;

    HRESULT STDMETHODCALLTYPE CreateFence(UINT64 InitialValue, D3D12_FENCE_FLAGS Flags,
                                        const IID &riid, void **ppFence) override;

    HRESULT STDMETHODCALLTYPE GetDeviceRemovedReason() override;

    void STDMETHODCALLTYPE GetCopyableFootprints(const D3D12_RESOURCE_DESC *pResourceDesc,
                                                UINT FirstSubresource, UINT NumSubresources,
                                                UINT64 BaseOffset,
                                                D3D12_PLACED_SUBRESOURCE_FOOTPRINT *pLayouts,
                                                UINT *pNumRows, UINT64 *pRowSizeInBytes,
                                                UINT64 *pTotalBytes) override;

    HRESULT STDMETHODCALLTYPE CreateQueryHeap(const D3D12_QUERY_HEAP_DESC *pDesc, const IID &riid,
                                                void **ppvHeap) override;

    HRESULT STDMETHODCALLTYPE SetStablePowerState(BOOL Enable) override;

    HRESULT STDMETHODCALLTYPE CreateCommandSignature(const D3D12_COMMAND_SIGNATURE_DESC *pDesc,
                                                    ID3D12RootSignature *pRootSignature,
                                                    const IID &riid, void **ppvCommandSignature) override;

    void STDMETHODCALLTYPE GetResourceTiling(ID3D12Resource *pTiledResource,
                                            UINT *pNumTilesForEntireResource,
                                            D3D12_PACKED_MIP_INFO *pPackedMipDesc,
                                            D3D12_TILE_SHAPE *pStandardTileShapeForNonPackedMips,
                                            UINT *pNumSubresourceTilings,
                                            UINT FirstSubresourceTilingToGet,
                                            D3D12_SUBRESOURCE_TILING *pSubresourceTilingsForNonPackedMips) override;

    // Implement ID3D12Device1
    HRESULT STDMETHODCALLTYPE CreatePipelineLibrary(const void *pLibraryBlob, SIZE_T BlobLength,
                                                    const IID &riid, void **ppPipelineLibrary) override;

    HRESULT STDMETHODCALLTYPE SetEventOnMultipleFenceCompletion(ID3D12Fence *const *ppFences, const UINT64 *pFenceValues, UINT NumFences,
                                                                D3D12_MULTIPLE_FENCE_WAIT_FLAGS Flags, HANDLE hEvent) override;

    HRESULT STDMETHODCALLTYPE SetResidencyPriority(UINT NumObjects, ID3D12Pageable *const *ppObjects,
                                                    const D3D12_RESIDENCY_PRIORITY *pPriorities) override;

    // Implement ID3D12Device2
    HRESULT STDMETHODCALLTYPE CreatePipelineState(const D3D12_PIPELINE_STATE_STREAM_DESC *pDesc,
                                                const IID &riid, void **ppPipelineState) override;

    // Implement ID3D12Device3
    HRESULT STDMETHODCALLTYPE OpenExistingHeapFromAddress(const void *pAddress, const IID &riid, void **ppvHeap) override;

    HRESULT STDMETHODCALLTYPE OpenExistingHeapFromFileMapping(HANDLE hFileMapping, const IID &riid, void **ppvHeap) override;

    HRESULT STDMETHODCALLTYPE EnqueueMakeResident(D3D12_RESIDENCY_FLAGS Flags, UINT NumObjects,
                                                ID3D12Pageable *const *ppObjects,
                                                ID3D12Fence *pFenceToSignal,
                                                UINT64 FenceValueToSignal) override;

    // Implement ID3D12Device4
    HRESULT STDMETHODCALLTYPE CreateCommandList1(UINT nodeMask, D3D12_COMMAND_LIST_TYPE type,
                                                D3D12_COMMAND_LIST_FLAGS flags, const IID &riid,
                                                void **ppCommandList) override;

    HRESULT STDMETHODCALLTYPE CreateProtectedResourceSession(_In_ const D3D12_PROTECTED_RESOURCE_SESSION_DESC *pDesc,
                                                            _In_ REFIID riid, _COM_Outptr_ void **ppSession) override;

    HRESULT STDMETHODCALLTYPE CreateCommittedResource1(const D3D12_HEAP_PROPERTIES *pHeapProperties,
                                                    D3D12_HEAP_FLAGS HeapFlags,
                                                    const D3D12_RESOURCE_DESC *pDesc,
                                                    D3D12_RESOURCE_STATES InitialResourceState,
                                                    const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                    ID3D12ProtectedResourceSession *pProtectedSession, 
                                                    const IID &riidResource,
                                                    void **ppvResource) override;

    HRESULT STDMETHODCALLTYPE CreateHeap1(const D3D12_HEAP_DESC *pDesc,
                                        ID3D12ProtectedResourceSession *pProtectedSession,
                                        const IID &riid, void **ppvHeap) override;

    HRESULT STDMETHODCALLTYPE CreateReservedResource1(const D3D12_RESOURCE_DESC *pDesc,
                                                    D3D12_RESOURCE_STATES InitialState,
                                                    const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                    ID3D12ProtectedResourceSession *
                                                    pProtectedSession, const IID &riid,
                                                    void **ppvResource) override;

    D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE GetResourceAllocationInfo1(
                                                    UINT visibleMask, UINT numResourceDescs,
                                                    _In_reads_(numResourceDescs) const D3D12_RESOURCE_DESC *pResourceDescs,
                                                    _Out_writes_opt_(numResourceDescs) D3D12_RESOURCE_ALLOCATION_INFO1 *pResourceAllocationInfo1) override;

    // Implement ID3D12Device5
    HRESULT STDMETHODCALLTYPE CreateLifetimeTracker(ID3D12LifetimeOwner *pOwner, const IID &riid,
                                                    void **ppvTracker) override;

    void STDMETHODCALLTYPE RemoveDevice() override;

    HRESULT STDMETHODCALLTYPE EnumerateMetaCommands(_Inout_ UINT *pNumMetaCommands,
                                                    _Out_writes_opt_(*pNumMetaCommands) D3D12_META_COMMAND_DESC *pDescs) override;

    HRESULT STDMETHODCALLTYPE EnumerateMetaCommandParameters(
                                                _In_ REFGUID CommandId, _In_ D3D12_META_COMMAND_PARAMETER_STAGE Stage,
                                                _Out_opt_ UINT *pTotalStructureSizeInBytes, _Inout_ UINT *pParameterCount,
                                                _Out_writes_opt_(*pParameterCount) D3D12_META_COMMAND_PARAMETER_DESC *pParameterDescs) override;

    HRESULT STDMETHODCALLTYPE CreateMetaCommand(const GUID &CommandId, UINT NodeMask,
                                                const void *pCreationParametersData,
                                                SIZE_T CreationParametersDataSizeInBytes,
                                                const IID &riid, void **ppMetaCommand) override;

    HRESULT STDMETHODCALLTYPE CreateStateObject(const D3D12_STATE_OBJECT_DESC *pDesc, const IID &riid,
                                                void **ppStateObject) override;

    void STDMETHODCALLTYPE GetRaytracingAccelerationStructurePrebuildInfo(
                                                _In_ const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS *pDesc,
                                                _Out_ D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO *pInfo) override;

    
    D3D12_DRIVER_MATCHING_IDENTIFIER_STATUS STDMETHODCALLTYPE CheckDriverMatchingIdentifier(
                                                _In_ D3D12_SERIALIZED_DATA_TYPE SerializedDataType,
                                                _In_ const D3D12_SERIALIZED_DATA_DRIVER_MATCHING_IDENTIFIER *pIdentifierToCheck) override;

    // Implement ID3D12Device6
    HRESULT STDMETHODCALLTYPE SetBackgroundProcessingMode(
                                                D3D12_BACKGROUND_PROCESSING_MODE Mode, D3D12_MEASUREMENTS_ACTION MeasurementsAction,
                                                _In_opt_ HANDLE hEventToSignalUponCompletion, _Out_opt_ BOOL *pbFurtherMeasurementsDesired) override;

    // Implement ID3D12Device7
    HRESULT STDMETHODCALLTYPE AddToStateObject(const D3D12_STATE_OBJECT_DESC *pAddition,
                                                ID3D12StateObject *pStateObjectToGrowFrom,
                                                const IID &riid, void **ppNewStateObject) override;

    HRESULT STDMETHODCALLTYPE CreateProtectedResourceSession1(_In_ const D3D12_PROTECTED_RESOURCE_SESSION_DESC1 *pDesc,
                                                            _In_ REFIID riid, _COM_Outptr_ void **ppSession) override;

    // Implement ID3D12Device8
    D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE GetResourceAllocationInfo2(
                                                UINT visibleMask, UINT numResourceDescs,
                                                _In_reads_(numResourceDescs) const D3D12_RESOURCE_DESC1 *pResourceDescs,
                                                _Out_writes_opt_(numResourceDescs) D3D12_RESOURCE_ALLOCATION_INFO1 *pResourceAllocationInfo1) override;

    HRESULT STDMETHODCALLTYPE CreateCommittedResource2(const D3D12_HEAP_PROPERTIES *pHeapProperties,
                                                        D3D12_HEAP_FLAGS HeapFlags,
                                                        const D3D12_RESOURCE_DESC1 *pDesc,
                                                        D3D12_RESOURCE_STATES InitialResourceState,
                                                        const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                        ID3D12ProtectedResourceSession *
                                                        pProtectedSession, const IID &riidResource,
                                                        void **ppvResource) override;

    HRESULT STDMETHODCALLTYPE CreatePlacedResource1(ID3D12Heap *pHeap, UINT64 HeapOffset,
                                                    const D3D12_RESOURCE_DESC1 *pDesc,
                                                    D3D12_RESOURCE_STATES InitialState,
                                                    const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                    const IID &riid, void **ppvResource) override;

    void STDMETHODCALLTYPE CreateSamplerFeedbackUnorderedAccessView(
                                                _In_opt_ ID3D12Resource *pTargetedResource, _In_opt_ ID3D12Resource *pFeedbackResource,
                                                _In_ D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) override;

    void STDMETHODCALLTYPE GetCopyableFootprints1(
                                                _In_ const D3D12_RESOURCE_DESC1 *pResourceDesc,
                                                _In_range_(0, D3D12_REQ_SUBRESOURCES) UINT FirstSubresource,
                                                _In_range_(0, D3D12_REQ_SUBRESOURCES - FirstSubresource) UINT NumSubresources,
                                                UINT64 BaseOffset,
                                                _Out_writes_opt_(NumSubresources) D3D12_PLACED_SUBRESOURCE_FOOTPRINT *pLayouts,
                                                _Out_writes_opt_(NumSubresources) UINT *pNumRows,
                                                _Out_writes_opt_(NumSubresources) UINT64 *pRowSizeInBytes, _Out_opt_ UINT64 *pTotalBytes) override;

    // Implement ID3D12Device9
    HRESULT STDMETHODCALLTYPE CreateShaderCacheSession(_In_ const D3D12_SHADER_CACHE_SESSION_DESC *pDesc, REFIID riid,
                            _COM_Outptr_opt_ void **ppvSession) override;

    HRESULT STDMETHODCALLTYPE ShaderCacheControl(D3D12_SHADER_CACHE_KIND_FLAGS Kinds, D3D12_SHADER_CACHE_CONTROL_FLAGS Control) override;

    HRESULT STDMETHODCALLTYPE CreateCommandQueue1(const D3D12_COMMAND_QUEUE_DESC *pDesc,
                                                const IID &CreatorID, const IID &riid,
                                                void **ppCommandQueue) override;

    // Implement ID3D12Device10
    HRESULT STDMETHODCALLTYPE CreateCommittedResource3( 
                                                _In_  const D3D12_HEAP_PROPERTIES *pHeapProperties,
                                                D3D12_HEAP_FLAGS HeapFlags,
                                                _In_  const D3D12_RESOURCE_DESC1 *pDesc,
                                                D3D12_BARRIER_LAYOUT InitialLayout,
                                                _In_opt_  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                _In_opt_  ID3D12ProtectedResourceSession *pProtectedSession,
                                                UINT32 NumCastableFormats,
                                                _In_opt_count_(NumCastableFormats) const DXGI_FORMAT *pCastableFormats,
                                                REFIID riidResource,
                                                _COM_Outptr_opt_  void **ppvResource) override;

    HRESULT STDMETHODCALLTYPE CreatePlacedResource2( 
                                                _In_  ID3D12Heap *pHeap,
                                                UINT64 HeapOffset,
                                                _In_  const D3D12_RESOURCE_DESC1 *pDesc,
                                                D3D12_BARRIER_LAYOUT InitialLayout,
                                                _In_opt_  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                UINT32 NumCastableFormats,
                                                _In_opt_count_(NumCastableFormats) const DXGI_FORMAT *pCastableFormats,
                                                REFIID riid,
                                                _COM_Outptr_opt_  void **ppvResource) override;

    HRESULT STDMETHODCALLTYPE CreateReservedResource2( 
                                                _In_  const D3D12_RESOURCE_DESC *pDesc,
                                                D3D12_BARRIER_LAYOUT InitialLayout,
                                                _In_opt_  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                _In_opt_  ID3D12ProtectedResourceSession *pProtectedSession,
                                                UINT32 NumCastableFormats,
                                                _In_opt_count_(NumCastableFormats) const DXGI_FORMAT *pCastableFormats,
                                                REFIID riid,
                                                _COM_Outptr_opt_  void **ppvResource) override;

    // Implement ID3D12Device11
    void STDMETHODCALLTYPE CreateSampler2(_In_  const D3D12_SAMPLER_DESC2 *pDesc, _In_  D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) override;

    // Implement ID3D12Device12
    D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE GetResourceAllocationInfo3(
            UINT visibleMask,
            UINT numResourceDescs,
            _In_reads_(numResourceDescs)  const D3D12_RESOURCE_DESC1 *pResourceDescs,
            _In_opt_count_(numResourceDescs)  const UINT32 *pNumCastableFormats,
            _In_opt_count_(numResourceDescs)  const DXGI_FORMAT *const *ppCastableFormats,
            _Out_writes_opt_(numResourceDescs)  D3D12_RESOURCE_ALLOCATION_INFO1 *pResourceAllocationInfo1) override;

    // Implement ID3D12Device13
    HRESULT STDMETHODCALLTYPE OpenExistingHeapFromAddress1(
            _In_  const void *pAddress,
            SIZE_T size,
            REFIID riid,
            _COM_Outptr_  void **ppvHeap) override;

    // Implement ID3D12Device14
    HRESULT STDMETHODCALLTYPE CreateRootSignatureFromSubobjectInLibrary(
            _In_  UINT nodeMask,
            _In_reads_(blobLengthInBytes)  const void *pLibraryBlob,
            _In_  SIZE_T blobLengthInBytes,
            _In_opt_  LPCWSTR subobjectName,
            REFIID riid,
            _COM_Outptr_  void **ppvRootSignature) override;
};

