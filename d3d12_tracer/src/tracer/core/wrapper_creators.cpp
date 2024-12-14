//
// Created by ZZK on 2024/11/23.
//

#include <tracer/core/wrapper_creators.h>
#include <tracer/d3d12/d3d12_command_allocator_wrap.h>
#include <tracer/d3d12/d3d12_command_list10_wrap.h>
#include <tracer/d3d12/d3d12_command_queue_wrap.h>
#include <tracer/d3d12/d3d12_command_signature_wrap.h>
#include <tracer/d3d12/d3d12_device14_wrap.h>
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
#include <tracer/d3d12/d3d10_blob_wrap.h>
#include <tracer/d3d12/d3d12_debug_wrap.h>
#include <tracer/d3d12/d3d12_sharing_contract_wrap.h>
#include <tracer/d3d12/d3d_destruction_notifier_wrap.h>

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

	void WrapIUnknown(REFIID riid, void **object)
	{
		// Note: do nothing
	}

	void WrapIDXGIKeyedMutex(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = IDXGIKeyedMutexWrapper::QueryExistingDXGIKeyedMutex(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			wrap_object->Release();
			*object = existing;
			return;
		}

		*object = new IDXGIKeyedMutexWrapper{ riid, wrap_object };
		IDXGIKeyedMutexWrapper::InsertDXGIKeyedMutex(wrap_object, static_cast<IDXGIKeyedMutexWrapper *>(*object));
	}

	void WrapIDXGIDisplayControl(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = IDXGIDisplayControlWrapper::QueryExistingDXGIDisplayControl(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			wrap_object->Release();
			*object = existing;
			return;
		}

		*object = new IDXGIDisplayControlWrapper{ riid, wrap_object };
		IDXGIDisplayControlWrapper::InsertDXGIDisplayControl(wrap_object, static_cast<IDXGIDisplayControlWrapper *>(*object));
	}

	void WrapIDXGIOutputDuplication(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = IDXGIOutputDuplicationWrapper::QueryExistingDXGIOutputDuplication(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			wrap_object->Release();
			*object = existing;
			return;
		}

		*object = new IDXGIOutputDuplicationWrapper{ riid, wrap_object };
		IDXGIOutputDuplicationWrapper::InsertDXGIOutputDuplication(wrap_object, static_cast<IDXGIOutputDuplicationWrapper *>(*object));
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
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = IDXGIDecodeSwapChainWrapper::QueryExistingDXGIDecodeSwapChain(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			wrap_object->Release();
			*object = existing;
			return;
		}

		*object = new IDXGIDecodeSwapChainWrapper{ riid, wrap_object };
		IDXGIDecodeSwapChainWrapper::InsertDXGIDecodeSwapChain(wrap_object, static_cast<IDXGIDecodeSwapChainWrapper *>(*object));
	}

	void WrapIDXGIFactoryMedia(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = IDXGIFactoryMediaWrapper::QueryExistingDXGIFactoryMedia(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			wrap_object->Release();
			*object = existing;
			return;
		}

		*object = new IDXGIFactoryMediaWrapper{ riid, wrap_object };
		IDXGIFactoryMediaWrapper::InsertDXGIFactoryMedia(wrap_object, static_cast<IDXGIFactoryMediaWrapper *>(*object));
	}

	void WrapIDXGISwapChainMedia(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = IDXGISwapChainMediaWrapper::QueryExistingDXGISwapChainMedia(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			wrap_object->Release();
			*object = existing;
			return;
		}

		*object = new IDXGISwapChainMediaWrapper{ riid, wrap_object };
		IDXGISwapChainMediaWrapper::InsertDXGISwapChainMedia(wrap_object, static_cast<IDXGISwapChainMediaWrapper *>(*object));
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
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12RootSignatureWrapper::QueryExistingD3D12RootSignature(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12RootSignatureWrapper{ riid, wrap_object };
		ID3D12RootSignatureWrapper::InsertD3D12RootSignature(wrap_object, static_cast<ID3D12RootSignatureWrapper *>(*object));
	}

	void WrapID3D12RootSignatureDeserializer(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12RootSignatureDeserializerWrapper::QueryExistingD3D12RootSignatureDeserializer(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12RootSignatureDeserializerWrapper{ riid, wrap_object };
		ID3D12RootSignatureDeserializerWrapper::InsertD3D12RootSignatureDeserializer(wrap_object, static_cast<ID3D12RootSignatureDeserializerWrapper *>(*object));
	}

	void WrapID3D12VersionedRootSignatureDeserializer(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12VersionedRootSignatureDeserializerWrapper::QueryExistingD3D12VersionedRootSignatureDeserializer(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12VersionedRootSignatureDeserializerWrapper{ riid, wrap_object };
		ID3D12VersionedRootSignatureDeserializerWrapper::InsertD3D12VersionedRootSignatureDeserializer(wrap_object, static_cast<ID3D12VersionedRootSignatureDeserializerWrapper *>(*object));
	}

	void WrapID3D12CommandAllocator(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12CommandAllocatorWrapper::QueryExistingD3D12CommandAllocator(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12CommandAllocatorWrapper{ riid, wrap_object };
		ID3D12CommandAllocatorWrapper::InsertD3D12CommandAllocator(wrap_object, static_cast<ID3D12CommandAllocatorWrapper *>(*object));
	}

	void WrapID3D12Fence(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12Fence1Wrapper::QueryExistingD3D12Fence(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12Fence1Wrapper{ riid, wrap_object };
		ID3D12Fence1Wrapper::InsertD3D12Fence(wrap_object, static_cast<ID3D12Fence1Wrapper *>(*object));
	}

	void WrapID3D12PipelineState(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12PipelineStateWrapper::QueryExistingD3D12PipelineState(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12PipelineStateWrapper{ riid, wrap_object };
		ID3D12PipelineStateWrapper::InsertD3D12PipelineState(wrap_object, static_cast<ID3D12PipelineStateWrapper *>(*object));
	}

	void WrapID3D12DescriptorHeap(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12DescriptorHeapWrapper::QueryExistingD3D12DescriptorHeap(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12DescriptorHeapWrapper{ riid, wrap_object };
		ID3D12DescriptorHeapWrapper::InsertD3D12DescriptorHeap(wrap_object, static_cast<ID3D12DescriptorHeapWrapper *>(*object));
	}

	void WrapID3D12QueryHeap(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12QueryHeapWrapper::QueryExistingD3D12QueryHeap(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12QueryHeapWrapper{ riid, wrap_object };
		ID3D12QueryHeapWrapper::InsertD3D12QueryHeap(wrap_object, static_cast<ID3D12QueryHeapWrapper *>(*object));
	}

	void WrapID3D12CommandSignature(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12CommandSignatureWrapper::QueryExistingD3D12CommandSignature(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12CommandSignatureWrapper{ riid, wrap_object };
		ID3D12CommandSignatureWrapper::InsertD3D12CommandSignature(wrap_object, static_cast<ID3D12CommandSignatureWrapper *>(*object));
	}

	void WrapID3D12CommandQueue(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12CommandQueueWrapper::QueryExistingD3D12CommandQueue(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12CommandQueueWrapper{ riid, wrap_object };
		ID3D12CommandQueueWrapper::InsertD3D12CommandQueue(wrap_object, static_cast<ID3D12CommandQueueWrapper *>(*object));
	}

	void WrapID3D12PipelineLibrary(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12PipelineLibrary1Wrapper::QueryExistingD3D12PipelineLibrary(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12PipelineLibrary1Wrapper{ riid, wrap_object };
		ID3D12PipelineLibrary1Wrapper::InsertD3D12PipelineLibrary(wrap_object, static_cast<ID3D12PipelineLibrary1Wrapper *>(*object));
	}

	void WrapID3D12LifetimeOwner(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12LifetimeOwnerWrapper::QueryExistingD3D12LifetimeOwner(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12LifetimeOwnerWrapper{ riid, wrap_object };
		ID3D12LifetimeOwnerWrapper::InsertD3D12LifetimeOwner(wrap_object, static_cast<ID3D12LifetimeOwnerWrapper *>(*object));
	}

	void WrapID3D12SwapChainAssistant(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12SwapChainAssistantWrapper::QueryExistingD3D12SwapChainAssistant(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12SwapChainAssistantWrapper{ riid, wrap_object };
		ID3D12SwapChainAssistantWrapper::InsertD3D12SwapChainAssistant(wrap_object, static_cast<ID3D12SwapChainAssistantWrapper *>(*object));
	}

	void WrapID3D12LifetimeTracker(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12LifetimeTrackerWrapper::QueryExistingD3D12LifetimeTracer(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12LifetimeTrackerWrapper{ riid, wrap_object };
		ID3D12LifetimeTrackerWrapper::InsertD3D12LifetimeTracer(wrap_object, static_cast<ID3D12LifetimeTrackerWrapper *>(*object));
	}

	void WrapID3D12StateObject(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12StateObjectWrapper::QueryExistingD3D12StateObject(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12StateObjectWrapper{ riid, wrap_object };
		ID3D12StateObjectWrapper::InsertD3D12StateObject(wrap_object, static_cast<ID3D12StateObjectWrapper *>(*object));
	}

	void WrapID3D12StateObjectProperties(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12StateObjectProperties1Wrapper::QueryExistingD3D12StateObjectProperties1(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12StateObjectProperties1Wrapper{ riid, wrap_object };
		ID3D12StateObjectProperties1Wrapper::InsertD3D12StateObjectProperties1(wrap_object, static_cast<ID3D12StateObjectProperties1Wrapper *>(*object));
	}

	void WrapID3D12DeviceRemovedExtendedDataSettings(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12DeviceRemovedExtendedDataSettings2Wrapper::QueryExistingD3D12DeviceRemovedSettings2(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12DeviceRemovedExtendedDataSettings2Wrapper{ riid, wrap_object };
		ID3D12DeviceRemovedExtendedDataSettings2Wrapper::InsertD3D12DeviceRemovedSettings2(wrap_object, static_cast<ID3D12DeviceRemovedExtendedDataSettings2Wrapper *>(*object));
	}

	void WrapID3D12DeviceRemovedExtendedData(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12DeviceRemovedExtendedData2Wrapper::QueryExistingD3D12DeviceRemovedData2(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12DeviceRemovedExtendedData2Wrapper{ riid, wrap_object };
		ID3D12DeviceRemovedExtendedData2Wrapper::InsertD3D12DeviceRemovedData2(wrap_object, static_cast<ID3D12DeviceRemovedExtendedData2Wrapper *>(*object));
	}

	void WrapID3D12ProtectedResourceSession(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12ProtectedResourceSession1Wrapper::QueryExistingD3D12ResourceSession1(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12ProtectedResourceSession1Wrapper{ riid, wrap_object };
		ID3D12ProtectedResourceSession1Wrapper::InsertD3D12ResourceSession1(wrap_object, static_cast<ID3D12ProtectedResourceSession1Wrapper *>(*object));
	}

	void WrapID3D12Resource(const IID &riid, void **object)
	{
		// TODO: consider existing object, also used by IDXGISwapChain::GetBuffer
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12Resource2Wrapper::QueryExistingD3D12Resource(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12Resource2Wrapper{ riid, wrap_object };
		ID3D12Resource2Wrapper::InsertD3D12Resource(wrap_object, static_cast<ID3D12Resource2Wrapper *>(*object));
	}

	void WrapID3D12Heap(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12Heap1Wrapper::QueryExistingD3D12Heap(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12Heap1Wrapper{ riid, wrap_object };
		ID3D12Heap1Wrapper::InsertD3D12Heap(wrap_object, static_cast<ID3D12Heap1Wrapper *>(*object));
	}

	void WrapID3D12MetaCommand(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12CommandQueueWrapper::QueryExistingD3D12CommandQueue(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12MetaCommandWrapper{ riid, wrap_object };
		ID3D12MetaCommandWrapper::InsertD3D12MetaCommand(wrap_object, static_cast<ID3D12MetaCommandWrapper *>(*object));
	}

	void WrapID3D12ShaderCacheSession(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12ShaderCacheSessionWrapper::QueryExistingD3D12ShaderCacheSession(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12ShaderCacheSessionWrapper{ riid, wrap_object };
		ID3D12ShaderCacheSessionWrapper::InsertD3D12ShaderCacheSession(wrap_object, static_cast<ID3D12ShaderCacheSessionWrapper *>(*object));
	}

	void WrapID3D12Device(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12Device14Wrapper::QueryExistingD3D12Device(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12Device14Wrapper{ riid, wrap_object };
		ID3D12Device14Wrapper::InsertD3D12Device(wrap_object, static_cast<ID3D12Device14Wrapper *>(*object));
	}

	void WrapID3D12VirtualizationGuestDevice(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12VirtualizationGuestDeviceWrapper::QueryExistingD3D12GuestDevice(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12VirtualizationGuestDeviceWrapper{ riid, wrap_object };
		ID3D12VirtualizationGuestDeviceWrapper::InsertD3D12GuestDevice(wrap_object, static_cast<ID3D12VirtualizationGuestDeviceWrapper *>(*object));
	}

	void WrapID3D12Tools(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = reinterpret_cast<IUnknown *>(*object);
		auto existing = ID3D12ToolsWrapper::QueryExistingD3D12Tools(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12ToolsWrapper{ riid, wrap_object };
		ID3D12ToolsWrapper::InsertD3D12Tools(wrap_object, static_cast<ID3D12ToolsWrapper *>(*object));
	}

	void WrapID3D12SDKConfiguration(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12SDKConfiguration1Wrapper::QueryExistingD3D12SDKConfiguration1(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12SDKConfiguration1Wrapper{ riid, wrap_object };
		ID3D12SDKConfiguration1Wrapper::InsertD3D12SDKConfiguration1(wrap_object, static_cast<ID3D12SDKConfiguration1Wrapper *>(*object));
	}

	void WrapID3D12DeviceFactory(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12DeviceFactoryWrapper::QueryExistingD3D12DeviceFactory(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12DeviceFactoryWrapper{ riid, wrap_object };
		ID3D12DeviceFactoryWrapper::InsertD3D12DeviceFactory(wrap_object, static_cast<ID3D12DeviceFactoryWrapper *>(*object));
	}

	void WrapID3D12DeviceConfiguration(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12DeviceConfiguration1Wrapper::QueryExistingD3D12DeviceConfiguration1(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12DeviceConfiguration1Wrapper{ riid, wrap_object };
		ID3D12DeviceConfiguration1Wrapper::InsertD3D12DeviceConfiguration1(wrap_object, static_cast<ID3D12DeviceConfiguration1Wrapper *>(*object));
	}

	void WrapID3D12CommandList(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12GraphicsCommandList10Wrapper::QueryExistingD3D12GraphicsCommandList(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12GraphicsCommandList10Wrapper{ riid, wrap_object };
		ID3D12GraphicsCommandList10Wrapper::InsertD3D12GraphicsCommandList(wrap_object, static_cast<ID3D12GraphicsCommandList10Wrapper *>(*object));
	}

	void WrapID3D12DSRDeviceFactory(const IID &riid, void **object)
	{
		// TODO: consider existing object, currently do no consider dsr
	}

	void WrapID3D10Blob(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing =  ID3D10BlobWrapper::QueryExistingD3D10Blob(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D10BlobWrapper{ riid, wrap_object };
		ID3D10BlobWrapper::InsertD3D10Blob(*object, static_cast<ID3D10BlobWrapper *>(*object));
	}

	void WrapID3DDestructionNotifier(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3DDestructionNotifierWrapper::QueryExistingD3D12DestructionNotifier(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3DDestructionNotifierWrapper{ riid, wrap_object };
		ID3DDestructionNotifierWrapper::InsertD3D12DestructionNotifier(wrap_object, static_cast<ID3DDestructionNotifierWrapper *>(*object));
	}

	void WrapID3D12Debug(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing =  ID3D12Debug6Wrapper::QueryExistingD3D12Debug6(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12Debug6Wrapper{ riid, wrap_object };
		ID3D12Debug6Wrapper::InsertD3D12Debug6(wrap_object, static_cast<ID3D12Debug6Wrapper *>(*object));
	}

	void WrapID3D12Debug1(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12Debug1Wrapper::QueryExistingD3D12Debug1(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12Debug1Wrapper{ riid, wrap_object };
		ID3D12Debug1Wrapper::InsertD3D12Debug1(wrap_object, static_cast<ID3D12Debug1Wrapper *>(*object));
	}

	void WrapID3D12Debug2(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing =  ID3D12Debug2Wrapper::QueryExistingD3D12Debug2(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12Debug2Wrapper{ riid, wrap_object };
		ID3D12Debug2Wrapper::InsertD3D12Debug2(wrap_object, static_cast<ID3D12Debug2Wrapper *>(*object));
	}

	void WrapID3D12DebugDevice(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing =  ID3D12DebugDevice2Wrapper::QueryExistingD3D12DebugDevice2(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12DebugDevice2Wrapper{ riid, wrap_object };
		ID3D12DebugDevice2Wrapper::InsertD3D12DebugDevice2(wrap_object, static_cast<ID3D12DebugDevice2Wrapper *>(*object));
	}

	void WrapID3D12DebugDevice1(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing =  ID3D12DebugDevice1Wrapper::QueryExistingD3D12DebugDevice1(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12DebugDevice1Wrapper{ riid, wrap_object };
		ID3D12DebugDevice1Wrapper::InsertD3D12DebugDevice1(wrap_object, static_cast<ID3D12DebugDevice1Wrapper *>(*object));
	}

	void WrapID3D12DebugCommandQueue(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing =  ID3D12DebugCommandQueue1Wrapper::QueryExistingD3D12DebugCommandQueue(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12DebugCommandQueue1Wrapper{ riid, wrap_object };
		ID3D12DebugCommandQueue1Wrapper::InsertD3D12DebugCommandQueue(wrap_object, static_cast<ID3D12DebugCommandQueue1Wrapper *>(*object));
	}

	void WrapID3D12DebugCommandList(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12DebugCommandList3Wrapper::QueryExistingD3D12DebugCommandList3(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12DebugCommandList3Wrapper{ riid, wrap_object };
		ID3D12DebugCommandList3Wrapper::InsertD3D12DebugCommandList3(wrap_object, static_cast<ID3D12DebugCommandList3Wrapper *>(*object));
	}

	void WrapID3D12DebugCommandList1(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12DebugCommandList1Wrapper::QueryExistingD3D12DebugCommandList1(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12DebugCommandList1Wrapper{ riid, wrap_object };
		ID3D12DebugCommandList1Wrapper::InsertD3D12DebugCommandList1(wrap_object, static_cast<ID3D12DebugCommandList1Wrapper *>(*object));
	}

	void WrapID3D12SharingContract(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12SharingContractWrapper::QueryExistingD3D12SharingContract(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12SharingContractWrapper{ riid, wrap_object };
		ID3D12SharingContractWrapper::InsertD3D12SharingContract(wrap_object, static_cast<ID3D12SharingContractWrapper *>(*object));
	}

	void WrapID3D12ManualWriteTrackingResource(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12ManualWriteTrackingResourceWrapper::QueryExistingD3D12ManualResource(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12ManualWriteTrackingResourceWrapper{ riid, wrap_object };
		ID3D12ManualWriteTrackingResourceWrapper::InsertD3D12ManualResource(wrap_object, static_cast<ID3D12ManualWriteTrackingResourceWrapper *>(*object));
	}

	void WrapID3D12InfoQueue(const IID &riid, void **object)
	{
		// TODO: consider existing object
		auto wrap_object = static_cast<IUnknown *>(*object);
		auto existing = ID3D12InfoQueue1Wrapper::QueryExistingD3D12InfoQueue1(wrap_object);
		if (existing != nullptr)
		{
			existing->AddRef();
			*object = existing;
			return;
		}

		*object = new ID3D12InfoQueue1Wrapper{ riid, wrap_object };
		ID3D12InfoQueue1Wrapper::InsertD3D12InfoQueue1(wrap_object, static_cast<ID3D12InfoQueue1Wrapper *>(*object));
	}

}