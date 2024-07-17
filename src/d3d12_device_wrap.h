#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <dxgi.h>
#include <dxgi1_2.h>
#include <dxgi1_3.h>
#include <dxgi1_4.h>
#include <dxgi1_5.h>
#include <dxgi1_6.h>

#include <map>

#if defined(max)
    #undef max
#endif

#if defined(min)
    #undef min
#endif

#if defined(near)
    #undef near
#endif

#if defined(far)
    #undef far
#endif

class WrappedID3D12Device final : public ID3D12Device10
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

    static std::map<ID3D12Device *, WrappedID3D12Device *> m_device_wrappers;

public:
    explicit WrappedID3D12Device(ID3D12Device *real_device);

    static WrappedID3D12Device *create(ID3D12Device *real_device);

public:
    // Implement IUnknown
    ULONG STDMETHODCALLTYPE AddRef() final;

    ULONG STDMETHODCALLTYPE Release() final ;

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) final;

	// Implement ID3D12Object
	HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID guid, UINT *pDataSize, void *pData) final;

	HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID guid, UINT DataSize, const void *pData) final;

	HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID guid, const IUnknown *pData) final;

	HRESULT STDMETHODCALLTYPE SetName(LPCWSTR Name) final;

    // Implement ID3D12Device
    UINT STDMETHODCALLTYPE GetNodeCount() final;

	LUID STDMETHODCALLTYPE GetAdapterLuid() final;

    HRESULT STDMETHODCALLTYPE CreateCommandQueue(const D3D12_COMMAND_QUEUE_DESC *pDesc, const IID &riid, void **ppCommandQueue) final;

    HRESULT STDMETHODCALLTYPE CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE type, const IID &riid,
                                            void **ppCommandAllocator) final;

    HRESULT STDMETHODCALLTYPE CreateGraphicsPipelineState(const D3D12_GRAPHICS_PIPELINE_STATE_DESC *pDesc, const IID &riid, void **ppPipelineState) final;

    HRESULT STDMETHODCALLTYPE CreateComputePipelineState(const D3D12_COMPUTE_PIPELINE_STATE_DESC *pDesc, const IID &riid, void **ppPipelineState) final;

    HRESULT STDMETHODCALLTYPE CreateCommandList(UINT nodeMask, D3D12_COMMAND_LIST_TYPE type,
                                        		ID3D12CommandAllocator *pCommandAllocator,
                                        		ID3D12PipelineState *pInitialState, const IID &riid,
                                        		void **ppCommandList) final;

    HRESULT STDMETHODCALLTYPE CheckFeatureSupport(D3D12_FEATURE Feature, void *pFeatureSupportData, UINT FeatureSupportDataSize) final;

    HRESULT STDMETHODCALLTYPE CreateDescriptorHeap(const D3D12_DESCRIPTOR_HEAP_DESC *pDescriptorHeapDesc, const IID &riid, void **ppvHeap) final;

    UINT STDMETHODCALLTYPE GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapType) final;

    HRESULT STDMETHODCALLTYPE CreateRootSignature(UINT nodeMask, const void *pBlobWithRootSignature,
                                                SIZE_T blobLengthInBytes, const IID &riid,
                                                void **ppvRootSignature) final;

    void STDMETHODCALLTYPE CreateConstantBufferView(const D3D12_CONSTANT_BUFFER_VIEW_DESC *pDesc,
                                            		D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) final;

    void STDMETHODCALLTYPE CreateShaderResourceView(ID3D12Resource *pResource,
                                        			const D3D12_SHADER_RESOURCE_VIEW_DESC *pDesc,
                                            		D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) final;
    
    void STDMETHODCALLTYPE CreateUnorderedAccessView(ID3D12Resource *pResource,
                                                   	ID3D12Resource *pCounterResource,
                                                   	const D3D12_UNORDERED_ACCESS_VIEW_DESC *pDesc,
                                                	D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) final;

    void STDMETHODCALLTYPE CreateRenderTargetView(ID3D12Resource *pResource,
                                                const D3D12_RENDER_TARGET_VIEW_DESC *pDesc,
                                                D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) final;

    void STDMETHODCALLTYPE CreateDepthStencilView(ID3D12Resource *pResource,
                                                const D3D12_DEPTH_STENCIL_VIEW_DESC *pDesc,
                                                D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) final;

    void STDMETHODCALLTYPE CreateSampler(const D3D12_SAMPLER_DESC *pDesc,
                                    	D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) final;

    void STDMETHODCALLTYPE CopyDescriptors(UINT NumDestDescriptorRanges,
                                         const D3D12_CPU_DESCRIPTOR_HANDLE *pDestDescriptorRangeStarts,
                                         const UINT *pDestDescriptorRangeSizes,
                                         UINT NumSrcDescriptorRanges,
                                         const D3D12_CPU_DESCRIPTOR_HANDLE *pSrcDescriptorRangeStarts,
                                         const UINT *pSrcDescriptorRangeSizes,
                                         D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapsType) final;

    void STDMETHODCALLTYPE CopyDescriptorsSimple(UINT NumDescriptors,
                                               	D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptorRangeStart,
                                               	D3D12_CPU_DESCRIPTOR_HANDLE SrcDescriptorRangeStart,
                                               	D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapsType) final;

    D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE GetResourceAllocationInfo(UINT visibleMask, UINT numResourceDescs, const D3D12_RESOURCE_DESC *pResourceDescs) final;

    D3D12_HEAP_PROPERTIES STDMETHODCALLTYPE GetCustomHeapProperties(UINT nodeMask, D3D12_HEAP_TYPE heapType) final;

    HRESULT STDMETHODCALLTYPE CreateCommittedResource(const D3D12_HEAP_PROPERTIES *pHeapProperties,
                                                    D3D12_HEAP_FLAGS HeapFlags,
                                                    const D3D12_RESOURCE_DESC *pDesc,
                                                    D3D12_RESOURCE_STATES InitialResourceState,
                                                    const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                    const IID &riidResource, void **ppvResource) final;

    HRESULT STDMETHODCALLTYPE CreateHeap(const D3D12_HEAP_DESC *pDesc, const IID &riid, void **ppvHeap) final;

    HRESULT STDMETHODCALLTYPE CreatePlacedResource(ID3D12Heap *pHeap, UINT64 HeapOffset,
                                                   const D3D12_RESOURCE_DESC *pDesc,
                                                   D3D12_RESOURCE_STATES InitialState,
                                                   const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                   const IID &riid, void **ppvResource) final;

    HRESULT STDMETHODCALLTYPE CreateReservedResource(const D3D12_RESOURCE_DESC *pDesc,
                                                    D3D12_RESOURCE_STATES InitialState,
                                                    const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                    const IID &riid, void **ppvResource) final;

    HRESULT STDMETHODCALLTYPE CreateSharedHandle(ID3D12DeviceChild *pObject,
                                               	const SECURITY_ATTRIBUTES *pAttributes, DWORD Access,
                                               	LPCWSTR Name, HANDLE *pHandle) final;

    HRESULT STDMETHODCALLTYPE OpenSharedHandle(HANDLE NTHandle, const IID &riid, void **ppvObj) final;

    HRESULT STDMETHODCALLTYPE OpenSharedHandleByName(LPCWSTR Name, DWORD Access, HANDLE *pNTHandle) final;

    HRESULT STDMETHODCALLTYPE MakeResident(UINT NumObjects, ID3D12Pageable *const *ppObjects) final;

    HRESULT STDMETHODCALLTYPE Evict(UINT NumObjects, ID3D12Pageable *const *ppObjects) final;

    HRESULT STDMETHODCALLTYPE CreateFence(UINT64 InitialValue, D3D12_FENCE_FLAGS Flags,
                                        const IID &riid, void **ppFence) final;

    HRESULT STDMETHODCALLTYPE GetDeviceRemovedReason() final;

    void STDMETHODCALLTYPE GetCopyableFootprints(const D3D12_RESOURCE_DESC *pResourceDesc,
                                               	UINT FirstSubresource, UINT NumSubresources,
                                               	UINT64 BaseOffset,
                                               	D3D12_PLACED_SUBRESOURCE_FOOTPRINT *pLayouts,
                                               	UINT *pNumRows, UINT64 *pRowSizeInBytes,
                                               	UINT64 *pTotalBytes) final;

    HRESULT STDMETHODCALLTYPE CreateQueryHeap(const D3D12_QUERY_HEAP_DESC *pDesc, const IID &riid,
                                             void **ppvHeap) final;

    HRESULT STDMETHODCALLTYPE SetStablePowerState(BOOL Enable) final;

    HRESULT STDMETHODCALLTYPE CreateCommandSignature(const D3D12_COMMAND_SIGNATURE_DESC *pDesc,
                                                   ID3D12RootSignature *pRootSignature,
                                                   const IID &riid, void **ppvCommandSignature) final;

    void STDMETHODCALLTYPE GetResourceTiling(ID3D12Resource *pTiledResource,
                                           	UINT *pNumTilesForEntireResource,
                                           	D3D12_PACKED_MIP_INFO *pPackedMipDesc,
                                           	D3D12_TILE_SHAPE *pStandardTileShapeForNonPackedMips,
                                           	UINT *pNumSubresourceTilings,
                                           	UINT FirstSubresourceTilingToGet,
                                           	D3D12_SUBRESOURCE_TILING *pSubresourceTilingsForNonPackedMips) final;

    // Implement ID3D12Device1
    HRESULT STDMETHODCALLTYPE CreatePipelineLibrary(const void *pLibraryBlob, SIZE_T BlobLength,
                                                  	const IID &riid, void **ppPipelineLibrary) final;

    HRESULT STDMETHODCALLTYPE SetEventOnMultipleFenceCompletion(ID3D12Fence *const *ppFences, const UINT64 *pFenceValues, UINT NumFences,
														D3D12_MULTIPLE_FENCE_WAIT_FLAGS Flags, HANDLE hEvent) final;

    HRESULT STDMETHODCALLTYPE SetResidencyPriority(UINT NumObjects, ID3D12Pageable *const *ppObjects,
                                                 const D3D12_RESIDENCY_PRIORITY *pPriorities) final;

    // Implement ID3D12Device2
    HRESULT STDMETHODCALLTYPE CreatePipelineState(const D3D12_PIPELINE_STATE_STREAM_DESC *pDesc,
                                                const IID &riid, void **ppPipelineState) final;

    // Implement ID3D12Device3
    HRESULT STDMETHODCALLTYPE OpenExistingHeapFromAddress(const void *pAddress, const IID &riid, void **ppvHeap) final;

    HRESULT STDMETHODCALLTYPE OpenExistingHeapFromFileMapping(HANDLE hFileMapping, const IID &riid, void **ppvHeap) final;

    HRESULT STDMETHODCALLTYPE EnqueueMakeResident(D3D12_RESIDENCY_FLAGS Flags, UINT NumObjects,
                                                ID3D12Pageable *const *ppObjects,
                                                ID3D12Fence *pFenceToSignal,
                                                UINT64 FenceValueToSignal) final;

    // Implement ID3D12Device4
    HRESULT STDMETHODCALLTYPE CreateCommandList1(UINT nodeMask, D3D12_COMMAND_LIST_TYPE type,
                                            	D3D12_COMMAND_LIST_FLAGS flags, const IID &riid,
                                            	void **ppCommandList) final;

    HRESULT STDMETHODCALLTYPE CreateProtectedResourceSession(_In_ const D3D12_PROTECTED_RESOURCE_SESSION_DESC *pDesc,
                                 							_In_ REFIID riid, _COM_Outptr_ void **ppSession) final;

    HRESULT STDMETHODCALLTYPE CreateCommittedResource1(const D3D12_HEAP_PROPERTIES *pHeapProperties,
                                                    D3D12_HEAP_FLAGS HeapFlags,
                                                    const D3D12_RESOURCE_DESC *pDesc,
                                                    D3D12_RESOURCE_STATES InitialResourceState,
                                                    const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                    ID3D12ProtectedResourceSession *pProtectedSession, 
													const IID &riidResource,
                                                    void **ppvResource) final;

    HRESULT STDMETHODCALLTYPE CreateHeap1(const D3D12_HEAP_DESC *pDesc,
                                        ID3D12ProtectedResourceSession *pProtectedSession,
                                        const IID &riid, void **ppvHeap) final;

    HRESULT STDMETHODCALLTYPE CreateReservedResource1(const D3D12_RESOURCE_DESC *pDesc,
                                                    D3D12_RESOURCE_STATES InitialState,
                                                    const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                    ID3D12ProtectedResourceSession *
                                                    pProtectedSession, const IID &riid,
                                                    void **ppvResource) final;

    D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE GetResourceAllocationInfo1(
      										UINT visibleMask, UINT numResourceDescs,
      										_In_reads_(numResourceDescs) const D3D12_RESOURCE_DESC *pResourceDescs,
      										_Out_writes_opt_(numResourceDescs) D3D12_RESOURCE_ALLOCATION_INFO1 *pResourceAllocationInfo1) final;

    // Implement ID3D12Device5
    HRESULT STDMETHODCALLTYPE CreateLifetimeTracker(ID3D12LifetimeOwner *pOwner, const IID &riid,
                                                  	void **ppvTracker) final;

    void STDMETHODCALLTYPE RemoveDevice() final;

    HRESULT STDMETHODCALLTYPE EnumerateMetaCommands(_Inout_ UINT *pNumMetaCommands,
                                                    _Out_writes_opt_(*pNumMetaCommands) D3D12_META_COMMAND_DESC *pDescs) final;

    HRESULT STDMETHODCALLTYPE EnumerateMetaCommandParameters(
      											_In_ REFGUID CommandId, _In_ D3D12_META_COMMAND_PARAMETER_STAGE Stage,
      											_Out_opt_ UINT *pTotalStructureSizeInBytes, _Inout_ UINT *pParameterCount,
      											_Out_writes_opt_(*pParameterCount) D3D12_META_COMMAND_PARAMETER_DESC *pParameterDescs) final;

    HRESULT STDMETHODCALLTYPE CreateMetaCommand(const GUID &CommandId, UINT NodeMask,
                                              const void *pCreationParametersData,
                                              SIZE_T CreationParametersDataSizeInBytes,
                                              const IID &riid, void **ppMetaCommand) final;

    HRESULT STDMETHODCALLTYPE CreateStateObject(const D3D12_STATE_OBJECT_DESC *pDesc, const IID &riid,
                                              	void **ppStateObject) final;

    void STDMETHODCALLTYPE GetRaytracingAccelerationStructurePrebuildInfo(
      										_In_ const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS *pDesc,
      										_Out_ D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO *pInfo) final;

    
    D3D12_DRIVER_MATCHING_IDENTIFIER_STATUS STDMETHODCALLTYPE CheckDriverMatchingIdentifier(
      										_In_ D3D12_SERIALIZED_DATA_TYPE SerializedDataType,
      										_In_ const D3D12_SERIALIZED_DATA_DRIVER_MATCHING_IDENTIFIER *pIdentifierToCheck) final;


    HRESULT STDMETHODCALLTYPE QueryVideoMemoryInfo(UINT NodeIndex, DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup,
                       							_Out_ DXGI_QUERY_VIDEO_MEMORY_INFO *pVideoMemoryInfo);

    // Implement ID3D12Device6
    HRESULT STDMETHODCALLTYPE SetBackgroundProcessingMode(
      						D3D12_BACKGROUND_PROCESSING_MODE Mode, D3D12_MEASUREMENTS_ACTION MeasurementsAction,
      						_In_opt_ HANDLE hEventToSignalUponCompletion, _Out_opt_ BOOL *pbFurtherMeasurementsDesired) final;

    // Implement ID3D12Device7
    HRESULT STDMETHODCALLTYPE AddToStateObject(const D3D12_STATE_OBJECT_DESC *pAddition,
                                             ID3D12StateObject *pStateObjectToGrowFrom,
                                             const IID &riid, void **ppNewStateObject) final;

    HRESULT STDMETHODCALLTYPE CreateProtectedResourceSession1(_In_ const D3D12_PROTECTED_RESOURCE_SESSION_DESC1 *pDesc,
                                  							_In_ REFIID riid, _COM_Outptr_ void **ppSession) final;

    // Implement ID3D12Device8
    D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE GetResourceAllocationInfo2(
      										UINT visibleMask, UINT numResourceDescs,
      										_In_reads_(numResourceDescs) const D3D12_RESOURCE_DESC1 *pResourceDescs,
      										_Out_writes_opt_(numResourceDescs) D3D12_RESOURCE_ALLOCATION_INFO1 *pResourceAllocationInfo1) final;

    HRESULT STDMETHODCALLTYPE CreateCommittedResource2(const D3D12_HEAP_PROPERTIES *pHeapProperties,
                                            		D3D12_HEAP_FLAGS HeapFlags,
                                            		const D3D12_RESOURCE_DESC1 *pDesc,
                                            		D3D12_RESOURCE_STATES InitialResourceState,
                                            		const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                            		ID3D12ProtectedResourceSession *
                                            		pProtectedSession, const IID &riidResource,
                                            		void **ppvResource) final;

    HRESULT STDMETHODCALLTYPE CreatePlacedResource1(ID3D12Heap *pHeap, UINT64 HeapOffset,
                                                  const D3D12_RESOURCE_DESC1 *pDesc,
                                                  D3D12_RESOURCE_STATES InitialState,
                                                  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                  const IID &riid, void **ppvResource) final;

    void STDMETHODCALLTYPE CreateSamplerFeedbackUnorderedAccessView(
      						_In_opt_ ID3D12Resource *pTargetedResource, _In_opt_ ID3D12Resource *pFeedbackResource,
      						_In_ D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor) final;

    void STDMETHODCALLTYPE GetCopyableFootprints1(
      						_In_ const D3D12_RESOURCE_DESC1 *pResourceDesc,
      						_In_range_(0, D3D12_REQ_SUBRESOURCES) UINT FirstSubresource,
      						_In_range_(0, D3D12_REQ_SUBRESOURCES - FirstSubresource) UINT NumSubresources,
      						UINT64 BaseOffset,
      						_Out_writes_opt_(NumSubresources) D3D12_PLACED_SUBRESOURCE_FOOTPRINT *pLayouts,
      						_Out_writes_opt_(NumSubresources) UINT *pNumRows,
      						_Out_writes_opt_(NumSubresources) UINT64 *pRowSizeInBytes, _Out_opt_ UINT64 *pTotalBytes) final;

    // Implement ID3D12Device9
    HRESULT STDMETHODCALLTYPE CreateShaderCacheSession(_In_ const D3D12_SHADER_CACHE_SESSION_DESC *pDesc, REFIID riid,
                            _COM_Outptr_opt_ void **ppvSession) final;

    HRESULT STDMETHODCALLTYPE ShaderCacheControl(D3D12_SHADER_CACHE_KIND_FLAGS Kinds, D3D12_SHADER_CACHE_CONTROL_FLAGS Control) final;

    HRESULT STDMETHODCALLTYPE CreateCommandQueue1(const D3D12_COMMAND_QUEUE_DESC *pDesc,
                                                const IID &CreatorID, const IID &riid,
                                                void **ppCommandQueue) final;

    // Implement ID3D12Device10
    HRESULT STDMETHODCALLTYPE CreateCommittedResource3( 
            				_In_  const D3D12_HEAP_PROPERTIES *pHeapProperties,
            				D3D12_HEAP_FLAGS HeapFlags,
            				_In_  const D3D12_RESOURCE_DESC1 *pDesc,
            				D3D12_BARRIER_LAYOUT InitialLayout,
            				_In_opt_  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
            				_In_opt_  ID3D12ProtectedResourceSession *pProtectedSession,
            				UINT32 NumCastableFormats,
            				_In_opt_count_(NumCastableFormats)  DXGI_FORMAT *pCastableFormats,
            				REFIID riidResource,
            				_COM_Outptr_opt_  void **ppvResource) final;

    HRESULT STDMETHODCALLTYPE CreatePlacedResource2( 
            					_In_  ID3D12Heap *pHeap,
            					UINT64 HeapOffset,
            					_In_  const D3D12_RESOURCE_DESC1 *pDesc,
            					D3D12_BARRIER_LAYOUT InitialLayout,
            					_In_opt_  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
            					UINT32 NumCastableFormats,
            					_In_opt_count_(NumCastableFormats)  DXGI_FORMAT *pCastableFormats,
            					REFIID riid,
            					_COM_Outptr_opt_  void **ppvResource) final;

    HRESULT STDMETHODCALLTYPE CreateReservedResource2( 
            					_In_  const D3D12_RESOURCE_DESC *pDesc,
            					D3D12_BARRIER_LAYOUT InitialLayout,
            					_In_opt_  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
            					_In_opt_  ID3D12ProtectedResourceSession *pProtectedSession,
            					UINT32 NumCastableFormats,
            					_In_opt_count_(NumCastableFormats)  DXGI_FORMAT *pCastableFormats,
            					REFIID riid,
            					_COM_Outptr_opt_  void **ppvResource) final;
};

