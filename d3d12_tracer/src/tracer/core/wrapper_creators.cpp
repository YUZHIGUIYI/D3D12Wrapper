//
// Created by ZZK on 2024/11/23.
//

#include <tracer/core/wrapper_creators.h>
#include <tracer/d3d12/d3d12_command_allocator_wrap.h>
#include <tracer/d3d12/d3d12_command_list9_wrap.h>
#include <tracer/d3d12/d3d12_command_queue_wrap.h>
#include <tracer/d3d12/d3d12_command_signature_wrap.h>
#include <tracer/d3d12/d3d12_device12_wrap.h>
#include <tracer/d3d12/d3d12_device_configuration_wrap.h>
#include <tracer/d3d12/d3d12_device_factory_wrap.h>
#include <tracer/d3d12/d3d12_device_removed_extended_wrap.h>
#include <tracer/d3d12/d3d12_fence_wrap.h>
#include <tracer/d3d12/d3d12_guest_device_wrap.h>
#include <tracer/d3d12/d3d12_heap_wrap.h>
#include <tracer/d3d12/d3d12_info_queue_wrap.h>
#include <tracer/d3d12/d3d12_lifetime_wrap.h>
#include <tracer/d3d12/d3d12_meta_command_wrap.h>
#include <tracer/d3d12/d3d12_pipeline_library_wrap.h>
#include <tracer/d3d12/d3d12_pipeline_state_wrap.h>
#include <tracer/d3d12/d3d12_protected_session_wrap.h>
#include <tracer/d3d12/d3d12_resource_wrap.h>
#include <tracer/d3d12/d3d12_root_signature_wrap.h>
#include <tracer/d3d12/d3d12_sdk_wrap.h>
#include <tracer/d3d12/d3d12_shader_cache_session_wrap.h>
#include <tracer/d3d12/d3d12_state_object_wrap.h>
#include <tracer/d3d12/d3d12_swap_chain_wrap.h>
#include <tracer/d3d12/d3d12_tools_wrap.h>
#include <tracer/dxgi/dxgi_wrappers.h>

#include "tracer/d3d12/d3d10_blob_wrap.h"
#include "tracer/d3d12/d3d12_debug_wrap.h"
#include "tracer/d3d12/d3d12_sharing_contract_wrap.h"
#include "tracer/d3d12/d3d_destruction_notifier_wrap.h"

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
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = IDXGISurface2Wrapper::QueryExistingDXGISurface(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			wrap_object->Release();
			*object = existing;
			return;
		}

		*object = new IDXGISurface2Wrapper{ riid, wrap_object };
		IDXGISurface2Wrapper::InsertDXGISurface(wrap_object, static_cast<IDXGISurface2Wrapper *>(*object));
	}

	void WrapIDXGIResource(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = IDXGIResource1Wrapper::QueryExistingDXGIResource(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			wrap_object->Release();
			*object = existing;
			return;
		}

		*object = new IDXGIResource1Wrapper{ riid, wrap_object };
		IDXGIResource1Wrapper::InsertDXGIResource(wrap_object, static_cast<IDXGIResource1Wrapper *>(*object));
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
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = IDXGISwapChain4Wrapper::QueryExistingDXGISwapChain(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			wrap_object->Release();
			*object = existing;
			return;
		}

		*object = new IDXGISwapChain4Wrapper{ riid, wrap_object };
		IDXGISwapChain4Wrapper::InsertDXGISwapChain(wrap_object, static_cast<IDXGISwapChain4Wrapper *>(*object));
	}

	void WrapIDXGIDevice(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = IDXGIDevice4Wrapper::QueryExistingDXGIDevice(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			wrap_object->Release();
			*object = existing;
			return;
		}

		*object = new IDXGIDevice4Wrapper{ riid, wrap_object };
		IDXGIDevice4Wrapper::InsertDXGIDevice(wrap_object, static_cast<IDXGIDevice4Wrapper *>(*object));
	}

	void WrapIDXGIAdapter(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = IDXGIAdapter4Wrapper::QueryExistingDXGIAdapter(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			// wrap_object->Release();
			*object = existing;
			return;
		}

		*object = new IDXGIAdapter4Wrapper{ riid, wrap_object };
		IDXGIAdapter4Wrapper::InsertDXGIAdapter(wrap_object, static_cast<IDXGIAdapter4Wrapper *>(*object));
	}

	void WrapIDXGIOutput(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = IDXGIOutput6Wrapper::QueryExistingDXGIOutput(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			wrap_object->Release();
			*object = existing;
			return;
		}

		*object = new IDXGIOutput6Wrapper{ riid, wrap_object };
		IDXGIOutput6Wrapper::InsertDXGIOutput(wrap_object, static_cast<IDXGIOutput6Wrapper *>(*object));
	}

	void WrapIDXGIFactory(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = IDXGIFactory7Wrapper::QueryExistingDXGIFactory(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			// wrap_object->Release();
			*object = existing;
			return;
		}

		*object = new IDXGIFactory7Wrapper{ riid, wrap_object };
		IDXGIFactory7Wrapper::InsertDXGIFactory(wrap_object, static_cast<IDXGIFactory7Wrapper *>(*object));
	}

	void WrapID3D12RootSignature(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12RootSignatureWrapper{ riid, *wrap_object };
	}

	void WrapID3D12RootSignatureDeserializer(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12RootSignatureDeserializerWrapper{ riid, *wrap_object };
	}

	void WrapID3D12VersionedRootSignatureDeserializer(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12VersionedRootSignatureDeserializerWrapper{ riid, *wrap_object };
	}

	void WrapID3D12CommandAllocator(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12CommandAllocatorWrapper{ riid, *wrap_object };
	}

	void WrapID3D12Fence(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12Fence1Wrapper{ riid, *wrap_object };
	}

	void WrapID3D12PipelineState(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12PipelineStateWrapper{ riid, *wrap_object };
	}

	void WrapID3D12DescriptorHeap(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12DescriptorHeapWrapper{ riid, *wrap_object };
	}

	void WrapID3D12QueryHeap(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12QueryHeapWrapper{ riid, *wrap_object };
	}

	void WrapID3D12CommandSignature(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12CommandSignatureWrapper{ riid, *wrap_object };
	}

	void WrapID3D12CommandQueue(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12CommandQueueWrapper{ riid, *wrap_object };
	}

	void WrapID3D12PipelineLibrary(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12PipelineLibrary1Wrapper{ riid, *wrap_object };
	}

	void WrapID3D12LifetimeOwner(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12LifetimeOwnerWrapper{ riid, *wrap_object };
	}

	void WrapID3D12SwapChainAssistant(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12SwapChainAssistantWrapper{ riid, *wrap_object };
	}

	void WrapID3D12LifetimeTracker(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12LifetimeTrackerWrapper{ riid, *wrap_object };
	}

	void WrapID3D12StateObject(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12StateObjectWrapper{ riid, *wrap_object };
	}

	void WrapID3D12StateObjectProperties(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12StateObjectPropertiesWrapper{ riid, *wrap_object };
	}

	void WrapID3D12DeviceRemovedExtendedDataSettings(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12DeviceRemovedExtendedDataSettings2Wrapper{ riid, *wrap_object };
	}

	void WrapID3D12DeviceRemovedExtendedData(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12DeviceRemovedExtendedData2Wrapper{ riid, *wrap_object };
	}

	void WrapID3D12ProtectedResourceSession(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12ProtectedResourceSession1Wrapper{ riid, *wrap_object };
	}

	void WrapID3D12Resource(const IID &riid, void **object)
	{
		// TODO: consider existing object, also used by IDXGISwapChain::GetBuffer
		// auto wrap_object = reinterpret_cast<IUnknown **>(object);
		// *object = new ID3D12Resource2Wrapper{ riid, *wrap_object };
	}

	void WrapID3D12Heap(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12Heap1Wrapper{ riid, *wrap_object };
	}

	void WrapID3D12MetaCommand(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12MetaCommandWrapper{ riid, *wrap_object };
	}

	void WrapID3D12ShaderCacheSession(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12ShaderCacheSessionWrapper{ riid, *wrap_object };
	}

	void WrapID3D12Device(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12Device12Wrapper{ riid, *wrap_object };
	}

	void WrapID3D12VirtualizationGuestDevice(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12VirtualizationGuestDeviceWrapper{ riid, *wrap_object };
	}

	void WrapID3D12Tools(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12ToolsWrapper{ riid, *wrap_object };
	}

	void WrapID3D12SDKConfiguration(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12SDKConfiguration1Wrapper{ riid, *wrap_object };
	}

	void WrapID3D12DeviceFactory(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12DeviceFactoryWrapper{ riid, *wrap_object };
	}

	void WrapID3D12DeviceConfiguration(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12DeviceConfigurationWrapper{ riid, *wrap_object };
	}

	void WrapID3D12CommandList(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12GraphicsCommandList9Wrapper{ riid, *wrap_object };
	}

	void WrapID3D12DSRDeviceFactory(const IID &riid, void **object)
	{
		// TODO: consider existing object, currently do no consider dsr
	}

	void WrapID3D10Blob(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D10BlobWrapper{ riid, *wrap_object };
	}

	void WrapID3DDestructionNotifier(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3DDestructionNotifierWrapper{ riid, *wrap_object };
	}

	void WrapID3D12Debug(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12Debug6Wrapper{ riid, *wrap_object };
	}

	void WrapID3D12Debug1(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12Debug1Wrapper{ riid, *wrap_object };
	}

	void WrapID3D12Debug2(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12Debug2Wrapper{ riid, *wrap_object };
	}

	void WrapID3D12DebugDevice(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12DebugDevice2Wrapper{ riid, *wrap_object };
	}

	void WrapID3D12DebugDevice1(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12DebugDevice1Wrapper{ riid, *wrap_object };
	}

	void WrapID3D12DebugCommandQueue(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12DebugCommandQueue1Wrapper{ riid, *wrap_object };
	}

	void WrapID3D12DebugCommandList(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12DebugCommandList3Wrapper{ riid, *wrap_object };
	}

	void WrapID3D12DebugCommandList1(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12DebugCommandList1Wrapper{ riid, *wrap_object };
	}

	void WrapID3D12SharingContract(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12SharingContractWrapper{ riid, *wrap_object };
	}

	void WrapID3D12ManualWriteTrackingResource(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12ManualWriteTrackingResourceWrapper{ riid, *wrap_object };
	}

	void WrapID3D12InfoQueue(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown **>(object);
		*object = new ID3D12InfoQueue1Wrapper{ riid, *wrap_object };
	}

}