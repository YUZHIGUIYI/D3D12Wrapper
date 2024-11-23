//
// Created by ZZK on 2024/11/17.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
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
	struct IDXGISurface2Wrapper : IDXGISurface1Wrapper
	{
		IDXGISurface2Wrapper(REFIID riid, IUnknown *object);

		~IDXGISurface2Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE GetResource(REFIID riid, void **ppParentResource, UINT *pSubresourceIndex);
	};

	// Wrap IDXGIResource1
	struct IDXGIResource1Wrapper : IDXGIResourceWrapper
	{
		IDXGIResource1Wrapper(REFIID riid, IUnknown *object);

		~IDXGIResource1Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE CreateSubresourceSurface(UINT index, IDXGISurface2 **ppSurface);

		virtual HRESULT STDMETHODCALLTYPE CreateSharedHandle(const SECURITY_ATTRIBUTES *pAttributes, DWORD dwAccess, LPCWSTR lpName, HANDLE *pHandle);
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
	struct IDXGISwapChain4Wrapper : IDXGISwapChain3Wrapper
	{
		IDXGISwapChain4Wrapper(REFIID riid, IUnknown *object);

		~IDXGISwapChain4Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE SetHDRMetaData(DXGI_HDR_METADATA_TYPE Type, UINT Size, void *pMetaData);
	};

	// Wrap IDXGIDevice4
	struct IDXGIDevice4Wrapper : IDXGIDevice3Wrapper
	{
		IDXGIDevice4Wrapper(REFIID riid, IUnknown *object);

		~IDXGIDevice4Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE OfferResources1(UINT NumResources, IDXGIResource *const *ppResources, DXGI_OFFER_RESOURCE_PRIORITY Priority, UINT Flags);

		virtual HRESULT STDMETHODCALLTYPE ReclaimResources1(UINT NumResources, IDXGIResource *const *ppResources, DXGI_RECLAIM_RESOURCE_RESULTS *pResults);
	};

	// Wrap IDXGIFactory5
	struct IDXGIFactory5Wrapper : IDXGIFactory4Wrapper
	{
		IDXGIFactory5Wrapper(REFIID riid, IUnknown *object);

		~IDXGIFactory5Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE CheckFeatureSupport(DXGI_FEATURE Feature, void *pFeatureSupportData, UINT FeatureSupportDataSize);
	};

	// Wrap IDXGIAdapter4
	struct IDXGIAdapter4Wrapper : IDXGIAdapter3Wrapper
	{
		IDXGIAdapter4Wrapper(REFIID riid, IUnknown *object);

		~IDXGIAdapter4Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE GetDesc3(DXGI_ADAPTER_DESC3 *pDesc);
	};

	// Wrap IDXGIOutput6
	struct IDXGIOutput6Wrapper : IDXGIOutput5Wrapper
	{
		IDXGIOutput6Wrapper(REFIID riid, IUnknown *object);

		~IDXGIOutput6Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE GetDesc1(DXGI_OUTPUT_DESC1 *pDesc);

		virtual HRESULT STDMETHODCALLTYPE CheckHardwareCompositionSupport(UINT *pFlags);
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
	struct IDXGIFactory7Wrapper : IDXGIFactory6Wrapper
	{
		IDXGIFactory7Wrapper(REFIID riid, IUnknown *object);

		~IDXGIFactory7Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE RegisterAdaptersChangedEvent(HANDLE hEvent, DWORD *pdwCookie);

		virtual HRESULT STDMETHODCALLTYPE UnregisterAdaptersChangedEvent(DWORD dwCookie);
	};
}
