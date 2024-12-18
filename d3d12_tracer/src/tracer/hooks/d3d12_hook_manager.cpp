//
// Created by ZZK on 2024/7/25.
//

#include <tracer/core/wrapper_creators.h>
#include <tracer/d3d12/d3d12_command_allocator_wrap.h>
#include <tracer/d3d12/d3d12_command_list_wrap.h>
#include <tracer/d3d12/d3d12_command_queue_wrap.h>
#include <tracer/d3d12/d3d12_device_wrap.h>
#include <tracer/hooks/d3d12_hook_manager.h>

namespace gfxshim
{
    D3D12HookManager::D3D12HookManager()
    : resource_manager_impl(std::make_unique<ResourceManagerImpl>())
    {
        AllocConsole();
        freopen_s(reinterpret_cast<FILE **>(stdout), "CONOUT$", "w", stdout);
        D3D12_WRAPPER_DEBUG("Initialized D3D12 hook manager successfully");
    }

    D3D12HookManager::~D3D12HookManager()
    {
        for (auto &&wrapped_resource_pair : wrapped_resource_storage)
        {
            DestroyResource(wrapped_resource_pair.second);
        }
        resource_manager_impl->wrapped_device_pool.deallocate();
        resource_manager_impl->wrapped_command_queue_pool.deallocate();
        resource_manager_impl->wrapped_command_allocator_pool.deallocate();
        resource_manager_impl->wrapped_command_list_pool.deallocate();

        D3D12_WRAPPER_DEBUG("Release D3D12 hook manager successfully");
    }

    void D3D12HookManager::DestroyResource(const WrappedResource &wrapped_resource)
    {
        if (wrapped_resource.resource_type == WrappedResourceType::Device)
        {
            DestroyResource<WrappedID3D12Device>(static_cast<WrappedID3D12Device *>(wrapped_resource.raw_resource_ptr));
        } else if (wrapped_resource.resource_type == WrappedResourceType::CommandQueue)
        {
            DestroyResource<WrappedID3D12CommandQueue>(static_cast<WrappedID3D12CommandQueue *>(wrapped_resource.raw_resource_ptr));
        } else if (wrapped_resource.resource_type == WrappedResourceType::CommandAllocator)
        {
            DestroyResource<WrappedID3D12CommandAllocator>(static_cast<WrappedID3D12CommandAllocator *>(wrapped_resource.raw_resource_ptr));
        } else if (wrapped_resource.resource_type == WrappedResourceType::GraphicsCommandList)
        {
            DestroyResource<WrappedID3D12GraphicsCommandList>(static_cast<WrappedID3D12GraphicsCommandList *>(wrapped_resource.raw_resource_ptr));
        }
    }

    void D3D12HookManager::RegisterCommandListTracer(ID3D12GraphicsCommandList *command_list_pointer)
    {
        static uint32_t command_list_id = 0;
        if (!command_list_tracer_storage.contains(command_list_pointer))
        {
            command_list_tracer_storage[command_list_pointer] = std::make_unique<D3D12CommandListTracer>(device_tracer, command_list_id);
            ++command_list_id;
        }
    }

    void D3D12HookManager::StoreRTVAndResource(uint64_t rtv_descriptor, ID3D12Resource *resource, const D3D12_RENDER_TARGET_VIEW_DESC *render_target_view_desc)
    {
        device_tracer.StoreRTVAndResource(rtv_descriptor, resource, render_target_view_desc);
    }

    void D3D12HookManager::StoreDSVAndResource(uint64_t dsv_descriptor, ID3D12Resource *resource, const D3D12_DEPTH_STENCIL_VIEW_DESC *depth_stencil_view_desc)
    {
        device_tracer.StoreDSVAndResource(dsv_descriptor, resource, depth_stencil_view_desc);
    }

    void D3D12HookManager::StoreUAVAndResource(uint64_t uav_descriptor, ID3D12Resource *resource, const D3D12_UNORDERED_ACCESS_VIEW_DESC *unordered_access_view_desc)
    {
        device_tracer.StoreUAVAndResource(uav_descriptor, resource, unordered_access_view_desc);
    }

    void D3D12HookManager::StoreRootBufferMapping(ID3D12Resource *buffer)
    {
        device_tracer.StoreRootBufferMapping(buffer);
    }

    void D3D12HookManager::StoreCommandSignature(uint64_t command_signature_pointer, const D3D12_COMMAND_SIGNATURE_DESC *command_signature_desc)
    {
        device_tracer.StoreCommandSignature(command_signature_pointer, command_signature_desc);
    }

    void D3D12HookManager::StoreBlobToRootSignatureDescMapping(uint64_t blob_pointer, const D3D12_ROOT_SIGNATURE_DESC *root_signature_desc)
    {
        device_tracer.StoreBlobToRootSignatureDescMapping(blob_pointer, root_signature_desc);
    }

    void D3D12HookManager::StoreBlobToVersionedRootSignatureDescMapping(uint64_t blob_pointer, const D3D12_VERSIONED_ROOT_SIGNATURE_DESC *versioned_root_signature_desc)
    {
        device_tracer.StoreBlobToVersionedRootSignatureDescMapping(blob_pointer, versioned_root_signature_desc);
    }

    void D3D12HookManager::UpdateBlobToRootSignatureMapping(uint64_t blob_pointer, ID3D12RootSignature *root_signature)
    {
        device_tracer.UpdateBlobToRootSignatureMapping(blob_pointer, root_signature);
    }

    void D3D12HookManager::SetDescriptorSize(ID3D12Device *device)
    {
        device_tracer.SetDescriptorSize(device);
    }

    void D3D12HookManager::UpdateRTVAndDSVStatesPerDraw(ID3D12GraphicsCommandList *command_list_pointer,
                                                        uint32_t render_target_descriptors_num,
                                                        const D3D12_CPU_DESCRIPTOR_HANDLE *render_target_descriptors,
                                                        const D3D12_CPU_DESCRIPTOR_HANDLE *depth_stencil_descriptor)
    {
        if (!command_list_tracer_storage.contains(command_list_pointer))
        {
            return;
        }

        if (render_target_descriptors_num > 0 || depth_stencil_descriptor != nullptr)
        {
            auto &&command_list_tracer = command_list_tracer_storage[command_list_pointer];
            command_list_tracer->ClearRTVAndDSVStatesPerDraw();
            for (uint32_t i = 0; i < render_target_descriptors_num; ++i)
            {
                command_list_tracer->UpdateRTVStatePerDraw(render_target_descriptors[i].ptr);
            }
            if (depth_stencil_descriptor != nullptr)
            {
                command_list_tracer->UpdateDSVStatePerDraw(depth_stencil_descriptor->ptr);
            }
        }
    }

    void D3D12HookManager::UpdateUAVStatePerDraw(ID3D12GraphicsCommandList *command_list_pointer, uint64_t starting_gpu_descriptor)
    {
        if (command_list_tracer_storage.contains(command_list_pointer))
        {
            command_list_tracer_storage[command_list_pointer]->UpdateUAVStatePerDraw(starting_gpu_descriptor);
        }
    }

    void D3D12HookManager::UpdateUAVStatePerDispatch(ID3D12GraphicsCommandList *command_list_pointer, uint64_t starting_gpu_descriptor)
    {
        if (command_list_tracer_storage.contains(command_list_pointer))
        {
            command_list_tracer_storage[command_list_pointer]->UpdateUAVStatePerDispatch(starting_gpu_descriptor);
        }
    }

    void D3D12HookManager::UpdateUAVStatePerDispatch(ID3D12GraphicsCommandList *command_list_pointer, uint32_t root_parameter_index, uint64_t starting_gpu_descriptor)
    {
        if (command_list_tracer_storage.contains(command_list_pointer))
        {
            command_list_tracer_storage[command_list_pointer]->UpdateUAVStatePerDispatch(root_parameter_index, starting_gpu_descriptor);
        }
    }

    void D3D12HookManager::CollectStagingResourcePerDraw(ID3D12Device *device, ID3D12GraphicsCommandList *command_list_pointer)
    {
        if (command_list_tracer_storage.contains(command_list_pointer))
        {
            command_list_tracer_storage[command_list_pointer]->CollectStagingResourcePerDraw(device, command_list_pointer);
        }
    }

    void D3D12HookManager::CollectStagingResourcePerDispatch(ID3D12Device *device, ID3D12GraphicsCommandList *command_list_pointer)
    {
        if (command_list_tracer_storage.contains(command_list_pointer))
        {
            command_list_tracer_storage[command_list_pointer]->CollectStagingResourcePerDispatch(device, command_list_pointer);
        }
    }

    void D3D12HookManager::CollectStagingResourcePerIndirect(ID3D12Device *device, ID3D12GraphicsCommandList *command_list_pointer, uint64_t command_signature_pointer)
    {
        if (command_list_tracer_storage.contains(command_list_pointer))
        {
            command_list_tracer_storage[command_list_pointer]->CollectStagingResourcePerIndirect(device, command_list_pointer, command_signature_pointer);
        }
    }

    void D3D12HookManager::CollectStagingResourcePerBundle(ID3D12Device *device, ID3D12GraphicsCommandList *direct_command_list_pointer, ID3D12GraphicsCommandList *bundle_command_list_pointer)
    {
        if (command_list_tracer_storage.contains(direct_command_list_pointer) && command_list_tracer_storage.contains(bundle_command_list_pointer))
        {
            auto &&direct_command_list_tracer = command_list_tracer_storage[direct_command_list_pointer];
            auto &&bundle_command_list_tracer = command_list_tracer_storage[bundle_command_list_pointer];
            if (const uint32_t draw_count_in_bundle = bundle_command_list_tracer->QueryDrawCountInBundle(); draw_count_in_bundle > 0U)
            {
                direct_command_list_tracer->CollectStagingResourcePerDraw(device, direct_command_list_pointer);
            }
            if (const uint32_t dispatch_count_in_bundle = bundle_command_list_tracer->QueryDispatchCountInBundle(); dispatch_count_in_bundle > 0U)
            {
                direct_command_list_tracer->CollectStagingResourcePerDispatch(device, direct_command_list_pointer);
            }
            // TODO: consider execute indirect
        }
    }

    void D3D12HookManager::ResetDescriptorHeaps(ID3D12GraphicsCommandList *command_list_pointer, uint32_t descriptor_heaps_num, ID3D12DescriptorHeap *const *descriptor_heaps_pointer)
    {
        if (command_list_tracer_storage.contains(command_list_pointer))
        {
            command_list_tracer_storage[command_list_pointer]->ResetDescriptorHeaps(descriptor_heaps_num, descriptor_heaps_pointer);
        }
    }

    void D3D12HookManager::ResetComputePipelineRootSignature(ID3D12GraphicsCommandList *command_list_pointer, ID3D12RootSignature *compute_root_signature)
    {
        if (command_list_tracer_storage.contains(command_list_pointer))
        {
            command_list_tracer_storage[command_list_pointer]->ResetComputePipelineRootSignature(compute_root_signature);
        }
    }

    void D3D12HookManager::PerDrawAndDispatchDump(std::span<ID3D12GraphicsCommandList *> graphics_command_list_pointers, ID3D12Fence *fence, uint64_t fence_value)
    {
        for (auto &&command_list_pointer : graphics_command_list_pointers)
        {
            if (command_list_tracer_storage.contains(command_list_pointer))
            {
                auto &&command_list_tracer = command_list_tracer_storage[command_list_pointer];
                command_list_tracer->PerDrawDump(fence, fence_value);
                command_list_tracer->PerDispatchDump(fence, fence_value);
                command_list_tracer->Advance();
            }
        }
    }

    void D3D12HookManager::InitializeD3D12DispatchTable(const D3D12DispatchTable &in_d3d12_dispatch_table)
    {
        d3d12_dispatch_table = in_d3d12_dispatch_table;
    }

    void D3D12HookManager::InitializeDXGIDispatchTable(const DXGIDispatchTable &in_dxgi_dispatch_table)
    {
        dxgi_dispatch_table = in_dxgi_dispatch_table;
    }

    const D3D12DispatchTable &D3D12HookManager::QueryD3D12DispatchTable() const
    {
        return d3d12_dispatch_table;
    }

    const DXGIDispatchTable &D3D12HookManager::QueryDXGIDispatchTable() const
    {
        return dxgi_dispatch_table;
    }

    D3D12HookManager &D3D12HookManager::GetInstance()
    {
        static D3D12HookManager s_d3d12_hook_manager{};
        return s_d3d12_hook_manager;
    }

    // Wrap d3d12 exported functions
    HRESULT WINAPI D3D12HookManager::D3D12GetDebugInterface(_In_ REFIID riid, _COM_Outptr_opt_ void **ppvDebug)
    {
        HRESULT result = E_UNEXPECTED;
        auto &&d3d12_dispatch_table = D3D12HookManager::GetInstance().QueryD3D12DispatchTable();
        if (d3d12_dispatch_table.D3D12GetDebugInterface != nullptr)
        {
            result = d3d12_dispatch_table.D3D12GetDebugInterface(riid, ppvDebug);
            D3D12_WRAPPER_DEBUG("Invoke D3D12GetDebugInterface");
			if (SUCCEEDED(result))
			{
				encode::WrapObject(riid, ppvDebug);
			}
        }
        return result;
    }

    HRESULT WINAPI D3D12HookManager::D3D12GetInterface(_In_ REFCLSID rclsid, _In_ REFIID riid, _COM_Outptr_opt_ void **ppvDebug)
    {
        HRESULT result = E_UNEXPECTED;
        auto &&d3d12_dispatch_table = D3D12HookManager::GetInstance().QueryD3D12DispatchTable();
        if (d3d12_dispatch_table.D3D12GetInterface != nullptr)
        {
            result = d3d12_dispatch_table.D3D12GetInterface(rclsid, riid, ppvDebug);
            D3D12_WRAPPER_DEBUG("Invoke D3D12GetInterface");
			if (SUCCEEDED(result))
			{
				encode::WrapObject(riid, ppvDebug);
			}
        }
        return result;
    }

    HRESULT WINAPI D3D12HookManager::D3D12CreateDevice(_In_opt_ IUnknown *pAdapter,
                                                        D3D_FEATURE_LEVEL MinimumFeatureLevel,
                                                        _In_ REFIID riid,
                                                        _COM_Outptr_opt_ void **ppDevice)
    {
		HRESULT result = E_UNEXPECTED;
		auto &&d3d12_dispatch_table = D3D12HookManager::GetInstance().QueryD3D12DispatchTable();
		if (d3d12_dispatch_table.D3D12CreateDevice != nullptr)
		{
		    result = d3d12_dispatch_table.D3D12CreateDevice(encode::GetWrappedObject<IUnknown>(pAdapter), MinimumFeatureLevel, riid, ppDevice);
		    D3D12_WRAPPER_DEBUG("Invoke D3D12CreateDevice");
		    if (SUCCEEDED(result) && ppDevice != nullptr && (*ppDevice != nullptr))
		    {
				auto unwrapped_device = *ppDevice;
				encode::WrapObject(riid, ppDevice);
				D3D12_WRAPPER_DEBUG("Real device pointer: {}, wrapped device pointer: {}", unwrapped_device, *ppDevice);
		    }
			return result;
		}
		// Old method
        if(SUCCEEDED(result) && ppDevice != nullptr && (*ppDevice != nullptr))
        {
            if(riid == __uuidof(ID3D12Device)   || riid == __uuidof(ID3D12Device2)  || riid == __uuidof(ID3D12Device3)  || riid == __uuidof(ID3D12Device4) ||
               riid == __uuidof(ID3D12Device5)  || riid == __uuidof(ID3D12Device6)  || riid == __uuidof(ID3D12Device7)  || riid == __uuidof(ID3D12Device8) ||
               riid == __uuidof(ID3D12Device9)  || riid == __uuidof(ID3D12Device10) || riid == __uuidof(ID3D12Device11) || riid == __uuidof(ID3D12Device12)||
               riid == __uuidof(ID3D12Device13) || riid == __uuidof(ID3D12Device14))
            {
                auto &&d3d12_hook_manager = D3D12HookManager::GetInstance();
                auto *real_device = static_cast<ID3D12Device *>(*ppDevice);
                auto *wrapped_device = d3d12_hook_manager.ConstructResource<WrappedID3D12Device>(real_device);
                d3d12_hook_manager.SetDescriptorSize(real_device);
                *ppDevice = wrapped_device;
                D3D12_WRAPPER_DEBUG("Wrapped device pointer: {}", reinterpret_cast<void *>(wrapped_device));
            }
        }

        return result;
    }

    HRESULT WINAPI D3D12HookManager::D3D12SerializeRootSignature(
            _In_ const D3D12_ROOT_SIGNATURE_DESC *pRootSignature,
            _In_ D3D_ROOT_SIGNATURE_VERSION Version,
            _Out_ ID3DBlob **ppBlob,
            _Always_(_Outptr_opt_result_maybenull_) ID3DBlob **ppErrorBlob)
    {
        HRESULT result = E_UNEXPECTED;
        auto &&d3d12_dispatch_table = D3D12HookManager::GetInstance().QueryD3D12DispatchTable();
        if (d3d12_dispatch_table.D3D12SerializeRootSignature != nullptr)
        {
            result = d3d12_dispatch_table.D3D12SerializeRootSignature(pRootSignature, Version, ppBlob, ppErrorBlob);
			D3D12_WRAPPER_DEBUG("Invoke D3D12SerializeRootSignature");
            if (SUCCEEDED(result) && ppBlob != nullptr && (*ppBlob) != nullptr)
            {
				auto &&d3d12_hook_manager = D3D12HookManager::GetInstance();
				auto blob_pointer = reinterpret_cast<uint64_t>((*ppBlob)->GetBufferPointer());
				d3d12_hook_manager.UpdateBlobToRootSignatureMapping(blob_pointer, nullptr);
				d3d12_hook_manager.StoreBlobToRootSignatureDescMapping(blob_pointer, pRootSignature);
				encode::WrapObject(__uuidof(ID3D10Blob), reinterpret_cast<void **>(ppBlob));
				encode::WrapObject(__uuidof(ID3D10Blob), reinterpret_cast<void **>(ppErrorBlob));
            }
        }
        return result;
    }

    HRESULT WINAPI D3D12HookManager::D3D12SerializeVersionedRootSignature(
            _In_ const D3D12_VERSIONED_ROOT_SIGNATURE_DESC *pRootSignature,
            _Out_ ID3DBlob **ppBlob,
            _Always_(_Outptr_opt_result_maybenull_) ID3DBlob **ppErrorBlob)
    {
        HRESULT result = E_UNEXPECTED;
        auto &&d3d12_dispatch_table = D3D12HookManager::GetInstance().QueryD3D12DispatchTable();
        if (d3d12_dispatch_table.D3D12SerializeVersionedRootSignature != nullptr)
        {
            result = d3d12_dispatch_table.D3D12SerializeVersionedRootSignature(pRootSignature, ppBlob, ppErrorBlob);
			D3D12_WRAPPER_DEBUG("Invoke D3D12SerializeVersionedRootSignature");
            if (SUCCEEDED(result) && ppBlob != nullptr && (*ppBlob) != nullptr)
            {
				auto &&d3d12_hook_manager = D3D12HookManager::GetInstance();
				auto blob_pointer = reinterpret_cast<uint64_t>((*ppBlob)->GetBufferPointer());
				d3d12_hook_manager.UpdateBlobToRootSignatureMapping(blob_pointer, nullptr);
				d3d12_hook_manager.StoreBlobToVersionedRootSignatureDescMapping(blob_pointer, pRootSignature);
				encode::WrapObject(__uuidof(ID3D10Blob), reinterpret_cast<void **>(ppBlob));
				encode::WrapObject(__uuidof(ID3D10Blob), reinterpret_cast<void **>(ppErrorBlob));
            }
        }
        return result;
    }

    HRESULT WINAPI D3D12HookManager::D3D12CreateRootSignatureDeserializer(
            _In_reads_bytes_(SrcDataSizeInBytes) LPCVOID pSrcData,
            _In_ SIZE_T SrcDataSizeInBytes,
            _In_ REFIID pRootSignatureDeserializerInterface,
            _Out_ void **ppRootSignatureDeserializer)
    {
        HRESULT result = E_UNEXPECTED;
        auto &&d3d12_dispatch_table = D3D12HookManager::GetInstance().QueryD3D12DispatchTable();
        if (d3d12_dispatch_table.D3D12CreateRootSignatureDeserializer != nullptr)
        {
            result = d3d12_dispatch_table.D3D12CreateRootSignatureDeserializer(pSrcData, SrcDataSizeInBytes, pRootSignatureDeserializerInterface, ppRootSignatureDeserializer);
            D3D12_WRAPPER_DEBUG("Invoke D3D12CreateRootSignatureDeserializer");
			if (SUCCEEDED(result))
			{
				encode::WrapObject(pRootSignatureDeserializerInterface, ppRootSignatureDeserializer);
			}
        }
        return result;
    }

    HRESULT WINAPI D3D12HookManager::D3D12CreateVersionedRootSignatureDeserializer(
            _In_reads_bytes_(SrcDataSizeInBytes) LPCVOID pSrcData,
            _In_ SIZE_T SrcDataSizeInBytes,
            _In_ REFIID pRootSignatureDeserializerInterface,
            _Out_ void **ppRootSignatureDeserializer)
    {
        HRESULT result = E_UNEXPECTED;
        auto &&d3d12_dispatch_table = D3D12HookManager::GetInstance().QueryD3D12DispatchTable();
        if (d3d12_dispatch_table.D3D12CreateVersionedRootSignatureDeserializer != nullptr)
        {
            result = d3d12_dispatch_table.D3D12CreateVersionedRootSignatureDeserializer(pSrcData, SrcDataSizeInBytes, pRootSignatureDeserializerInterface, ppRootSignatureDeserializer);
            D3D12_WRAPPER_DEBUG("Invoke D3D12CreateVersionedRootSignatureDeserializer");
			if (SUCCEEDED(result))
			{
				encode::WrapObject(pRootSignatureDeserializerInterface, ppRootSignatureDeserializer);
			}
        }
        return result;
    }

    HRESULT WINAPI D3D12HookManager::D3D12EnableExperimentalFeatures(
            UINT                               NumFeatures,
            _In_count_(NumFeatures) const IID *pIIDs,
            _In_opt_count_(NumFeatures) void  *pConfigurationStructs,
            _In_opt_count_(NumFeatures) UINT  *pConfigurationStructSizes)
    {
        HRESULT result = E_UNEXPECTED;
        auto &&d3d12_dispatch_table = D3D12HookManager::GetInstance().QueryD3D12DispatchTable();
        if (d3d12_dispatch_table.D3D12EnableExperimentalFeatures != nullptr)
        {
            result = d3d12_dispatch_table.D3D12EnableExperimentalFeatures(NumFeatures, pIIDs, pConfigurationStructs, pConfigurationStructSizes);
            D3D12_WRAPPER_DEBUG("Invoke D3D12EnableExperimentalFeatures");
        }
        return result;
    }

    // Wrap dxgi exported functions
    HRESULT D3D12HookManager::CreateDXGIFactory(const IID &riid, void **ppFactory)
    {
        HRESULT result = E_UNEXPECTED;
        auto &&dxgi_dispatch_table = D3D12HookManager::GetInstance().QueryDXGIDispatchTable();
        if (dxgi_dispatch_table.DXGICreateFactory != nullptr)
        {
            result = dxgi_dispatch_table.DXGICreateFactory(riid, ppFactory);
            D3D12_WRAPPER_DEBUG("Invoke CreateDXGIFactory");
			if (SUCCEEDED(result))
			{
				encode::WrapObject(riid, ppFactory);
			}
        }
        return result;
    }

    HRESULT D3D12HookManager::CreateDXGIFactory1(const IID &riid, void **ppFactory)
    {
        HRESULT result = E_UNEXPECTED;
        auto &&dxgi_dispatch_table = D3D12HookManager::GetInstance().QueryDXGIDispatchTable();
        if (dxgi_dispatch_table.DXGICreateFactory1 != nullptr)
        {
            result = dxgi_dispatch_table.DXGICreateFactory1(riid, ppFactory);
            D3D12_WRAPPER_DEBUG("Invoke CreateDXGIFactory1");
			if (SUCCEEDED(result))
			{
				encode::WrapObject(riid, ppFactory);
			}
        }
        return result;
    }

    HRESULT D3D12HookManager::CreateDXGIFactory2(UINT Flags, const IID &riid, void **ppFactory)
    {
        HRESULT result = E_UNEXPECTED;
        auto &&dxgi_dispatch_table = D3D12HookManager::GetInstance().QueryDXGIDispatchTable();
        if (dxgi_dispatch_table.DXGICreateFactory2 != nullptr)
        {
            result = dxgi_dispatch_table.DXGICreateFactory2(Flags, riid, ppFactory);
            D3D12_WRAPPER_DEBUG("Invoke CreateDXGIFactory2");
			if (SUCCEEDED(result) && ppFactory != nullptr && *ppFactory != nullptr)
			{
				encode::WrapObject(riid, ppFactory);
			}
        }
        return result;
    }

    HRESULT D3D12HookManager::DXGIGetDebugInterface1(UINT Flags, const IID &riid, void **ppDebug)
    {
        HRESULT result = E_UNEXPECTED;
        auto &&dxgi_dispatch_table = D3D12HookManager::GetInstance().QueryDXGIDispatchTable();
        if (dxgi_dispatch_table.DXGIGetDebugInterface1 != nullptr)
        {
            result = dxgi_dispatch_table.DXGIGetDebugInterface1(Flags, riid, ppDebug);
            D3D12_WRAPPER_DEBUG("Invoke DXGIGetDebugInterface1");
			if (SUCCEEDED(result))
			{
				encode::WrapObject(riid, ppDebug);
			}
        }
        return result;
    }

    HRESULT D3D12HookManager::DXGIDeclareAdapterRemovalSupport()
    {
        HRESULT result = E_UNEXPECTED;
        auto &&dxgi_dispatch_table = D3D12HookManager::GetInstance().QueryDXGIDispatchTable();
        if (dxgi_dispatch_table.DXGIDeclareAdapterRemovalSupport != nullptr)
        {
            result = dxgi_dispatch_table.DXGIDeclareAdapterRemovalSupport();
            D3D12_WRAPPER_DEBUG("Invoke DXGIDeclareAdapterRemovalSupport");
        }
        return result;
    }
}