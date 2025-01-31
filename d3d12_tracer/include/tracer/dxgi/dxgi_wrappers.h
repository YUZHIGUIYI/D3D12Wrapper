//
// Created by ZZK on 2024/11/17.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	// New wrapped IDXGIKeyMutex
	struct IDXGIKeyedMutexWrapper final : IDXGIKeyedMutex
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, IDXGIKeyedMutexWrapper *> s_dxgi_keyed_mutex_manager{};
		inline static std::mutex s_dxgi_keyed_mutex_mutex{};

	public:
		IDXGIKeyedMutexWrapper(REFIID riid, IUnknown *object);

		virtual ~IDXGIKeyedMutexWrapper() = default;

		// IDXGIKeyedMutexWrapper manager
		static void InsertDXGIKeyedMutex(void *object_key, IDXGIKeyedMutexWrapper *keyed_mutex)
		{
			std::lock_guard guard{ s_dxgi_keyed_mutex_mutex };
			s_dxgi_keyed_mutex_manager[object_key] = keyed_mutex;
		}

		static IDXGIKeyedMutexWrapper *QueryExistingDXGIKeyedMutex(void *object_key)
		{
			std::lock_guard guard{ s_dxgi_keyed_mutex_mutex };
			if (s_dxgi_keyed_mutex_manager.contains(object_key))
			{
				return s_dxgi_keyed_mutex_manager[object_key];
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

		// IDXGIObject
		HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID Name, UINT DataSize, const void *pData) override;

		HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown) override;

		HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID Name, UINT* pDataSize, void *pData) override;

		HRESULT STDMETHODCALLTYPE GetParent(REFIID riid, void **ppParent) override;

		// IDXGIDeviceSubObject
		HRESULT STDMETHODCALLTYPE GetDevice(REFIID riid, void **ppDevice) override;

		// IDXGIKeyMutex
		HRESULT STDMETHODCALLTYPE AcquireSync(UINT64 Key, DWORD dwMilliseconds) override;

		HRESULT STDMETHODCALLTYPE ReleaseSync(UINT64 Key) override;
	};

	// New wrapped IDXGIDisplayControl
	struct IDXGIDisplayControlWrapper : IDXGIDisplayControl
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, IDXGIDisplayControlWrapper *> s_dxgi_display_control_manager{};
		inline static std::mutex s_dxgi_display_control_mutex{};

	public:
		IDXGIDisplayControlWrapper(REFIID riid, IUnknown *object);

		virtual ~IDXGIDisplayControlWrapper() = default;

		// IDXGIDisplayControlWrapper manager
		static void InsertDXGIDisplayControl(void *object_key, IDXGIDisplayControlWrapper *display_control)
		{
			std::lock_guard guard{ s_dxgi_display_control_mutex };
			s_dxgi_display_control_manager[object_key] = display_control;
		}

		static IDXGIDisplayControlWrapper *QueryExistingDXGIDisplayControl(void *object_key)
		{
			std::lock_guard guard{ s_dxgi_display_control_mutex };
			if (s_dxgi_display_control_manager.contains(object_key))
			{
				return s_dxgi_display_control_manager[object_key];
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

		// IDXGIDisplayControl
		BOOL STDMETHODCALLTYPE IsStereoEnabled() override;

		void STDMETHODCALLTYPE SetStereoEnabled(BOOL enabled) override;
	};

	// New wrapped IDXGIOutputDuplication
	struct IDXGIOutputDuplicationWrapper final : IDXGIOutputDuplication
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, IDXGIOutputDuplicationWrapper *> s_dxgi_output_duplication_manager{};
		inline static std::mutex s_dxgi_output_duplication_mutex{};

	public:
		IDXGIOutputDuplicationWrapper(REFIID riid, IUnknown *object);

		virtual ~IDXGIOutputDuplicationWrapper() = default;

		// IDXGIOutputDuplicationWrapper manager
		static void InsertDXGIOutputDuplication(void *object_key, IDXGIOutputDuplicationWrapper *output_duplication)
		{
			std::lock_guard guard{ s_dxgi_output_duplication_mutex };
			s_dxgi_output_duplication_manager[object_key] = output_duplication;
		}

		static IDXGIOutputDuplicationWrapper *QueryExistingDXGIOutputDuplication(void *object_key)
		{
			std::lock_guard guard{ s_dxgi_output_duplication_mutex };
			if (s_dxgi_output_duplication_manager.contains(object_key))
			{
				return s_dxgi_output_duplication_manager[object_key];
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

		// IDXGIObject
		HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID Name, UINT DataSize, const void *pData) override;

		HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown) override;

		HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID Name, UINT* pDataSize, void *pData) override;

		HRESULT STDMETHODCALLTYPE GetParent(REFIID riid, void **ppParent) override;

		// IDXGIOutputDuplication
		void STDMETHODCALLTYPE GetDesc(DXGI_OUTDUPL_DESC *pDesc) override;

		HRESULT STDMETHODCALLTYPE AcquireNextFrame(UINT TimeoutInMilliseconds, DXGI_OUTDUPL_FRAME_INFO *pFrameInfo, IDXGIResource **ppDesktopResource) override;

		HRESULT STDMETHODCALLTYPE GetFrameDirtyRects(UINT DirtyRectsBufferSize, RECT *pDirtyRectsBuffer, UINT *pDirtyRectsBufferSizeRequired) override;

		HRESULT STDMETHODCALLTYPE GetFrameMoveRects(UINT MoveRectsBufferSize, DXGI_OUTDUPL_MOVE_RECT *pMoveRectBuffer, UINT *pMoveRectsBufferSizeRequired) override;

		HRESULT STDMETHODCALLTYPE GetFramePointerShape(UINT PointerShapeBufferSize, void *pPointerShapeBuffer, UINT *pPointerShapeBufferSizeRequired, DXGI_OUTDUPL_POINTER_SHAPE_INFO *pPointerShapeInfo) override;

		HRESULT STDMETHODCALLTYPE MapDesktopSurface(DXGI_MAPPED_RECT *pLockedRect) override;

		HRESULT STDMETHODCALLTYPE UnMapDesktopSurface() override;

		HRESULT STDMETHODCALLTYPE ReleaseFrame() override;
	};

	// New wrapped IDXGISurface2
	struct IDXGISurface2Wrapper final : IDXGISurface2
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, IDXGISurface2Wrapper *> s_dxgi_surface_manager{};
		inline static std::mutex s_dxgi_surface_mutex{};

	public:
		IDXGISurface2Wrapper(REFIID riid, IUnknown *object);

		virtual ~IDXGISurface2Wrapper() = default;

		// IDXGISurface2Wrapper manager
		static void InsertDXGISurface(void *object_key, IDXGISurface2Wrapper *surface)
		{
			std::lock_guard guard{ s_dxgi_surface_mutex };
			s_dxgi_surface_manager[object_key] = surface;
		}

		static IDXGISurface2Wrapper *QueryExistingDXGISurface(void *object_key)
		{
			std::lock_guard guard{ s_dxgi_surface_mutex };
			if (s_dxgi_surface_manager.contains(object_key))
			{
				return s_dxgi_surface_manager[object_key];
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

		// IDXGIObject
		HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID Name, UINT DataSize, const void *pData) override;

		HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown) override;

		HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID Name, UINT* pDataSize, void *pData) override;

		HRESULT STDMETHODCALLTYPE GetParent(REFIID riid, void **ppParent) override;

		// IDXGIDeviceSubObject
		HRESULT STDMETHODCALLTYPE GetDevice(REFIID riid, void **ppDevice) override;

		// IDXGISurface
		HRESULT STDMETHODCALLTYPE GetDesc(DXGI_SURFACE_DESC *pDesc) override;

		HRESULT STDMETHODCALLTYPE Map(DXGI_MAPPED_RECT *pLockedRect, UINT MapFlags) override;

		HRESULT STDMETHODCALLTYPE Unmap() override;

		// IDXGISurface1
		HRESULT STDMETHODCALLTYPE GetDC(BOOL Discard, HDC* phdc) override;

		HRESULT STDMETHODCALLTYPE ReleaseDC(RECT* pDirtyRect) override;

		// IDXGISurface2
		HRESULT STDMETHODCALLTYPE GetResource(REFIID riid, void **ppParentResource, UINT *pSubresourceIndex) override;
	};

	// New wrapped IDXGIResource1
	struct IDXGIResource1Wrapper final : IDXGIResource1
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, IDXGIResource1Wrapper *> s_dxgi_resource_manager{};
		inline static std::mutex s_dxgi_resource_mutex{};

	public:
		IDXGIResource1Wrapper(REFIID riid, IUnknown *object);

		virtual ~IDXGIResource1Wrapper() = default;

		// IDXGIResource1Wrapper manager
		static void InsertDXGIResource(void *object_key, IDXGIResource1Wrapper *resource)
		{
			std::lock_guard guard{ s_dxgi_resource_mutex };
			s_dxgi_resource_manager[object_key] = resource;
		}

		static IDXGIResource1Wrapper *QueryExistingDXGIResource(void *object_key)
		{
			std::lock_guard guard{ s_dxgi_resource_mutex };
			if (s_dxgi_resource_manager.contains(object_key))
			{
				return s_dxgi_resource_manager[object_key];
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

		// IDXGIObject
		HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID Name, UINT DataSize, const void *pData) override;

		HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown) override;

		HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID Name, UINT* pDataSize, void *pData) override;

		HRESULT STDMETHODCALLTYPE GetParent(REFIID riid, void **ppParent) override;

		// IDXGIDeviceSubObject
		HRESULT STDMETHODCALLTYPE GetDevice(REFIID riid, void **ppDevice) override;

		// IDXGIResource
		HRESULT STDMETHODCALLTYPE GetSharedHandle(HANDLE *pSharedHandle) override;

		HRESULT STDMETHODCALLTYPE GetUsage(DXGI_USAGE *pUsage) override;

		HRESULT STDMETHODCALLTYPE SetEvictionPriority(UINT EvictionPriority) override;

		HRESULT STDMETHODCALLTYPE GetEvictionPriority(UINT *pEvictionPriority) override;

		// IDXGIResource1
		HRESULT STDMETHODCALLTYPE CreateSubresourceSurface(UINT index, IDXGISurface2 **ppSurface) override;

		HRESULT STDMETHODCALLTYPE CreateSharedHandle(const SECURITY_ATTRIBUTES *pAttributes, DWORD dwAccess, LPCWSTR lpName, HANDLE *pHandle) override;
	};

	// New wrapped IDXGIDecodeSwapChain
	struct IDXGIDecodeSwapChainWrapper final : IDXGIDecodeSwapChain
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, IDXGIDecodeSwapChainWrapper *> s_dxgi_decode_swap_chain_manager{};
		inline static std::mutex s_dxgi_decode_swap_chain_mutex{};

	public:
		IDXGIDecodeSwapChainWrapper(REFIID riid, IUnknown *object);

		virtual ~IDXGIDecodeSwapChainWrapper() = default;

		// IDXGIDecodeSwapChainWrapper manager
		static void InsertDXGIDecodeSwapChain(void *object_key, IDXGIDecodeSwapChainWrapper *decode_swap_chain)
		{
			std::lock_guard guard{ s_dxgi_decode_swap_chain_mutex };
			s_dxgi_decode_swap_chain_manager[object_key] = decode_swap_chain;
		}

		static IDXGIDecodeSwapChainWrapper *QueryExistingDXGIDecodeSwapChain(void *object_key)
		{
			std::lock_guard guard{ s_dxgi_decode_swap_chain_mutex };
			if (s_dxgi_decode_swap_chain_manager.contains(object_key))
			{
				return s_dxgi_decode_swap_chain_manager[object_key];
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

		// IDXGIDecodeSwapChain
		HRESULT STDMETHODCALLTYPE PresentBuffer(UINT BufferToPresent, UINT SyncInterval, UINT Flags) override;

		HRESULT STDMETHODCALLTYPE SetSourceRect(const RECT *pRect) override;

		HRESULT STDMETHODCALLTYPE SetTargetRect(const RECT *pRect) override;

		HRESULT STDMETHODCALLTYPE SetDestSize(UINT Width, UINT Height) override;

		HRESULT STDMETHODCALLTYPE GetSourceRect(RECT *pRect) override;

		HRESULT STDMETHODCALLTYPE GetTargetRect(RECT *pRect) override;

		HRESULT STDMETHODCALLTYPE GetDestSize(UINT *pWidth, UINT *pHeight) override;

		HRESULT STDMETHODCALLTYPE SetColorSpace(DXGI_MULTIPLANE_OVERLAY_YCbCr_FLAGS ColorSpace) override;

		DXGI_MULTIPLANE_OVERLAY_YCbCr_FLAGS STDMETHODCALLTYPE GetColorSpace() override;
	};

	// New wrapped IDXGIFactoryMedia
	struct IDXGIFactoryMediaWrapper final : IDXGIFactoryMedia
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, IDXGIFactoryMediaWrapper *> s_dxgi_factory_media_manager{};
		inline static std::mutex s_dxgi_factory_media_mutex{};

	public:
		IDXGIFactoryMediaWrapper(REFIID riid, IUnknown *object);

		virtual ~IDXGIFactoryMediaWrapper() = default;

		// IDXGIFactoryMediaWrapper manager
		static void InsertDXGIFactoryMedia(void *object_key, IDXGIFactoryMediaWrapper *factory_media)
		{
			std::lock_guard guard{ s_dxgi_factory_media_mutex };
			s_dxgi_factory_media_manager[object_key] = factory_media;
		}

		static IDXGIFactoryMediaWrapper *QueryExistingDXGIFactoryMedia(void *object_key)
		{
			std::lock_guard guard{ s_dxgi_factory_media_mutex };
			if (s_dxgi_factory_media_manager.contains(object_key))
			{
				return s_dxgi_factory_media_manager[object_key];
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

		// IDXGIFactoryMedia
		HRESULT STDMETHODCALLTYPE CreateSwapChainForCompositionSurfaceHandle(IUnknown *pDevice, HANDLE hSurface,
																			 const DXGI_SWAP_CHAIN_DESC1 *pDesc,
																			 IDXGIOutput *pRestrictToOutput,
																			 IDXGISwapChain1 **ppSwapChain) override;

		HRESULT STDMETHODCALLTYPE CreateDecodeSwapChainForCompositionSurfaceHandle(IUnknown *pDevice, HANDLE hSurface, DXGI_DECODE_SWAP_CHAIN_DESC *pDesc,
																					IDXGIResource *pYuvDecodeBuffers, IDXGIOutput *pRestrictToOutput, IDXGIDecodeSwapChain **ppSwapChain) override;
	};

	// New wrapped IDXGISwapChainMedia
	struct IDXGISwapChainMediaWrapper final : IDXGISwapChainMedia
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, IDXGISwapChainMediaWrapper *> s_dxgi_swap_chain_media_manager{};
		inline static std::mutex s_dxgi_swap_chain_media_mutex{};

	public:
		IDXGISwapChainMediaWrapper(REFIID riid, IUnknown *object);

		virtual ~IDXGISwapChainMediaWrapper() = default;

		// IDXGISwapChainMediaWrapper manager
		static void InsertDXGISwapChainMedia(void *object_key, IDXGISwapChainMediaWrapper *swap_chain_media)
		{
			std::lock_guard guard{ s_dxgi_swap_chain_media_mutex };
			s_dxgi_swap_chain_media_manager[object_key] = swap_chain_media;
		}

		static IDXGISwapChainMediaWrapper *QueryExistingDXGISwapChainMedia(void *object_key)
		{
			std::lock_guard guard{ s_dxgi_swap_chain_media_mutex };
			if (s_dxgi_swap_chain_media_manager.contains(object_key))
			{
				return s_dxgi_swap_chain_media_manager[object_key];
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

		// IDXGISwapChainMedia
		HRESULT STDMETHODCALLTYPE GetFrameStatisticsMedia(DXGI_FRAME_STATISTICS_MEDIA *pStats) override;

		HRESULT STDMETHODCALLTYPE SetPresentDuration(UINT Duration) override;

		HRESULT STDMETHODCALLTYPE CheckPresentDurationSupport(UINT DesiredPresentDuration, UINT *pClosestSmallerPresentDuration, UINT *pClosestLargerPresentDuration) override;
	};

	// New wrapped IDXGISwapChain4
	struct IDXGISwapChain4Wrapper final : IDXGISwapChain4
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, IDXGISwapChain4Wrapper *> s_dxgi_swap_chain_manager{};
		inline static std::mutex s_dxgi_swap_chain_mutex{};

	public:
		IDXGISwapChain4Wrapper(REFIID riid, IUnknown *object);

		virtual ~IDXGISwapChain4Wrapper() = default;

		// IDXGISwapChain4Wrapper manager
		static void InsertDXGISwapChain(void *object_key, IDXGISwapChain4Wrapper *adapter)
		{
			std::lock_guard guard{ s_dxgi_swap_chain_mutex };
			s_dxgi_swap_chain_manager[object_key] = adapter;
		}

		static IDXGISwapChain4Wrapper *QueryExistingDXGISwapChain(void *object_key)
		{
			std::lock_guard guard{ s_dxgi_swap_chain_mutex };
			if (s_dxgi_swap_chain_manager.contains(object_key))
			{
				return s_dxgi_swap_chain_manager[object_key];
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

		// IDXGIObject
		HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID Name, UINT DataSize, const void *pData) override;

		HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown) override;

		HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID Name, UINT* pDataSize, void *pData) override;

		HRESULT STDMETHODCALLTYPE GetParent(REFIID riid, void **ppParent) override;

		// IDXGIDeviceSubObject
		HRESULT STDMETHODCALLTYPE GetDevice(REFIID riid, void **ppDevice) override;

		// IDXGISwapChain
		HRESULT STDMETHODCALLTYPE Present(UINT SyncInterval, UINT Flags) override;

		HRESULT STDMETHODCALLTYPE GetBuffer(UINT Buffer, REFIID riid, void **ppSurface) override;

		HRESULT STDMETHODCALLTYPE SetFullscreenState(BOOL Fullscreen, IDXGIOutput *pTarget) override;

		HRESULT STDMETHODCALLTYPE GetFullscreenState(BOOL *pFullscreen, IDXGIOutput **ppTarget) override;

		HRESULT STDMETHODCALLTYPE GetDesc(DXGI_SWAP_CHAIN_DESC *pDesc) override;

		HRESULT STDMETHODCALLTYPE ResizeBuffers(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) override;

		HRESULT STDMETHODCALLTYPE ResizeTarget(const DXGI_MODE_DESC *pNewTargetParameters) override;

		HRESULT STDMETHODCALLTYPE GetContainingOutput(IDXGIOutput **ppOutput) override;

		HRESULT STDMETHODCALLTYPE GetFrameStatistics(DXGI_FRAME_STATISTICS *pStats) override;

		HRESULT STDMETHODCALLTYPE GetLastPresentCount(UINT *pLastPresentCount) override;

		// IDXGISwapChain1
		HRESULT STDMETHODCALLTYPE GetDesc1(DXGI_SWAP_CHAIN_DESC1 *pDesc) override;

		HRESULT STDMETHODCALLTYPE GetFullscreenDesc(DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pDesc) override;

		HRESULT STDMETHODCALLTYPE GetHwnd(HWND *pHwnd) override;

		HRESULT STDMETHODCALLTYPE GetCoreWindow(REFIID refiid, void **ppUnk) override;

		HRESULT STDMETHODCALLTYPE Present1(UINT SyncInterval, UINT PresentFlags, const DXGI_PRESENT_PARAMETERS *pPresentParameters) override;

		BOOL STDMETHODCALLTYPE IsTemporaryMonoSupported() override;

		HRESULT STDMETHODCALLTYPE GetRestrictToOutput(IDXGIOutput **ppRestrictToOutput) override;

		HRESULT STDMETHODCALLTYPE SetBackgroundColor(const DXGI_RGBA *pColor) override;

		HRESULT STDMETHODCALLTYPE GetBackgroundColor(DXGI_RGBA *pColor) override;

		HRESULT STDMETHODCALLTYPE SetRotation(DXGI_MODE_ROTATION Rotation) override;

		HRESULT STDMETHODCALLTYPE GetRotation(DXGI_MODE_ROTATION *pRotation) override;

		// IDXGISwapChain2
		HRESULT STDMETHODCALLTYPE SetSourceSize(UINT Width, UINT Height) override;

		HRESULT STDMETHODCALLTYPE GetSourceSize(UINT *pWidth, UINT *pHeight) override;

		HRESULT STDMETHODCALLTYPE SetMaximumFrameLatency(UINT MaxLatency) override;

		HRESULT STDMETHODCALLTYPE GetMaximumFrameLatency(UINT *pMaxLatency) override;

		HANDLE STDMETHODCALLTYPE GetFrameLatencyWaitableObject() override;

		HRESULT STDMETHODCALLTYPE SetMatrixTransform(const DXGI_MATRIX_3X2_F *pMatrix) override;

		HRESULT STDMETHODCALLTYPE GetMatrixTransform(DXGI_MATRIX_3X2_F *pMatrix) override;

		// IDXGISwapChain3
		UINT STDMETHODCALLTYPE GetCurrentBackBufferIndex() override;

		HRESULT STDMETHODCALLTYPE CheckColorSpaceSupport(DXGI_COLOR_SPACE_TYPE ColorSpace, UINT *pColorSpaceSupport) override;

		HRESULT STDMETHODCALLTYPE SetColorSpace1(DXGI_COLOR_SPACE_TYPE ColorSpace) override;

		HRESULT STDMETHODCALLTYPE ResizeBuffers1(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT Format,
														UINT SwapChainFlags, const UINT *pCreationNodeMask, IUnknown *const *ppPresentQueue) override;

		// IDXGISwapChain4
		HRESULT STDMETHODCALLTYPE SetHDRMetaData(DXGI_HDR_METADATA_TYPE Type, UINT Size, void *pMetaData) override;
	};

	// New wrapped IDXGIDevice4
	struct IDXGIDevice4Wrapper final : IDXGIDevice4
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, IDXGIDevice4Wrapper *> s_dxgi_device_manager{};
		inline static std::mutex s_dxgi_device_mutex{};

	public:
		IDXGIDevice4Wrapper(REFIID riid, IUnknown *object);

		virtual ~IDXGIDevice4Wrapper() = default;

		// IDXGIDevice4Wrapper manager
		static void InsertDXGIDevice(void *object_key, IDXGIDevice4Wrapper *adapter)
		{
			std::lock_guard guard{ s_dxgi_device_mutex };
			s_dxgi_device_manager[object_key] = adapter;
		}

		static IDXGIDevice4Wrapper *QueryExistingDXGIDevice(void *object_key)
		{
			std::lock_guard guard{ s_dxgi_device_mutex };
			if (s_dxgi_device_manager.contains(object_key))
			{
				return s_dxgi_device_manager[object_key];
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

		// IDXGIObject
		HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID Name, UINT DataSize, const void *pData) override;

		HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown) override;

		HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID Name, UINT* pDataSize, void *pData) override;

		HRESULT STDMETHODCALLTYPE GetParent(REFIID riid, void **ppParent) override;

		// IDXGIDevice
		HRESULT STDMETHODCALLTYPE GetAdapter(IDXGIAdapter **pAdapter) override;

		HRESULT STDMETHODCALLTYPE CreateSurface(const DXGI_SURFACE_DESC *pDesc, UINT NumSurfaces, DXGI_USAGE Usage, const DXGI_SHARED_RESOURCE *pSharedResource, IDXGISurface **ppSurface) override;

		HRESULT STDMETHODCALLTYPE QueryResourceResidency(IUnknown *const *ppResources, DXGI_RESIDENCY *pResidencyStatus, UINT NumResources) override;

		HRESULT STDMETHODCALLTYPE SetGPUThreadPriority(INT Priority) override;

		HRESULT STDMETHODCALLTYPE GetGPUThreadPriority(INT *pPriority) override;

		// IDXGIDevice1
		HRESULT STDMETHODCALLTYPE SetMaximumFrameLatency(UINT MaxLatency) override;

		HRESULT STDMETHODCALLTYPE GetMaximumFrameLatency(UINT *pMaxLatency) override;

		// IDXGIDevice2
		HRESULT STDMETHODCALLTYPE OfferResources(UINT NumResources, IDXGIResource *const *ppResources, DXGI_OFFER_RESOURCE_PRIORITY Priority) override;

		HRESULT STDMETHODCALLTYPE ReclaimResources(UINT NumResources, IDXGIResource *const *ppResources, BOOL *pDiscarded) override;

		HRESULT STDMETHODCALLTYPE EnqueueSetEvent(HANDLE hEvent) override;

		// IDXGIDevice3
		void STDMETHODCALLTYPE Trim() override;

		// IDXGIDevice4
		HRESULT STDMETHODCALLTYPE OfferResources1(UINT NumResources, IDXGIResource *const *ppResources,
												  DXGI_OFFER_RESOURCE_PRIORITY Priority, UINT Flags) override;

		HRESULT STDMETHODCALLTYPE ReclaimResources1(UINT NumResources, IDXGIResource *const *ppResources, DXGI_RECLAIM_RESOURCE_RESULTS *pResults) override;
	};

	// New wrapped IDXGIAdapter4
	struct IDXGIAdapter4Wrapper : IDXGIAdapter4
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, IDXGIAdapter4Wrapper *> s_dxgi_adapter_manager{};
		inline static std::mutex s_dxgi_adapter_mutex{};

	public:
		IDXGIAdapter4Wrapper(REFIID riid, IUnknown *object);

		virtual ~IDXGIAdapter4Wrapper() = default;

		// IDXGIAdapter4Wrapper manager
		static void InsertDXGIAdapter(void *object_key, IDXGIAdapter4Wrapper *adapter)
		{
			std::lock_guard guard{ s_dxgi_adapter_mutex };
			s_dxgi_adapter_manager[object_key] = adapter;
		}

		static IDXGIAdapter4Wrapper *QueryExistingDXGIAdapter(void *object_key)
		{
			std::lock_guard guard{ s_dxgi_adapter_mutex };
			if (s_dxgi_adapter_manager.contains(object_key))
			{
				return s_dxgi_adapter_manager[object_key];
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

		// IDXGIObject
		HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID Name, UINT DataSize, const void *pData) override;

		HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown) override;

		HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID Name, UINT* pDataSize, void *pData) override;

		HRESULT STDMETHODCALLTYPE GetParent(REFIID riid, void **ppParent) override;

		// IDXGIAdapter
		HRESULT STDMETHODCALLTYPE EnumOutputs(UINT Output, IDXGIOutput **ppOutput) override;

		HRESULT STDMETHODCALLTYPE GetDesc(DXGI_ADAPTER_DESC *pDesc) override;

		HRESULT STDMETHODCALLTYPE CheckInterfaceSupport(REFGUID InterfaceName, LARGE_INTEGER *pUMDVersion) override;

		// IDXGIAdapter1
		HRESULT STDMETHODCALLTYPE GetDesc1(DXGI_ADAPTER_DESC1 *pDesc) override;

		// IDXGIAdapter2
		HRESULT STDMETHODCALLTYPE GetDesc2(DXGI_ADAPTER_DESC2 *pDesc) override;

		// IDXGIAdapter3
		HRESULT STDMETHODCALLTYPE RegisterHardwareContentProtectionTeardownStatusEvent(HANDLE hEvent, DWORD *pdwCookie) override;

		void STDMETHODCALLTYPE UnregisterHardwareContentProtectionTeardownStatus(DWORD dwCookie) override;

		HRESULT STDMETHODCALLTYPE QueryVideoMemoryInfo(UINT NodeIndex, DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup,
																DXGI_QUERY_VIDEO_MEMORY_INFO *pVideoMemoryInfo) override;

		HRESULT STDMETHODCALLTYPE SetVideoMemoryReservation(UINT NodeIndex, DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup, UINT64 Reservation) override;

		HRESULT STDMETHODCALLTYPE RegisterVideoMemoryBudgetChangeNotificationEvent(HANDLE hEvent, DWORD *pdwCookie) override;

		void STDMETHODCALLTYPE UnregisterVideoMemoryBudgetChangeNotification(DWORD dwCookie) override;

		// IDXGIAdapter4
		HRESULT STDMETHODCALLTYPE GetDesc3(DXGI_ADAPTER_DESC3 *pDesc) override;
	};

	// New wrapped IDXGIOutput6
	struct IDXGIOutput6Wrapper final : IDXGIOutput6
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, IDXGIOutput6Wrapper *> s_dxgi_output_manager{};
		inline static std::mutex s_dxgi_output_mutex{};

	public:
		IDXGIOutput6Wrapper(REFIID riid, IUnknown *object);

		~IDXGIOutput6Wrapper() = default;

		// IDXGIOutput6Wrapper manager
		static void InsertDXGIOutput(void *object_key, IDXGIOutput6Wrapper *output)
		{
			std::lock_guard guard{ s_dxgi_output_mutex };
			s_dxgi_output_manager[object_key] = output;
		}

		static IDXGIOutput6Wrapper *QueryExistingDXGIOutput(void *object_key)
		{
			std::lock_guard guard{ s_dxgi_output_mutex };
			if (s_dxgi_output_manager.contains(object_key))
			{
				return s_dxgi_output_manager[object_key];
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

		// IDXGIObject
		HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID Name, UINT DataSize, const void *pData) override;

		HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown) override;

		HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID Name, UINT* pDataSize, void *pData) override;

		HRESULT STDMETHODCALLTYPE GetParent(REFIID riid, void **ppParent) override;

		// IDXGIOutput
		HRESULT STDMETHODCALLTYPE GetDesc(DXGI_OUTPUT_DESC *pDesc) override;

		HRESULT STDMETHODCALLTYPE GetDisplayModeList(DXGI_FORMAT EnumFormat, UINT Flags, UINT *pNumModes, DXGI_MODE_DESC *pDesc) override;

		HRESULT STDMETHODCALLTYPE FindClosestMatchingMode(const DXGI_MODE_DESC *pModeToMatch, DXGI_MODE_DESC *pClosestMatch, IUnknown *pConcernedDevice) override;

		HRESULT STDMETHODCALLTYPE WaitForVBlank() override;

		HRESULT STDMETHODCALLTYPE TakeOwnership(IUnknown *pDevice, BOOL Exclusive) override;

		void STDMETHODCALLTYPE ReleaseOwnership() override;

		HRESULT STDMETHODCALLTYPE GetGammaControlCapabilities(DXGI_GAMMA_CONTROL_CAPABILITIES *pGammaCaps) override;

		HRESULT STDMETHODCALLTYPE SetGammaControl(const DXGI_GAMMA_CONTROL *pArray) override;

		HRESULT STDMETHODCALLTYPE GetGammaControl(DXGI_GAMMA_CONTROL *pArray) override;

		HRESULT STDMETHODCALLTYPE SetDisplaySurface(IDXGISurface *pScanoutSurface) override;

		HRESULT STDMETHODCALLTYPE GetDisplaySurfaceData(IDXGISurface *pDestination) override;

		HRESULT STDMETHODCALLTYPE GetFrameStatistics(DXGI_FRAME_STATISTICS *pStats) override;

		// IDXGIOutput1
		HRESULT STDMETHODCALLTYPE GetDisplayModeList1(DXGI_FORMAT EnumFormat, UINT Flags, UINT *pNumModes, DXGI_MODE_DESC1 *pDesc) override;

		HRESULT STDMETHODCALLTYPE FindClosestMatchingMode1(const DXGI_MODE_DESC1 *pModeToMatch, DXGI_MODE_DESC1 *pClosestMatch, IUnknown *pConcernedDevice) override;

		HRESULT STDMETHODCALLTYPE GetDisplaySurfaceData1(IDXGIResource *pDestination) override;

		HRESULT STDMETHODCALLTYPE DuplicateOutput(IUnknown *pDevice, IDXGIOutputDuplication **ppOutputDuplication) override;

		// IDXGIOutput2
		BOOL STDMETHODCALLTYPE SupportsOverlays() override;

		// IDXGIOutput3
		HRESULT STDMETHODCALLTYPE CheckOverlaySupport(DXGI_FORMAT EnumFormat, IUnknown *pConcernedDevice, UINT *pFlags) override;

		// IDXGIOutput4
		HRESULT STDMETHODCALLTYPE CheckOverlayColorSpaceSupport(DXGI_FORMAT Format, DXGI_COLOR_SPACE_TYPE ColorSpace, IUnknown *pConcernedDevice, UINT *pFlags) override;

		// IDXGIOutput5
		HRESULT STDMETHODCALLTYPE DuplicateOutput1(IUnknown *pDevice, UINT Flags, UINT SupportedFormatsCount,
													const DXGI_FORMAT *pSupportedFormats, IDXGIOutputDuplication **ppOutputDuplication) override;

		// IDXGIOutput6
		HRESULT STDMETHODCALLTYPE GetDesc1(DXGI_OUTPUT_DESC1 *pDesc) override;

		HRESULT STDMETHODCALLTYPE CheckHardwareCompositionSupport(UINT *pFlags) override;
	};

	// New wrapped IDXGIFactory7
	struct IDXGIFactory7Wrapper final : IDXGIFactory7
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, IDXGIFactory7Wrapper *> s_dxgi_factory_manager{};
		inline static std::mutex s_dxgi_factory_mutex{};

	public:
		IDXGIFactory7Wrapper(REFIID riid, IUnknown *object);

		~IDXGIFactory7Wrapper() = default;

		// IDXGIFactory7Wrapper manager
		static void InsertDXGIFactory(void *object_key, IDXGIFactory7Wrapper *factory)
		{
			std::lock_guard guard{ s_dxgi_factory_mutex };
			s_dxgi_factory_manager[object_key] = factory;
		}

		static IDXGIFactory7Wrapper *QueryExistingDXGIFactory(void *object_key)
		{
			std::lock_guard guard{ s_dxgi_factory_mutex };
			if (s_dxgi_factory_manager.contains(object_key))
			{
				return s_dxgi_factory_manager[object_key];
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

		// IDXGIObject
		HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID Name, UINT DataSize, const void *pData) override;

		HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown) override;

		HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID Name, UINT* pDataSize, void *pData) override;

		HRESULT STDMETHODCALLTYPE GetParent(REFIID riid, void **ppParent) override;

		// IDXGIFactory
		HRESULT STDMETHODCALLTYPE EnumAdapters(UINT Adapter, IDXGIAdapter **ppAdapter) override;

		HRESULT STDMETHODCALLTYPE MakeWindowAssociation(HWND WindowHandle, UINT Flags) override;

		HRESULT STDMETHODCALLTYPE GetWindowAssociation(HWND *pWindowHandle) override;

		HRESULT STDMETHODCALLTYPE CreateSwapChain(IUnknown *pDevice, DXGI_SWAP_CHAIN_DESC *pDesc, IDXGISwapChain **ppSwapChain) override;

		HRESULT STDMETHODCALLTYPE CreateSoftwareAdapter(HMODULE Module, IDXGIAdapter **ppAdapter) override;

		// IDXGIFactory1
		HRESULT STDMETHODCALLTYPE EnumAdapters1(UINT Adapter, IDXGIAdapter1 **ppAdapter) override;

		BOOL STDMETHODCALLTYPE IsCurrent() override;

		// IDXGIFactory2
		BOOL STDMETHODCALLTYPE IsWindowedStereoEnabled() override;

		HRESULT STDMETHODCALLTYPE CreateSwapChainForHwnd(IUnknown *pDevice, HWND hWnd, const DXGI_SWAP_CHAIN_DESC1 *pDesc,
																const DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pFullscreenDesc, IDXGIOutput *pRestrictToOutput, IDXGISwapChain1 **ppSwapChain) override;

		HRESULT STDMETHODCALLTYPE CreateSwapChainForCoreWindow(IUnknown *pDevice, IUnknown *pWindow, const DXGI_SWAP_CHAIN_DESC1 *pDesc,
																	IDXGIOutput* pRestrictToOutput, IDXGISwapChain1 **ppSwapChain) override;

		HRESULT STDMETHODCALLTYPE GetSharedResourceAdapterLuid(HANDLE hResource, LUID *pLuid) override;

		HRESULT STDMETHODCALLTYPE RegisterStereoStatusWindow(HWND WindowHandle, UINT wMsg, DWORD *pdwCookie) override;

		HRESULT STDMETHODCALLTYPE RegisterStereoStatusEvent(HANDLE hEvent, DWORD *pdwCookie) override;

		void STDMETHODCALLTYPE UnregisterStereoStatus(DWORD dwCookie) override;

		HRESULT STDMETHODCALLTYPE RegisterOcclusionStatusWindow(HWND WindowHandle, UINT wMsg, DWORD *pdwCookie) override;

		HRESULT STDMETHODCALLTYPE RegisterOcclusionStatusEvent(HANDLE hEvent, DWORD *pdwCookie) override;

		void STDMETHODCALLTYPE UnregisterOcclusionStatus(DWORD dwCookie) override;

		HRESULT STDMETHODCALLTYPE CreateSwapChainForComposition(IUnknown *pDevice, const DXGI_SWAP_CHAIN_DESC1 *pDesc,
																		IDXGIOutput *pRestrictToOutput, IDXGISwapChain1 **ppSwapChain) override;

		// IDXGIFactory3
		virtual UINT STDMETHODCALLTYPE GetCreationFlags();

		// IDXGIFactory4
		HRESULT STDMETHODCALLTYPE EnumAdapterByLuid(LUID AdapterLuid, REFIID riid, void **ppvAdapter) override;

		HRESULT STDMETHODCALLTYPE EnumWarpAdapter(REFIID riid, void **ppvAdapter) override;

		// IDXGIFactory5
		HRESULT STDMETHODCALLTYPE CheckFeatureSupport(DXGI_FEATURE Feature, void *pFeatureSupportData, UINT FeatureSupportDataSize) override;

		// IDXGIFactory6
		HRESULT STDMETHODCALLTYPE EnumAdapterByGpuPreference(UINT Adapter, DXGI_GPU_PREFERENCE GpuPreference, REFIID riid, void **ppvAdapter) override;

		// IDXGIFactory7
		HRESULT STDMETHODCALLTYPE RegisterAdaptersChangedEvent(HANDLE hEvent, DWORD *pdwCookie) override;

		HRESULT STDMETHODCALLTYPE UnregisterAdaptersChangedEvent(DWORD dwCookie) override;
	};
}
