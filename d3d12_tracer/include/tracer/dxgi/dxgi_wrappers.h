//
// Created by ZZK on 2024/11/17.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

// namespace gfxshim
// {
	// Wrap IDXGIObject
	struct IDXGIObjectWrapper : IUnknownWrapper
	{
		IDXGIObjectWrapper(REFIID riid, IUnknown *object);

		~IDXGIObjectWrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID Name, UINT DataSize, const void *pData);

		virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown);

		virtual HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID Name, UINT* pDataSize, void *pData);

		virtual HRESULT STDMETHODCALLTYPE GetParent(REFIID riid, void **ppParent);
	};

	// Wrap IDXGIDeviceSubObject
	struct IDXGIDeviceSubObjectWrapper : IDXGIObjectWrapper
	{
		IDXGIDeviceSubObjectWrapper(REFIID riid, IUnknown *object);

		~IDXGIDeviceSubObjectWrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE GetDevice(REFIID riid, void **ppDevice);
	};

	// Wrap IDXGIResource
	struct IDXGIResourceWrapper : IDXGIDeviceSubObjectWrapper
	{
		IDXGIResourceWrapper(REFIID riid, IUnknown *object);

		~IDXGIResourceWrapper() override;

		virtual HRESULT STDMETHODCALLTYPE GetSharedHandle(HANDLE *pSharedHandle);

		virtual HRESULT STDMETHODCALLTYPE GetUsage(DXGI_USAGE *pUsage);

		virtual HRESULT STDMETHODCALLTYPE SetEvictionPriority(UINT EvictionPriority);

		virtual HRESULT STDMETHODCALLTYPE GetEvictionPriority(UINT *pEvictionPriority);
	};

	// Wrap IDXGIKeyMutex
	struct IDXGIKeyedMutexWrapper : IDXGIDeviceSubObjectWrapper
	{
		IDXGIKeyedMutexWrapper(REFIID riid, IUnknown *object);

		~IDXGIKeyedMutexWrapper() override;

		virtual HRESULT STDMETHODCALLTYPE AcquireSync(UINT64 Key, DWORD dwMilliseconds);

		virtual HRESULT STDMETHODCALLTYPE ReleaseSync(UINT64 Key);
	};

	// Wrap IDXGISurface
	struct IDXGISurfaceWrapper : IDXGIDeviceSubObjectWrapper
	{
		IDXGISurfaceWrapper(REFIID riid, IUnknown *object);

		~IDXGISurfaceWrapper() override;

		virtual HRESULT STDMETHODCALLTYPE GetDesc(DXGI_SURFACE_DESC *pDesc);

		virtual HRESULT STDMETHODCALLTYPE Map(DXGI_MAPPED_RECT *pLockedRect, UINT MapFlags);

		virtual HRESULT STDMETHODCALLTYPE Unmap();
	};

	// Wrap IDXGISurface1
	struct IDXGISurface1Wrapper : IDXGISurfaceWrapper
	{
		IDXGISurface1Wrapper(REFIID riid, IUnknown *object);

		~IDXGISurface1Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE GetDC(BOOL Discard, HDC* phdc);

		virtual HRESULT STDMETHODCALLTYPE ReleaseDC(RECT* pDirtyRect);
	};

	// Wrap IDXGIAdapter
	struct IDXGIAdapterWrapper : IDXGIObjectWrapper
	{
		IDXGIAdapterWrapper(REFIID riid, IUnknown *object);

		~IDXGIAdapterWrapper() override;

		virtual HRESULT STDMETHODCALLTYPE EnumOutputs(UINT Output, IDXGIOutput **ppOutput);

		virtual HRESULT STDMETHODCALLTYPE GetDesc(DXGI_ADAPTER_DESC *pDesc);

		virtual HRESULT STDMETHODCALLTYPE CheckInterfaceSupport(REFGUID InterfaceName, LARGE_INTEGER *pUMDVersion);
	};

	// Wrap IDXGIOutput
	struct IDXGIOutputWrapper : IDXGIObjectWrapper
	{
		IDXGIOutputWrapper(REFIID riid, IUnknown *object);

		~IDXGIOutputWrapper() override;

		virtual HRESULT STDMETHODCALLTYPE GetDesc(DXGI_OUTPUT_DESC *pDesc);

		virtual HRESULT STDMETHODCALLTYPE GetDisplayModeList(DXGI_FORMAT EnumFormat, UINT Flags, UINT *pNumModes, DXGI_MODE_DESC *pDesc);

		virtual HRESULT STDMETHODCALLTYPE FindClosestMatchingMode(const DXGI_MODE_DESC *pModeToMatch, DXGI_MODE_DESC *pClosestMatch, IUnknown *pConcernedDevice);

		virtual HRESULT STDMETHODCALLTYPE WaitForVBlank();

		virtual HRESULT STDMETHODCALLTYPE TakeOwnership(IUnknown *pDevice, BOOL Exclusive);

		virtual void STDMETHODCALLTYPE ReleaseOwnership();

		virtual HRESULT STDMETHODCALLTYPE GetGammaControlCapabilities(DXGI_GAMMA_CONTROL_CAPABILITIES *pGammaCaps);

		virtual HRESULT STDMETHODCALLTYPE SetGammaControl(const DXGI_GAMMA_CONTROL *pArray);

		virtual HRESULT STDMETHODCALLTYPE GetGammaControl(DXGI_GAMMA_CONTROL *pArray);

		virtual HRESULT STDMETHODCALLTYPE SetDisplaySurface(IDXGISurface *pScanoutSurface);

		virtual HRESULT STDMETHODCALLTYPE GetDisplaySurfaceData(IDXGISurface *pDestination);

		virtual HRESULT STDMETHODCALLTYPE GetFrameStatistics(DXGI_FRAME_STATISTICS *pStats);
	};

	// Wrap IDXGISwapChain
	struct IDXGISwapChainWrapper : IDXGIDeviceSubObjectWrapper
	{
		IDXGISwapChainWrapper(REFIID riid, IUnknown *object);

		~IDXGISwapChainWrapper() override;

		virtual HRESULT STDMETHODCALLTYPE Present(UINT SyncInterval, UINT Flags);

		virtual HRESULT STDMETHODCALLTYPE GetBuffer(UINT Buffer, REFIID riid, void **ppSurface);

		virtual HRESULT STDMETHODCALLTYPE SetFullscreenState(BOOL Fullscreen, IDXGIOutput *pTarget);

		virtual HRESULT STDMETHODCALLTYPE GetFullscreenState(BOOL *pFullscreen, IDXGIOutput **ppTarget);

		virtual HRESULT STDMETHODCALLTYPE GetDesc(DXGI_SWAP_CHAIN_DESC *pDesc);

		virtual HRESULT STDMETHODCALLTYPE ResizeBuffers(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

		virtual HRESULT STDMETHODCALLTYPE ResizeTarget(const DXGI_MODE_DESC *pNewTargetParameters);

		virtual HRESULT STDMETHODCALLTYPE GetContainingOutput(IDXGIOutput **ppOutput);

		virtual HRESULT STDMETHODCALLTYPE GetFrameStatistics(DXGI_FRAME_STATISTICS *pStats);

		virtual HRESULT STDMETHODCALLTYPE GetLastPresentCount(UINT *pLastPresentCount);
	};

	// Wrap IDXGIFactory
	struct IDXGIFactoryWrapper : IDXGIObjectWrapper
	{
		inline static std::unordered_map<void *, IDXGIFactoryWrapper *> s_dxgi_factory_manager{};

		static void InsertDXGIFactory(void *object_key, IDXGIFactoryWrapper *factory) {
			s_dxgi_factory_manager[object_key] = factory;
		}

		static IDXGIFactoryWrapper *QueryExistingDXGIFactory(void *object_key) {
			if (s_dxgi_factory_manager.contains(object_key)) {
				return s_dxgi_factory_manager[object_key];
			}
			return nullptr;
		}

		IDXGIFactoryWrapper(REFIID riid, IUnknown *object);

		~IDXGIFactoryWrapper() override;

		virtual HRESULT STDMETHODCALLTYPE EnumAdapters(UINT Adapter, IDXGIAdapter **ppAdapter);

		virtual HRESULT STDMETHODCALLTYPE MakeWindowAssociation(HWND WindowHandle, UINT Flags);

		virtual HRESULT STDMETHODCALLTYPE GetWindowAssociation(HWND *pWindowHandle);

		virtual HRESULT STDMETHODCALLTYPE CreateSwapChain(IUnknown *pDevice, DXGI_SWAP_CHAIN_DESC *pDesc, IDXGISwapChain **ppSwapChain);

		virtual HRESULT STDMETHODCALLTYPE CreateSoftwareAdapter(HMODULE Module, IDXGIAdapter **ppAdapter);
	};

	// Wrap IDXGIDevice
	struct IDXGIDeviceWrapper : IDXGIObjectWrapper
	{
		IDXGIDeviceWrapper(REFIID riid, IUnknown *object);

		~IDXGIDeviceWrapper() override;

		virtual HRESULT STDMETHODCALLTYPE GetAdapter(IDXGIAdapter **pAdapter);

		virtual HRESULT STDMETHODCALLTYPE CreateSurface(const DXGI_SURFACE_DESC *pDesc, UINT NumSurfaces, DXGI_USAGE Usage, const DXGI_SHARED_RESOURCE *pSharedResource, IDXGISurface **ppSurface);

		virtual HRESULT STDMETHODCALLTYPE QueryResourceResidency(IUnknown *const *ppResources, DXGI_RESIDENCY *pResidencyStatus, UINT NumResources);

		virtual HRESULT STDMETHODCALLTYPE SetGPUThreadPriority(INT Priority);

		virtual HRESULT STDMETHODCALLTYPE GetGPUThreadPriority(INT *pPriority);
	};

	// Wrap IDXGIFactory1
	struct IDXGIFactory1Wrapper : IDXGIFactoryWrapper
	{
		IDXGIFactory1Wrapper(REFIID riid, IUnknown *object);

		~IDXGIFactory1Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE EnumAdapters1(UINT Adapter, IDXGIAdapter1 **ppAdapter);

		virtual BOOL STDMETHODCALLTYPE IsCurrent();
	};

	// Wrap IDXGIAdapter1
	struct IDXGIAdapter1Wrapper : IDXGIAdapterWrapper
	{
		IDXGIAdapter1Wrapper(REFIID riid, IUnknown *object);

		~IDXGIAdapter1Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE GetDesc1(DXGI_ADAPTER_DESC1 *pDesc);
	};

	// Wrap IDXGIDevice1
	struct IDXGIDevice1Wrapper : IDXGIDeviceWrapper
	{
		IDXGIDevice1Wrapper(REFIID riid, IUnknown *object);

		~IDXGIDevice1Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE SetMaximumFrameLatency(UINT MaxLatency);

		virtual HRESULT STDMETHODCALLTYPE GetMaximumFrameLatency(UINT *pMaxLatency);
	};

	// Wrap IDXGIDisplayControl
	struct IDXGIDisplayControlWrapper : IUnknownWrapper
	{
		IDXGIDisplayControlWrapper(REFIID riid, IUnknown *object);

		~IDXGIDisplayControlWrapper() override;

		virtual BOOL STDMETHODCALLTYPE IsStereoEnabled();

		virtual void STDMETHODCALLTYPE SetStereoEnabled(BOOL enabled);
	};

	// Wrap IDXGIOutputDuplication
	struct IDXGIOutputDuplicationWrapper : IDXGIObjectWrapper
	{
		IDXGIOutputDuplicationWrapper(REFIID riid, IUnknown *object);

		~IDXGIOutputDuplicationWrapper() override;

		virtual void STDMETHODCALLTYPE GetDesc(DXGI_OUTDUPL_DESC *pDesc);

		virtual HRESULT STDMETHODCALLTYPE AcquireNextFrame(UINT TimeoutInMilliseconds, DXGI_OUTDUPL_FRAME_INFO *pFrameInfo, IDXGIResource **ppDesktopResource);

		virtual HRESULT STDMETHODCALLTYPE GetFrameDirtyRects(UINT DirtyRectsBufferSize, RECT *pDirtyRectsBuffer, UINT *pDirtyRectsBufferSizeRequired);

		virtual HRESULT STDMETHODCALLTYPE GetFrameMoveRects(UINT MoveRectsBufferSize, DXGI_OUTDUPL_MOVE_RECT *pMoveRectBuffer, UINT *pMoveRectsBufferSizeRequired);

		virtual HRESULT STDMETHODCALLTYPE GetFramePointerShape(UINT PointerShapeBufferSize, void *pPointerShapeBuffer, UINT *pPointerShapeBufferSizeRequired, DXGI_OUTDUPL_POINTER_SHAPE_INFO *pPointerShapeInfo);

		virtual HRESULT STDMETHODCALLTYPE MapDesktopSurface(DXGI_MAPPED_RECT *pLockedRect);

		virtual HRESULT STDMETHODCALLTYPE UnMapDesktopSurface();

		virtual HRESULT STDMETHODCALLTYPE ReleaseFrame();
	};

	// Wrap IDXGISurface2
	// struct IDXGISurface2Wrapper : IDXGISurface1Wrapper
	// {
	// 	IDXGISurface2Wrapper(REFIID riid, IUnknown *object);
	//
	// 	~IDXGISurface2Wrapper() override = default;
	//
	// 	virtual HRESULT STDMETHODCALLTYPE GetResource(REFIID riid, void **ppParentResource, UINT *pSubresourceIndex);
	// };

	// New wrapped IDXGISurface2
	struct IDXGISurface2Wrapper final : IDXGISurface2
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, IDXGISurface2Wrapper *> s_dxgi_surface_manager{};

	public:
		IDXGISurface2Wrapper(REFIID riid, IUnknown *object);

		virtual ~IDXGISurface2Wrapper() = default;

		// IDXGISurface2Wrapper manager
		static void InsertDXGISurface(void *object_key, IDXGISurface2Wrapper *surface)
		{
			s_dxgi_surface_manager[object_key] = surface;
		}

		static IDXGISurface2Wrapper *QueryExistingDXGISurface(void *object_key)
		{
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

	// Wrap IDXGIResource1
	// struct IDXGIResource1Wrapper : IDXGIResourceWrapper
	// {
	// 	IDXGIResource1Wrapper(REFIID riid, IUnknown *object);
	//
	// 	~IDXGIResource1Wrapper() override = default;
	//
	// 	virtual HRESULT STDMETHODCALLTYPE CreateSubresourceSurface(UINT index, IDXGISurface2 **ppSurface);
	//
	// 	virtual HRESULT STDMETHODCALLTYPE CreateSharedHandle(const SECURITY_ATTRIBUTES *pAttributes, DWORD dwAccess, LPCWSTR lpName, HANDLE *pHandle);
	// };

	// New wrapped IDXGIResource1
	struct IDXGIResource1Wrapper final : IDXGIResource1
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, IDXGIResource1Wrapper *> s_dxgi_resource_manager{};

	public:
		IDXGIResource1Wrapper(REFIID riid, IUnknown *object);

		virtual ~IDXGIResource1Wrapper() = default;

		// IDXGIResource1Wrapper manager
		static void InsertDXGIResource(void *object_key, IDXGIResource1Wrapper *resource)
		{
			s_dxgi_resource_manager[object_key] = resource;
		}

		static IDXGIResource1Wrapper *QueryExistingDXGIResource(void *object_key)
		{
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

	// Wrap IDXGIDevice2
	struct IDXGIDevice2Wrapper : IDXGIDevice1Wrapper
	{
		IDXGIDevice2Wrapper(REFIID riid, IUnknown *object);

		~IDXGIDevice2Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE OfferResources(UINT NumResources, IDXGIResource *const *ppResources, DXGI_OFFER_RESOURCE_PRIORITY Priority);

		virtual HRESULT STDMETHODCALLTYPE ReclaimResources(UINT NumResources, IDXGIResource *const *ppResources, BOOL *pDiscarded);

		virtual HRESULT STDMETHODCALLTYPE EnqueueSetEvent(HANDLE hEvent);
	};

	// Wrap IDXGISwapChain1
	struct IDXGISwapChain1Wrapper : IDXGISwapChainWrapper
	{
		IDXGISwapChain1Wrapper(REFIID riid, IUnknown *object);

		~IDXGISwapChain1Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE GetDesc1(DXGI_SWAP_CHAIN_DESC1 *pDesc);

		virtual HRESULT STDMETHODCALLTYPE GetFullscreenDesc(DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pDesc);

		virtual HRESULT STDMETHODCALLTYPE GetHwnd(HWND *pHwnd);

		virtual HRESULT STDMETHODCALLTYPE GetCoreWindow(REFIID refiid, void **ppUnk);

		virtual HRESULT STDMETHODCALLTYPE Present1(UINT SyncInterval, UINT PresentFlags, const DXGI_PRESENT_PARAMETERS *pPresentParameters);

		virtual BOOL STDMETHODCALLTYPE IsTemporaryMonoSupported();

		virtual HRESULT STDMETHODCALLTYPE GetRestrictToOutput(IDXGIOutput **ppRestrictToOutput);

		virtual HRESULT STDMETHODCALLTYPE SetBackgroundColor(const DXGI_RGBA *pColor);

		virtual HRESULT STDMETHODCALLTYPE GetBackgroundColor(DXGI_RGBA *pColor);

		virtual HRESULT STDMETHODCALLTYPE SetRotation(DXGI_MODE_ROTATION Rotation);

		virtual HRESULT STDMETHODCALLTYPE GetRotation(DXGI_MODE_ROTATION *pRotation);
	};

	// Wrap IDXGIFactory2
	struct IDXGIFactory2Wrapper : IDXGIFactory1Wrapper
	{
		IDXGIFactory2Wrapper(REFIID riid, IUnknown *object);

		~IDXGIFactory2Wrapper() override = default;

		virtual BOOL STDMETHODCALLTYPE IsWindowedStereoEnabled();

		virtual HRESULT STDMETHODCALLTYPE CreateSwapChainForHwnd(IUnknown *pDevice, HWND hWnd, const DXGI_SWAP_CHAIN_DESC1 *pDesc,
																const DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pFullscreenDesc, IDXGIOutput *pRestrictToOutput, IDXGISwapChain1 **ppSwapChain);

		virtual HRESULT STDMETHODCALLTYPE CreateSwapChainForCoreWindow(IUnknown *pDevice, IUnknown *pWindow, const DXGI_SWAP_CHAIN_DESC1 *pDesc,
																	IDXGIOutput* pRestrictToOutput, IDXGISwapChain1 **ppSwapChain);

		virtual HRESULT STDMETHODCALLTYPE GetSharedResourceAdapterLuid(HANDLE hResource, LUID *pLuid);

		virtual HRESULT STDMETHODCALLTYPE RegisterStereoStatusWindow(HWND WindowHandle, UINT wMsg, DWORD *pdwCookie);

		virtual HRESULT STDMETHODCALLTYPE RegisterStereoStatusEvent(HANDLE hEvent, DWORD *pdwCookie);

		virtual void STDMETHODCALLTYPE UnregisterStereoStatus(DWORD dwCookie);

		virtual HRESULT STDMETHODCALLTYPE RegisterOcclusionStatusWindow(HWND WindowHandle, UINT wMsg, DWORD *pdwCookie);

		virtual HRESULT STDMETHODCALLTYPE RegisterOcclusionStatusEvent(HANDLE hEvent, DWORD *pdwCookie);

		virtual void STDMETHODCALLTYPE UnregisterOcclusionStatus(DWORD dwCookie);

		virtual HRESULT STDMETHODCALLTYPE CreateSwapChainForComposition(IUnknown *pDevice, const DXGI_SWAP_CHAIN_DESC1 *pDesc,
																		IDXGIOutput *pRestrictToOutput, IDXGISwapChain1 **ppSwapChain);
	};

	// Wrap IDXGIAdapter2
	struct IDXGIAdapter2Wrapper : IDXGIAdapter1Wrapper
	{
		IDXGIAdapter2Wrapper(REFIID riid, IUnknown *object);

		~IDXGIAdapter2Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE GetDesc2(DXGI_ADAPTER_DESC2 *pDesc);
	};

	// Wrap IDXGIOutput1
	struct IDXGIOutput1Wrapper : IDXGIOutputWrapper
	{
		IDXGIOutput1Wrapper(REFIID riid, IUnknown *object);

		~IDXGIOutput1Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE GetDisplayModeList1(DXGI_FORMAT EnumFormat, UINT Flags, UINT *pNumModes, DXGI_MODE_DESC1 *pDesc);

		virtual HRESULT STDMETHODCALLTYPE FindClosestMatchingMode1(const DXGI_MODE_DESC1 *pModeToMatch, DXGI_MODE_DESC1 *pClosestMatch, IUnknown *pConcernedDevice);

		virtual HRESULT STDMETHODCALLTYPE GetDisplaySurfaceData1(IDXGIResource *pDestination);

		virtual HRESULT STDMETHODCALLTYPE DuplicateOutput(IUnknown *pDevice, IDXGIOutputDuplication **ppOutputDuplication);
	};

	// Wrap IDXGIDevice3
	struct IDXGIDevice3Wrapper : IDXGIDevice2Wrapper
	{
		IDXGIDevice3Wrapper(REFIID riid, IUnknown *object);

		~IDXGIDevice3Wrapper() override = default;

		virtual void STDMETHODCALLTYPE Trim();
	};

	// Wrap IDXGISwapChain2
	struct IDXGISwapChain2Wrapper : IDXGISwapChain1Wrapper
	{
		IDXGISwapChain2Wrapper(REFIID riid, IUnknown *object);

		~IDXGISwapChain2Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE SetSourceSize(UINT Width, UINT Height);

		virtual HRESULT STDMETHODCALLTYPE GetSourceSize(UINT *pWidth, UINT *pHeight);

		virtual HRESULT STDMETHODCALLTYPE SetMaximumFrameLatency(UINT MaxLatency);

		virtual HRESULT STDMETHODCALLTYPE GetMaximumFrameLatency(UINT *pMaxLatency);

		virtual HANDLE STDMETHODCALLTYPE GetFrameLatencyWaitableObject();

		virtual HRESULT STDMETHODCALLTYPE SetMatrixTransform(const DXGI_MATRIX_3X2_F *pMatrix);

		virtual HRESULT STDMETHODCALLTYPE GetMatrixTransform(DXGI_MATRIX_3X2_F *pMatrix);
	};

	// Wrap IDXGIOutput2
	struct IDXGIOutput2Wrapper : IDXGIOutput1Wrapper
	{
		IDXGIOutput2Wrapper(REFIID riid, IUnknown *object);

		~IDXGIOutput2Wrapper() override = default;

		virtual BOOL STDMETHODCALLTYPE SupportsOverlays();
	};

	// Wrap IDXGIFactory3
	struct IDXGIFactory3Wrapper : IDXGIFactory2Wrapper
	{
		IDXGIFactory3Wrapper(REFIID riid, IUnknown *object);

		~IDXGIFactory3Wrapper() override = default;

		virtual UINT STDMETHODCALLTYPE GetCreationFlags();
	};

	// Wrap IDXGIDecodeSwapChain
	struct IDXGIDecodeSwapChainWrapper : IUnknownWrapper
	{
		IDXGIDecodeSwapChainWrapper(REFIID riid, IUnknown *object);

		~IDXGIDecodeSwapChainWrapper() override;

		virtual HRESULT STDMETHODCALLTYPE PresentBuffer(UINT BufferToPresent, UINT SyncInterval, UINT Flags);

		virtual HRESULT STDMETHODCALLTYPE SetSourceRect(const RECT *pRect);

		virtual HRESULT STDMETHODCALLTYPE SetTargetRect(const RECT *pRect);

		virtual HRESULT STDMETHODCALLTYPE SetDestSize(UINT Width, UINT Height);

		virtual HRESULT STDMETHODCALLTYPE GetSourceRect(RECT *pRect);

		virtual HRESULT STDMETHODCALLTYPE GetTargetRect(RECT *pRect);

		virtual HRESULT STDMETHODCALLTYPE GetDestSize(UINT *pWidth, UINT *pHeight);

		virtual HRESULT STDMETHODCALLTYPE SetColorSpace(DXGI_MULTIPLANE_OVERLAY_YCbCr_FLAGS ColorSpace);

		virtual DXGI_MULTIPLANE_OVERLAY_YCbCr_FLAGS STDMETHODCALLTYPE GetColorSpace();
	};

	// Wrap IDXGIFactoryMedia
	struct IDXGIFactoryMediaWrapper : IUnknownWrapper
	{
		IDXGIFactoryMediaWrapper(REFIID riid, IUnknown *object);

		~IDXGIFactoryMediaWrapper() override;

		virtual HRESULT STDMETHODCALLTYPE CreateSwapChainForCompositionSurfaceHandle(IUnknown *pDevice, HANDLE hSurface, const DXGI_SWAP_CHAIN_DESC1 *pDesc,
																					IDXGIOutput *pRestrictToOutput, IDXGISwapChain1 **ppSwapChain);

		virtual HRESULT STDMETHODCALLTYPE CreateDecodeSwapChainForCompositionSurfaceHandle(IUnknown *pDevice, HANDLE hSurface, DXGI_DECODE_SWAP_CHAIN_DESC *pDesc,
																					IDXGIResource *pYuvDecodeBuffers, IDXGIOutput *pRestrictToOutput, IDXGIDecodeSwapChain **ppSwapChain);
	};

	// Wrap IDXGISwapChainMedia
	struct IDXGISwapChainMediaWrapper : IUnknownWrapper
	{
		IDXGISwapChainMediaWrapper(REFIID riid, IUnknown *object);

		~IDXGISwapChainMediaWrapper() override;

		virtual HRESULT STDMETHODCALLTYPE GetFrameStatisticsMedia(DXGI_FRAME_STATISTICS_MEDIA *pStats);

		virtual HRESULT STDMETHODCALLTYPE SetPresentDuration(UINT Duration);

		virtual HRESULT STDMETHODCALLTYPE CheckPresentDurationSupport(UINT DesiredPresentDuration, UINT *pClosestSmallerPresentDuration, UINT *pClosestLargerPresentDuration);
	};

	// Wrap IDXGIOutput3
	struct IDXGIOutput3Wrapper : IDXGIOutput2Wrapper
	{
		IDXGIOutput3Wrapper(REFIID riid, IUnknown *object);

		~IDXGIOutput3Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE CheckOverlaySupport(DXGI_FORMAT EnumFormat, IUnknown *pConcernedDevice, UINT *pFlags);
	};

	// Wrap IDXGISwapChain3
	struct IDXGISwapChain3Wrapper : IDXGISwapChain2Wrapper
	{
		IDXGISwapChain3Wrapper(REFIID riid, IUnknown *object);

		~IDXGISwapChain3Wrapper() override = default;

		virtual UINT STDMETHODCALLTYPE GetCurrentBackBufferIndex();

		virtual HRESULT STDMETHODCALLTYPE CheckColorSpaceSupport(DXGI_COLOR_SPACE_TYPE ColorSpace, UINT *pColorSpaceSupport);

		virtual HRESULT STDMETHODCALLTYPE SetColorSpace1(DXGI_COLOR_SPACE_TYPE ColorSpace);

		virtual HRESULT STDMETHODCALLTYPE ResizeBuffers1(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT Format,
														UINT SwapChainFlags, const UINT *pCreationNodeMask, IUnknown *const *ppPresentQueue);
	};

	// Wrap IDXGIOutput4
	struct IDXGIOutput4Wrapper : IDXGIOutput3Wrapper
	{
		IDXGIOutput4Wrapper(REFIID riid, IUnknown *object);

		~IDXGIOutput4Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE CheckOverlayColorSpaceSupport(DXGI_FORMAT Format, DXGI_COLOR_SPACE_TYPE ColorSpace,
																		IUnknown *pConcernedDevice, UINT *pFlags);
	};

	// Wrap IDXGIFactory4
	struct IDXGIFactory4Wrapper : IDXGIFactory3Wrapper
	{
		IDXGIFactory4Wrapper(REFIID riid, IUnknown *object);

		~IDXGIFactory4Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE EnumAdapterByLuid(LUID AdapterLuid, REFIID riid, void **ppvAdapter);

		virtual HRESULT STDMETHODCALLTYPE EnumWarpAdapter(REFIID riid, void **ppvAdapter);
	};

	// Wrap IDXGIAdapter3
	struct IDXGIAdapter3Wrapper : IDXGIAdapter2Wrapper
	{
		IDXGIAdapter3Wrapper(REFIID riid, IUnknown *object);

		~IDXGIAdapter3Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE RegisterHardwareContentProtectionTeardownStatusEvent(HANDLE hEvent, DWORD *pdwCookie);

		virtual void STDMETHODCALLTYPE UnregisterHardwareContentProtectionTeardownStatus(DWORD dwCookie);

		virtual HRESULT STDMETHODCALLTYPE QueryVideoMemoryInfo(UINT NodeIndex, DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup,
																DXGI_QUERY_VIDEO_MEMORY_INFO *pVideoMemoryInfo);

		virtual HRESULT STDMETHODCALLTYPE SetVideoMemoryReservation(UINT NodeIndex, DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup, UINT64 Reservation);

		virtual HRESULT STDMETHODCALLTYPE RegisterVideoMemoryBudgetChangeNotificationEvent(HANDLE hEvent, DWORD *pdwCookie);

		virtual void STDMETHODCALLTYPE UnregisterVideoMemoryBudgetChangeNotification(DWORD dwCookie);
	};

	// Wrap IDXGIOutput5
	struct IDXGIOutput5Wrapper : IDXGIOutput4Wrapper
	{
		IDXGIOutput5Wrapper(REFIID riid, IUnknown *object);

		~IDXGIOutput5Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE DuplicateOutput1(IUnknown *pDevice, UINT Flags, UINT SupportedFormatsCount,
															const DXGI_FORMAT *pSupportedFormats, IDXGIOutputDuplication **ppOutputDuplication);
	};

	// Wrap IDXGISwapChain4
	// struct IDXGISwapChain4Wrapper : IDXGISwapChain3Wrapper
	// {
	// 	IDXGISwapChain4Wrapper(REFIID riid, IUnknown *object);
	//
	// 	~IDXGISwapChain4Wrapper() override = default;
	//
	// 	virtual HRESULT STDMETHODCALLTYPE SetHDRMetaData(DXGI_HDR_METADATA_TYPE Type, UINT Size, void *pMetaData);
	// };

	// New wrapped IDXGISwapChain4
	struct IDXGISwapChain4Wrapper final : IDXGISwapChain4
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, IDXGISwapChain4Wrapper *> s_dxgi_swap_chain_manager{};

	public:
		IDXGISwapChain4Wrapper(REFIID riid, IUnknown *object);

		virtual ~IDXGISwapChain4Wrapper() = default;

		// IDXGISwapChain4Wrapper manager
		static void InsertDXGISwapChain(void *object_key, IDXGISwapChain4Wrapper *adapter)
		{
			s_dxgi_swap_chain_manager[object_key] = adapter;
		}

		static IDXGISwapChain4Wrapper *QueryExistingDXGISwapChain(void *object_key)
		{
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

	// Wrap IDXGIDevice4
	// struct IDXGIDevice4Wrapper : IDXGIDevice3Wrapper
	// {
	// 	IDXGIDevice4Wrapper(REFIID riid, IUnknown *object);
	//
	// 	~IDXGIDevice4Wrapper() override = default;
	//
	// 	virtual HRESULT STDMETHODCALLTYPE OfferResources1(UINT NumResources, IDXGIResource *const *ppResources, DXGI_OFFER_RESOURCE_PRIORITY Priority, UINT Flags);
	//
	// 	virtual HRESULT STDMETHODCALLTYPE ReclaimResources1(UINT NumResources, IDXGIResource *const *ppResources, DXGI_RECLAIM_RESOURCE_RESULTS *pResults);
	// };

	// New wrapped IDXGIDevice4
	struct IDXGIDevice4Wrapper final : IDXGIDevice4
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, IDXGIDevice4Wrapper *> s_dxgi_device_manager{};

	public:
		IDXGIDevice4Wrapper(REFIID riid, IUnknown *object);

		virtual ~IDXGIDevice4Wrapper() = default;

		// IDXGIDevice4Wrapper manager
		static void InsertDXGIDevice(void *object_key, IDXGIDevice4Wrapper *adapter)
		{
			s_dxgi_device_manager[object_key] = adapter;
		}

		static IDXGIDevice4Wrapper *QueryExistingDXGIDevice(void *object_key)
		{
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

	// Wrap IDXGIFactory5
	struct IDXGIFactory5Wrapper : IDXGIFactory4Wrapper
	{
		IDXGIFactory5Wrapper(REFIID riid, IUnknown *object);

		~IDXGIFactory5Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE CheckFeatureSupport(DXGI_FEATURE Feature, void *pFeatureSupportData, UINT FeatureSupportDataSize);
	};

	// Wrap IDXGIAdapter4
	// struct IDXGIAdapter4Wrapper : IDXGIAdapter3Wrapper
	// {
	// 	IDXGIAdapter4Wrapper(REFIID riid, IUnknown *object);
	//
	// 	~IDXGIAdapter4Wrapper() override = default;
	//
	// 	virtual HRESULT STDMETHODCALLTYPE GetDesc3(DXGI_ADAPTER_DESC3 *pDesc);
	// };

	// New wrapped IDXGIAdapter4
	struct IDXGIAdapter4Wrapper : IDXGIAdapter4
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, IDXGIAdapter4Wrapper *> s_dxgi_adapter_manager{};

	public:
		IDXGIAdapter4Wrapper(REFIID riid, IUnknown *object);

		virtual ~IDXGIAdapter4Wrapper() = default;

		// IDXGIAdapter4Wrapper manager
		static void InsertDXGIAdapter(void *object_key, IDXGIAdapter4Wrapper *adapter)
		{
			s_dxgi_adapter_manager[object_key] = adapter;
		}

		static IDXGIAdapter4Wrapper *QueryExistingDXGIAdapter(void *object_key)
		{
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

	// Wrap IDXGIOutput6
	// struct IDXGIOutput6Wrapper : IDXGIOutput5Wrapper
	// {
	// 	IDXGIOutput6Wrapper(REFIID riid, IUnknown *object);
	//
	// 	~IDXGIOutput6Wrapper() override = default;
	//
	// 	virtual HRESULT STDMETHODCALLTYPE GetDesc1(DXGI_OUTPUT_DESC1 *pDesc);
	//
	// 	virtual HRESULT STDMETHODCALLTYPE CheckHardwareCompositionSupport(UINT *pFlags);
	// };

	// New wrapped IDXGIOutput6
	struct IDXGIOutput6Wrapper final : IDXGIOutput6
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, IDXGIOutput6Wrapper *> s_dxgi_output_manager{};

	public:
		IDXGIOutput6Wrapper(REFIID riid, IUnknown *object);

		~IDXGIOutput6Wrapper() = default;

		// IDXGIOutput6Wrapper manager
		static void InsertDXGIOutput(void *object_key, IDXGIOutput6Wrapper *output)
		{
			s_dxgi_output_manager[object_key] = output;
		}

		static IDXGIOutput6Wrapper *QueryExistingDXGIOutput(void *object_key)
		{
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

	// Wrap IDXGIFactory6
	struct IDXGIFactory6Wrapper : IDXGIFactory5Wrapper
	{
		IDXGIFactory6Wrapper(REFIID riid, IUnknown *object);

		~IDXGIFactory6Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE EnumAdapterByGpuPreference(UINT Adapter, DXGI_GPU_PREFERENCE GpuPreference,
																	REFIID riid, void **ppvAdapter);
	};

	// Wrap IDXGIFactory7
	// struct IDXGIFactory7Wrapper : IDXGIFactory6Wrapper
	// {
	// 	IDXGIFactory7Wrapper(REFIID riid, IUnknown *object);
	//
	// 	~IDXGIFactory7Wrapper() override = default;
	//
	// 	virtual HRESULT STDMETHODCALLTYPE RegisterAdaptersChangedEvent(HANDLE hEvent, DWORD *pdwCookie);
	//
	// 	virtual HRESULT STDMETHODCALLTYPE UnregisterAdaptersChangedEvent(DWORD dwCookie);
	// };

	// New wrapped IDXGIFactory7
	struct IDXGIFactory7Wrapper final : IDXGIFactory7
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, IDXGIFactory7Wrapper *> s_dxgi_factory_manager{};

	public:
		IDXGIFactory7Wrapper(REFIID riid, IUnknown *object);

		~IDXGIFactory7Wrapper() = default;

		// IDXGIFactory7Wrapper manager
		static void InsertDXGIFactory(void *object_key, IDXGIFactory7Wrapper *factory)
		{
			s_dxgi_factory_manager[object_key] = factory;
		}

		static IDXGIFactory7Wrapper *QueryExistingDXGIFactory(void *object_key)
		{
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
// }
