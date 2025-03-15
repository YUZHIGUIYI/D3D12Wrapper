//
// Created by ZZK on 2024/7/31.
//

#include <tracer/hooks/d3d12_tracer.h>
#include <format>

namespace gfxshim
{
    static void CollectRootParameter(const uint32_t parameter_index, const D3D12_ROOT_PARAMETER1 &root_parameter, RootSignatureInfo &root_signature_info)
    {
        if (root_parameter.ParameterType != D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE)
        {
            return;
        }

        auto &&root_table = root_parameter.DescriptorTable;
        std::vector<D3D12_DESCRIPTOR_RANGE1> descriptor_ranges{};
        descriptor_ranges.reserve(root_table.NumDescriptorRanges);
        for (uint32_t range_index = 0; range_index < root_table.NumDescriptorRanges; ++range_index)
        {
            descriptor_ranges.emplace_back(root_table.pDescriptorRanges[range_index]);
        }
        root_signature_info.index_to_descriptor_ranges_mapping.try_emplace(parameter_index, std::move(descriptor_ranges));
    }

    static D3D12_RENDER_TARGET_VIEW_DESC TranslateUAVDescToRTVDesc(const D3D12_UNORDERED_ACCESS_VIEW_DESC &uav_desc)
    {
        D3D12_RENDER_TARGET_VIEW_DESC rtv_desc{};
        switch (uav_desc.ViewDimension)
        {
            case D3D12_UAV_DIMENSION_BUFFER:
            {
                // TODO: finish
                rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_BUFFER;
                rtv_desc.Buffer.FirstElement = uav_desc.Buffer.FirstElement;
                rtv_desc.Buffer.NumElements = uav_desc.Buffer.NumElements;
                break;
            }
            case D3D12_UAV_DIMENSION_TEXTURE1D:
            {
                rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE1D;
                rtv_desc.Texture1D.MipSlice = uav_desc.Texture1D.MipSlice;
                break;
            }
            case D3D12_UAV_DIMENSION_TEXTURE1DARRAY:
            {
                rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE1DARRAY;
                rtv_desc.Texture1DArray.MipSlice = uav_desc.Texture1DArray.MipSlice;
                rtv_desc.Texture1DArray.FirstArraySlice = uav_desc.Texture1DArray.FirstArraySlice;
                rtv_desc.Texture1DArray.ArraySize = uav_desc.Texture1DArray.ArraySize;
                break;
            }
            case D3D12_UAV_DIMENSION_TEXTURE2D:
            {
                rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
                rtv_desc.Texture2D.MipSlice = uav_desc.Texture2D.MipSlice;
                rtv_desc.Texture2D.PlaneSlice = uav_desc.Texture2D.PlaneSlice;
                break;
            }
            case D3D12_UAV_DIMENSION_TEXTURE2DARRAY:
            {
                rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DARRAY;
                rtv_desc.Texture2DArray.MipSlice = uav_desc.Texture2DArray.MipSlice;
                rtv_desc.Texture2DArray.FirstArraySlice = uav_desc.Texture2DArray.FirstArraySlice;
                rtv_desc.Texture2DArray.ArraySize = uav_desc.Texture2DArray.ArraySize;
                rtv_desc.Texture2DArray.PlaneSlice = uav_desc.Texture2DArray.PlaneSlice;
                break;
            }
            case D3D12_UAV_DIMENSION_TEXTURE2DMS:
            {
                rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DMS;
                rtv_desc.Texture2DMS.UnusedField_NothingToDefine = uav_desc.Texture2DMS.UnusedField_NothingToDefine;
                break;
            }
            case D3D12_UAV_DIMENSION_TEXTURE2DMSARRAY:
            {
                rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DMSARRAY;
                rtv_desc.Texture2DMSArray.FirstArraySlice = uav_desc.Texture2DMSArray.FirstArraySlice;
                rtv_desc.Texture2DMSArray.ArraySize = uav_desc.Texture2DMSArray.ArraySize;
                break;
            }
            case D3D12_UAV_DIMENSION_TEXTURE3D:
            {
                rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE3D;
                rtv_desc.Texture3D.MipSlice = uav_desc.Texture3D.MipSlice;
                rtv_desc.Texture3D.FirstWSlice = uav_desc.Texture3D.FirstWSlice;
                rtv_desc.Texture3D.WSize = uav_desc.Texture3D.WSize;
                break;
            }
            default:
            {
                D3D12_WRAPPER_CRITICAL("Unsupported uav view dimension");
                break;
            }
        }
        return rtv_desc;
    }

    void D3D12DeviceTracer::StoreRTVAndResource(uint64_t rtv_descriptor, ID3D12Resource *resource, const D3D12_RENDER_TARGET_VIEW_DESC *render_target_view_desc)
    {
        std::lock_guard guard{ lock_mutex };
        D3D12_RENDER_TARGET_VIEW_DESC valid_rtv_desc{};
        if (render_target_view_desc == nullptr)
        {
            auto resource_desc = resource->GetDesc();
            if (resource_desc.Dimension != D3D12_RESOURCE_DIMENSION_TEXTURE2D)
            {
                D3D12_WRAPPER_WARN("Currently only consider texture 2d when rtv desc is nullptr");
                return;
            }
            if (resource_desc.SampleDesc.Count > 1U)
            {
                valid_rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DMS;
                valid_rtv_desc.Format = resource_desc.Format;
            } else
            {
                valid_rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
                valid_rtv_desc.Format = resource_desc.Format;
                valid_rtv_desc.Texture2D.MipSlice = 0U;
                valid_rtv_desc.Texture2D.PlaneSlice = 0U;
            }
        } else
        {
            valid_rtv_desc = *render_target_view_desc;
        }

        bool is_cube_map = false;
        if (valid_rtv_desc.ViewDimension == D3D12_RTV_DIMENSION_TEXTURE2DARRAY)
        {
            if (valid_rtv_desc.Texture2DArray.FirstArraySlice == 0U && valid_rtv_desc.Texture2DArray.ArraySize == 6U)
            {
                is_cube_map = true;
            }
        }
        render_target_view_info_storage[rtv_descriptor] = RenderTargetViewInfo{ resource, valid_rtv_desc, D3D12_RESOURCE_STATE_RENDER_TARGET, is_cube_map };
    }

    void D3D12DeviceTracer::StoreDSVAndResource(uint64_t dsv_descriptor, ID3D12Resource *resource, const D3D12_DEPTH_STENCIL_VIEW_DESC *depth_stencil_view_desc)
    {
        std::lock_guard guard{ lock_mutex };
        depth_stencil_view_info_storage[dsv_descriptor] = DepthStencilViewInfo{ resource, D3D12_RESOURCE_STATE_DEPTH_WRITE };
    }

    void D3D12DeviceTracer::StoreUAVAndResource(uint64_t uav_descriptor, ID3D12Resource *resource, const D3D12_UNORDERED_ACCESS_VIEW_DESC *unordered_access_view_desc)
    {
        std::lock_guard guard{ lock_mutex };
        unordered_access_view_info_storage[uav_descriptor] = UnorderedAccessViewInfo{ resource, *unordered_access_view_desc, D3D12_RESOURCE_STATE_UNORDERED_ACCESS };
    }

    void D3D12DeviceTracer::StoreRootBufferMapping(ID3D12Resource *buffer)
    {
        std::lock_guard guard{ lock_mutex };
        const auto buffer_gpu_va = static_cast<uint64_t>(buffer->GetGPUVirtualAddress());
        root_buffer_info_storage[buffer_gpu_va] = buffer;
    }

    void D3D12DeviceTracer::StoreCommandSignature(uint64_t command_signature_pointer, const D3D12_COMMAND_SIGNATURE_DESC *command_signature_desc)
    {
        std::lock_guard guard{ lock_mutex };
        const auto indirect_arguments_pointer = command_signature_desc->pArgumentDescs;
        const auto indirect_arguments_num = command_signature_desc->NumArgumentDescs;
        D3D12_INDIRECT_ARGUMENT_TYPE expected_indirect_type = D3D12_INDIRECT_ARGUMENT_TYPE_VERTEX_BUFFER_VIEW;
        for (uint32_t i = 0; i < indirect_arguments_num; ++i)
        {
            if (const auto indirect_type = indirect_arguments_pointer[i].Type;
                indirect_type == D3D12_INDIRECT_ARGUMENT_TYPE_DRAW || indirect_type == D3D12_INDIRECT_ARGUMENT_TYPE_DRAW_INDEXED || indirect_type == D3D12_INDIRECT_ARGUMENT_TYPE_DISPATCH)
            {
                expected_indirect_type = indirect_type;
            }
        }
        command_signature_info_storage[command_signature_pointer] = CommandSignatureInfo{ expected_indirect_type };
    }

    void D3D12DeviceTracer::UpdateBlobToRootSignatureMapping(uint64_t blob_pointer, ID3D12RootSignature *root_signature)
    {
        std::lock_guard guard{ lock_mutex };
        if (blob_pointer == 0)
        {
            return;
        }
        if (blob_to_root_signature_mapping.contains(blob_pointer))
        {
            // Update root signature and its creation description
            blob_to_root_signature_mapping[blob_pointer] = root_signature;
            root_signature_pointer_to_blob_mapping.try_emplace(root_signature, blob_pointer);
        } else
        {
            blob_to_root_signature_mapping[blob_pointer] = root_signature;
        }
    }

    void D3D12DeviceTracer::StoreBlobToRootSignatureDescMapping(uint64_t blob_pointer, const D3D12_ROOT_SIGNATURE_DESC *root_signature_desc)
    {
        std::lock_guard guard{ lock_mutex };
        if (root_signature_desc == nullptr)
        {
            return;
        }

        RootSignatureInfo root_signature_info{};
        for (uint32_t parameter_index = 0; parameter_index < root_signature_desc->NumParameters; ++parameter_index)
        {
            auto &&root_parameter = root_signature_desc->pParameters[parameter_index];
            if (root_parameter.ParameterType == D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE)
            {
                auto &&root_table = root_parameter.DescriptorTable;
                std::vector<D3D12_DESCRIPTOR_RANGE1> descriptor_ranges{};
                descriptor_ranges.reserve(root_table.NumDescriptorRanges);
                for (uint32_t range_index = 0; range_index < root_table.NumDescriptorRanges; ++range_index)
                {
                    D3D12_DESCRIPTOR_RANGE1 range1{};
                    range1.RangeType = root_table.pDescriptorRanges[range_index].RangeType;
                    range1.NumDescriptors = root_table.pDescriptorRanges[range_index].NumDescriptors;
                    range1.BaseShaderRegister = root_table.pDescriptorRanges[range_index].BaseShaderRegister;
                    range1.RegisterSpace = root_table.pDescriptorRanges[range_index].RegisterSpace;
                    range1.Flags = D3D12_DESCRIPTOR_RANGE_FLAG_NONE;
                    range1.OffsetInDescriptorsFromTableStart = root_table.pDescriptorRanges[range_index].OffsetInDescriptorsFromTableStart;
                    descriptor_ranges.emplace_back(range1);
                }
                root_signature_info.index_to_descriptor_ranges_mapping.try_emplace(parameter_index, std::move(descriptor_ranges));
            }
        }
        blob_to_root_signature_info_mapping.try_emplace(blob_pointer, std::move(root_signature_info));
    }

    void D3D12DeviceTracer::StoreBlobToVersionedRootSignatureDescMapping(uint64_t blob_pointer, const D3D12_VERSIONED_ROOT_SIGNATURE_DESC *versioned_root_signature_desc)
    {
        std::lock_guard guard{ lock_mutex };
        if (versioned_root_signature_desc == nullptr)
        {
            return;
        }

        // Currently only concern uav and root table
        if (versioned_root_signature_desc->Version == D3D_ROOT_SIGNATURE_VERSION_1_0)
        {
            return StoreBlobToRootSignatureDescMapping(blob_pointer, &versioned_root_signature_desc->Desc_1_0);
        } else if (versioned_root_signature_desc->Version == D3D_ROOT_SIGNATURE_VERSION_1_1)
        {
            RootSignatureInfo root_signature_info{};
            auto &&root_signature_desc = versioned_root_signature_desc->Desc_1_1;
            for (uint32_t parameter_index = 0; parameter_index < root_signature_desc.NumParameters; ++parameter_index)
            {
                auto &&root_parameter = root_signature_desc.pParameters[parameter_index];
                CollectRootParameter(parameter_index, root_parameter, root_signature_info);
            }
            blob_to_root_signature_info_mapping.try_emplace(blob_pointer, std::move(root_signature_info));
        } else if (versioned_root_signature_desc->Version == D3D_ROOT_SIGNATURE_VERSION_1_2)
        {
            RootSignatureInfo root_signature_info{};
            auto &&root_signature_desc = versioned_root_signature_desc->Desc_1_2;
            for (uint32_t parameter_index = 0; parameter_index < root_signature_desc.NumParameters; ++parameter_index)
            {
                auto &&root_parameter = root_signature_desc.pParameters[parameter_index];
                CollectRootParameter(parameter_index, root_parameter, root_signature_info);
            }
            blob_to_root_signature_info_mapping.try_emplace(blob_pointer, std::move(root_signature_info));
        } else
        {
            D3D12_WRAPPER_CRITICAL("Unsupported versioned root signature");
        }
    }

    void D3D12DeviceTracer::SetDescriptorSize(ID3D12Device *device)
    {
        std::lock_guard guard{ lock_mutex };
        srv_uav_descriptor_size = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    }

    RootSignatureIndex D3D12DeviceTracer::QueryComputeRootSignature(ID3D12RootSignature *compute_root_signature)
    {
        std::lock_guard guard{ lock_mutex };
        if (root_signature_pointer_to_blob_mapping.contains(compute_root_signature))
        {
            auto blob_pointer = root_signature_pointer_to_blob_mapping[compute_root_signature];
            return RootSignatureIndex{ blob_pointer, compute_root_signature };
        }
        return RootSignatureIndex{ 0, compute_root_signature };
    }

    uint32_t D3D12DeviceTracer::QueryNonSamplerDescriptorSize() const
    {
        return srv_uav_descriptor_size;
    }

    D3D12_INDIRECT_ARGUMENT_TYPE D3D12DeviceTracer::QueryIndirectArgumentType(uint64_t command_signature_pointer)
    {
        std::lock_guard guard{ lock_mutex };
        if (command_signature_info_storage.contains(command_signature_pointer))
        {
            return command_signature_info_storage[command_signature_pointer].indirect_type;
        }
        return D3D12_INDIRECT_ARGUMENT_TYPE_VERTEX_BUFFER_VIEW;
    }

    ID3D12Resource *D3D12DeviceTracer::QueryRootBuffer(uint64_t gpu_va)
    {
        std::lock_guard guard{ lock_mutex };
        if (root_buffer_info_storage.contains(gpu_va))
        {
            return root_buffer_info_storage[gpu_va];
        }
        return nullptr;
    }

    void D3D12DeviceTracer::UpdateRTVStatePerDraw(uint64_t rtv_descriptor, std::unordered_map<uint64_t, RenderTargetViewInfo> &render_target_view_info_per_draw)
    {
        std::lock_guard guard{ lock_mutex };
        ID3D12Resource *resource = nullptr;
        D3D12_RENDER_TARGET_VIEW_DESC rtv_desc{};
        bool is_cube_map = false;
        if (render_target_view_info_storage.contains(rtv_descriptor))
        {
            auto &&rtv_state = render_target_view_info_storage[rtv_descriptor];
            resource = rtv_state.d3d12_resource;
            rtv_desc = rtv_state.rtv_desc;
            is_cube_map = rtv_state.cube_map;
        }
        render_target_view_info_per_draw[rtv_descriptor] = RenderTargetViewInfo{ resource, rtv_desc, D3D12_RESOURCE_STATE_RENDER_TARGET, is_cube_map };
    }

    void D3D12DeviceTracer::UpdateDSVStatePerDraw(uint64_t dsv_descriptor, std::unordered_map<uint64_t, DepthStencilViewInfo> &depth_stencil_view_info_per_draw)
    {
        std::lock_guard guard{ lock_mutex };
        ID3D12Resource *resource = nullptr;
        if (depth_stencil_view_info_storage.contains(dsv_descriptor))
        {
            auto &&dsv_state = depth_stencil_view_info_storage[dsv_descriptor];
            resource = dsv_state.d3d12_resource;
        }
        depth_stencil_view_info_per_draw[dsv_descriptor] = DepthStencilViewInfo{ resource, D3D12_RESOURCE_STATE_DEPTH_WRITE };
    }

    void D3D12DeviceTracer::UpdateUAVStatePerDispatch(uint64_t starting_gpu_descriptor, std::unordered_map<uint64_t, UnorderedAccessViewInfo> &unordered_access_view_info_per_dispatch)
    {
        std::lock_guard guard{ lock_mutex };
        if (unordered_access_view_info_storage.contains(starting_gpu_descriptor))
        {
            unordered_access_view_info_per_dispatch[starting_gpu_descriptor] = unordered_access_view_info_storage[starting_gpu_descriptor];
        }
    }

    void D3D12DeviceTracer::UpdateUAVStatePerDispatch(uint32_t root_parameter_index, uint64_t starting_gpu_descriptor, uint64_t cur_blob_pointer,
                                                        ID3D12DescriptorHeap *cur_descriptor_heap,
                                                        std::unordered_map<uint64_t, UnorderedAccessViewInfo> &unordered_access_view_info_per_dispatch)
    {
        std::lock_guard guard{ lock_mutex };
        auto &&cur_compute_root_signature_info = blob_to_root_signature_info_mapping[cur_blob_pointer];
        if (!cur_compute_root_signature_info.index_to_descriptor_ranges_mapping.contains(root_parameter_index))
        {
            return;
        }
        auto &&descriptor_ranges = cur_compute_root_signature_info.index_to_descriptor_ranges_mapping[root_parameter_index];
        for (auto &&descriptor_range : descriptor_ranges)
        {
            // Must advance the input uav_gpu_descriptor for CBV_SRV_UAV descriptor heap, since the input uav_gpu_descriptor is located at the beginning of root table
            if (descriptor_range.RangeType != D3D12_DESCRIPTOR_RANGE_TYPE_UAV)
            {
                if (descriptor_range.RangeType != D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER)
                {
                    starting_gpu_descriptor += (srv_uav_descriptor_size * descriptor_range.NumDescriptors);
                }
                continue;
            }

            // Find the uav cpu descriptor corresponding to the input uav_gpu_descriptor
            std::vector<uint64_t> real_cpu_descriptors{};
            auto heap_desc = cur_descriptor_heap->GetDesc();
            auto cpu_heap_start = cur_descriptor_heap->GetCPUDescriptorHandleForHeapStart().ptr;
            auto gpu_heap_start = cur_descriptor_heap->GetGPUDescriptorHandleForHeapStart().ptr;
            auto descriptors_num_in_range = descriptor_range.NumDescriptors;
            auto descriptors_num_in_heap = heap_desc.NumDescriptors;
            auto gpu_heap_end = gpu_heap_start + descriptors_num_in_heap * srv_uav_descriptor_size;
            if ((gpu_heap_start <= starting_gpu_descriptor) && (starting_gpu_descriptor <= gpu_heap_end))
            {
                uint32_t offset_from_start = (starting_gpu_descriptor - gpu_heap_start) / srv_uav_descriptor_size;
                uint32_t min_descriptors_num = std::min(descriptors_num_in_range, descriptors_num_in_heap);
                for (uint32_t descriptor_index = 0; descriptor_index < min_descriptors_num; ++descriptor_index)
                {
                    uint64_t real_cpu_descriptor = cpu_heap_start + (offset_from_start + descriptor_index) * srv_uav_descriptor_size;
                    real_cpu_descriptors.emplace_back(real_cpu_descriptor);
                }
            }

            // Collect the resource information corresponding to the uav cpu descriptor
            for (auto real_cpu_descriptor : real_cpu_descriptors)
            {
                if (unordered_access_view_info_storage.contains(real_cpu_descriptor))
                {
                    unordered_access_view_info_per_dispatch[real_cpu_descriptor] = unordered_access_view_info_storage[real_cpu_descriptor];
                }
            }

        }
    }

    D3D12CommandListTracer::DumpDecoration::DumpDecoration(const gfxshim::D3D12CommandListTracer &in_tracer, const std::wstring &action_string, DecorationFlag dump_flag)
    {
        auto current_execution_count = in_tracer.CheckExecutionCount();
        decorated_string = std::format(L"{}_{}", in_tracer.per_draw_dump_prefix, current_execution_count);
        if (dump_flag == DecorationFlag::DumpRTV)
        {
            decorated_string = std::format(L"{}_{}_RTV", decorated_string, action_string);
        } else if (dump_flag == DecorationFlag::DumpDSV)
        {
            decorated_string = std::format(L"{}_{}_DSV", decorated_string, action_string);
        } else
        {
            decorated_string = std::format(L"{}_{}_UAV", decorated_string, action_string);
        }
    }

    std::wstring &D3D12CommandListTracer::DumpDecoration::operator()()
    {
        return decorated_string;
    }

    D3D12CommandListTracer::D3D12CommandListTracer(D3D12DeviceTracer &device_tracer_ref, uint32_t command_list_id)
    : device_tracer(device_tracer_ref)
    {
        // Command list id + Execution count + Draw or dispatch action + Draw or dispatch count + Resource view type + Resource view number
        per_draw_dump_prefix = std::format(L"CL_{}_ExecuteCM", command_list_id);
        fence_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        D3D12_WRAPPER_ASSERT(fence_event != nullptr, "Fence event can not be nullptr");
    }

    D3D12CommandListTracer::~D3D12CommandListTracer()
    {
        if (fence_event != nullptr)
        {
            CloseHandle(fence_event);
        }
    }

    uint32_t D3D12CommandListTracer::IncreaseExecutionCount()
    {
        return execution_count.fetch_add(1, std::memory_order_seq_cst);
    }

    uint32_t D3D12CommandListTracer::CheckExecutionCount() const
    {
        return execution_count.load(std::memory_order_seq_cst);
    }

    uint32_t D3D12CommandListTracer::IncreaseDrawCount()
    {
        return draw_count.fetch_add(1, std::memory_order_seq_cst);
    }

    uint32_t D3D12CommandListTracer::CheckDrawCount() const
    {
        return draw_count.load(std::memory_order_seq_cst);
    }

    uint32_t D3D12CommandListTracer::IncreaseDispatchCount()
    {
        return dispatch_count.fetch_add(1, std::memory_order_seq_cst);
    }

    uint32_t D3D12CommandListTracer::CheckDispatchCount() const
    {
        return dispatch_count.load(std::memory_order_seq_cst);
    }

    void D3D12CommandListTracer::SetDumpFinish()
    {
        dump_finish.store(true, std::memory_order_seq_cst);
    }

    bool D3D12CommandListTracer::CheckDumpFinish() const
    {
        return dump_finish.load(std::memory_order_seq_cst);
    }

    void D3D12CommandListTracer::CollectStagingResourcePerDraw(ID3D12Device *device, ID3D12GraphicsCommandList *command_list_pointer)
    {
        // Record bundle command list draw count
        if (const auto command_list_type = command_list_pointer->GetType(); command_list_type == D3D12_COMMAND_LIST_TYPE_BUNDLE)
        {
            ++draw_count_in_bundle;
            return;
        }
        // For direct command list
        if (CheckDrawCount() > draw_count_limit)
        {
            return;  // TODO: test deferred per-draw-dump, limit to 180
        }

        D3D12_WRAPPER_DEBUG("Begin to deferred per-draw-dump");

        uint32_t rtv_index = 0;
        uint32_t dsv_index = 0;
        uint32_t uav_index = 0;
        std::wstring draw_action_string = std::format(L"Draw_{}", CheckDrawCount());
        DumpDecoration dump_decoration_rtv{ *this, draw_action_string, DecorationFlag::DumpRTV };
        DumpDecoration dump_decoration_dsv{ *this, draw_action_string, DecorationFlag::DumpDSV };
        DumpDecoration dump_decoration_uav{ *this, draw_action_string, DecorationFlag::DumpUAV };
        per_draw_dump_ready.store(true, std::memory_order_seq_cst);
        for (auto &&render_target_state : render_target_view_info_per_draw)
        {
            auto *target_resource = render_target_state.second.d3d12_resource;
            auto rtv_desc = render_target_state.second.rtv_desc;
            if (target_resource == nullptr)
            {
                continue;
            }

            auto resource_desc = target_resource->GetDesc();
            DirectX::CaptureTextureDesc capture_texture_desc{};
            if (resource_desc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER)
            {
                std::wstring render_target_filepath = std::format(L"{}_{}.bin", dump_decoration_rtv.decorated_string, rtv_index);
                DirectX::CaptureBufferDeferred(device, command_list_pointer, target_resource, capture_texture_desc);
                capture_rtv_texture_filepath_storage.emplace_back(std::move(render_target_filepath));
            } else
            {
                std::wstring render_target_filepath = std::format(L"{}_{}.dds", dump_decoration_rtv.decorated_string, rtv_index);
                DirectX::CaptureTextureSubresourceDeferred(device, command_list_pointer, target_resource, rtv_desc, capture_texture_desc, render_target_state.second.cube_map);
                capture_rtv_texture_filepath_storage.emplace_back(std::move(render_target_filepath));
            }
            capture_rtv_texture_desc_storage_per_execution.emplace_back(std::move(capture_texture_desc));
            ++rtv_index;
        }

        for (auto &&depth_stencil_state : depth_stencil_view_info_per_draw)
        {
            auto &&depth_stencil_info = depth_stencil_state.second;
            if (depth_stencil_info.d3d12_resource == nullptr)
            {
                continue;
            }

            DirectX::CaptureTextureDesc capture_texture_desc{};
            std::wstring depth_stencil_filepath = std::format(L"{}_{}.bin", dump_decoration_dsv.decorated_string, dsv_index);
            DirectX::CaptureTextureDeferred(device, command_list_pointer, depth_stencil_info.d3d12_resource, capture_texture_desc, false, false,
                                            depth_stencil_info.resource_state, depth_stencil_info.resource_state);
            capture_dsv_texture_filepath_storage.emplace_back(std::move(depth_stencil_filepath));
            capture_dsv_texture_desc_storage_per_execution.emplace_back(std::move(capture_texture_desc));
            ++dsv_index;
        }

        for (auto &&unordered_access_state : unordered_access_view_info_per_draw)
        {
            auto &&target_resource = unordered_access_state.second.d3d12_resource;
            auto uav_resource_state = unordered_access_state.second.resource_state;
            if (target_resource == nullptr)
            {
                continue;
            }
            auto resource_desc = target_resource->GetDesc();
            if (resource_desc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER)
            {
                DirectX::CaptureTextureDesc capture_texture_desc{};
                std::wstring unordered_access_filepath = std::format(L"{}_{}.bin", dump_decoration_uav.decorated_string, uav_index);
                DirectX::CaptureBufferDeferred(device, command_list_pointer, target_resource, capture_texture_desc, uav_resource_state, uav_resource_state);
                capture_uav_texture_filepath_storage_draw.emplace_back(std::move(unordered_access_filepath));
                capture_uav_texture_desc_storage_per_execution_draw.emplace_back(std::move(capture_texture_desc));
                ++uav_index;
            }
        }

        IncreaseDrawCount();

        D3D12_WRAPPER_DEBUG("End deferred per-draw-dump");
    }

    void D3D12CommandListTracer::PerDrawDump(ID3D12Fence *fence, uint64_t fence_value)
    {
        if (CheckExecutionCount() > execution_count_limit)
        {
            return;  // TODO: test deferred per-draw-dump, limit the number of executions
        }

        if (fence->GetCompletedValue() < fence_value)
        {
            fence->SetEventOnCompletion(fence_value, fence_event);
            WaitForSingleObjectEx(fence_event, INFINITE, FALSE);
        }

        for (size_t i = 0; i < capture_rtv_texture_desc_storage_per_execution.size(); ++i)
        {
            auto &&capture_texture_desc = capture_rtv_texture_desc_storage_per_execution[i];
            if (capture_texture_desc.capturedResourceDesc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER)
            {
                DirectX::SaveToBinFileImmediately(capture_texture_desc, capture_rtv_texture_filepath_storage[i].c_str());
            } else
            {
                DirectX::SaveToDDSFileImmediately(capture_texture_desc, DirectX::DDS_FLAGS_NONE, capture_rtv_texture_filepath_storage[i].c_str());
            }
        }

        for (size_t i = 0; i < capture_dsv_texture_desc_storage_per_execution.size(); ++i)
        {
            auto &&capture_texture_desc = capture_dsv_texture_desc_storage_per_execution[i];
            DirectX::SaveToBinFileImmediately(capture_texture_desc, capture_dsv_texture_filepath_storage[i].c_str());
        }

        for (size_t i = 0; i < capture_uav_texture_desc_storage_per_execution_draw.size(); ++i)
        {
            auto &&capture_texture_desc = capture_uav_texture_desc_storage_per_execution_draw[i];
            DirectX::SaveToBinFileImmediately(capture_texture_desc, capture_uav_texture_filepath_storage_draw[i].c_str());
        }

        capture_rtv_texture_desc_storage_per_execution.clear();
        capture_rtv_texture_filepath_storage.clear();
        render_target_view_info_per_draw.clear();

        capture_dsv_texture_desc_storage_per_execution.clear();
        capture_dsv_texture_filepath_storage.clear();
        depth_stencil_view_info_per_draw.clear();

        capture_uav_texture_desc_storage_per_execution_draw.clear();
        capture_uav_texture_filepath_storage_draw.clear();
        unordered_access_view_info_per_draw.clear();
    }

    void D3D12CommandListTracer::PerDispatchDump(ID3D12Fence *fence, uint64_t fence_value)
    {
        if (CheckExecutionCount() > execution_count_limit || per_dispatch_dump_ready.load(std::memory_order_seq_cst))
        {
            return;  // TODO: test deferred per-dispatch-dump, limit the number of executions
        }

        per_dispatch_dump_ready.store(true, std::memory_order_seq_cst);

        if (fence->GetCompletedValue() < fence_value)
        {
            fence->SetEventOnCompletion(fence_value, fence_event);
            WaitForSingleObjectEx(fence_event, INFINITE, FALSE);
        }

        for (size_t i = 0; i < capture_uav_texture_desc_storage_per_execution.size(); ++i)
        {
            auto &&capture_texture_desc = capture_uav_texture_desc_storage_per_execution[i];
            if (capture_texture_desc.capturedResourceDesc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER)
            {
                DirectX::SaveToBinFileImmediately(capture_texture_desc, capture_uav_texture_filepath_storage[i].c_str());
            } else
            {
                DirectX::SaveToDDSFileImmediately(capture_texture_desc, DirectX::DDS_FLAGS_NONE, capture_uav_texture_filepath_storage[i].c_str());
            }
        }

        capture_uav_texture_desc_storage_per_execution.clear();
        capture_uav_texture_filepath_storage.clear();
        unordered_access_view_info_per_dispatch.clear();

        per_dispatch_dump_ready.store(false, std::memory_order_seq_cst);
    }

    void D3D12CommandListTracer::Advance()
    {
        auto cur_execution_count = IncreaseExecutionCount();
        if (cur_execution_count == execution_count_limit)
        {
            SetDumpFinish();
        }
    }

    uint32_t D3D12CommandListTracer::QueryDrawCountInBundle() const
    {
        return draw_count_in_bundle;
    }

    uint32_t D3D12CommandListTracer::QueryDispatchCountInBundle() const
    {
        return dispatch_count_in_bundle;
    }

    void D3D12CommandListTracer::ClearRTVAndDSVStatesPerDraw()
    {
        if (per_draw_dump_ready.load(std::memory_order_seq_cst))
        {
            render_target_view_info_per_draw.clear();
            depth_stencil_view_info_per_draw.clear();
            per_draw_dump_ready.store(false, std::memory_order_seq_cst);
        }
    }

    void D3D12CommandListTracer::UpdateRTVStatePerDraw(uint64_t rtv_descriptor)
    {
        if (CheckDumpFinish())
        {
            return;
        }
        // Render target view
        if (render_target_view_info_per_draw.contains(rtv_descriptor))
        {
            render_target_view_info_per_draw[rtv_descriptor].resource_state = D3D12_RESOURCE_STATE_RENDER_TARGET;
        } else
        {
            device_tracer.UpdateRTVStatePerDraw(rtv_descriptor, render_target_view_info_per_draw);
        }
    }

    void D3D12CommandListTracer::UpdateDSVStatePerDraw(uint64_t dsv_descriptor)
    {
        if (CheckDumpFinish())
        {
            return;
        }
        // Depth stencil view
        if (depth_stencil_view_info_per_draw.contains(dsv_descriptor))
        {
            depth_stencil_view_info_per_draw[dsv_descriptor].resource_state = D3D12_RESOURCE_STATE_DEPTH_WRITE;  // TODO: check
        } else
        {
            device_tracer.UpdateDSVStatePerDraw(dsv_descriptor, depth_stencil_view_info_per_draw);
        }
    }

    void D3D12CommandListTracer::UpdateUAVStatePerDraw(uint64_t uav_descriptor)
    {
        if (CheckDumpFinish())
        {
            return;
        }
        // Unordered access view
        if (unordered_access_view_info_per_draw.contains(uav_descriptor))
        {
            unordered_access_view_info_per_draw[uav_descriptor].resource_state = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
        } else
        {
            // TODO: check
            if (auto *buffer = device_tracer.QueryRootBuffer(uav_descriptor); buffer != nullptr)
            {
                unordered_access_view_info_per_draw[uav_descriptor] = UnorderedAccessViewInfo{ buffer, D3D12_UNORDERED_ACCESS_VIEW_DESC{}, D3D12_RESOURCE_STATE_UNORDERED_ACCESS };
            }
        }
    }

    void D3D12CommandListTracer::ResetDescriptorHeaps(uint32_t descriptor_heaps_num, ID3D12DescriptorHeap *const *descriptor_heaps_ptr)
    {
        if (CheckDumpFinish())
        {
            return;
        }
        cur_descriptor_heaps.clear();
        for (uint32_t i = 0; i < descriptor_heaps_num; ++i)
        {
            cur_descriptor_heaps.emplace_back(descriptor_heaps_ptr[i]);
        }
    }

    void D3D12CommandListTracer::ResetComputePipelineRootSignature(ID3D12RootSignature *compute_root_signature)
    {
        if (CheckDumpFinish())
        {
            return;
        }
        // Clear unordered access view collection before SetComputeRootDescriptorTable or SetComputeRootUnorderedAccessView
        unordered_access_view_info_per_dispatch.clear();
        if (compute_root_signature)
        {
            auto root_signature_index = device_tracer.QueryComputeRootSignature(compute_root_signature);
            cur_blob_pointer = root_signature_index.blob_pointer;
            cur_compute_root_signature = root_signature_index.compute_root_signature;
        }
    }

    void D3D12CommandListTracer::UpdateUAVStatePerDispatch(uint64_t starting_gpu_descriptor)
    {
        if (CheckDumpFinish())
        {
            return;
        }
        if (per_dispatch_dump_ready.load(std::memory_order_seq_cst) || cur_compute_root_signature == nullptr)
        {
            return;
        }

        // TODO: check
        if (auto *buffer = device_tracer.QueryRootBuffer(starting_gpu_descriptor); buffer != nullptr)
        {
            unordered_access_view_info_per_dispatch[starting_gpu_descriptor] = UnorderedAccessViewInfo{ buffer, D3D12_UNORDERED_ACCESS_VIEW_DESC{}, D3D12_RESOURCE_STATE_UNORDERED_ACCESS };
        }
    }

    void D3D12CommandListTracer::UpdateUAVStatePerDispatch(uint32_t root_parameter_index, uint64_t starting_gpu_descriptor)
    {
        if (CheckDumpFinish())
        {
            return;
        }
        if (per_dispatch_dump_ready.load(std::memory_order_seq_cst) || cur_compute_root_signature == nullptr)
        {
            return;
        }
        ID3D12DescriptorHeap *cbv_srv_uav_descriptor_heap = nullptr;
        for (auto &&descriptor_heap : cur_descriptor_heaps)
        {
            auto heap_desc = descriptor_heap->GetDesc();
            if (heap_desc.Type == D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)
            {
                cbv_srv_uav_descriptor_heap = descriptor_heap;
                break;
            }
        }
        if (cbv_srv_uav_descriptor_heap == nullptr)
        {
            return;
        }
        device_tracer.UpdateUAVStatePerDispatch(root_parameter_index, starting_gpu_descriptor, cur_blob_pointer, cbv_srv_uav_descriptor_heap, unordered_access_view_info_per_dispatch);
    }

    void D3D12CommandListTracer::CollectStagingResourcePerDispatch(ID3D12Device *device, ID3D12GraphicsCommandList *command_list_pointer)
    {
        // Record bundle command list dispatch count
        if (const auto command_list_type = command_list_pointer->GetType(); command_list_type == D3D12_COMMAND_LIST_TYPE_BUNDLE)
        {
            ++dispatch_count_in_bundle;
            return;
        }
        // For direct command list or compute command list
        if (per_dispatch_dump_ready.load(std::memory_order_seq_cst) || CheckDispatchCount() > dispatch_count_limit)
        {
            return;
        }

        D3D12_WRAPPER_DEBUG("Begin to deferred per-dispatch-dump");

        uint32_t uav_index = 0;
        // std::wstring dispatch_action_string = L"_Dispatch_" + std::to_wstring(dispatch_count.load(std::memory_order_seq_cst));
        std::wstring dispatch_action_string = std::format(L"Dispatch_{}", dispatch_count.load(std::memory_order_seq_cst));
        DumpDecoration dump_decoration_uav{ *this, dispatch_action_string, DecorationFlag::DumpUAV };
        for (auto &&unordered_access_state : unordered_access_view_info_per_dispatch)
        {
            auto *target_resource = unordered_access_state.second.d3d12_resource;
            auto resource_state = unordered_access_state.second.resource_state;
            auto uav_desc = unordered_access_state.second.uav_desc;
            if (target_resource == nullptr)
            {
                continue;
            }

            auto resource_desc = target_resource->GetDesc();
            DirectX::CaptureTextureDesc capture_texture_desc{};
            // std::wstring unordered_access_filepath = dump_decoration_uav.decorated_string + std::to_wstring(uav_index);

            if (resource_desc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER)
            {
                std::wstring unordered_access_filepath = std::format(L"{}_{}.bin", dump_decoration_uav.decorated_string, uav_index);
                DirectX::CaptureBufferDeferred(device, command_list_pointer, target_resource, capture_texture_desc,
                                                resource_state, resource_state);
                capture_uav_texture_filepath_storage.emplace_back(std::move(unordered_access_filepath));
            } else
            {
                std::wstring unordered_access_filepath = std::format(L"{}_{}.dds", dump_decoration_uav.decorated_string, uav_index);
                auto rtv_desc = TranslateUAVDescToRTVDesc(uav_desc);
                DirectX::CaptureTextureSubresourceDeferred(device, command_list_pointer, target_resource, rtv_desc, capture_texture_desc, false,
                                                            resource_state, resource_state);
                capture_uav_texture_filepath_storage.emplace_back(std::move(unordered_access_filepath));
            }

            capture_uav_texture_desc_storage_per_execution.emplace_back(std::move(capture_texture_desc));
            ++uav_index;
        }

        IncreaseDispatchCount();
        D3D12_WRAPPER_DEBUG("End deferred per-dispatch-dump");
    }

    void D3D12CommandListTracer::CollectStagingResourcePerIndirect(ID3D12Device *device, ID3D12GraphicsCommandList *command_list_pointer, uint64_t command_signature_pointer)
    {
        // TODO: consider dispatch
        D3D12_INDIRECT_ARGUMENT_TYPE indirect_type = device_tracer.QueryIndirectArgumentType(command_signature_pointer);
        if (indirect_type == D3D12_INDIRECT_ARGUMENT_TYPE_DRAW || indirect_type == D3D12_INDIRECT_ARGUMENT_TYPE_DRAW_INDEXED)
        {
            CollectStagingResourcePerDraw(device, command_list_pointer);
        } else if (indirect_type == D3D12_INDIRECT_ARGUMENT_TYPE_DISPATCH)
        {
            CollectStagingResourcePerDispatch(device, command_list_pointer);
        } else
        {
            D3D12_WRAPPER_WARN("Non draw or dispatch command signature");
        }
    }
}