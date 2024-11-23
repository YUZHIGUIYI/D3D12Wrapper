//
// Created by ZZK on 2024/11/23.
//

#include <tracer/core/wrapper_creators.h>
#include <tracer/dxgi/dxgi_wrappers.h>



namespace gfxshim::encode
{
	void WrapObject(const IID &riid, void **object)
	{
		if (object != nullptr && (*object != nullptr))
		{
			if (const auto it = kWrapFunctionTable.find(riid); it != kWrapFunctionTable.end())
			{
				it->second(riid, object);
			} else
			{
				D3D12_WRAPPER_WARN("An object with an unknown IID");
			}
		}
	}

	void WrapObjectArray(const IID &riid, void **object, uint32_t num_object)
	{
		for (uint32_t i = 0U; i < num_object; ++i)
		{
			WrapObject(riid, &object[i]);
		}
	}

	void WrapIDXGIKeyedMutex(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new IDXGIKeyedMutexWrapper{ riid, *wrap_object };
	}

	void WrapIDXGIDisplayControl(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new IDXGIDisplayControlWrapper{ riid, *wrap_object };
	}

	void WrapIDXGIOutputDuplication(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new IDXGIOutputDuplicationWrapper{ riid, *wrap_object };
	}

	void WrapIDXGISurface(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new IDXGISurface2Wrapper{ riid, *wrap_object };
	}

	void WrapIDXGIResource(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new IDXGIResource1Wrapper{ riid, *wrap_object };
	}

	void WrapIDXGIDecodeSwapChain(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new IDXGIDecodeSwapChainWrapper{ riid, *wrap_object };
	}

	void WrapIDXGIFactoryMedia(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new IDXGIFactoryMediaWrapper{ riid, *wrap_object };
	}

	void WrapIDXGISwapChainMedia(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new IDXGISwapChainMediaWrapper{ riid, *wrap_object };
	}

	void WrapIDXGISwapChain(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new IDXGISwapChain4Wrapper{ riid, *wrap_object };
	}

	void WrapIDXGIDevice(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new IDXGIDevice4Wrapper{ riid, *wrap_object };
	}

	void WrapIDXGIAdapter(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new IDXGIAdapter4Wrapper{ riid, *wrap_object };
	}

	void WrapIDXGIOutput(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new IDXGIOutput6Wrapper{ riid, *wrap_object };
	}

	void WrapIDXGIFactory(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new IDXGIFactory7Wrapper{ riid, *wrap_object };
	}

	void WrapID3D12RootSignature(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12RootSignatureDeserializer(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12VersionedRootSignatureDeserializer(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12CommandAllocator(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12Fence(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12PipelineState(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12DescriptorHeap(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12QueryHeap(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12CommandSignature(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12CommandQueue(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12PipelineLibrary(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12LifetimeOwner(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12SwapChainAssistant(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12LifetimeTracker(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12StateObject(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12StateObjectProperties(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12DeviceRemovedExtendedDataSettings(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12DeviceRemovedExtendedData(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12ProtectedResourceSession(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12Resource(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12Heap(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12MetaCommand(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12ShaderCacheSession(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12Device(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12VirtualizationGuestDevice(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12Tools(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12SDKConfiguration(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12DeviceFactory(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12DeviceConfiguration(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12CommandList(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12DSRDeviceFactory(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D10Blob(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3DDestructionNotifier(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12Debug(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12Debug1(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12Debug2(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12DebugDevice(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12DebugDevice1(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12DebugCommandQueue(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12DebugCommandList(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12DebugCommandList1(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12SharingContract(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12ManualWriteTrackingResource(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

	void WrapID3D12InfoQueue(const IID &riid, void **object)
	{
		// TODO: consider existing object
	}

}