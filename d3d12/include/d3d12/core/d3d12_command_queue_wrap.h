#pragma once

#include <d3d12/common/d3d12_wrap_common.h>

class WrappedID3D12Device;

class WrappedID3D12DebugCommandQueue : public ID3D12DebugCommandQueue
{
private:
    ID3D12DebugCommandQueue *m_pQueue = nullptr;

    WrappedID3D12Device *m_wrapped_device = nullptr;

public:
    // Implement IUnknown
    ULONG STDMETHODCALLTYPE AddRef() final;

    ULONG STDMETHODCALLTYPE Release() final;

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) final;

    // Implement ID3D12DebugCommandQueue
    BOOL STDMETHODCALLTYPE AssertResourceState(ID3D12Resource *pResource, UINT Subresource, UINT State) final;
};

class WrappedID3D12CommandQueue : public ID3D12CommandQueue
{
private:
    ID3D12CommandQueue *m_pQueue = nullptr;
    WrappedID3D12Device *m_wrapped_device = nullptr;
    std::vector<ID3D12GraphicsCommandList *> m_cur_command_lists = {};
    bool m_signal_queue_finish = false;

public:
    WrappedID3D12CommandQueue(ID3D12CommandQueue *real_command_queue, WrappedID3D12Device *wrapped_device);

    ~WrappedID3D12CommandQueue();

    [[nodiscard]] ID3D12CommandQueue *GetReal() const;

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

    // Implement ID3D12CommandQueue
    void STDMETHODCALLTYPE UpdateTileMappings(ID3D12Resource *pResource, UINT NumResourceRegions,
                                            const D3D12_TILED_RESOURCE_COORDINATE *
                                            pResourceRegionStartCoordinates,
                                            const D3D12_TILE_REGION_SIZE *pResourceRegionSizes,
                                            ID3D12Heap *pHeap, UINT NumRanges,
                                            const D3D12_TILE_RANGE_FLAGS *pRangeFlags,
                                            const UINT *pHeapRangeStartOffsets,
                                            const UINT *pRangeTileCounts,
                                            D3D12_TILE_MAPPING_FLAGS Flags) final;

    void STDMETHODCALLTYPE CopyTileMappings(ID3D12Resource *pDstResource,
                                            const D3D12_TILED_RESOURCE_COORDINATE *
                                            pDstRegionStartCoordinate, ID3D12Resource *pSrcResource,
                                            const D3D12_TILED_RESOURCE_COORDINATE *pSrcRegionStartCoordinate,
                                            const D3D12_TILE_REGION_SIZE *pRegionSize,
                                            D3D12_TILE_MAPPING_FLAGS Flags) final;

    void STDMETHODCALLTYPE ExecuteCommandLists(UINT NumCommandLists,
                                    ID3D12CommandList *const *ppCommandLists) final;

    void STDMETHODCALLTYPE SetMarker(UINT Metadata, const void *pData, UINT Size) final;

    void STDMETHODCALLTYPE BeginEvent(UINT Metadata, const void *pData, UINT Size) final;

    void STDMETHODCALLTYPE EndEvent() final;

    HRESULT STDMETHODCALLTYPE Signal(ID3D12Fence *pFence, UINT64 Value) final;

    HRESULT STDMETHODCALLTYPE Wait(ID3D12Fence *pFence, UINT64 Value) final;

    HRESULT STDMETHODCALLTYPE GetTimestampFrequency(UINT64 *pFrequency) final;

    HRESULT STDMETHODCALLTYPE GetClockCalibration(UINT64 *pGpuTimestamp, UINT64 *pCpuTimestamp) final;

    D3D12_COMMAND_QUEUE_DESC STDMETHODCALLTYPE GetDesc() final;
};