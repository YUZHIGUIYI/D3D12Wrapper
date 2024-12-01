//
// Created by ZZK on 2024/11/17.
//

#include <tracer/dxgi/dxgi_wrappers.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	// Wrap IDXGIObject
	IDXGIObjectWrapper::IDXGIObjectWrapper(const IID& riid, IUnknown* object)
	: IUnknownWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGIObjectWrapper::SetPrivateData(const GUID &Name, UINT DataSize, const void *pData)
	{
		const auto result = GetWrappedObjectAs<IDXGIObject>()->SetPrivateData(Name, DataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIObjectWrapper::SetPrivateDataInterface(const GUID &Name, const IUnknown *pUnknown)
	{
		const auto result = GetWrappedObjectAs<IDXGIObject>()->SetPrivateDataInterface(Name, encode::GetWrappedObject<IUnknown>(pUnknown));
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIObjectWrapper::GetPrivateData(const GUID &Name, UINT *pDataSize, void *pData)
	{
		const auto result = GetWrappedObjectAs<IDXGIObject>()->GetPrivateData(Name, pDataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIObjectWrapper::GetParent(const IID &riid, void **ppParent)
	{
		const auto result = GetWrappedObjectAs<IDXGIObject>()->GetParent(riid, ppParent);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppParent);
		}
		return result;
	}

	// Wrap IDXGIDeviceSubObject
	IDXGIDeviceSubObjectWrapper::IDXGIDeviceSubObjectWrapper(const IID &riid, IUnknown *object)
	: IDXGIObjectWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGIDeviceSubObjectWrapper::GetDevice(const IID &riid, void **ppDevice)
	{
		const auto result = GetWrappedObjectAs<IDXGIDeviceSubObject>()->GetDevice(riid, ppDevice);
		if (SUCCEEDED(result))
		{
			// TODO: wrap device
			encode::WrapObject(riid, ppDevice);
		}
		return result;
	}

	// Wrap IDXGIResource
	IDXGIResourceWrapper::IDXGIResourceWrapper(const IID &riid, IUnknown *object)
	: IDXGIDeviceSubObjectWrapper(riid, object)
	{

	}

	IDXGIResourceWrapper::~IDXGIResourceWrapper() = default;

	HRESULT STDMETHODCALLTYPE IDXGIResourceWrapper::GetSharedHandle(HANDLE *pSharedHandle)
	{
		const auto result = GetWrappedObjectAs<IDXGIResource>()->GetSharedHandle(pSharedHandle);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIResourceWrapper::GetUsage(DXGI_USAGE *pUsage)
	{
		const auto result = GetWrappedObjectAs<IDXGIResource>()->GetUsage(pUsage);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIResourceWrapper::SetEvictionPriority(UINT EvictionPriority)
	{
		const auto result = GetWrappedObjectAs<IDXGIResource>()->SetEvictionPriority(EvictionPriority);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIResourceWrapper::GetEvictionPriority(UINT *pEvictionPriority)
	{
		const auto result = GetWrappedObjectAs<IDXGIResource>()->GetEvictionPriority(pEvictionPriority);
		return result;
	}

	// Wrap IDXGIKeyMutex
	IDXGIKeyedMutexWrapper::IDXGIKeyedMutexWrapper(const IID &riid, IUnknown *object)
	: IDXGIDeviceSubObjectWrapper(riid, object)
	{

	}

	IDXGIKeyedMutexWrapper::~IDXGIKeyedMutexWrapper() = default;

	HRESULT STDMETHODCALLTYPE IDXGIKeyedMutexWrapper::AcquireSync(UINT64 Key, DWORD dwMilliseconds)
	{
		const auto result = GetWrappedObjectAs<IDXGIKeyedMutex>()->AcquireSync(Key, dwMilliseconds);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIKeyedMutexWrapper::ReleaseSync(UINT64 Key)
	{
		const auto result = GetWrappedObjectAs<IDXGIKeyedMutex>()->ReleaseSync(Key);
		return result;
	}

	// Wrap IDXGISurface
	IDXGISurfaceWrapper::IDXGISurfaceWrapper(const IID &riid, IUnknown *object)
	: IDXGIDeviceSubObjectWrapper(riid, object)
	{

	}

	IDXGISurfaceWrapper::~IDXGISurfaceWrapper() = default;

	HRESULT STDMETHODCALLTYPE IDXGISurfaceWrapper::GetDesc(DXGI_SURFACE_DESC *pDesc)
	{
		const auto result = GetWrappedObjectAs<IDXGISurface>()->GetDesc(pDesc);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISurfaceWrapper::Map(DXGI_MAPPED_RECT *pLockedRect, UINT MapFlags)
	{
		const auto result = GetWrappedObjectAs<IDXGISurface>()->Map(pLockedRect, MapFlags);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISurfaceWrapper::Unmap()
	{
		const auto result = GetWrappedObjectAs<IDXGISurface>()->Unmap();
		return result;
	}

	// Wrap IDXGISurface1
	IDXGISurface1Wrapper::IDXGISurface1Wrapper(const IID &riid, IUnknown *object)
	: IDXGISurfaceWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGISurface1Wrapper::GetDC(BOOL Discard, HDC *phdc)
	{
		const auto result = GetWrappedObjectAs<IDXGISurface1>()->GetDC(Discard, phdc);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISurface1Wrapper::ReleaseDC(RECT *pDirtyRect)
	{
		const auto result = GetWrappedObjectAs<IDXGISurface1>()->ReleaseDC(pDirtyRect);
		return result;
	}

	// Wrap IDXGIAdapter
	IDXGIAdapterWrapper::IDXGIAdapterWrapper(const IID &riid, IUnknown *object)
	: IDXGIObjectWrapper(riid, object)
	{

	}

	IDXGIAdapterWrapper::~IDXGIAdapterWrapper() = default;

	HRESULT STDMETHODCALLTYPE IDXGIAdapterWrapper::EnumOutputs(UINT Output, IDXGIOutput **ppOutput)
	{
		const auto result = GetWrappedObjectAs<IDXGIAdapter>()->EnumOutputs(Output, ppOutput);
		// TODO: wrap dxgi output
		if (SUCCEEDED(result))
		{
			encode::WrapObject(__uuidof(IDXGIOutput), reinterpret_cast<void **>(ppOutput));
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIAdapterWrapper::GetDesc(DXGI_ADAPTER_DESC *pDesc)
	{
		const auto result = GetWrappedObjectAs<IDXGIAdapter>()->GetDesc(pDesc);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIAdapterWrapper::CheckInterfaceSupport(const GUID &InterfaceName, LARGE_INTEGER *pUMDVersion)
	{
		const auto result = GetWrappedObjectAs<IDXGIAdapter>()->CheckInterfaceSupport(InterfaceName, pUMDVersion);
		return result;
	}

	// Wrap IDXGIOutput
	IDXGIOutputWrapper::IDXGIOutputWrapper(const IID &riid, IUnknown *object)
	: IDXGIObjectWrapper(riid, object)
	{

	}

	IDXGIOutputWrapper::~IDXGIOutputWrapper() = default;

	HRESULT STDMETHODCALLTYPE IDXGIOutputWrapper::GetDesc(DXGI_OUTPUT_DESC *pDesc)
	{
		const auto result = GetWrappedObjectAs<IDXGIOutput>()->GetDesc(pDesc);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIOutputWrapper::GetDisplayModeList(DXGI_FORMAT EnumFormat, UINT Flags, UINT *pNumModes, DXGI_MODE_DESC *pDesc)
	{
		const auto result = GetWrappedObjectAs<IDXGIOutput>()->GetDisplayModeList(EnumFormat, Flags, pNumModes, pDesc);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIOutputWrapper::FindClosestMatchingMode(const DXGI_MODE_DESC *pModeToMatch,
														DXGI_MODE_DESC *pClosestMatch, IUnknown *pConcernedDevice)
	{
		const auto result = GetWrappedObjectAs<IDXGIOutput>()->FindClosestMatchingMode(pModeToMatch, pClosestMatch,
									encode::GetWrappedObject<IUnknown>(pConcernedDevice));
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIOutputWrapper::WaitForVBlank()
	{
		const auto result = GetWrappedObjectAs<IDXGIOutput>()->WaitForVBlank();
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIOutputWrapper::TakeOwnership(IUnknown *pDevice, BOOL Exclusive)
	{
		const auto result = GetWrappedObjectAs<IDXGIOutput>()->TakeOwnership(encode::GetWrappedObject<IUnknown>(pDevice), Exclusive);
		return result;
	}

	void STDMETHODCALLTYPE IDXGIOutputWrapper::ReleaseOwnership()
	{
		GetWrappedObjectAs<IDXGIOutput>()->ReleaseOwnership();
	}

	HRESULT STDMETHODCALLTYPE IDXGIOutputWrapper::GetGammaControlCapabilities(DXGI_GAMMA_CONTROL_CAPABILITIES *pGammaCaps)
	{
		const auto result = GetWrappedObjectAs<IDXGIOutput>()->GetGammaControlCapabilities(pGammaCaps);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIOutputWrapper::SetGammaControl(const DXGI_GAMMA_CONTROL *pArray)
	{
		const auto result = GetWrappedObjectAs<IDXGIOutput>()->SetGammaControl(pArray);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIOutputWrapper::GetGammaControl(DXGI_GAMMA_CONTROL *pArray)
	{
		const auto result = GetWrappedObjectAs<IDXGIOutput>()->GetGammaControl(pArray);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIOutputWrapper::SetDisplaySurface(IDXGISurface *pScanoutSurface)
	{
		const auto result = GetWrappedObjectAs<IDXGIOutput>()->SetDisplaySurface(encode::GetWrappedObject<IDXGISurface>(pScanoutSurface));
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIOutputWrapper::GetDisplaySurfaceData(IDXGISurface *pDestination)
	{
		const auto result = GetWrappedObjectAs<IDXGIOutput>()->GetDisplaySurfaceData(encode::GetWrappedObject<IDXGISurface>(pDestination));
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIOutputWrapper::GetFrameStatistics(DXGI_FRAME_STATISTICS *pStats)
	{
		const auto result = GetWrappedObjectAs<IDXGIOutput>()->GetFrameStatistics(pStats);
		return result;
	}

	// Wrap IDXGISwapChain
	IDXGISwapChainWrapper::IDXGISwapChainWrapper(const IID &riid, IUnknown *object)
	: IDXGIDeviceSubObjectWrapper(riid, object)
	{

	}

	IDXGISwapChainWrapper::~IDXGISwapChainWrapper() = default;

	HRESULT STDMETHODCALLTYPE IDXGISwapChainWrapper::Present(UINT SyncInterval, UINT Flags)
	{
		// TODO: add flag
		const auto result = GetWrappedObjectAs<IDXGISwapChain>()->Present(SyncInterval, Flags);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChainWrapper::GetBuffer(UINT Buffer, const IID &riid, void **ppSurface)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain>()->GetBuffer(Buffer, riid, ppSurface);
		// TODO: wrap surface
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppSurface);
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChainWrapper::SetFullscreenState(BOOL Fullscreen, IDXGIOutput *pTarget)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain>()->SetFullscreenState(Fullscreen, encode::GetWrappedObject<IDXGIOutput>(pTarget));
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChainWrapper::GetFullscreenState(BOOL *pFullscreen, IDXGIOutput **ppTarget)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain>()->GetFullscreenState(pFullscreen, ppTarget);
		// TODO: wrap target as dxgi output
		if (SUCCEEDED(result))
		{
			encode::WrapObject(__uuidof(IDXGIOutput), reinterpret_cast<void **>(ppTarget));
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChainWrapper::GetDesc(DXGI_SWAP_CHAIN_DESC *pDesc)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain>()->GetDesc(pDesc);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChainWrapper::ResizeBuffers(UINT BufferCount, UINT Width, UINT Height,
																	DXGI_FORMAT NewFormat, UINT SwapChainFlags)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain>()->ResizeBuffers(BufferCount, Width, Height, NewFormat, SwapChainFlags);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChainWrapper::ResizeTarget(const DXGI_MODE_DESC *pNewTargetParameters)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain>()->ResizeTarget(pNewTargetParameters);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChainWrapper::GetContainingOutput(IDXGIOutput **ppOutput)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain>()->GetContainingOutput(ppOutput);
		// TODO: wrap dxgi output
		if (SUCCEEDED(result))
		{
			encode::WrapObject(__uuidof(IDXGIOutput), reinterpret_cast<void **>(ppOutput));
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChainWrapper::GetFrameStatistics(DXGI_FRAME_STATISTICS *pStats)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain>()->GetFrameStatistics(pStats);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChainWrapper::GetLastPresentCount(UINT *pLastPresentCount)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain>()->GetLastPresentCount(pLastPresentCount);
		return result;
	}

	// Wrap IDXGIFactory
	IDXGIFactoryWrapper::IDXGIFactoryWrapper(const IID &riid, IUnknown *object)
	: IDXGIObjectWrapper(riid, object)
	{

	}

	IDXGIFactoryWrapper::~IDXGIFactoryWrapper() = default;

	HRESULT STDMETHODCALLTYPE IDXGIFactoryWrapper::EnumAdapters(UINT Adapter, IDXGIAdapter **ppAdapter)
	{
		const auto result = GetWrappedObjectAs<IDXGIFactory>()->EnumAdapters(Adapter, ppAdapter);
		// TODO: wrap adapter
		if (SUCCEEDED(result))
		{
			encode::WrapObject(__uuidof(IDXGIAdapter), reinterpret_cast<void **>(ppAdapter));
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIFactoryWrapper::MakeWindowAssociation(HWND WindowHandle, UINT Flags)
	{
		const auto result = GetWrappedObjectAs<IDXGIFactory>()->MakeWindowAssociation(WindowHandle, Flags);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIFactoryWrapper::GetWindowAssociation(HWND *pWindowHandle)
	{
		const auto result = GetWrappedObjectAs<IDXGIFactory>()->GetWindowAssociation(pWindowHandle);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIFactoryWrapper::CreateSwapChain(IUnknown *pDevice, DXGI_SWAP_CHAIN_DESC *pDesc,
																	IDXGISwapChain **ppSwapChain)
	{
		const auto result = GetWrappedObjectAs<IDXGIFactory>()->CreateSwapChain(encode::GetWrappedObject<IUnknown>(pDevice), pDesc, ppSwapChain);
		// TODO: wrap swap chain
		if (SUCCEEDED(result))
		{
			encode::WrapObject(__uuidof(IDXGISwapChain), reinterpret_cast<void **>(ppSwapChain));
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIFactoryWrapper::CreateSoftwareAdapter(HMODULE Module, IDXGIAdapter **ppAdapter)
	{
		const auto result = GetWrappedObjectAs<IDXGIFactory>()->CreateSoftwareAdapter(Module, ppAdapter);
		// TODO: wrap adapter
		if (SUCCEEDED(result))
		{
			encode::WrapObject(__uuidof(IDXGIAdapter), reinterpret_cast<void **>(ppAdapter));
		}
		return result;
	}

	// Wrap IDXGIDevice
	IDXGIDeviceWrapper::IDXGIDeviceWrapper(const IID &riid, IUnknown *object)
	: IDXGIObjectWrapper(riid, object)
	{

	}

	IDXGIDeviceWrapper::~IDXGIDeviceWrapper() = default;

	HRESULT STDMETHODCALLTYPE IDXGIDeviceWrapper::GetAdapter(IDXGIAdapter **pAdapter)
	{
		const auto result = GetWrappedObjectAs<IDXGIDevice>()->GetAdapter(pAdapter);
		// TODO: wrap adapter
		if (SUCCEEDED(result))
		{
			encode::WrapObject(__uuidof(IDXGIAdapter), reinterpret_cast<void **>(pAdapter));
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIDeviceWrapper::CreateSurface(const DXGI_SURFACE_DESC *pDesc, UINT NumSurfaces, DXGI_USAGE Usage,
																const DXGI_SHARED_RESOURCE *pSharedResource, IDXGISurface **ppSurface)
	{
		const auto result = GetWrappedObjectAs<IDXGIDevice>()->CreateSurface(pDesc, NumSurfaces, Usage, pSharedResource, ppSurface);
		// TODO: wrap surface array
		if (SUCCEEDED(result))
		{
			encode::WrapObjectArray(__uuidof(IDXGISurface), reinterpret_cast<void **>(ppSurface), NumSurfaces);
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIDeviceWrapper::QueryResourceResidency(IUnknown *const *ppResources, DXGI_RESIDENCY *pResidencyStatus, UINT NumResources)
	{
		HRESULT result = S_OK;
		// TODO: unwrap resources
		if (NumResources > 0U && ppResources != nullptr)
		{
			std::vector<IUnknown *> unwrapResources(NumResources);
			for (uint32_t i = 0U; i < NumResources; ++i)
			{
				unwrapResources[i] = encode::GetWrappedObject<IUnknown>(ppResources[i]);
			}
			result = GetWrappedObjectAs<IDXGIDevice>()->QueryResourceResidency(unwrapResources.data(), pResidencyStatus, NumResources);
		} else
		{
			result = GetWrappedObjectAs<IDXGIDevice>()->QueryResourceResidency(ppResources, pResidencyStatus, NumResources);
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIDeviceWrapper::SetGPUThreadPriority(INT Priority)
	{
		const auto result = GetWrappedObjectAs<IDXGIDevice>()->SetGPUThreadPriority(Priority);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIDeviceWrapper::GetGPUThreadPriority(INT *pPriority)
	{
		const auto result = GetWrappedObjectAs<IDXGIDevice>()->GetGPUThreadPriority(pPriority);
		return result;
	}

	// Wrap IDXGIFactory1
	IDXGIFactory1Wrapper::IDXGIFactory1Wrapper(const IID &riid, IUnknown *object)
	: IDXGIFactoryWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGIFactory1Wrapper::EnumAdapters1(UINT Adapter, IDXGIAdapter1 **ppAdapter)
	{
		const auto result = GetWrappedObjectAs<IDXGIFactory1>()->EnumAdapters1(Adapter, ppAdapter);
		// TODO: wrap adapter
		if (SUCCEEDED(result))
		{
			encode::WrapObject(__uuidof(IDXGIAdapter1), reinterpret_cast<void **>(ppAdapter));
		}
		return result;
	}

	BOOL STDMETHODCALLTYPE IDXGIFactory1Wrapper::IsCurrent()
	{
		const auto result = GetWrappedObjectAs<IDXGIFactory1>()->IsCurrent();
		return result;
	}

	// Wrap IDXGIAdapter1
	IDXGIAdapter1Wrapper::IDXGIAdapter1Wrapper(const IID &riid, IUnknown *object)
	: IDXGIAdapterWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGIAdapter1Wrapper::GetDesc1(DXGI_ADAPTER_DESC1 *pDesc)
	{
		const auto result = GetWrappedObjectAs<IDXGIAdapter1>()->GetDesc1(pDesc);
		return result;
	}

	// Wrap IDXGIDevice1
	IDXGIDevice1Wrapper::IDXGIDevice1Wrapper(const IID &riid, IUnknown *object)
	: IDXGIDeviceWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGIDevice1Wrapper::SetMaximumFrameLatency(UINT MaxLatency)
	{
		const auto result = GetWrappedObjectAs<IDXGIDevice1>()->SetMaximumFrameLatency(MaxLatency);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIDevice1Wrapper::GetMaximumFrameLatency(UINT *pMaxLatency)
	{
		const auto result = GetWrappedObjectAs<IDXGIDevice1>()->GetMaximumFrameLatency(pMaxLatency);
		return result;
	}

	// Wrap IDXGIDisplayControl
	IDXGIDisplayControlWrapper::IDXGIDisplayControlWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	IDXGIDisplayControlWrapper::~IDXGIDisplayControlWrapper() = default;

	BOOL STDMETHODCALLTYPE IDXGIDisplayControlWrapper::IsStereoEnabled()
	{
		const auto result = GetWrappedObjectAs<IDXGIDisplayControl>()->IsStereoEnabled();
		return result;
	}

	void STDMETHODCALLTYPE IDXGIDisplayControlWrapper::SetStereoEnabled(BOOL enabled)
	{
		GetWrappedObjectAs<IDXGIDisplayControl>()->SetStereoEnabled(enabled);
	}

	// Wrap IDXGIOutputDuplication
	IDXGIOutputDuplicationWrapper::IDXGIOutputDuplicationWrapper(const IID &riid, IUnknown *object)
	: IDXGIObjectWrapper(riid, object)
	{

	}

	IDXGIOutputDuplicationWrapper::~IDXGIOutputDuplicationWrapper() = default;

	void STDMETHODCALLTYPE IDXGIOutputDuplicationWrapper::GetDesc(DXGI_OUTDUPL_DESC *pDesc)
	{
		GetWrappedObjectAs<IDXGIOutputDuplication>()->GetDesc(pDesc);
	}

	HRESULT STDMETHODCALLTYPE IDXGIOutputDuplicationWrapper::AcquireNextFrame(UINT TimeoutInMilliseconds,
																			DXGI_OUTDUPL_FRAME_INFO *pFrameInfo,
																			IDXGIResource **ppDesktopResource)
	{
		const auto result = GetWrappedObjectAs<IDXGIOutputDuplication>()->AcquireNextFrame(TimeoutInMilliseconds, pFrameInfo,
																									ppDesktopResource);
		// TODO: wrap resource
		if (SUCCEEDED(result))
		{
			encode::WrapObject(__uuidof(IDXGIResource), reinterpret_cast<void **>(ppDesktopResource));
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIOutputDuplicationWrapper::GetFrameDirtyRects(UINT DirtyRectsBufferSize, RECT *pDirtyRectsBuffer,
																				UINT *pDirtyRectsBufferSizeRequired)
	{
		const auto result = GetWrappedObjectAs<IDXGIOutputDuplication>()->GetFrameDirtyRects(DirtyRectsBufferSize, pDirtyRectsBuffer, pDirtyRectsBufferSizeRequired);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIOutputDuplicationWrapper::GetFrameMoveRects(UINT MoveRectsBufferSize,
																				DXGI_OUTDUPL_MOVE_RECT *pMoveRectBuffer,
																				UINT *pMoveRectsBufferSizeRequired)
	{
		const auto result = GetWrappedObjectAs<IDXGIOutputDuplication>()->GetFrameMoveRects(MoveRectsBufferSize, pMoveRectBuffer, pMoveRectsBufferSizeRequired);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIOutputDuplicationWrapper::GetFramePointerShape(UINT PointerShapeBufferSize, void *pPointerShapeBuffer,
																					UINT *pPointerShapeBufferSizeRequired, DXGI_OUTDUPL_POINTER_SHAPE_INFO *pPointerShapeInfo)
	{
		const auto result = GetWrappedObjectAs<IDXGIOutputDuplication>()->GetFramePointerShape(PointerShapeBufferSize,  pPointerShapeBuffer, pPointerShapeBufferSizeRequired, pPointerShapeInfo);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIOutputDuplicationWrapper::MapDesktopSurface(DXGI_MAPPED_RECT *pLockedRect)
	{
		const auto result = GetWrappedObjectAs<IDXGIOutputDuplication>()->MapDesktopSurface(pLockedRect);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIOutputDuplicationWrapper::UnMapDesktopSurface()
	{
		const auto result = GetWrappedObjectAs<IDXGIOutputDuplication>()->UnMapDesktopSurface();
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIOutputDuplicationWrapper::ReleaseFrame()
	{
		const auto result = GetWrappedObjectAs<IDXGIOutputDuplication>()->ReleaseFrame();
		return result;
	}

	// Wrap IDXGISurface2
	IDXGISurface2Wrapper::IDXGISurface2Wrapper(const IID &riid, IUnknown *object)
	: IDXGISurface1Wrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGISurface2Wrapper::GetResource(const IID &riid, void **ppParentResource, UINT *pSubresourceIndex)
	{
		const auto result = GetWrappedObjectAs<IDXGISurface2>()->GetResource(riid, ppParentResource, pSubresourceIndex);
		// TODO: wrap parent resource
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppParentResource);
		}
		return result;
	}

	// Wrap IDXGIResource1
	IDXGIResource1Wrapper::IDXGIResource1Wrapper(const IID &riid, IUnknown *object)
	: IDXGIResourceWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGIResource1Wrapper::CreateSubresourceSurface(UINT index, IDXGISurface2 **ppSurface)
	{
		const auto result = GetWrappedObjectAs<IDXGIResource1>()->CreateSubresourceSurface(index, ppSurface);
		// TODO: wrap surface2
		if (SUCCEEDED(result))
		{
			encode::WrapObject(__uuidof(IDXGISurface2), reinterpret_cast<void **>(ppSurface));
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIResource1Wrapper::CreateSharedHandle(const SECURITY_ATTRIBUTES *pAttributes, DWORD dwAccess,
																		LPCWSTR lpName, HANDLE *pHandle)
	{
		const auto result = GetWrappedObjectAs<IDXGIResource1>()->CreateSharedHandle(pAttributes, dwAccess, lpName, pHandle);
		return result;
	}

	// Wrap IDXGIDevice2
	IDXGIDevice2Wrapper::IDXGIDevice2Wrapper(const IID &riid, IUnknown *object)
	: IDXGIDevice1Wrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGIDevice2Wrapper::OfferResources(UINT NumResources, IDXGIResource *const *ppResources,
																	DXGI_OFFER_RESOURCE_PRIORITY Priority)
	{
		// TODO: unwrap resources
		HRESULT result = S_OK;
		if (NumResources > 0U)
		{
			std::vector<IDXGIResource *> unwrap_resources(NumResources);
			for (uint32_t i = 0U; i < NumResources; ++i)
			{
				unwrap_resources[i] = encode::GetWrappedObject<IDXGIResource>(ppResources[i]);
			}
			result = GetWrappedObjectAs<IDXGIDevice2>()->OfferResources(NumResources, unwrap_resources.data(), Priority);
		} else
		{
			result = GetWrappedObjectAs<IDXGIDevice2>()->OfferResources(NumResources, ppResources, Priority);
		}

		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIDevice2Wrapper::ReclaimResources(UINT NumResources, IDXGIResource *const *ppResources, BOOL *pDiscarded)
	{
		// TODO: unwrap resources
		HRESULT result = S_OK;
		if (NumResources > 0U)
		{
			std::vector<IDXGIResource *> unwrap_resources(NumResources);
			for (uint32_t i = 0U; i < NumResources; ++i)
			{
				unwrap_resources[i] = encode::GetWrappedObject<IDXGIResource>(ppResources[i]);
			}
			result = GetWrappedObjectAs<IDXGIDevice2>()->ReclaimResources(NumResources, unwrap_resources.data(), pDiscarded);
		} else
		{
			result = GetWrappedObjectAs<IDXGIDevice2>()->ReclaimResources(NumResources, ppResources, pDiscarded);
		}

		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIDevice2Wrapper::EnqueueSetEvent(HANDLE hEvent)
	{
		const auto result = GetWrappedObjectAs<IDXGIDevice2>()->EnqueueSetEvent(hEvent);
		return result;
	}

	// Wrap IDXGISwapChain1
	IDXGISwapChain1Wrapper::IDXGISwapChain1Wrapper(const IID &riid, IUnknown *object)
	: IDXGISwapChainWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChain1Wrapper::GetDesc1(DXGI_SWAP_CHAIN_DESC1 *pDesc)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain1>()->GetDesc1(pDesc);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChain1Wrapper::GetFullscreenDesc(DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pDesc)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain1>()->GetFullscreenDesc(pDesc);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChain1Wrapper::GetHwnd(HWND *pHwnd)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain1>()->GetHwnd(pHwnd);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChain1Wrapper::GetCoreWindow(const IID &refiid, void **ppUnk)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain1>()->GetCoreWindow(refiid, ppUnk);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(refiid, ppUnk);
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChain1Wrapper::Present1(UINT SyncInterval, UINT PresentFlags, const DXGI_PRESENT_PARAMETERS *pPresentParameters)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain1>()->Present1(SyncInterval, PresentFlags, pPresentParameters);
		return result;
	}

	BOOL STDMETHODCALLTYPE IDXGISwapChain1Wrapper::IsTemporaryMonoSupported()
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain1>()->IsTemporaryMonoSupported();
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChain1Wrapper::GetRestrictToOutput(IDXGIOutput **ppRestrictToOutput)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain1>()->GetRestrictToOutput(ppRestrictToOutput);
		// TODO: wrap dxgi output
		if (SUCCEEDED(result))
		{
			encode::WrapObject(__uuidof(IDXGIOutput), reinterpret_cast<void **>(ppRestrictToOutput));
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChain1Wrapper::SetBackgroundColor(const DXGI_RGBA *pColor)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain1>()->SetBackgroundColor(pColor);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChain1Wrapper::GetBackgroundColor(DXGI_RGBA *pColor)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain1>()->GetBackgroundColor(pColor);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChain1Wrapper::SetRotation(DXGI_MODE_ROTATION Rotation)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain1>()->SetRotation(Rotation);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChain1Wrapper::GetRotation(DXGI_MODE_ROTATION *pRotation)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain1>()->GetRotation(pRotation);
		return result;
	}

	// Wrap IDXGIFactory2
	IDXGIFactory2Wrapper::IDXGIFactory2Wrapper(const IID &riid, IUnknown *object) \
	: IDXGIFactory1Wrapper(riid, object)
	{

	}

	BOOL STDMETHODCALLTYPE IDXGIFactory2Wrapper::IsWindowedStereoEnabled()
	{
		const auto result = GetWrappedObjectAs<IDXGIFactory2>()->IsWindowedStereoEnabled();
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIFactory2Wrapper::CreateSwapChainForHwnd(IUnknown *pDevice, HWND hWnd, const DXGI_SWAP_CHAIN_DESC1 *pDesc, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pFullscreenDesc,
																			IDXGIOutput *pRestrictToOutput, IDXGISwapChain1 **ppSwapChain)
	{
		// TODO: unwrap and wrap
		const auto result = GetWrappedObjectAs<IDXGIFactory2>()->CreateSwapChainForHwnd(encode::GetWrappedObject<IUnknown>(pDevice), hWnd, pDesc, pFullscreenDesc,
																								encode::GetWrappedObject<IDXGIOutput>(pRestrictToOutput), ppSwapChain);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(__uuidof(IDXGISwapChain1), reinterpret_cast<void **>(ppSwapChain));
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIFactory2Wrapper::CreateSwapChainForCoreWindow(IUnknown *pDevice, IUnknown *pWindow, const DXGI_SWAP_CHAIN_DESC1 *pDesc,
																				IDXGIOutput *pRestrictToOutput, IDXGISwapChain1 **ppSwapChain)
	{
		// TODO: unwrap and wrap
		const auto result = GetWrappedObjectAs<IDXGIFactory2>()->CreateSwapChainForCoreWindow(encode::GetWrappedObject<IUnknown>(pDevice),
																										encode::GetWrappedObject<IUnknown>(pWindow), pDesc,
																										encode::GetWrappedObject<IDXGIOutput>(pRestrictToOutput), ppSwapChain);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(__uuidof(IDXGISwapChain1), reinterpret_cast<void **>(ppSwapChain));
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIFactory2Wrapper::GetSharedResourceAdapterLuid(HANDLE hResource, LUID *pLuid)
	{
		const auto result = GetWrappedObjectAs<IDXGIFactory2>()->GetSharedResourceAdapterLuid(hResource, pLuid);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIFactory2Wrapper::RegisterStereoStatusWindow(HWND WindowHandle, UINT wMsg, DWORD *pdwCookie)
	{
		const auto result = GetWrappedObjectAs<IDXGIFactory2>()->RegisterStereoStatusWindow(WindowHandle, wMsg, pdwCookie);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIFactory2Wrapper::RegisterStereoStatusEvent(HANDLE hEvent, DWORD *pdwCookie)
	{
		const auto result = GetWrappedObjectAs<IDXGIFactory2>()->RegisterStereoStatusEvent(hEvent, pdwCookie);
		return result;
	}

	void STDMETHODCALLTYPE IDXGIFactory2Wrapper::UnregisterStereoStatus(DWORD dwCookie)
	{
		GetWrappedObjectAs<IDXGIFactory2>()->UnregisterStereoStatus(dwCookie);
	}

	HRESULT STDMETHODCALLTYPE IDXGIFactory2Wrapper::RegisterOcclusionStatusWindow(HWND WindowHandle, UINT wMsg, DWORD *pdwCookie)
	{
		const auto result = GetWrappedObjectAs<IDXGIFactory2>()->RegisterOcclusionStatusWindow(WindowHandle, wMsg, pdwCookie);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIFactory2Wrapper::RegisterOcclusionStatusEvent(HANDLE hEvent, DWORD *pdwCookie)
	{
		const auto result = GetWrappedObjectAs<IDXGIFactory2>()->RegisterOcclusionStatusEvent(hEvent, pdwCookie);
		return result;
	}

	void STDMETHODCALLTYPE IDXGIFactory2Wrapper::UnregisterOcclusionStatus(DWORD dwCookie)
	{
		GetWrappedObjectAs<IDXGIFactory2>()->UnregisterOcclusionStatus(dwCookie);
	}

	HRESULT STDMETHODCALLTYPE IDXGIFactory2Wrapper::CreateSwapChainForComposition(IUnknown *pDevice, const DXGI_SWAP_CHAIN_DESC1 *pDesc,
																				IDXGIOutput *pRestrictToOutput, IDXGISwapChain1 **ppSwapChain)
	{
		// TODO: wrap
		const auto result = GetWrappedObjectAs<IDXGIFactory2>()->CreateSwapChainForComposition(encode::GetWrappedObject<IUnknown>(pDevice), pDesc,
																										encode::GetWrappedObject<IDXGIOutput>(pRestrictToOutput), ppSwapChain);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(__uuidof(IDXGISwapChain1), reinterpret_cast<void **>(ppSwapChain));
		}
		return result;
	}

	// Wrap IDXGIAdapter2
	IDXGIAdapter2Wrapper::IDXGIAdapter2Wrapper(const IID &riid, IUnknown *object)
	: IDXGIAdapter1Wrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGIAdapter2Wrapper::GetDesc2(DXGI_ADAPTER_DESC2 *pDesc)
	{
		const auto result = GetWrappedObjectAs<IDXGIAdapter2>()->GetDesc2(pDesc);
		return result;
	}

	// Wrap IDXGIOutput1
	IDXGIOutput1Wrapper::IDXGIOutput1Wrapper(const IID &riid, IUnknown *object)
	: IDXGIOutputWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGIOutput1Wrapper::GetDisplayModeList1(DXGI_FORMAT EnumFormat, UINT Flags, UINT *pNumModes, DXGI_MODE_DESC1 *pDesc)
	{
		const auto result = GetWrappedObjectAs<IDXGIOutput1>()->GetDisplayModeList1(EnumFormat, Flags, pNumModes, pDesc);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIOutput1Wrapper::FindClosestMatchingMode1(const DXGI_MODE_DESC1 *pModeToMatch,
																			DXGI_MODE_DESC1 *pClosestMatch, IUnknown *pConcernedDevice)
	{
		const auto result = GetWrappedObjectAs<IDXGIOutput1>()->FindClosestMatchingMode1(pModeToMatch, pClosestMatch,
																		encode::GetWrappedObject<IUnknown>(pConcernedDevice));
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIOutput1Wrapper::GetDisplaySurfaceData1(IDXGIResource *pDestination)
	{
		// TODO: check
		const auto result = GetWrappedObjectAs<IDXGIOutput1>()->GetDisplaySurfaceData1(encode::GetWrappedObject<IDXGIResource>(pDestination));
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIOutput1Wrapper::DuplicateOutput(IUnknown *pDevice, IDXGIOutputDuplication **ppOutputDuplication)
	{
		// TODO: check
		const auto result = GetWrappedObjectAs<IDXGIOutput1>()->DuplicateOutput(encode::GetWrappedObject<IUnknown>(pDevice), ppOutputDuplication);
		// TODO: wrap duplication
		if (SUCCEEDED(result))
		{
			encode::WrapObject(__uuidof(IDXGIOutputDuplication), reinterpret_cast<void **>(ppOutputDuplication));
		}
		return result;
	}

	// Wrap IDXGIDevice3
	IDXGIDevice3Wrapper::IDXGIDevice3Wrapper(const IID &riid, IUnknown *object)
	: IDXGIDevice2Wrapper(riid, object)
	{

	}

	void STDMETHODCALLTYPE IDXGIDevice3Wrapper::Trim()
	{
		GetWrappedObjectAs<IDXGIDevice3>()->Trim();
	}

	// Wrap IDXGISwapChain2
	IDXGISwapChain2Wrapper::IDXGISwapChain2Wrapper(const IID &riid, IUnknown *object)
	: IDXGISwapChain1Wrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChain2Wrapper::SetSourceSize(UINT Width, UINT Height)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain2>()->SetSourceSize(Width, Height);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChain2Wrapper::GetSourceSize(UINT *pWidth, UINT *pHeight)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain2>()->GetSourceSize(pWidth, pHeight);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChain2Wrapper::SetMaximumFrameLatency(UINT MaxLatency)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain2>()->SetMaximumFrameLatency(MaxLatency);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChain2Wrapper::GetMaximumFrameLatency(UINT *pMaxLatency)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain2>()->GetMaximumFrameLatency(pMaxLatency);
		return result;
	}

	HANDLE STDMETHODCALLTYPE IDXGISwapChain2Wrapper::GetFrameLatencyWaitableObject()
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain2>()->GetFrameLatencyWaitableObject();
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChain2Wrapper::SetMatrixTransform(const DXGI_MATRIX_3X2_F *pMatrix)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain2>()->SetMatrixTransform(pMatrix);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChain2Wrapper::GetMatrixTransform(DXGI_MATRIX_3X2_F *pMatrix)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain2>()->GetMatrixTransform(pMatrix);
		return result;
	}

	// Wrap IDXGIOutput2
	IDXGIOutput2Wrapper::IDXGIOutput2Wrapper(const IID &riid, IUnknown *object)
	: IDXGIOutput1Wrapper(riid, object)
	{

	}

	BOOL STDMETHODCALLTYPE IDXGIOutput2Wrapper::SupportsOverlays()
	{
		const auto result = GetWrappedObjectAs<IDXGIOutput2>()->SupportsOverlays();
		return result;
	}

	// Wrap IDXGIFactory3
	IDXGIFactory3Wrapper::IDXGIFactory3Wrapper(const IID &riid, IUnknown *object)
	: IDXGIFactory2Wrapper(riid, object)
	{

	}

	UINT STDMETHODCALLTYPE IDXGIFactory3Wrapper::GetCreationFlags()
	{
		const auto result = GetWrappedObjectAs<IDXGIFactory3>()->GetCreationFlags();
		return result;
	}

	// Wrap IDXGIDecodeSwapChain
	IDXGIDecodeSwapChainWrapper::IDXGIDecodeSwapChainWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	IDXGIDecodeSwapChainWrapper::~IDXGIDecodeSwapChainWrapper() = default;

	HRESULT STDMETHODCALLTYPE IDXGIDecodeSwapChainWrapper::PresentBuffer(UINT BufferToPresent, UINT SyncInterval, UINT Flags)
	{
		const auto result = GetWrappedObjectAs<IDXGIDecodeSwapChain>()->PresentBuffer(BufferToPresent, SyncInterval, Flags);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIDecodeSwapChainWrapper::SetSourceRect(const RECT *pRect)
	{
		const auto result = GetWrappedObjectAs<IDXGIDecodeSwapChain>()->SetSourceRect(pRect);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIDecodeSwapChainWrapper::SetTargetRect(const RECT *pRect)
	{
		const auto result = GetWrappedObjectAs<IDXGIDecodeSwapChain>()->SetTargetRect(pRect);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIDecodeSwapChainWrapper::SetDestSize(UINT Width, UINT Height)
	{
		const auto result = GetWrappedObjectAs<IDXGIDecodeSwapChain>()->SetDestSize(Width, Height);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIDecodeSwapChainWrapper::GetSourceRect(RECT *pRect)
	{
		const auto result = GetWrappedObjectAs<IDXGIDecodeSwapChain>()->GetSourceRect(pRect);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIDecodeSwapChainWrapper::GetTargetRect(RECT *pRect)
	{
		const auto result = GetWrappedObjectAs<IDXGIDecodeSwapChain>()->GetTargetRect(pRect);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIDecodeSwapChainWrapper::GetDestSize(UINT *pWidth, UINT *pHeight)
	{
		const auto result = GetWrappedObjectAs<IDXGIDecodeSwapChain>()->GetDestSize(pWidth, pHeight);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIDecodeSwapChainWrapper::SetColorSpace(DXGI_MULTIPLANE_OVERLAY_YCbCr_FLAGS ColorSpace)
	{
		const auto result = GetWrappedObjectAs<IDXGIDecodeSwapChain>()->SetColorSpace(ColorSpace);
		return result;
	}

	DXGI_MULTIPLANE_OVERLAY_YCbCr_FLAGS STDMETHODCALLTYPE IDXGIDecodeSwapChainWrapper::GetColorSpace()
	{
		const auto result = GetWrappedObjectAs<IDXGIDecodeSwapChain>()->GetColorSpace();
		return result;
	}

	// Wrap IDXGIFactoryMedia
	IDXGIFactoryMediaWrapper::IDXGIFactoryMediaWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	IDXGIFactoryMediaWrapper::~IDXGIFactoryMediaWrapper() = default;

	HRESULT STDMETHODCALLTYPE IDXGIFactoryMediaWrapper::CreateSwapChainForCompositionSurfaceHandle(IUnknown *pDevice, HANDLE hSurface, const DXGI_SWAP_CHAIN_DESC1 *pDesc,
																									IDXGIOutput *pRestrictToOutput, IDXGISwapChain1 **ppSwapChain)
	{
		// TODO: check and wrap swap chain
		const auto result = GetWrappedObjectAs<IDXGIFactoryMedia>()->CreateSwapChainForCompositionSurfaceHandle(
									encode::GetWrappedObject<IUnknown>(pDevice),
									hSurface,
									pDesc,
									encode::GetWrappedObject<IDXGIOutput>(pRestrictToOutput),
									ppSwapChain);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(__uuidof(IDXGISwapChain1), reinterpret_cast<void**>(ppSwapChain));
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIFactoryMediaWrapper::CreateDecodeSwapChainForCompositionSurfaceHandle(
						IUnknown *pDevice, HANDLE hSurface, DXGI_DECODE_SWAP_CHAIN_DESC *pDesc, IDXGIResource *pYuvDecodeBuffers,
						IDXGIOutput *pRestrictToOutput, IDXGIDecodeSwapChain **ppSwapChain)
	{
		// TODO: check and wrap swap chain
		const auto result = GetWrappedObjectAs<IDXGIFactoryMedia>()->CreateDecodeSwapChainForCompositionSurfaceHandle(
									encode::GetWrappedObject<IUnknown>(pDevice),
									hSurface,
									pDesc,
									encode::GetWrappedObject<IDXGIResource>(pYuvDecodeBuffers),
									encode::GetWrappedObject<IDXGIOutput>(pRestrictToOutput),
									ppSwapChain);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(__uuidof(IDXGIDecodeSwapChain), reinterpret_cast<void **>(ppSwapChain));
		}
		return result;
	}

	// Wrap IDXGISwapChainMedia
	IDXGISwapChainMediaWrapper::IDXGISwapChainMediaWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	IDXGISwapChainMediaWrapper::~IDXGISwapChainMediaWrapper() = default;

	HRESULT STDMETHODCALLTYPE IDXGISwapChainMediaWrapper::GetFrameStatisticsMedia(DXGI_FRAME_STATISTICS_MEDIA *pStats)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChainMedia>()->GetFrameStatisticsMedia(pStats);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChainMediaWrapper::SetPresentDuration(UINT Duration)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChainMedia>()->SetPresentDuration(Duration);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChainMediaWrapper::CheckPresentDurationSupport(UINT DesiredPresentDuration, UINT *pClosestSmallerPresentDuration, UINT *pClosestLargerPresentDuration)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChainMedia>()->CheckPresentDurationSupport(DesiredPresentDuration, pClosestSmallerPresentDuration, pClosestLargerPresentDuration);
		return result;
	}

	// Wrap IDXGIOutput3
	IDXGIOutput3Wrapper::IDXGIOutput3Wrapper(const IID &riid, IUnknown *object)
	: IDXGIOutput2Wrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGIOutput3Wrapper::CheckOverlaySupport(DXGI_FORMAT EnumFormat, IUnknown *pConcernedDevice, UINT *pFlags)
	{
		const auto result = GetWrappedObjectAs<IDXGIOutput3>()->CheckOverlaySupport(EnumFormat, encode::GetWrappedObject<IUnknown>(pConcernedDevice), pFlags);
		return result;
	}

	// Wrap IDXGISwapChain3
	IDXGISwapChain3Wrapper::IDXGISwapChain3Wrapper(const IID &riid, IUnknown *object)
	: IDXGISwapChain2Wrapper(riid, object)
	{

	}

	UINT STDMETHODCALLTYPE IDXGISwapChain3Wrapper::GetCurrentBackBufferIndex()
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain3>()->GetCurrentBackBufferIndex();
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChain3Wrapper::CheckColorSpaceSupport(DXGI_COLOR_SPACE_TYPE ColorSpace, UINT *pColorSpaceSupport)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain3>()->CheckColorSpaceSupport(ColorSpace, pColorSpaceSupport);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChain3Wrapper::SetColorSpace1(DXGI_COLOR_SPACE_TYPE ColorSpace)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain3>()->SetColorSpace1(ColorSpace);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChain3Wrapper::ResizeBuffers1(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT Format,
																	UINT SwapChainFlags, const UINT *pCreationNodeMask, IUnknown *const *ppPresentQueue)
	{
		// TODO: unwrap queues
		HRESULT result = S_OK;
		if (BufferCount > 0U && ppPresentQueue != nullptr)
		{
			std::vector<IUnknown *> unwrap_present_queues(BufferCount);
			for (uint32_t i = 0U; i < BufferCount; ++i)
			{
				unwrap_present_queues[i] = encode::GetWrappedObject<IUnknown>(ppPresentQueue[i]);
			}
			result = GetWrappedObjectAs<IDXGISwapChain3>()->ResizeBuffers1(BufferCount, Width, Height, Format,
										SwapChainFlags, pCreationNodeMask, unwrap_present_queues.data());
		} else
		{
			result = GetWrappedObjectAs<IDXGISwapChain3>()->ResizeBuffers1(BufferCount, Width, Height, Format,
										SwapChainFlags, pCreationNodeMask, ppPresentQueue);
		}
		return result;
	}

	// Wrap IDXGIOutput4
	IDXGIOutput4Wrapper::IDXGIOutput4Wrapper(const IID &riid, IUnknown *object)
	: IDXGIOutput3Wrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGIOutput4Wrapper::CheckOverlayColorSpaceSupport(DXGI_FORMAT Format, DXGI_COLOR_SPACE_TYPE ColorSpace,
																				IUnknown *pConcernedDevice, UINT *pFlags)
	{
		const auto result = GetWrappedObjectAs<IDXGIOutput4>()->CheckOverlayColorSpaceSupport(Format, ColorSpace,
																		encode::GetWrappedObject<IUnknown>(pConcernedDevice), pFlags);
		return result;
	}

	// Wrap IDXGIFactory4
	IDXGIFactory4Wrapper::IDXGIFactory4Wrapper(const IID &riid, IUnknown *object)
	: IDXGIFactory3Wrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGIFactory4Wrapper::EnumAdapterByLuid(LUID AdapterLuid, const IID &riid, void **ppvAdapter)
	{
		const auto result = GetWrappedObjectAs<IDXGIFactory4>()->EnumAdapterByLuid(AdapterLuid, riid, ppvAdapter);
		// TODO: wrap adapter
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvAdapter);
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIFactory4Wrapper::EnumWarpAdapter(const IID &riid, void **ppvAdapter)
	{
		const auto result = GetWrappedObjectAs<IDXGIFactory4>()->EnumWarpAdapter(riid, ppvAdapter);
		// TODO: wrap adapter
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvAdapter);
		}
		return result;
	}

	// Wrap IDXGIAdapter3
	IDXGIAdapter3Wrapper::IDXGIAdapter3Wrapper(const IID &riid, IUnknown *object)
	: IDXGIAdapter2Wrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGIAdapter3Wrapper::RegisterHardwareContentProtectionTeardownStatusEvent(HANDLE hEvent, DWORD *pdwCookie)
	{
		const auto result = GetWrappedObjectAs<IDXGIAdapter3>()->RegisterHardwareContentProtectionTeardownStatusEvent(hEvent, pdwCookie);
		return result;
	}

	void STDMETHODCALLTYPE IDXGIAdapter3Wrapper::UnregisterHardwareContentProtectionTeardownStatus(DWORD dwCookie)
	{
		GetWrappedObjectAs<IDXGIAdapter3>()->UnregisterHardwareContentProtectionTeardownStatus(dwCookie);
	}

	HRESULT STDMETHODCALLTYPE IDXGIAdapter3Wrapper::QueryVideoMemoryInfo(UINT NodeIndex, DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup,
																		DXGI_QUERY_VIDEO_MEMORY_INFO *pVideoMemoryInfo)
	{
		const auto result = GetWrappedObjectAs<IDXGIAdapter3>()->QueryVideoMemoryInfo(NodeIndex, MemorySegmentGroup, pVideoMemoryInfo);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIAdapter3Wrapper::SetVideoMemoryReservation(UINT NodeIndex, DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup,
																				UINT64 Reservation)
	{
		const auto result = GetWrappedObjectAs<IDXGIAdapter3>()->SetVideoMemoryReservation(NodeIndex, MemorySegmentGroup, Reservation);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIAdapter3Wrapper::RegisterVideoMemoryBudgetChangeNotificationEvent(HANDLE hEvent, DWORD *pdwCookie)
	{
		const auto result = GetWrappedObjectAs<IDXGIAdapter3>()->RegisterVideoMemoryBudgetChangeNotificationEvent(hEvent, pdwCookie);
		return result;
	}

	void STDMETHODCALLTYPE IDXGIAdapter3Wrapper::UnregisterVideoMemoryBudgetChangeNotification(DWORD dwCookie)
	{
		GetWrappedObjectAs<IDXGIAdapter3>()->UnregisterVideoMemoryBudgetChangeNotification(dwCookie);
	}

	// Wrap IDXGIOutput5
	IDXGIOutput5Wrapper::IDXGIOutput5Wrapper(const IID &riid, IUnknown *object)
	: IDXGIOutput4Wrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGIOutput5Wrapper::DuplicateOutput1(IUnknown *pDevice, UINT Flags, UINT SupportedFormatsCount,
												  const DXGI_FORMAT *pSupportedFormats,
												  IDXGIOutputDuplication **ppOutputDuplication)
	{
		const auto result = GetWrappedObjectAs<IDXGIOutput5>()->DuplicateOutput1(encode::GetWrappedObject<IUnknown>(pDevice), Flags, SupportedFormatsCount,
																						pSupportedFormats, ppOutputDuplication);
		// TODO: wrap output
		if (SUCCEEDED(result))
		{
			encode::WrapObject(__uuidof(IDXGIOutputDuplication), reinterpret_cast<void **>(ppOutputDuplication));
		}
		return result;
	}

	IDXGISwapChain4Wrapper::IDXGISwapChain4Wrapper(const IID &riid, IUnknown *object)
	: IDXGISwapChain3Wrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGISwapChain4Wrapper::SetHDRMetaData(DXGI_HDR_METADATA_TYPE Type, UINT Size, void *pMetaData)
	{
		const auto result = GetWrappedObjectAs<IDXGISwapChain4>()->SetHDRMetaData(Type, Size, pMetaData);
		return result;
	}

	// Wrap IDXGIDevice4
	IDXGIDevice4Wrapper::IDXGIDevice4Wrapper(const IID &riid, IUnknown *object)
	: IDXGIDevice3Wrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGIDevice4Wrapper::OfferResources1(UINT NumResources, IDXGIResource *const *ppResources,
																	DXGI_OFFER_RESOURCE_PRIORITY Priority, UINT Flags)
	{
		// TODO: Unwrap resources
		HRESULT result = S_OK;
		if (NumResources > 0U && ppResources != nullptr)
		{
			std::vector<IDXGIResource *> unwrap_resources(NumResources);
			for (uint32_t i = 0U; i < NumResources; ++i)
			{
				unwrap_resources[i] = encode::GetWrappedObject<IDXGIResource>(ppResources[i]);
			}
			result = GetWrappedObjectAs<IDXGIDevice4>()->OfferResources1(NumResources, unwrap_resources.data(), Priority, Flags);
		} else
		{
			result = GetWrappedObjectAs<IDXGIDevice4>()->OfferResources1(NumResources, ppResources, Priority, Flags);
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIDevice4Wrapper::ReclaimResources1(UINT NumResources, IDXGIResource *const *ppResources,
																	DXGI_RECLAIM_RESOURCE_RESULTS *pResults)
	{
		// TODO: unwrap resources
		HRESULT result = S_OK;
		if (NumResources > 0U && ppResources != nullptr)
		{
			std::vector<IDXGIResource *> unwrap_resources(NumResources);
			for (uint32_t i = 0U; i < NumResources; ++i)
			{
				unwrap_resources[i] = encode::GetWrappedObject<IDXGIResource>(ppResources[i]);
			}
			result = GetWrappedObjectAs<IDXGIDevice4>()->ReclaimResources1(NumResources, unwrap_resources.data(), pResults);
		} else
		{
			result = GetWrappedObjectAs<IDXGIDevice4>()->ReclaimResources1(NumResources, ppResources, pResults);
		}
		return result;
	}

	// Wrap IDXGIFactory5
	IDXGIFactory5Wrapper::IDXGIFactory5Wrapper(const IID &riid, IUnknown *object)
	: IDXGIFactory4Wrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGIFactory5Wrapper::CheckFeatureSupport(DXGI_FEATURE Feature, void *pFeatureSupportData, UINT FeatureSupportDataSize)
	{
		const auto result = GetWrappedObjectAs<IDXGIFactory5>()->CheckFeatureSupport(Feature, pFeatureSupportData, FeatureSupportDataSize);
		return result;
	}

	// Wrap IDXGIAdapter4
	IDXGIAdapter4Wrapper::IDXGIAdapter4Wrapper(const IID &riid, IUnknown *object)
	: IDXGIAdapter3Wrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGIAdapter4Wrapper::GetDesc3(DXGI_ADAPTER_DESC3 *pDesc)
	{
		const auto result = GetWrappedObjectAs<IDXGIAdapter4>()->GetDesc3(pDesc);
		return result;
	}

	// Wrap IDXGIOutput6
	IDXGIOutput6Wrapper::IDXGIOutput6Wrapper(const IID &riid, IUnknown *object)
	: IDXGIOutput5Wrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGIOutput6Wrapper::GetDesc1(DXGI_OUTPUT_DESC1 *pDesc)
	{
		const auto result = GetWrappedObjectAs<IDXGIOutput6>()->GetDesc1(pDesc);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIOutput6Wrapper::CheckHardwareCompositionSupport(UINT *pFlags)
	{
		const auto result = GetWrappedObjectAs<IDXGIOutput6>()->CheckHardwareCompositionSupport(pFlags);
		return result;
	}

	// Wrap IDXGIFactory6
	IDXGIFactory6Wrapper::IDXGIFactory6Wrapper(const IID &riid, IUnknown *object)
	: IDXGIFactory5Wrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGIFactory6Wrapper::EnumAdapterByGpuPreference(UINT Adapter, DXGI_GPU_PREFERENCE GpuPreference,
																				const IID &riid, void **ppvAdapter)
	{
		const auto result = GetWrappedObjectAs<IDXGIFactory6>()->EnumAdapterByGpuPreference(Adapter, GpuPreference, riid,
																									ppvAdapter);
		// TODO: wrap adapter
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvAdapter);
		}
		return result;
	}

	// Wrap IDXGIFactory7
	IDXGIFactory7Wrapper::IDXGIFactory7Wrapper(const IID &riid, IUnknown *object)
	: IDXGIFactory6Wrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE IDXGIFactory7Wrapper::RegisterAdaptersChangedEvent(HANDLE hEvent, DWORD *pdwCookie)
	{
		const auto result = GetWrappedObjectAs<IDXGIFactory7>()->RegisterAdaptersChangedEvent(hEvent, pdwCookie);
		return result;
	}

	HRESULT STDMETHODCALLTYPE IDXGIFactory7Wrapper::UnregisterAdaptersChangedEvent(DWORD dwCookie)
	{
		const auto result = GetWrappedObjectAs<IDXGIFactory7>()->UnregisterAdaptersChangedEvent(dwCookie);
		return result;
	}

}














