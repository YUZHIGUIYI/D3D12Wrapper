//
// Created by ZZK on 2024/11/21.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim::encode
{
	struct IIDHash
	{
		std::size_t operator()(REFIID riid) const noexcept
		{
			const auto *ptr = reinterpret_cast<const uint32_t *>(&riid);
			return ptr[0] ^ ptr[1] ^ ptr[2] ^ ptr[3];
		}
	};

	void WrapObject(REFIID riid, void **object);

	void WrapObjectArray(REFIID riid, void **object, uint32_t num_object);

	void WrapIDXGIKeyedMutex(REFIID riid, void **object);

	void WrapIDXGIDisplayControl(REFIID riid, void **object);

	void WrapIDXGIOutputDuplication(REFIID riid, void **object);

	void WrapIDXGISurface(REFIID riid, void **object);

	void WrapIDXGIResource(REFIID riid, void **object);

	void WrapIDXGIDecodeSwapChain(REFIID riid, void **object);

	void WrapIDXGIFactoryMedia(REFIID riid, void **object);

	void WrapIDXGISwapChainMedia(REFIID riid, void **object);

	void WrapIDXGISwapChain(REFIID riid, void **object);

	void WrapIDXGIDevice(REFIID riid, void **object);

	void WrapIDXGIAdapter(REFIID riid, void **object);

	void WrapIDXGIOutput(REFIID riid, void **object);

	void WrapIDXGIFactory(REFIID riid, void **object);

	void WrapID3D12RootSignature(REFIID riid, void **object);

	void WrapID3D12RootSignatureDeserializer(REFIID riid, void **object);

	void WrapID3D12VersionedRootSignatureDeserializer(REFIID riid, void **object);

	void WrapID3D12CommandAllocator(REFIID riid, void **object);

	void WrapID3D12Fence(REFIID riid, void **object);

	void WrapID3D12PipelineState(REFIID riid, void **object);

	void WrapID3D12DescriptorHeap(REFIID riid, void **object);

	void WrapID3D12QueryHeap(REFIID riid, void **object);

	void WrapID3D12CommandSignature(REFIID riid, void **object);

	void WrapID3D12CommandQueue(REFIID riid, void **object);

	void WrapID3D12PipelineLibrary(REFIID riid, void **object);

	void WrapID3D12LifetimeOwner(REFIID riid, void **object);

	void WrapID3D12SwapChainAssistant(REFIID riid, void **object);

	void WrapID3D12LifetimeTracker(REFIID riid, void **object);

	void WrapID3D12StateObject(REFIID riid, void **object);

	void WrapID3D12StateObjectProperties(REFIID riid, void **object);

	void WrapID3D12DeviceRemovedExtendedDataSettings(REFIID riid, void **object);

	void WrapID3D12DeviceRemovedExtendedData(REFIID riid, void **object);

	void WrapID3D12ProtectedResourceSession(REFIID riid, void **object);

	void WrapID3D12Resource(REFIID riid, void **object);

	void WrapID3D12Heap(REFIID riid, void **object);

	void WrapID3D12MetaCommand(REFIID riid, void **object);

	void WrapID3D12ShaderCacheSession(REFIID riid, void **object);

	void WrapID3D12Device(REFIID riid, void **object);

	void WrapID3D12VirtualizationGuestDevice(REFIID riid, void **object);

	void WrapID3D12Tools(REFIID riid, void **object);

	void WrapID3D12SDKConfiguration(REFIID riid, void **object);

	void WrapID3D12DeviceFactory(REFIID riid, void **object);

	void WrapID3D12DeviceConfiguration(REFIID riid, void **object);

	void WrapID3D12CommandList(REFIID riid, void **object);

	void WrapID3D12DSRDeviceFactory(REFIID riid, void **object);

	void WrapID3D10Blob(REFIID riid, void **object);

	void WrapID3DDestructionNotifier(REFIID riid, void **object);

	void WrapID3D12Debug(REFIID riid, void **object);

	void WrapID3D12Debug1(REFIID riid, void **object);

	void WrapID3D12Debug2(REFIID riid, void **object);

	void WrapID3D12DebugDevice(REFIID riid, void **object);

	void WrapID3D12DebugDevice1(REFIID riid, void **object);

	void WrapID3D12DebugCommandQueue(REFIID riid, void **object);

	void WrapID3D12DebugCommandList(REFIID riid, void **object);

	void WrapID3D12DebugCommandList1(REFIID riid, void **object);

	void WrapID3D12SharingContract(REFIID riid, void **object);

	void WrapID3D12ManualWriteTrackingResource(REFIID riid, void **object);

	void WrapID3D12InfoQueue(REFIID riid, void **object);

	const std::unordered_map<IID, std::function<void(REFIID, void **)>, IIDHash> kWrapFunctionTable{
		{ __uuidof(IDXGIKeyedMutex), WrapIDXGIKeyedMutex },
		{ __uuidof(IDXGIDisplayControl), WrapIDXGIDisplayControl },
		{ __uuidof(IDXGIOutputDuplication), WrapIDXGIOutputDuplication },
		{ __uuidof(IDXGISurface), WrapIDXGISurface },
		{ __uuidof(IDXGISurface1), WrapIDXGISurface },
		{ __uuidof(IDXGISurface2), WrapIDXGISurface },
		{ __uuidof(IDXGIResource), WrapIDXGIResource },
		{ __uuidof(IDXGIResource1), WrapIDXGIResource },
		{ __uuidof(IDXGIDecodeSwapChain), WrapIDXGIDecodeSwapChain },
		{ __uuidof(IDXGIFactoryMedia), WrapIDXGIFactoryMedia },
		{ __uuidof(IDXGISwapChainMedia), WrapIDXGISwapChainMedia },
		{ __uuidof(IDXGISwapChain), WrapIDXGISwapChain },
		{ __uuidof(IDXGISwapChain1), WrapIDXGISwapChain },
		{ __uuidof(IDXGISwapChain2), WrapIDXGISwapChain },
		{ __uuidof(IDXGISwapChain3), WrapIDXGISwapChain },
		{ __uuidof(IDXGISwapChain4), WrapIDXGISwapChain },
		{ __uuidof(IDXGIDevice), WrapIDXGIDevice },
		{ __uuidof(IDXGIDevice1), WrapIDXGIDevice },
		{ __uuidof(IDXGIDevice2), WrapIDXGIDevice },
		{ __uuidof(IDXGIDevice3), WrapIDXGIDevice },
		{ __uuidof(IDXGIDevice4), WrapIDXGIDevice },
		{ __uuidof(IDXGIAdapter), WrapIDXGIAdapter },
		{ __uuidof(IDXGIAdapter1), WrapIDXGIAdapter },
		{ __uuidof(IDXGIAdapter2), WrapIDXGIAdapter },
		{ __uuidof(IDXGIAdapter3), WrapIDXGIAdapter },
		{ __uuidof(IDXGIAdapter4), WrapIDXGIAdapter },
		{ __uuidof(IDXGIOutput), WrapIDXGIOutput },
		{ __uuidof(IDXGIOutput1), WrapIDXGIOutput },
		{ __uuidof(IDXGIOutput2), WrapIDXGIOutput },
		{ __uuidof(IDXGIOutput3), WrapIDXGIOutput },
		{ __uuidof(IDXGIOutput4), WrapIDXGIOutput },
		{ __uuidof(IDXGIOutput5), WrapIDXGIOutput },
		{ __uuidof(IDXGIOutput6), WrapIDXGIOutput },
		{ __uuidof(IDXGIFactory), WrapIDXGIFactory },
		{ __uuidof(IDXGIFactory1), WrapIDXGIFactory },
		{ __uuidof(IDXGIFactory2), WrapIDXGIFactory },
		{ __uuidof(IDXGIFactory3), WrapIDXGIFactory },
		{ __uuidof(IDXGIFactory4), WrapIDXGIFactory },
		{ __uuidof(IDXGIFactory5), WrapIDXGIFactory },
		{ __uuidof(IDXGIFactory6), WrapIDXGIFactory },
		{ __uuidof(IDXGIFactory7), WrapIDXGIFactory },
		{ __uuidof(ID3D12RootSignature), WrapID3D12RootSignature },
		{ __uuidof(ID3D12RootSignatureDeserializer), WrapID3D12RootSignatureDeserializer },
		{ __uuidof(ID3D12VersionedRootSignatureDeserializer), WrapID3D12VersionedRootSignatureDeserializer },
		{ __uuidof(ID3D12CommandAllocator), WrapID3D12CommandAllocator },
		{ __uuidof(ID3D12Fence), WrapID3D12Fence },
		{ __uuidof(ID3D12Fence1), WrapID3D12Fence },
		{ __uuidof(ID3D12PipelineState), WrapID3D12PipelineState },
		{ __uuidof(ID3D12DescriptorHeap), WrapID3D12DescriptorHeap },
		{ __uuidof(ID3D12QueryHeap), WrapID3D12QueryHeap },
		{ __uuidof(ID3D12CommandSignature), WrapID3D12CommandSignature },
		{ __uuidof(ID3D12CommandQueue), WrapID3D12CommandQueue },
		{ __uuidof(ID3D12PipelineLibrary), WrapID3D12PipelineLibrary },
		{ __uuidof(ID3D12PipelineLibrary1), WrapID3D12PipelineLibrary },
		{ __uuidof(ID3D12LifetimeOwner), WrapID3D12LifetimeOwner },
		{ __uuidof(ID3D12SwapChainAssistant), WrapID3D12SwapChainAssistant },
		{ __uuidof(ID3D12LifetimeTracker), WrapID3D12LifetimeTracker },
		{ __uuidof(ID3D12StateObject), WrapID3D12StateObject },
		{ __uuidof(ID3D12StateObjectProperties), WrapID3D12StateObjectProperties },
		{ __uuidof(ID3D12DeviceRemovedExtendedDataSettings), WrapID3D12DeviceRemovedExtendedDataSettings },
		{ __uuidof(ID3D12DeviceRemovedExtendedDataSettings1), WrapID3D12DeviceRemovedExtendedDataSettings },
		{ __uuidof(ID3D12DeviceRemovedExtendedDataSettings2), WrapID3D12DeviceRemovedExtendedDataSettings },
		{ __uuidof(ID3D12DeviceRemovedExtendedData), WrapID3D12DeviceRemovedExtendedData },
		{ __uuidof(ID3D12DeviceRemovedExtendedData1), WrapID3D12DeviceRemovedExtendedData },
		{ __uuidof(ID3D12DeviceRemovedExtendedData2), WrapID3D12DeviceRemovedExtendedData },
		{ __uuidof(ID3D12ProtectedResourceSession), WrapID3D12ProtectedResourceSession },
		{ __uuidof(ID3D12ProtectedResourceSession1), WrapID3D12ProtectedResourceSession },
		{ __uuidof(ID3D12Resource), WrapID3D12Resource },
		{ __uuidof(ID3D12Resource1), WrapID3D12Resource },
		{ __uuidof(ID3D12Resource2), WrapID3D12Resource },
		{ __uuidof(ID3D12Heap), WrapID3D12Heap },
		{ __uuidof(ID3D12Heap1), WrapID3D12Heap },
		{ __uuidof(ID3D12MetaCommand), WrapID3D12MetaCommand },
		{ __uuidof(ID3D12ShaderCacheSession), WrapID3D12ShaderCacheSession },
		{ __uuidof(ID3D12Device), WrapID3D12Device },
		{ __uuidof(ID3D12Device1), WrapID3D12Device },
		{ __uuidof(ID3D12Device2), WrapID3D12Device },
		{ __uuidof(ID3D12Device3), WrapID3D12Device },
		{ __uuidof(ID3D12Device4), WrapID3D12Device },
		{ __uuidof(ID3D12Device5), WrapID3D12Device },
		{ __uuidof(ID3D12Device6), WrapID3D12Device },
		{ __uuidof(ID3D12Device7), WrapID3D12Device },
		{ __uuidof(ID3D12Device8), WrapID3D12Device },
		{ __uuidof(ID3D12Device9), WrapID3D12Device },
		{ __uuidof(ID3D12Device10), WrapID3D12Device },
		{ __uuidof(ID3D12Device11), WrapID3D12Device },
		{ __uuidof(ID3D12Device12), WrapID3D12Device },
		{ __uuidof(ID3D12VirtualizationGuestDevice), WrapID3D12VirtualizationGuestDevice },
		{ __uuidof(ID3D12Tools), WrapID3D12Tools },
		{ __uuidof(ID3D12SDKConfiguration), WrapID3D12SDKConfiguration },
		{ __uuidof(ID3D12SDKConfiguration1), WrapID3D12SDKConfiguration },
		{ __uuidof(ID3D12DeviceFactory), WrapID3D12DeviceFactory },
		{ __uuidof(ID3D12DeviceConfiguration), WrapID3D12DeviceConfiguration },
		{ __uuidof(ID3D12CommandList), WrapID3D12CommandList },
		{ __uuidof(ID3D12GraphicsCommandList), WrapID3D12CommandList },
		{ __uuidof(ID3D12GraphicsCommandList1), WrapID3D12CommandList },
		{ __uuidof(ID3D12GraphicsCommandList2), WrapID3D12CommandList },
		{ __uuidof(ID3D12GraphicsCommandList3), WrapID3D12CommandList },
		{ __uuidof(ID3D12GraphicsCommandList4), WrapID3D12CommandList },
		{ __uuidof(ID3D12GraphicsCommandList5), WrapID3D12CommandList },
		{ __uuidof(ID3D12GraphicsCommandList6), WrapID3D12CommandList },
		{ __uuidof(ID3D12GraphicsCommandList7), WrapID3D12CommandList },
		{ __uuidof(ID3D12GraphicsCommandList8), WrapID3D12CommandList },
		{ __uuidof(ID3D12GraphicsCommandList9), WrapID3D12CommandList },
		// { IID_ID3D12DSRDeviceFactory, WrapID3D12DSRDeviceFactory },  // TODO: add
		{ __uuidof(ID3D10Blob), WrapID3D10Blob },
		{ __uuidof(ID3DDestructionNotifier), WrapID3DDestructionNotifier },
		{ __uuidof(ID3D12Debug1), WrapID3D12Debug1 },
		{ __uuidof(ID3D12Debug2), WrapID3D12Debug2 },
		{ __uuidof(ID3D12Debug), WrapID3D12Debug },
		{ __uuidof(ID3D12Debug1), WrapID3D12Debug },
		{ __uuidof(ID3D12Debug2), WrapID3D12Debug },
		{ __uuidof(ID3D12Debug3), WrapID3D12Debug },
		{ __uuidof(ID3D12Debug4), WrapID3D12Debug },
		{ __uuidof(ID3D12Debug5), WrapID3D12Debug },
		{ __uuidof(ID3D12Debug6), WrapID3D12Debug },
		{ __uuidof(ID3D12DebugDevice1), WrapID3D12DebugDevice1 },
		{ __uuidof(ID3D12DebugDevice), WrapID3D12DebugDevice },
		{ __uuidof(ID3D12DebugDevice1), WrapID3D12DebugDevice },
		{ __uuidof(ID3D12DebugDevice2), WrapID3D12DebugDevice },
		{ __uuidof(ID3D12DebugCommandQueue), WrapID3D12DebugCommandQueue },
		{ __uuidof(ID3D12DebugCommandQueue1), WrapID3D12DebugCommandQueue },
		{ __uuidof(ID3D12DebugCommandList1), WrapID3D12DebugCommandList1 },
		{ __uuidof(ID3D12DebugCommandList), WrapID3D12DebugCommandList },
		{ __uuidof(ID3D12DebugCommandList1), WrapID3D12DebugCommandList },
		{ __uuidof(ID3D12DebugCommandList2), WrapID3D12DebugCommandList },
		{ __uuidof(ID3D12DebugCommandList3), WrapID3D12DebugCommandList },
		{ __uuidof(ID3D12SharingContract), WrapID3D12SharingContract },
		{ __uuidof(ID3D12ManualWriteTrackingResource), WrapID3D12ManualWriteTrackingResource },
		{ __uuidof(ID3D12InfoQueue), WrapID3D12InfoQueue },
		{ __uuidof(ID3D12InfoQueue1), WrapID3D12InfoQueue },
	};

}
