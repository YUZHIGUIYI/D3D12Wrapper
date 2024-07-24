#include <d3d12/core/d3d12_command_queue_wrap.h>
#include <d3d12/core/d3d12_command_list_wrap.h>
#include <d3d12/core/d3d12_device_wrap.h>

WrappedD3D12CommandQueue::WrappedD3D12CommandQueue(ID3D12CommandQueue *real_command_queue, WrappedID3D12Device *wrapped_device)
: m_pQueue(real_command_queue), m_wrapped_device(wrapped_device)
{
    m_pQueue->AddRef();
}

WrappedD3D12CommandQueue::~WrappedD3D12CommandQueue() = default;

ULONG STDMETHODCALLTYPE WrappedID3D12DebugCommandQueue::AddRef()
{
    return m_pQueue->AddRef();
}

ULONG STDMETHODCALLTYPE WrappedID3D12DebugCommandQueue::Release()
{
    return m_pQueue->Release();
}

HRESULT STDMETHODCALLTYPE WrappedID3D12DebugCommandQueue::QueryInterface(REFIID riid, void **ppvObject)
{
    return m_pQueue->QueryInterface(riid, ppvObject);
}

BOOL STDMETHODCALLTYPE WrappedID3D12DebugCommandQueue::AssertResourceState(ID3D12Resource *pResource, UINT Subresource,
                                        UINT State)
{
    return m_pQueue->AssertResourceState(pResource, Subresource, State);
}

ULONG STDMETHODCALLTYPE WrappedD3D12CommandQueue::AddRef()
{
    return m_pQueue->AddRef();
}

ULONG STDMETHODCALLTYPE WrappedD3D12CommandQueue::Release()
{
    return m_pQueue->Release();
}

HRESULT STDMETHODCALLTYPE WrappedD3D12CommandQueue::QueryInterface(REFIID riid, void **ppvObject)
{
    return m_pQueue->QueryInterface(riid, ppvObject);
}

HRESULT STDMETHODCALLTYPE WrappedD3D12CommandQueue::GetPrivateData(REFGUID guid, UINT *pDataSize, void *pData)
{
    return m_pQueue->GetPrivateData(guid, pDataSize, pData);
}

HRESULT STDMETHODCALLTYPE WrappedD3D12CommandQueue::SetPrivateData(REFGUID guid, UINT DataSize, const void *pData)
{
    return m_pQueue->SetPrivateData(guid, DataSize, pData);
}

HRESULT STDMETHODCALLTYPE WrappedD3D12CommandQueue::SetPrivateDataInterface(REFGUID guid, const IUnknown *pData)
{
    return m_pQueue->SetPrivateDataInterface(guid, pData);
}

HRESULT STDMETHODCALLTYPE WrappedD3D12CommandQueue::SetName(LPCWSTR Name)
{
    return m_pQueue->SetName(Name);
}

HRESULT STDMETHODCALLTYPE WrappedD3D12CommandQueue::GetDevice(REFIID riid, _COM_Outptr_opt_ void **ppvDevice)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    HRESULT result = m_wrapped_device->GetDevice(riid, ppvDevice);
    return result;
}

void STDMETHODCALLTYPE WrappedD3D12CommandQueue::UpdateTileMappings(ID3D12Resource *pResource, UINT NumResourceRegions,
                                            const D3D12_TILED_RESOURCE_COORDINATE *
                                            pResourceRegionStartCoordinates,
                                            const D3D12_TILE_REGION_SIZE *pResourceRegionSizes,
                                            ID3D12Heap *pHeap, UINT NumRanges,
                                            const D3D12_TILE_RANGE_FLAGS *pRangeFlags,
                                            const UINT *pHeapRangeStartOffsets,
                                            const UINT *pRangeTileCounts,
                                            D3D12_TILE_MAPPING_FLAGS Flags)
{
    m_pQueue->UpdateTileMappings(pResource, NumResourceRegions, pResourceRegionStartCoordinates, pResourceRegionSizes, 
                        pHeap, NumRanges, pRangeFlags, pHeapRangeStartOffsets, pRangeTileCounts, Flags);
}

void STDMETHODCALLTYPE WrappedD3D12CommandQueue::CopyTileMappings(ID3D12Resource *pDstResource,
                                            const D3D12_TILED_RESOURCE_COORDINATE *pDstRegionStartCoordinate,
                                            ID3D12Resource *pSrcResource,
                                            const D3D12_TILED_RESOURCE_COORDINATE *pSrcRegionStartCoordinate,
                                            const D3D12_TILE_REGION_SIZE *pRegionSize,
                                            D3D12_TILE_MAPPING_FLAGS Flags)
{
    m_pQueue->CopyTileMappings(pDstResource, pDstRegionStartCoordinate, pSrcResource, 
                        pSrcRegionStartCoordinate, pRegionSize, Flags);
}

void STDMETHODCALLTYPE WrappedD3D12CommandQueue::ExecuteCommandLists(UINT NumCommandLists, ID3D12CommandList *const *ppCommandLists)
{
    // TODO: check
    D3D12_WRAPPER_ASSERT(NumCommandLists > 0, "The number of command lists should be greater than 0");
    std::vector<ID3D12CommandList *> real_command_lists;
    for (uint32_t i = 0; i < NumCommandLists; ++i)
    {
        if (auto *wrapped_command_list = dynamic_cast<WrappedID3D12GraphicsCommandList *>(ppCommandLists[i]))
        {
            real_command_lists.push_back(wrapped_command_list->GetReal());
        } else
        {
            real_command_lists.push_back(ppCommandLists[i]);
        }
    }
    m_pQueue->ExecuteCommandLists(NumCommandLists, real_command_lists.data());
}

void STDMETHODCALLTYPE WrappedD3D12CommandQueue::SetMarker(UINT Metadata, const void *pData, UINT Size)
{
    m_pQueue->SetMarker(Metadata, pData, Size);
}

void STDMETHODCALLTYPE WrappedD3D12CommandQueue::BeginEvent(UINT Metadata, const void *pData, UINT Size)
{
    m_pQueue->BeginEvent(Metadata, pData, Size);
}

void STDMETHODCALLTYPE WrappedD3D12CommandQueue::EndEvent()
{
    m_pQueue->EndEvent();
}

HRESULT STDMETHODCALLTYPE WrappedD3D12CommandQueue::Signal(ID3D12Fence *pFence, UINT64 Value)
{
    return m_pQueue->Signal(pFence, Value);
}

HRESULT STDMETHODCALLTYPE WrappedD3D12CommandQueue::Wait(ID3D12Fence *pFence, UINT64 Value)
{
    return m_pQueue->Wait(pFence, Value);
}

HRESULT STDMETHODCALLTYPE WrappedD3D12CommandQueue::GetTimestampFrequency(UINT64 *pFrequency)
{
    return m_pQueue->GetTimestampFrequency(pFrequency);
}

HRESULT STDMETHODCALLTYPE WrappedD3D12CommandQueue::GetClockCalibration(UINT64 *pGpuTimestamp, UINT64 *pCpuTimestamp)
{
    return m_pQueue->GetClockCalibration(pGpuTimestamp, pCpuTimestamp);
}

D3D12_COMMAND_QUEUE_DESC STDMETHODCALLTYPE WrappedD3D12CommandQueue::GetDesc()
{
    return m_pQueue->GetDesc();
}