#include <tracer/d3d12/d3d12_command_queue_wrap.h>
#include <tracer/d3d12/d3d12_command_list_wrap.h>
#include <tracer/d3d12/d3d12_device_wrap.h>
#include <tracer/hooks/d3d12_hook_manager.h>

namespace gfxshim
{
	ID3D12CommandQueueWrapper::ID3D12CommandQueueWrapper(const IID &riid, IUnknown *object)
	: ID3D12PageableWrapper(riid, object)
	{

	}

	void STDMETHODCALLTYPE ID3D12CommandQueueWrapper::UpdateTileMappings(
			ID3D12Resource *pResource, UINT NumResourceRegions,
			const D3D12_TILED_RESOURCE_COORDINATE *pResourceRegionStartCoordinates,
			const D3D12_TILE_REGION_SIZE *pResourceRegionSizes, ID3D12Heap *pHeap, UINT NumRanges,
			const D3D12_TILE_RANGE_FLAGS *pRangeFlags, const UINT *pHeapRangeStartOffsets, const UINT *pRangeTileCounts,
			D3D12_TILE_MAPPING_FLAGS Flags)
	{
		GetWrappedObjectAs<ID3D12CommandQueue>()->UpdateTileMappings(encode::GetWrappedObject<ID3D12Resource>(pResource), NumResourceRegions, pResourceRegionStartCoordinates,
														pResourceRegionSizes, encode::GetWrappedObject<ID3D12Heap>(pHeap), NumRanges,
														pRangeFlags, pHeapRangeStartOffsets, pRangeTileCounts, Flags);
	}

	void STDMETHODCALLTYPE ID3D12CommandQueueWrapper::CopyTileMappings(ID3D12Resource *pDstResource,
													 const D3D12_TILED_RESOURCE_COORDINATE *pDstRegionStartCoordinate,
													 ID3D12Resource *pSrcResource,
													 const D3D12_TILED_RESOURCE_COORDINATE *pSrcRegionStartCoordinate,
													 const D3D12_TILE_REGION_SIZE *pRegionSize,
													 D3D12_TILE_MAPPING_FLAGS Flags)
	{
		GetWrappedObjectAs<ID3D12CommandQueue>()->CopyTileMappings(encode::GetWrappedObject<ID3D12Resource>(pDstResource), pDstRegionStartCoordinate, encode::GetWrappedObject<ID3D12Resource>(pSrcResource),
																pSrcRegionStartCoordinate, pRegionSize, Flags);
	}

	void STDMETHODCALLTYPE ID3D12CommandQueueWrapper::ExecuteCommandLists(UINT NumCommandLists, ID3D12CommandList *const *ppCommandLists)
	{
		if (NumCommandLists > 0U && ppCommandLists != nullptr)
		{
			std::vector<ID3D12CommandList *> unwrap_command_lists(NumCommandLists);
			for (uint32_t i = 0U; i < NumCommandLists; ++i)
			{
				unwrap_command_lists[i] = encode::GetWrappedObject<ID3D12CommandList>(ppCommandLists[i]);
			}
			return GetWrappedObjectAs<ID3D12CommandQueue>()->ExecuteCommandLists(NumCommandLists, unwrap_command_lists.data());
		}
		return GetWrappedObjectAs<ID3D12CommandQueue>()->ExecuteCommandLists(NumCommandLists, ppCommandLists);
	}

	void STDMETHODCALLTYPE ID3D12CommandQueueWrapper::SetMarker(UINT Metadata, const void *pData, UINT Size)
	{
		GetWrappedObjectAs<ID3D12CommandQueue>()->SetMarker(Metadata, pData, Size);
	}

	void STDMETHODCALLTYPE ID3D12CommandQueueWrapper::BeginEvent(UINT Metadata, const void *pData, UINT Size)
	{
		GetWrappedObjectAs<ID3D12CommandQueue>()->BeginEvent(Metadata, pData, Size);
	}

	void STDMETHODCALLTYPE ID3D12CommandQueueWrapper::EndEvent()
	{
		GetWrappedObjectAs<ID3D12CommandQueue>()->EndEvent();
	}

	HRESULT STDMETHODCALLTYPE ID3D12CommandQueueWrapper::Signal(ID3D12Fence *pFence, UINT64 Value)
	{
		const auto result = GetWrappedObjectAs<ID3D12CommandQueue>()->Signal(encode::GetWrappedObject<ID3D12Fence>(pFence), Value);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12CommandQueueWrapper::Wait(ID3D12Fence *pFence, UINT64 Value)
	{
		const auto result = GetWrappedObjectAs<ID3D12CommandQueue>()->Wait(encode::GetWrappedObject<ID3D12Fence>(pFence), Value);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12CommandQueueWrapper::GetTimestampFrequency(UINT64 *pFrequency)
	{
		const auto result = GetWrappedObjectAs<ID3D12CommandQueue>()->GetTimestampFrequency(pFrequency);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12CommandQueueWrapper::GetClockCalibration(UINT64 *pGpuTimestamp, UINT64 *pCpuTimestamp)
	{
		const auto result = GetWrappedObjectAs<ID3D12CommandQueue>()->GetClockCalibration(pGpuTimestamp, pCpuTimestamp);
		return result;
	}

	D3D12_COMMAND_QUEUE_DESC STDMETHODCALLTYPE ID3D12CommandQueueWrapper::GetDesc()
	{
		const auto result = GetWrappedObjectAs<ID3D12CommandQueue>()->GetDesc();
		return result;
	}

}

WrappedID3D12CommandQueue::WrappedID3D12CommandQueue(ID3D12CommandQueue *real_command_queue, WrappedID3D12Device *wrapped_device)
: m_pQueue(real_command_queue), m_wrapped_device(wrapped_device)
{
    m_pQueue->AddRef();
}

WrappedID3D12CommandQueue::~WrappedID3D12CommandQueue() = default;

ID3D12CommandQueue *WrappedID3D12CommandQueue::GetReal() const
{
    return m_pQueue;
}

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
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    const auto result = m_pQueue->QueryInterface(riid, ppvObject);
    return result;
}

BOOL STDMETHODCALLTYPE WrappedID3D12DebugCommandQueue::AssertResourceState(ID3D12Resource *pResource, UINT Subresource, UINT State)
{
    return m_pQueue->AssertResourceState(pResource, Subresource, State);
}

ULONG STDMETHODCALLTYPE WrappedID3D12CommandQueue::AddRef()
{
    return m_pQueue->AddRef();
}

ULONG STDMETHODCALLTYPE WrappedID3D12CommandQueue::Release()
{
    return m_pQueue->Release();
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandQueue::QueryInterface(REFIID riid, void **ppvObject)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    const auto result = m_pQueue->QueryInterface(riid, ppvObject);
    return result;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandQueue::GetPrivateData(REFGUID guid, UINT *pDataSize, void *pData)
{
    return m_pQueue->GetPrivateData(guid, pDataSize, pData);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandQueue::SetPrivateData(REFGUID guid, UINT DataSize, const void *pData)
{
    return m_pQueue->SetPrivateData(guid, DataSize, pData);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandQueue::SetPrivateDataInterface(REFGUID guid, const IUnknown *pData)
{
    return m_pQueue->SetPrivateDataInterface(guid, pData);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandQueue::SetName(LPCWSTR Name)
{
    return m_pQueue->SetName(Name);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandQueue::GetDevice(REFIID riid, _COM_Outptr_opt_ void **ppvDevice)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    HRESULT result = m_wrapped_device->GetDevice(riid, ppvDevice);
    return result;
}

void STDMETHODCALLTYPE WrappedID3D12CommandQueue::UpdateTileMappings(ID3D12Resource *pResource, UINT NumResourceRegions,
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

void STDMETHODCALLTYPE WrappedID3D12CommandQueue::CopyTileMappings(ID3D12Resource *pDstResource,
                                            const D3D12_TILED_RESOURCE_COORDINATE *pDstRegionStartCoordinate,
                                            ID3D12Resource *pSrcResource,
                                            const D3D12_TILED_RESOURCE_COORDINATE *pSrcRegionStartCoordinate,
                                            const D3D12_TILE_REGION_SIZE *pRegionSize,
                                            D3D12_TILE_MAPPING_FLAGS Flags)
{
    m_pQueue->CopyTileMappings(pDstResource, pDstRegionStartCoordinate, pSrcResource, 
                        pSrcRegionStartCoordinate, pRegionSize, Flags);
}

void STDMETHODCALLTYPE WrappedID3D12CommandQueue::ExecuteCommandLists(UINT NumCommandLists, ID3D12CommandList *const *ppCommandLists)
{
    D3D12_WRAPPER_ASSERT(NumCommandLists > 0, "The number of command lists should be greater than 0");
    if (m_signal_queue_finish)
    {
        m_cur_command_lists.clear();
        m_signal_queue_finish = false;
    }
    std::vector<ID3D12CommandList *> real_command_lists;
    real_command_lists.reserve(NumCommandLists);
    for (uint32_t i = 0; i < NumCommandLists; ++i)
    {
        if (auto *wrapped_command_list = dynamic_cast<WrappedID3D12GraphicsCommandList *>(ppCommandLists[i]))
        {
            auto *real_command_list = wrapped_command_list->GetReal();
            real_command_lists.emplace_back(real_command_list);
            m_cur_command_lists.emplace_back(real_command_list);
        } else
        {
            real_command_lists.emplace_back(ppCommandLists[i]);
        }
    }
    m_pQueue->ExecuteCommandLists(NumCommandLists, real_command_lists.data());
}

void STDMETHODCALLTYPE WrappedID3D12CommandQueue::SetMarker(UINT Metadata, const void *pData, UINT Size)
{
    m_pQueue->SetMarker(Metadata, pData, Size);
}

void STDMETHODCALLTYPE WrappedID3D12CommandQueue::BeginEvent(UINT Metadata, const void *pData, UINT Size)
{
    m_pQueue->BeginEvent(Metadata, pData, Size);
}

void STDMETHODCALLTYPE WrappedID3D12CommandQueue::EndEvent()
{
    m_pQueue->EndEvent();
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandQueue::Signal(ID3D12Fence *pFence, UINT64 Value)
{
    auto result = m_pQueue->Signal(pFence, Value);
    if (!m_cur_command_lists.empty())
    {
        // TODO: test deferred per-draw-dump and deferred per-dispatch-dump and immediate dds-dumping or bin-dumping
        gfxshim::D3D12HookManager::GetInstance().PerDrawAndDispatchDump(m_cur_command_lists, pFence, Value);
        m_signal_queue_finish = true;
    }
    return result;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandQueue::Wait(ID3D12Fence *pFence, UINT64 Value)
{
    return m_pQueue->Wait(pFence, Value);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandQueue::GetTimestampFrequency(UINT64 *pFrequency)
{
    return m_pQueue->GetTimestampFrequency(pFrequency);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandQueue::GetClockCalibration(UINT64 *pGpuTimestamp, UINT64 *pCpuTimestamp)
{
    return m_pQueue->GetClockCalibration(pGpuTimestamp, pCpuTimestamp);
}

D3D12_COMMAND_QUEUE_DESC STDMETHODCALLTYPE WrappedID3D12CommandQueue::GetDesc()
{
    return m_pQueue->GetDesc();
}

extern "C" __declspec(dllexport) HRESULT QueryRealCommandQueue(IUnknown *wrapped_queue_pointer, IUnknown **real_command_queue_pointer)
{
    if (const auto *wrapped_command_queue = dynamic_cast<WrappedID3D12CommandQueue *>(wrapped_queue_pointer))
    {
        *real_command_queue_pointer = wrapped_command_queue->GetReal();
        return S_OK;
    }
    return E_FAIL;
}