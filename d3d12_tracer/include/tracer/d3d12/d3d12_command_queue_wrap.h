#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12CommandQueueWrapper final : ID3D12CommandQueue
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12CommandQueueWrapper *> s_d3d12_command_queue_manager{};
		inline static std::mutex s_d3d12_command_queue_mutex{};

	public:
		ID3D12CommandQueueWrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12CommandQueueWrapper() = default;

		// ID3D12CommandQueueWrapper manager
		static void InsertD3D12CommandQueue(void *object_key, ID3D12CommandQueueWrapper *command_queue)
		{
			std::lock_guard guard{ s_d3d12_command_queue_mutex };
			s_d3d12_command_queue_manager[object_key] = command_queue;
		}

		static ID3D12CommandQueueWrapper *QueryExistingD3D12CommandQueue(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_command_queue_mutex };
			if (s_d3d12_command_queue_manager.contains(object_key))
			{
				return s_d3d12_command_queue_manager[object_key];
			}
			return nullptr;
		}

		// Helper functions
		REFIID GetRiid() const;

		IUnknown *GetWrappedObject();

		const IUnknown *GetWrappedObject() const;

		template <typename T>
		T *GetWrappedObjectAs()
		{
			return reinterpret_cast<T *>(m_object.GetInterfacePtr());
		}

		template <typename T>
		const T *GetWrappedObjectAs() const
		{
			return reinterpret_cast<const T *>(m_object.GetInterfacePtr());
		}

		uint32_t GetRefCount() const;

		// IUnknown
		HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** object) override;

		ULONG STDMETHODCALLTYPE AddRef() override;

		ULONG STDMETHODCALLTYPE Release() override;

		// ID3D12Object
		HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID guid, UINT* pDataSize, void* pData) override;

		HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID guid, UINT DataSize, const void* pData) override;

		HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID guid, const IUnknown* pData) override;

		HRESULT STDMETHODCALLTYPE SetName(LPCWSTR Name) override;

		// ID3D12DeviceChild
		HRESULT STDMETHODCALLTYPE GetDevice(REFIID riid, void** ppvDevice) override;

		// ID3D12CommandQueue
		void STDMETHODCALLTYPE UpdateTileMappings(
					ID3D12Resource* pResource,
					UINT NumResourceRegions,
					const D3D12_TILED_RESOURCE_COORDINATE* pResourceRegionStartCoordinates,
					const D3D12_TILE_REGION_SIZE* pResourceRegionSizes,
					ID3D12Heap* pHeap,
					UINT NumRanges,
					const D3D12_TILE_RANGE_FLAGS* pRangeFlags,
					const UINT* pHeapRangeStartOffsets,
					const UINT* pRangeTileCounts,
					D3D12_TILE_MAPPING_FLAGS Flags) override;

		void STDMETHODCALLTYPE CopyTileMappings(
			ID3D12Resource* pDstResource,
			const D3D12_TILED_RESOURCE_COORDINATE* pDstRegionStartCoordinate,
			ID3D12Resource* pSrcResource,
			const D3D12_TILED_RESOURCE_COORDINATE* pSrcRegionStartCoordinate,
			const D3D12_TILE_REGION_SIZE* pRegionSize,
			D3D12_TILE_MAPPING_FLAGS Flags) override;

		void STDMETHODCALLTYPE ExecuteCommandLists(
			UINT NumCommandLists,
			ID3D12CommandList* const* ppCommandLists) override;

		void STDMETHODCALLTYPE SetMarker(
			UINT Metadata,
			const void* pData,
			UINT Size) override;

		void STDMETHODCALLTYPE BeginEvent(
			UINT Metadata,
			const void* pData,
			UINT Size) override;

		void STDMETHODCALLTYPE EndEvent() override;

		HRESULT STDMETHODCALLTYPE Signal(
			ID3D12Fence* pFence,
			UINT64 Value) override;

		HRESULT STDMETHODCALLTYPE Wait(
			ID3D12Fence* pFence,
			UINT64 Value) override;

		HRESULT STDMETHODCALLTYPE GetTimestampFrequency(UINT64* pFrequency) override;

		HRESULT STDMETHODCALLTYPE GetClockCalibration(
			UINT64* pGpuTimestamp,
			UINT64* pCpuTimestamp) override;

		D3D12_COMMAND_QUEUE_DESC STDMETHODCALLTYPE GetDesc() override;
	};
}

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