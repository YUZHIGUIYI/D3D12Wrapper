#include <d3d12/core/d3d12_device_wrap.h>
#include <d3d12/core/d3d12_command_queue_wrap.h>
#include <d3d12/core/d3d12_command_list_wrap.h>
#include <d3d12/core/d3d12_command_allocator_wrap.h>
#include <d3d12/tracer/d3d12_hook_manager.h>

namespace gfxshim
{
    std::unordered_map<IUnknown *, ID3D12DeviceWrapper *> ID3D12DeviceWrapper::m_device_wrapper_map;

    std::mutex ID3D12DeviceWrapper::m_device_wrapper_lock;

    ID3D12DeviceWrapper::ID3D12DeviceWrapper(REFIID riid, IUnknown *object)
    : ID3D12ObjectWrapper(riid, object)
    {

    }

    ID3D12DeviceWrapper::~ID3D12DeviceWrapper() = default;

    UINT STDMETHODCALLTYPE ID3D12DeviceWrapper::GetNodeCount()
    {
        return GetWrappedObjectAs<ID3D12Device>()->GetNodeCount();
    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceWrapper::CreateCommandQueue(
            const D3D12_COMMAND_QUEUE_DESC* pDesc,
            REFIID riid,
            void** ppCommandQueue)
    {
        HRESULT result = GetWrappedObjectAs<ID3D12Device>()->CreateCommandQueue(pDesc, riid, ppCommandQueue);
        // TODO: add custom command queue
        return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceWrapper::CreateCommandAllocator(
            D3D12_COMMAND_LIST_TYPE type,
            REFIID riid,
            void** ppCommandAllocator)
    {
        return GetWrappedObjectAs<ID3D12Device>()->CreateCommandAllocator(type, riid, ppCommandAllocator);
    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceWrapper::CreateGraphicsPipelineState(
            const D3D12_GRAPHICS_PIPELINE_STATE_DESC* pDesc,
            REFIID riid,
            void** ppPipelineState)
    {
        return GetWrappedObjectAs<ID3D12Device>()->CreateGraphicsPipelineState(pDesc, riid, ppPipelineState);
    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceWrapper::CreateComputePipelineState(
            const D3D12_COMPUTE_PIPELINE_STATE_DESC* pDesc,
            REFIID riid,
            void** ppPipelineState)
    {
        return GetWrappedObjectAs<ID3D12Device>()->CreateComputePipelineState(pDesc, riid, ppPipelineState);
    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceWrapper::CreateCommandList(
            UINT nodeMask,
            D3D12_COMMAND_LIST_TYPE type,
            ID3D12CommandAllocator* pCommandAllocator,
            ID3D12PipelineState* pInitialState,
            REFIID riid,
            void** ppCommandList)
    {
        return GetWrappedObjectAs<ID3D12Device>()->CreateCommandList(nodeMask, type, pCommandAllocator, pInitialState, riid, ppCommandList);
    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceWrapper::CheckFeatureSupport(
            D3D12_FEATURE Feature,
            void* pFeatureSupportData,
            UINT FeatureSupportDataSize)
    {
        return GetWrappedObjectAs<ID3D12Device>()->CheckFeatureSupport(Feature, pFeatureSupportData, FeatureSupportDataSize);
    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceWrapper::CreateDescriptorHeap(
            const D3D12_DESCRIPTOR_HEAP_DESC* pDescriptorHeapDesc,
            REFIID riid,
            void** ppvHeap)
    {
        return GetWrappedObjectAs<ID3D12Device>()->CreateDescriptorHeap(pDescriptorHeapDesc, riid, ppvHeap);
    }

    UINT STDMETHODCALLTYPE ID3D12DeviceWrapper::GetDescriptorHandleIncrementSize(
            D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapType)
    {
        return GetWrappedObjectAs<ID3D12Device>()->GetDescriptorHandleIncrementSize(DescriptorHeapType);
    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceWrapper::CreateRootSignature(
            UINT nodeMask,
            const void* pBlobWithRootSignature,
            SIZE_T blobLengthInBytes,
            REFIID riid,
            void** ppvRootSignature)
    {
        return GetWrappedObjectAs<ID3D12Device>()->CreateRootSignature(nodeMask, pBlobWithRootSignature, blobLengthInBytes, riid, ppvRootSignature);
    }

    void STDMETHODCALLTYPE ID3D12DeviceWrapper::CreateConstantBufferView(
            const D3D12_CONSTANT_BUFFER_VIEW_DESC* pDesc,
            D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
    {
        GetWrappedObjectAs<ID3D12Device>()->CreateConstantBufferView(pDesc, DestDescriptor);
    }

    void STDMETHODCALLTYPE ID3D12DeviceWrapper::CreateShaderResourceView(
            ID3D12Resource* pResource,
            const D3D12_SHADER_RESOURCE_VIEW_DESC* pDesc,
            D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
    {
        GetWrappedObjectAs<ID3D12Device>()->CreateShaderResourceView(pResource, pDesc, DestDescriptor);
    }

    void STDMETHODCALLTYPE ID3D12DeviceWrapper::CreateUnorderedAccessView(
            ID3D12Resource* pResource,
            ID3D12Resource* pCounterResource,
            const D3D12_UNORDERED_ACCESS_VIEW_DESC* pDesc,
            D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
    {
        GetWrappedObjectAs<ID3D12Device>()->CreateUnorderedAccessView(pResource, pCounterResource, pDesc, DestDescriptor);
    }

    void STDMETHODCALLTYPE ID3D12DeviceWrapper::CreateRenderTargetView(
            ID3D12Resource* pResource,
            const D3D12_RENDER_TARGET_VIEW_DESC* pDesc,
            D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
    {
        GetWrappedObjectAs<ID3D12Device>()->CreateRenderTargetView(pResource, pDesc, DestDescriptor);
    }

    void STDMETHODCALLTYPE ID3D12DeviceWrapper::CreateDepthStencilView(
            ID3D12Resource* pResource,
            const D3D12_DEPTH_STENCIL_VIEW_DESC* pDesc,
            D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
    {
        GetWrappedObjectAs<ID3D12Device>()->CreateDepthStencilView(pResource, pDesc, DestDescriptor);
    }

    void STDMETHODCALLTYPE ID3D12DeviceWrapper::CreateSampler(
            const D3D12_SAMPLER_DESC* pDesc,
            D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
    {
        GetWrappedObjectAs<ID3D12Device>()->CreateSampler(pDesc, DestDescriptor);
    }

    void STDMETHODCALLTYPE ID3D12DeviceWrapper::CopyDescriptors(
            UINT NumDestDescriptorRanges,
            const D3D12_CPU_DESCRIPTOR_HANDLE* pDestDescriptorRangeStarts,
            const UINT* pDestDescriptorRangeSizes,
            UINT NumSrcDescriptorRanges,
            const D3D12_CPU_DESCRIPTOR_HANDLE* pSrcDescriptorRangeStarts,
            const UINT* pSrcDescriptorRangeSizes,
            D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapsType)
    {
        GetWrappedObjectAs<ID3D12Device>()->CopyDescriptors(NumDestDescriptorRanges, pDestDescriptorRangeStarts, pDestDescriptorRangeSizes, NumSrcDescriptorRanges,
                                                            pSrcDescriptorRangeStarts, pSrcDescriptorRangeSizes, DescriptorHeapsType);
    }

    void STDMETHODCALLTYPE ID3D12DeviceWrapper::CopyDescriptorsSimple(
            UINT NumDescriptors,
            D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptorRangeStart,
            D3D12_CPU_DESCRIPTOR_HANDLE SrcDescriptorRangeStart,
            D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapsType)
    {
        GetWrappedObjectAs<ID3D12Device>()->CopyDescriptorsSimple(NumDescriptors, DestDescriptorRangeStart, SrcDescriptorRangeStart, DescriptorHeapsType);
    }

    D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE ID3D12DeviceWrapper::GetResourceAllocationInfo(
            UINT visibleMask,
            UINT numResourceDescs,
            const D3D12_RESOURCE_DESC* pResourceDescs)
    {
        return GetWrappedObjectAs<ID3D12Device>()->GetResourceAllocationInfo(visibleMask, numResourceDescs, pResourceDescs);
    }

    D3D12_HEAP_PROPERTIES STDMETHODCALLTYPE ID3D12DeviceWrapper::GetCustomHeapProperties(
            UINT nodeMask,
            D3D12_HEAP_TYPE heapType)
    {
        return GetWrappedObjectAs<ID3D12Device>()->GetCustomHeapProperties(nodeMask, heapType);
    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceWrapper::CreateCommittedResource(
            const D3D12_HEAP_PROPERTIES* pHeapProperties,
            D3D12_HEAP_FLAGS HeapFlags,
            const D3D12_RESOURCE_DESC* pDesc,
            D3D12_RESOURCE_STATES InitialResourceState,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            REFIID riidResource,
            void** ppvResource)
    {
        return GetWrappedObjectAs<ID3D12Device>()->CreateCommittedResource(pHeapProperties, HeapFlags, pDesc, InitialResourceState,
                                                                           pOptimizedClearValue, riidResource, ppvResource);
    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceWrapper::CreateHeap(
            const D3D12_HEAP_DESC* pDesc,
            REFIID riid,
            void** ppvHeap)
    {
        return GetWrappedObjectAs<ID3D12Device>()->CreateHeap(pDesc, riid, ppvHeap);
    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceWrapper::CreatePlacedResource(
            ID3D12Heap* pHeap,
            UINT64 HeapOffset,
            const D3D12_RESOURCE_DESC* pDesc,
            D3D12_RESOURCE_STATES InitialState,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            REFIID riid,
            void** ppvResource)
    {
        return GetWrappedObjectAs<ID3D12Device>()->CreatePlacedResource(pHeap, HeapOffset, pDesc, InitialState,
                                                                        pOptimizedClearValue, riid, ppvResource);
    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceWrapper::CreateReservedResource(
            const D3D12_RESOURCE_DESC* pDesc,
            D3D12_RESOURCE_STATES InitialState,
            const D3D12_CLEAR_VALUE* pOptimizedClearValue,
            REFIID riid,
            void** ppvResource)
    {
        return GetWrappedObjectAs<ID3D12Device>()->CreateReservedResource(pDesc, InitialState, pOptimizedClearValue, riid, ppvResource);
    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceWrapper::CreateSharedHandle(
            ID3D12DeviceChild* pObject,
            const SECURITY_ATTRIBUTES* pAttributes,
            DWORD Access,
            LPCWSTR Name,
            HANDLE* pHandle)
    {
        return GetWrappedObjectAs<ID3D12Device>()->CreateSharedHandle(pObject, pAttributes, Access, Name, pHandle);
    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceWrapper::OpenSharedHandle(
            HANDLE NTHandle,
            REFIID riid,
            void** ppvObj)
    {
        return GetWrappedObjectAs<ID3D12Device>()->OpenSharedHandle(NTHandle, riid, ppvObj);
    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceWrapper::OpenSharedHandleByName(
            LPCWSTR Name,
            DWORD Access,
            HANDLE* pNTHandle)
    {
        return GetWrappedObjectAs<ID3D12Device>()->OpenSharedHandleByName(Name, Access, pNTHandle);
    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceWrapper::MakeResident(
            UINT NumObjects,
            ID3D12Pageable* const* ppObjects)
    {
        return GetWrappedObjectAs<ID3D12Device>()->MakeResident(NumObjects, ppObjects);
    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceWrapper::Evict(
            UINT NumObjects,
            ID3D12Pageable* const* ppObjects)
    {
        return GetWrappedObjectAs<ID3D12Device>()->Evict(NumObjects, ppObjects);
    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceWrapper::CreateFence(
            UINT64 InitialValue,
            D3D12_FENCE_FLAGS Flags,
            REFIID riid,
            void** ppFence)
    {
        return GetWrappedObjectAs<ID3D12Device>()->CreateFence(InitialValue, Flags, riid, ppFence);
    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceWrapper::GetDeviceRemovedReason()
    {
        return GetWrappedObjectAs<ID3D12Device>()->GetDeviceRemovedReason();
    }

    void STDMETHODCALLTYPE ID3D12DeviceWrapper::GetCopyableFootprints(
            const D3D12_RESOURCE_DESC* pResourceDesc,
            UINT FirstSubresource,
            UINT NumSubresources,
            UINT64 BaseOffset,
            D3D12_PLACED_SUBRESOURCE_FOOTPRINT* pLayouts,
            UINT* pNumRows,
            UINT64* pRowSizeInBytes,
            UINT64* pTotalBytes)
    {
        GetWrappedObjectAs<ID3D12Device>()->GetCopyableFootprints(pResourceDesc, FirstSubresource, NumSubresources, BaseOffset,
                                                                  pLayouts, pNumRows, pRowSizeInBytes, pTotalBytes);
    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceWrapper::CreateQueryHeap(
            const D3D12_QUERY_HEAP_DESC* pDesc,
            REFIID riid,
            void** ppvHeap)
    {
        return GetWrappedObjectAs<ID3D12Device>()->CreateQueryHeap(pDesc, riid, ppvHeap);
    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceWrapper::SetStablePowerState(
            BOOL Enable)
    {
        return GetWrappedObjectAs<ID3D12Device>()->SetStablePowerState(Enable);
    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceWrapper::CreateCommandSignature(
            const D3D12_COMMAND_SIGNATURE_DESC* pDesc,
            ID3D12RootSignature* pRootSignature,
            REFIID riid,
            void** ppvCommandSignature)
    {
        return GetWrappedObjectAs<ID3D12Device>()->CreateCommandSignature(pDesc, pRootSignature, riid, ppvCommandSignature);
    }

    void STDMETHODCALLTYPE ID3D12DeviceWrapper::GetResourceTiling(
            ID3D12Resource* pTiledResource,
            UINT* pNumTilesForEntireResource,
            D3D12_PACKED_MIP_INFO* pPackedMipDesc,
            D3D12_TILE_SHAPE* pStandardTileShapeForNonPackedMips,
            UINT* pNumSubresourceTilings,
            UINT FirstSubresourceTilingToGet,
            D3D12_SUBRESOURCE_TILING* pSubresourceTilingsForNonPackedMips)
    {
        GetWrappedObjectAs<ID3D12Device>()->GetResourceTiling(pTiledResource, pNumTilesForEntireResource, pPackedMipDesc, pStandardTileShapeForNonPackedMips,
                                                              pNumSubresourceTilings, FirstSubresourceTilingToGet, pSubresourceTilingsForNonPackedMips);
    }

    LUID STDMETHODCALLTYPE ID3D12DeviceWrapper::GetAdapterLuid()
    {
        return GetWrappedObjectAs<ID3D12Device>()->GetAdapterLuid();
    }

    ULONG STDMETHODCALLTYPE ID3D12DeviceWrapper::Release()
    {
        auto result = IUnknownWrapper::Release();
        if (result == 0)
        {
            delete this;
        }
        return result;
    }
}

WrappedID3D12Device::WrappedID3D12Device(ID3D12Device *real_device)
: m_pDevice(real_device)
{
    if(m_pDevice)
    {
        m_pDevice->QueryInterface(__uuidof(ID3D12Device1), reinterpret_cast<void **>(&m_pDevice1));
        m_pDevice->QueryInterface(__uuidof(ID3D12Device2), reinterpret_cast<void **>(&m_pDevice2));
        m_pDevice->QueryInterface(__uuidof(ID3D12Device3), reinterpret_cast<void **>(&m_pDevice3));
        m_pDevice->QueryInterface(__uuidof(ID3D12Device4), reinterpret_cast<void **>(&m_pDevice4));
        m_pDevice->QueryInterface(__uuidof(ID3D12Device5), reinterpret_cast<void **>(&m_pDevice5));
        m_pDevice->QueryInterface(__uuidof(ID3D12Device6), reinterpret_cast<void **>(&m_pDevice6));
        m_pDevice->QueryInterface(__uuidof(ID3D12Device7), reinterpret_cast<void **>(&m_pDevice7));
        m_pDevice->QueryInterface(__uuidof(ID3D12Device8), reinterpret_cast<void **>(&m_pDevice8));
        m_pDevice->QueryInterface(__uuidof(ID3D12Device9), reinterpret_cast<void **>(&m_pDevice9));
        m_pDevice->QueryInterface(__uuidof(ID3D12Device10), reinterpret_cast<void **>(&m_pDevice10));
        m_pDevice->QueryInterface(__uuidof(ID3D12Device11), reinterpret_cast<void **>(&m_pDevice11));
        m_pDevice->QueryInterface(__uuidof(ID3D12Device12), reinterpret_cast<void **>(&m_pDevice12));
        m_pDevice->QueryInterface(__uuidof(ID3D12Device13), reinterpret_cast<void **>(&m_pDevice13));
        m_pDevice->QueryInterface(__uuidof(ID3D12Device14), reinterpret_cast<void **>(&m_pDevice14));

        m_pDevice->AddRef();
    }
}

WrappedID3D12Device::~WrappedID3D12Device() = default;

ID3D12Device *WrappedID3D12Device::GetReal() const
{
    return m_pDevice;
}

HRESULT WrappedID3D12Device::GetDevice(REFIID riid, void **ppvDevice)
{
    if (ppvDevice == nullptr)
    {
        return E_INVALIDARG;
    }

    if(riid == __uuidof(ID3D12Device)   || riid == __uuidof(ID3D12Device1)  || riid == __uuidof(ID3D12Device2)  || riid == __uuidof(ID3D12Device3) ||
       riid == __uuidof(ID3D12Device4)  || riid == __uuidof(ID3D12Device5)  || riid == __uuidof(ID3D12Device6)  || riid == __uuidof(ID3D12Device7) ||
       riid == __uuidof(ID3D12Device8)  || riid == __uuidof(ID3D12Device9)  || riid == __uuidof(ID3D12Device10) || riid == __uuidof(ID3D12Device11) ||
       riid == __uuidof(ID3D12Device12) || riid == __uuidof(ID3D12Device13) || riid == __uuidof(ID3D12Device14))
    {
        *ppvDevice = this;
        this->AddRef();
    }
    return S_OK;
}

ULONG STDMETHODCALLTYPE WrappedID3D12Device::AddRef()
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    auto reference_count = m_pDevice->AddRef();
    return reference_count;
}

ULONG STDMETHODCALLTYPE WrappedID3D12Device::Release()
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    auto reference_count = m_pDevice->Release();
    return reference_count;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::QueryInterface(REFIID riid, void **ppvObject)
{
    // TODO: check
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    const auto result = m_pDevice->QueryInterface(riid, ppvObject);
    if(riid == __uuidof(ID3D12Device)   || riid == __uuidof(ID3D12Device1)  || riid == __uuidof(ID3D12Device2)  || riid == __uuidof(ID3D12Device3) ||
       riid == __uuidof(ID3D12Device4)  || riid == __uuidof(ID3D12Device5)  || riid == __uuidof(ID3D12Device6)  || riid == __uuidof(ID3D12Device7) ||
       riid == __uuidof(ID3D12Device8)  || riid == __uuidof(ID3D12Device9)  || riid == __uuidof(ID3D12Device10) || riid == __uuidof(ID3D12Device11)||
       riid == __uuidof(ID3D12Device12) || riid == __uuidof(ID3D12Device13) || riid == __uuidof(ID3D12Device14))
    {
        *ppvObject = this;
        this->AddRef();
    }
    return result;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::GetPrivateData(REFGUID guid, UINT *pDataSize, void *pData)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice->GetPrivateData(guid, pDataSize, pData);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::SetPrivateData(REFGUID guid, UINT DataSize, const void *pData)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice->SetPrivateData(guid, DataSize, pData);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::SetPrivateDataInterface(REFGUID guid, const IUnknown *pData)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice->SetPrivateDataInterface(guid, pData);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::SetName(LPCWSTR Name)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice->SetName(Name);
}

UINT STDMETHODCALLTYPE WrappedID3D12Device::GetNodeCount()
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice->GetNodeCount();
}

LUID WrappedID3D12Device::GetAdapterLuid()
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice->GetAdapterLuid();
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateCommandQueue(const D3D12_COMMAND_QUEUE_DESC *pDesc, const IID &riid, void **ppCommandQueue)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);

    HRESULT result = m_pDevice->CreateCommandQueue(pDesc, riid, ppCommandQueue);
    if (SUCCEEDED(result) && (ppCommandQueue != nullptr) && (*ppCommandQueue != nullptr))
    {
        D3D12_WRAPPER_DEBUG("Real command queue pointer: {}", *ppCommandQueue);
        if (riid == __uuidof(ID3D12CommandQueue))
        {
            auto *real_queue = reinterpret_cast<ID3D12CommandQueue *>(*ppCommandQueue);
            auto *wrapped_command_queue = gfxshim::D3D12HookManager::GetInstance().ConstructResource<WrappedID3D12CommandQueue>(real_queue, this);
            *ppCommandQueue = wrapped_command_queue;
            D3D12_WRAPPER_DEBUG("Wrapped command queue pointer: {}", reinterpret_cast<void *>(wrapped_command_queue));
        }
    }

    return result;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE type, const IID &riid, void **ppCommandAllocator)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    assert(ppCommandAllocator != nullptr && (*ppCommandAllocator == nullptr));

    HRESULT result =  m_pDevice->CreateCommandAllocator(type, riid, ppCommandAllocator);
    if (SUCCEEDED(result) && ppCommandAllocator != nullptr && (*ppCommandAllocator != nullptr))
    {
        D3D12_WRAPPER_DEBUG("Real command allocator pointer: {}", *ppCommandAllocator);
        if (riid == __uuidof(ID3D12CommandAllocator))
        {
            auto *real_command_allocator = static_cast<ID3D12CommandAllocator *>(*ppCommandAllocator);
            auto *wrapped_command_allocator = gfxshim::D3D12HookManager::GetInstance().ConstructResource<WrappedID3D12CommandAllocator>(real_command_allocator, this);
            *ppCommandAllocator = wrapped_command_allocator;
            D3D12_WRAPPER_DEBUG("Wrapped command allocator pointer: {}", reinterpret_cast<void *>(wrapped_command_allocator));
        }
    } else
    {
        D3D12_WRAPPER_WARN("Failed to create command allocator");
    }
    return result;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateGraphicsPipelineState(const D3D12_GRAPHICS_PIPELINE_STATE_DESC *pDesc, const IID &riid, void **ppPipelineState)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice->CreateGraphicsPipelineState(pDesc, riid, ppPipelineState);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateComputePipelineState(const D3D12_COMPUTE_PIPELINE_STATE_DESC *pDesc, const IID &riid, void **ppPipelineState)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice->CreateComputePipelineState(pDesc, riid, ppPipelineState);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateCommandList(UINT nodeMask, D3D12_COMMAND_LIST_TYPE type,
                                        	                ID3D12CommandAllocator *pCommandAllocator, ID3D12PipelineState *pInitialState, 
                                                            const IID &riid, void **ppCommandList)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);

    ID3D12CommandAllocator *real_command_allocator = pCommandAllocator;
    if (pCommandAllocator)
    {
        if (auto *wrapped_command_allocator = dynamic_cast<WrappedID3D12CommandAllocator *>(pCommandAllocator))
        {
            real_command_allocator = wrapped_command_allocator->GetReal();
        }
    }

    HRESULT result = m_pDevice->CreateCommandList(nodeMask, type, real_command_allocator, pInitialState, riid, ppCommandList);
    if (SUCCEEDED(result) && ppCommandList != nullptr && (*ppCommandList != nullptr))
    {
        D3D12_WRAPPER_DEBUG("Real command list pointer: {}", *ppCommandList);
        if (riid == __uuidof(ID3D12GraphicsCommandList) || riid == __uuidof(ID3D12CommandList) ||
            riid == __uuidof(ID3D12GraphicsCommandList1) || riid == __uuidof(ID3D12GraphicsCommandList2) ||
            riid == __uuidof(ID3D12GraphicsCommandList3) || riid == __uuidof(ID3D12GraphicsCommandList4) ||
            riid == __uuidof(ID3D12GraphicsCommandList5) || riid == __uuidof(ID3D12GraphicsCommandList6) ||
            riid == __uuidof(ID3D12GraphicsCommandList7) || riid == __uuidof(ID3D12GraphicsCommandList8) ||
            riid == __uuidof(ID3D12GraphicsCommandList9) || riid == __uuidof(ID3D12GraphicsCommandList10))
        {
            auto &&hook_manager = gfxshim::D3D12HookManager::GetInstance();
            auto *real_command_list = static_cast<ID3D12GraphicsCommandList *>(*ppCommandList);
            auto *wrapped_command_list = hook_manager.
                                    ConstructResource<WrappedID3D12GraphicsCommandList>(real_command_list, this, dynamic_cast<WrappedID3D12CommandAllocator *>(pCommandAllocator));
            *ppCommandList = wrapped_command_list;
            hook_manager.RegisterCommandListTracer(real_command_list);
            D3D12_WRAPPER_DEBUG("Wrapped command list pointer: {}", reinterpret_cast<void *>(wrapped_command_list));
        }
    } else
    {
        D3D12_WRAPPER_WARN("Failed to create command list");
    }

    return result;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CheckFeatureSupport(D3D12_FEATURE Feature, void *pFeatureSupportData, UINT FeatureSupportDataSize)
{
    return m_pDevice->CheckFeatureSupport(Feature, pFeatureSupportData, FeatureSupportDataSize);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateDescriptorHeap(const D3D12_DESCRIPTOR_HEAP_DESC *pDescriptorHeapDesc, const IID &riid, void **ppvHeap)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice->CreateDescriptorHeap(pDescriptorHeapDesc, riid, ppvHeap);
}

UINT STDMETHODCALLTYPE WrappedID3D12Device::GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapType)
{
    return m_pDevice->GetDescriptorHandleIncrementSize(DescriptorHeapType);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateRootSignature(UINT nodeMask, const void *pBlobWithRootSignature,
                                                SIZE_T blobLengthInBytes, const IID &riid, void **ppvRootSignature)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    auto result =  m_pDevice->CreateRootSignature(nodeMask, pBlobWithRootSignature, blobLengthInBytes, riid, ppvRootSignature);
    if (pBlobWithRootSignature != nullptr && ppvRootSignature != nullptr && (*ppvRootSignature) != nullptr)
    {
        gfxshim::D3D12HookManager::GetInstance().UpdateBlobToRootSignatureMapping(reinterpret_cast<uint64_t>(pBlobWithRootSignature), reinterpret_cast<ID3D12RootSignature *>(*ppvRootSignature));
    }
    return result;
}

void STDMETHODCALLTYPE WrappedID3D12Device::CreateConstantBufferView(const D3D12_CONSTANT_BUFFER_VIEW_DESC *pDesc,
                                                D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
{
    m_pDevice->CreateConstantBufferView(pDesc, DestDescriptor);
}

void STDMETHODCALLTYPE WrappedID3D12Device::CreateShaderResourceView(ID3D12Resource *pResource,
                                        		    const D3D12_SHADER_RESOURCE_VIEW_DESC *pDesc,
                                            	    D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
{
    m_pDevice->CreateShaderResourceView(pResource, pDesc, DestDescriptor);
}

void STDMETHODCALLTYPE WrappedID3D12Device::CreateUnorderedAccessView(ID3D12Resource *pResource,
                                                   	ID3D12Resource *pCounterResource,
                                                   	const D3D12_UNORDERED_ACCESS_VIEW_DESC *pDesc,
                                                	D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
{
    m_pDevice->CreateUnorderedAccessView(pResource, pCounterResource, pDesc, DestDescriptor);
    if (pResource != nullptr && pDesc != nullptr)
    {
        gfxshim::D3D12HookManager::GetInstance().StoreUAVAndResource(DestDescriptor.ptr, pResource, pDesc);
        D3D12_WRAPPER_DEBUG("Create unordered access view, resource: {}, uav: {}, dimension: {}", reinterpret_cast<void *>(pResource), DestDescriptor.ptr, static_cast<uint32_t>(pDesc->ViewDimension));
    }
}

void STDMETHODCALLTYPE WrappedID3D12Device::CreateRenderTargetView(ID3D12Resource *pResource,
                                                const D3D12_RENDER_TARGET_VIEW_DESC *pDesc,
                                                D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
{
    m_pDevice->CreateRenderTargetView(pResource, pDesc, DestDescriptor);
    if (pResource != nullptr && pDesc != nullptr)
    {
        gfxshim::D3D12HookManager::GetInstance().StoreRTVAndResource(DestDescriptor.ptr, pResource, pDesc);
        D3D12_WRAPPER_DEBUG("Create render target view, resource: {}, rtv: {}, dimension: {}", reinterpret_cast<void *>(pResource), DestDescriptor.ptr, static_cast<uint32_t>(pDesc->ViewDimension));
    } else if (pResource != nullptr && pDesc == nullptr)
    {
        gfxshim::D3D12HookManager::GetInstance().StoreRTVAndResource(DestDescriptor.ptr, pResource, nullptr);
        D3D12_WRAPPER_WARN("Create render target view while using null rtv desc");
    }
}

void STDMETHODCALLTYPE WrappedID3D12Device::CreateDepthStencilView(ID3D12Resource *pResource,
                                                const D3D12_DEPTH_STENCIL_VIEW_DESC *pDesc,
                                                D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
{
    m_pDevice->CreateDepthStencilView(pResource, pDesc, DestDescriptor);
    if (pResource != nullptr && pDesc != nullptr)
    {
        gfxshim::D3D12HookManager::GetInstance().StoreDSVAndResource(DestDescriptor.ptr, pResource, pDesc);
        D3D12_WRAPPER_DEBUG("Create depth stencil view, resource: {}, rtv: {}, dimension: {}", reinterpret_cast<void *>(pResource), DestDescriptor.ptr, static_cast<uint32_t>(pDesc->ViewDimension));
    }
}

void STDMETHODCALLTYPE WrappedID3D12Device::CreateSampler(const D3D12_SAMPLER_DESC *pDesc,
                                                        D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    m_pDevice->CreateSampler(pDesc, DestDescriptor);
}

void STDMETHODCALLTYPE WrappedID3D12Device::CopyDescriptors(UINT NumDestDescriptorRanges,
                                                        const D3D12_CPU_DESCRIPTOR_HANDLE *pDestDescriptorRangeStarts,
                                                        const UINT *pDestDescriptorRangeSizes,
                                                        UINT NumSrcDescriptorRanges,
                                                        const D3D12_CPU_DESCRIPTOR_HANDLE *pSrcDescriptorRangeStarts,
                                                        const UINT *pSrcDescriptorRangeSizes,
                                                        D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapsType)
{
    m_pDevice->CopyDescriptors(NumDestDescriptorRanges, pDestDescriptorRangeStarts, pDestDescriptorRangeSizes, NumSrcDescriptorRanges, 
                            pSrcDescriptorRangeStarts, pSrcDescriptorRangeSizes, DescriptorHeapsType);
}

void STDMETHODCALLTYPE WrappedID3D12Device::CopyDescriptorsSimple(UINT NumDescriptors,
                                                D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptorRangeStart,
                                                D3D12_CPU_DESCRIPTOR_HANDLE SrcDescriptorRangeStart,
                                                D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapsType)
{
    m_pDevice->CopyDescriptorsSimple(NumDescriptors, DestDescriptorRangeStart, SrcDescriptorRangeStart, DescriptorHeapsType);
}

D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE WrappedID3D12Device::GetResourceAllocationInfo(UINT visibleMask, UINT numResourceDescs, 
                                                                    const D3D12_RESOURCE_DESC *pResourceDescs)
{
    return m_pDevice->GetResourceAllocationInfo(visibleMask, numResourceDescs, pResourceDescs);
}

D3D12_HEAP_PROPERTIES STDMETHODCALLTYPE WrappedID3D12Device::GetCustomHeapProperties(UINT nodeMask, D3D12_HEAP_TYPE heapType)
{
    return m_pDevice->GetCustomHeapProperties(nodeMask, heapType);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateCommittedResource(const D3D12_HEAP_PROPERTIES *pHeapProperties,
                                                        D3D12_HEAP_FLAGS HeapFlags,
                                                        const D3D12_RESOURCE_DESC *pDesc,
                                                        D3D12_RESOURCE_STATES InitialResourceState,
                                                        const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                        const IID &riidResource, void **ppvResource)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    HRESULT result =  m_pDevice->CreateCommittedResource(pHeapProperties, HeapFlags, pDesc, InitialResourceState,
                                                pOptimizedClearValue, riidResource, ppvResource);
    if (pDesc != nullptr && ppvResource != nullptr && (*ppvResource) != nullptr)
    {
        if (pDesc->Dimension == D3D12_RESOURCE_DIMENSION_BUFFER && (pDesc->Flags & D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS) != 0)
        {
            auto *buffer = static_cast<ID3D12Resource *>(*ppvResource);
            gfxshim::D3D12HookManager::GetInstance().StoreRootBufferMapping(buffer);
        }
    }
    return result;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateHeap(const D3D12_HEAP_DESC *pDesc, const IID &riid, void **ppvHeap)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice->CreateHeap(pDesc, riid, ppvHeap);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreatePlacedResource(ID3D12Heap *pHeap, UINT64 HeapOffset,
                                                        const D3D12_RESOURCE_DESC *pDesc,
                                                        D3D12_RESOURCE_STATES InitialState,
                                                        const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                        const IID &riid, void **ppvResource)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice->CreatePlacedResource(pHeap, HeapOffset, pDesc, InitialState, pOptimizedClearValue, riid, ppvResource);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateReservedResource(const D3D12_RESOURCE_DESC *pDesc,
                                                    D3D12_RESOURCE_STATES InitialState,
                                                    const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                    const IID &riid, void **ppvResource)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice->CreateReservedResource(pDesc, InitialState, pOptimizedClearValue, riid, ppvResource);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateSharedHandle(ID3D12DeviceChild *pObject,
                                            const SECURITY_ATTRIBUTES *pAttributes, DWORD Access,
                                            LPCWSTR Name, HANDLE *pHandle)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice->CreateSharedHandle(pObject, pAttributes, Access, Name, pHandle);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::OpenSharedHandle(HANDLE NTHandle, const IID &riid, void **ppvObj)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice->OpenSharedHandle(NTHandle, riid, ppvObj);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::OpenSharedHandleByName(LPCWSTR Name, DWORD Access, HANDLE *pNTHandle)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice->OpenSharedHandleByName(Name, Access, pNTHandle);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::MakeResident(UINT NumObjects, ID3D12Pageable *const *ppObjects)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice->MakeResident(NumObjects, ppObjects);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::Evict(UINT NumObjects, ID3D12Pageable *const *ppObjects)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice->Evict(NumObjects, ppObjects);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateFence(UINT64 InitialValue, D3D12_FENCE_FLAGS Flags,
                                                    const IID &riid, void **ppFence)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice->CreateFence(InitialValue, Flags, riid, ppFence);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::GetDeviceRemovedReason()
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice->GetDeviceRemovedReason();
}

void STDMETHODCALLTYPE WrappedID3D12Device::GetCopyableFootprints(const D3D12_RESOURCE_DESC *pResourceDesc,
                                                    UINT FirstSubresource, UINT NumSubresources,
                                                    UINT64 BaseOffset,
                                                    D3D12_PLACED_SUBRESOURCE_FOOTPRINT *pLayouts,
                                                    UINT *pNumRows, UINT64 *pRowSizeInBytes,
                                                    UINT64 *pTotalBytes)
{
    m_pDevice->GetCopyableFootprints(pResourceDesc, FirstSubresource, NumSubresources, BaseOffset, pLayouts, pNumRows, pRowSizeInBytes, pTotalBytes);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateQueryHeap(const D3D12_QUERY_HEAP_DESC *pDesc, const IID &riid,
                                                                void **ppvHeap)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice->CreateQueryHeap(pDesc, riid, ppvHeap);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::SetStablePowerState(BOOL Enable)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice->SetStablePowerState(Enable);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateCommandSignature(const D3D12_COMMAND_SIGNATURE_DESC *pDesc,
                                                   ID3D12RootSignature *pRootSignature,
                                                   const IID &riid, void **ppvCommandSignature)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    const auto result = m_pDevice->CreateCommandSignature(pDesc, pRootSignature, riid, ppvCommandSignature);
    if (pDesc != nullptr && ppvCommandSignature != nullptr && (*ppvCommandSignature) != nullptr)
    {
        gfxshim::D3D12HookManager::GetInstance().StoreCommandSignature(reinterpret_cast<uint64_t>(*ppvCommandSignature), pDesc);
    }
    return result;
}

void STDMETHODCALLTYPE WrappedID3D12Device::GetResourceTiling(ID3D12Resource *pTiledResource,
                                           	                UINT *pNumTilesForEntireResource,
                                           	                D3D12_PACKED_MIP_INFO *pPackedMipDesc,
                                           	                D3D12_TILE_SHAPE *pStandardTileShapeForNonPackedMips,
                                           	                UINT *pNumSubresourceTilings,
                                           	                UINT FirstSubresourceTilingToGet,
                                           	                D3D12_SUBRESOURCE_TILING *pSubresourceTilingsForNonPackedMips)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    m_pDevice->GetResourceTiling(pTiledResource, pNumTilesForEntireResource, pPackedMipDesc, 
                                pStandardTileShapeForNonPackedMips, pNumSubresourceTilings, FirstSubresourceTilingToGet, pSubresourceTilingsForNonPackedMips);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreatePipelineLibrary(const void *pLibraryBlob, SIZE_T BlobLength,
                                                                const IID &riid, void **ppPipelineLibrary)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice1->CreatePipelineLibrary(pLibraryBlob, BlobLength, riid, ppPipelineLibrary);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::SetEventOnMultipleFenceCompletion(ID3D12Fence *const *ppFences, const UINT64 *pFenceValues, UINT NumFences,
														D3D12_MULTIPLE_FENCE_WAIT_FLAGS Flags, HANDLE hEvent)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice1->SetEventOnMultipleFenceCompletion(ppFences, pFenceValues, NumFences, Flags, hEvent);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::SetResidencyPriority(UINT NumObjects, ID3D12Pageable *const *ppObjects,
                                                 const D3D12_RESIDENCY_PRIORITY *pPriorities)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice1->SetResidencyPriority(NumObjects, ppObjects, pPriorities);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreatePipelineState(const D3D12_PIPELINE_STATE_STREAM_DESC *pDesc,
                                                                const IID &riid, void **ppPipelineState)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice2->CreatePipelineState(pDesc, riid, ppPipelineState);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::OpenExistingHeapFromAddress(const void *pAddress, const IID &riid, void **ppvHeap)
{
    return m_pDevice3->OpenExistingHeapFromAddress(pAddress, riid, ppvHeap);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::OpenExistingHeapFromFileMapping(HANDLE hFileMapping, const IID &riid, void **ppvHeap)
{
    return m_pDevice3->OpenExistingHeapFromFileMapping(hFileMapping, riid, ppvHeap);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::EnqueueMakeResident(D3D12_RESIDENCY_FLAGS Flags, UINT NumObjects,
                                                                ID3D12Pageable *const *ppObjects,
                                                                ID3D12Fence *pFenceToSignal,
                                                                UINT64 FenceValueToSignal)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice3->EnqueueMakeResident(Flags, NumObjects, ppObjects, pFenceToSignal, FenceValueToSignal);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateCommandList1(UINT nodeMask, D3D12_COMMAND_LIST_TYPE type,
                                            	                D3D12_COMMAND_LIST_FLAGS flags, const IID &riid,
                                            	                void **ppCommandList)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);

    HRESULT result = m_pDevice4->CreateCommandList1(nodeMask, type, flags, riid, ppCommandList);
    if (SUCCEEDED(result) && ppCommandList != nullptr && (*ppCommandList != nullptr))
    {
        D3D12_WRAPPER_DEBUG("Real command list1 pointer: {}", *ppCommandList);
        if (riid == __uuidof(ID3D12GraphicsCommandList)  || riid == __uuidof(ID3D12GraphicsCommandList1)  || riid == __uuidof(ID3D12GraphicsCommandList2) ||
            riid == __uuidof(ID3D12GraphicsCommandList3) || riid == __uuidof(ID3D12GraphicsCommandList4)  || riid == __uuidof(ID3D12GraphicsCommandList5) ||
            riid == __uuidof(ID3D12GraphicsCommandList6) || riid == __uuidof(ID3D12GraphicsCommandList7)  || riid == __uuidof(ID3D12GraphicsCommandList8) ||
            riid == __uuidof(ID3D12GraphicsCommandList9) || riid == __uuidof(ID3D12GraphicsCommandList10) || riid == __uuidof(ID3D12CommandList))
        {
            auto &&hook_manager = gfxshim::D3D12HookManager::GetInstance();
            auto real_command_list = static_cast<ID3D12GraphicsCommandList *>(*ppCommandList);
            auto *wrapped_command_list = hook_manager.ConstructResource<WrappedID3D12GraphicsCommandList>(real_command_list, this, nullptr);
            hook_manager.RegisterCommandListTracer(real_command_list);
            *ppCommandList = wrapped_command_list;
            D3D12_WRAPPER_DEBUG("Wrapped command list1 pointer: {}", reinterpret_cast<void *>(wrapped_command_list));
        }
    }

    return result;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateProtectedResourceSession(_In_ const D3D12_PROTECTED_RESOURCE_SESSION_DESC *pDesc,
                                 						_In_ REFIID riid, _COM_Outptr_ void **ppSession)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice4->CreateProtectedResourceSession(pDesc, riid, ppSession);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateCommittedResource1(const D3D12_HEAP_PROPERTIES *pHeapProperties,
                                                    D3D12_HEAP_FLAGS HeapFlags,
                                                    const D3D12_RESOURCE_DESC *pDesc,
                                                    D3D12_RESOURCE_STATES InitialResourceState,
                                                    const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                    ID3D12ProtectedResourceSession *pProtectedSession, 
                                                    const IID &riidResource,
                                                    void **ppvResource)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    auto result = m_pDevice4->CreateCommittedResource1(pHeapProperties, HeapFlags, pDesc,
                                                InitialResourceState, pOptimizedClearValue, pProtectedSession, 
                                                riidResource, ppvResource);
    if (pDesc != nullptr && ppvResource != nullptr && (*ppvResource) != nullptr)
    {
        if (pDesc->Dimension == D3D12_RESOURCE_DIMENSION_BUFFER)
        {
            auto *buffer = static_cast<ID3D12Resource *>(*ppvResource);
            gfxshim::D3D12HookManager::GetInstance().StoreRootBufferMapping(buffer);
        }
    }
    return result;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateHeap1(const D3D12_HEAP_DESC *pDesc,
                                            ID3D12ProtectedResourceSession *pProtectedSession,
                                            const IID &riid, void **ppvHeap)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice4->CreateHeap1(pDesc, pProtectedSession, riid, ppvHeap);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateReservedResource1(const D3D12_RESOURCE_DESC *pDesc,
                                                D3D12_RESOURCE_STATES InitialState,
                                                const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                ID3D12ProtectedResourceSession *
                                                pProtectedSession, const IID &riid,
                                                void **ppvResource)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice4->CreateReservedResource1(pDesc, InitialState, pOptimizedClearValue, pProtectedSession, riid, ppvResource);
}

D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE WrappedID3D12Device::GetResourceAllocationInfo1(
                                            UINT visibleMask, UINT numResourceDescs,
      										_In_reads_(numResourceDescs) const D3D12_RESOURCE_DESC *pResourceDescs,
      										_Out_writes_opt_(numResourceDescs) D3D12_RESOURCE_ALLOCATION_INFO1 *pResourceAllocationInfo1)
{
    return m_pDevice4->GetResourceAllocationInfo1(visibleMask, numResourceDescs, pResourceDescs, pResourceAllocationInfo1);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateLifetimeTracker(ID3D12LifetimeOwner *pOwner, const IID &riid,
                                                  	void **ppvTracker)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice5->CreateLifetimeTracker(pOwner, riid, ppvTracker);
}

void STDMETHODCALLTYPE WrappedID3D12Device::RemoveDevice()
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    m_pDevice5->RemoveDevice();
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::EnumerateMetaCommands(_Inout_ UINT *pNumMetaCommands,
                                            _Out_writes_opt_(*pNumMetaCommands) D3D12_META_COMMAND_DESC *pDescs)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice5->EnumerateMetaCommands(pNumMetaCommands, pDescs);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::EnumerateMetaCommandParameters(
      										_In_ REFGUID CommandId, _In_ D3D12_META_COMMAND_PARAMETER_STAGE Stage,
      										_Out_opt_ UINT *pTotalStructureSizeInBytes, _Inout_ UINT *pParameterCount,
      										_Out_writes_opt_(*pParameterCount) D3D12_META_COMMAND_PARAMETER_DESC *pParameterDescs)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice5->EnumerateMetaCommandParameters(CommandId, Stage, pTotalStructureSizeInBytes, pParameterCount, pParameterDescs);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateMetaCommand(const GUID &CommandId, UINT NodeMask,
                                              const void *pCreationParametersData,
                                              SIZE_T CreationParametersDataSizeInBytes,
                                              const IID &riid, void **ppMetaCommand)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice5->CreateMetaCommand(CommandId, NodeMask, pCreationParametersData, CreationParametersDataSizeInBytes, riid, ppMetaCommand);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateStateObject(const D3D12_STATE_OBJECT_DESC *pDesc, const IID &riid,
                                              	void **ppStateObject)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice5->CreateStateObject(pDesc, riid, ppStateObject);
}

void STDMETHODCALLTYPE WrappedID3D12Device::GetRaytracingAccelerationStructurePrebuildInfo(
      										_In_ const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS *pDesc,
      										_Out_ D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO *pInfo)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice5->GetRaytracingAccelerationStructurePrebuildInfo(pDesc, pInfo);
}

D3D12_DRIVER_MATCHING_IDENTIFIER_STATUS STDMETHODCALLTYPE WrappedID3D12Device::CheckDriverMatchingIdentifier(
      										_In_ D3D12_SERIALIZED_DATA_TYPE SerializedDataType,
      										_In_ const D3D12_SERIALIZED_DATA_DRIVER_MATCHING_IDENTIFIER *pIdentifierToCheck)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice5->CheckDriverMatchingIdentifier(SerializedDataType, pIdentifierToCheck);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::SetBackgroundProcessingMode(
      						D3D12_BACKGROUND_PROCESSING_MODE Mode, D3D12_MEASUREMENTS_ACTION MeasurementsAction,
      						_In_opt_ HANDLE hEventToSignalUponCompletion, _Out_opt_ BOOL *pbFurtherMeasurementsDesired)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice6->SetBackgroundProcessingMode(Mode, MeasurementsAction, hEventToSignalUponCompletion, pbFurtherMeasurementsDesired);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::AddToStateObject(const D3D12_STATE_OBJECT_DESC *pAddition,
                                             ID3D12StateObject *pStateObjectToGrowFrom,
                                             const IID &riid, void **ppNewStateObject)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice7->AddToStateObject(pAddition, pStateObjectToGrowFrom, riid, ppNewStateObject);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateProtectedResourceSession1(_In_ const D3D12_PROTECTED_RESOURCE_SESSION_DESC1 *pDesc,
                                  							_In_ REFIID riid, _COM_Outptr_ void **ppSession)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice7->CreateProtectedResourceSession1(pDesc, riid, ppSession);
}

D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE WrappedID3D12Device::GetResourceAllocationInfo2(
      										UINT visibleMask, UINT numResourceDescs,
      										_In_reads_(numResourceDescs) const D3D12_RESOURCE_DESC1 *pResourceDescs,
      										_Out_writes_opt_(numResourceDescs) D3D12_RESOURCE_ALLOCATION_INFO1 *pResourceAllocationInfo1)
{
    return m_pDevice8->GetResourceAllocationInfo2(visibleMask, numResourceDescs, pResourceDescs, pResourceAllocationInfo1);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateCommittedResource2(const D3D12_HEAP_PROPERTIES *pHeapProperties,
                                            		D3D12_HEAP_FLAGS HeapFlags,
                                            		const D3D12_RESOURCE_DESC1 *pDesc,
                                            		D3D12_RESOURCE_STATES InitialResourceState,
                                            		const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                            		ID3D12ProtectedResourceSession *
                                            		pProtectedSession, const IID &riidResource,
                                            		void **ppvResource)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice8->CreateCommittedResource2(pHeapProperties, HeapFlags, pDesc, InitialResourceState, 
                    pOptimizedClearValue, pProtectedSession, riidResource, ppvResource);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreatePlacedResource1(ID3D12Heap *pHeap, UINT64 HeapOffset,
                                                  const D3D12_RESOURCE_DESC1 *pDesc,
                                                  D3D12_RESOURCE_STATES InitialState,
                                                  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                  const IID &riid, void **ppvResource)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice8->CreatePlacedResource1(pHeap, HeapOffset, pDesc, InitialState, pOptimizedClearValue, riid, ppvResource);
}

void STDMETHODCALLTYPE WrappedID3D12Device::CreateSamplerFeedbackUnorderedAccessView(
      						_In_opt_ ID3D12Resource *pTargetedResource, _In_opt_ ID3D12Resource *pFeedbackResource,
      						_In_ D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    m_pDevice8->CreateSamplerFeedbackUnorderedAccessView(pTargetedResource, pFeedbackResource, DestDescriptor);
}

void STDMETHODCALLTYPE WrappedID3D12Device::GetCopyableFootprints1(
      						_In_ const D3D12_RESOURCE_DESC1 *pResourceDesc,
      						_In_range_(0, D3D12_REQ_SUBRESOURCES) UINT FirstSubresource,
      						_In_range_(0, D3D12_REQ_SUBRESOURCES - FirstSubresource) UINT NumSubresources,
      						UINT64 BaseOffset,
      						_Out_writes_opt_(NumSubresources) D3D12_PLACED_SUBRESOURCE_FOOTPRINT *pLayouts,
      						_Out_writes_opt_(NumSubresources) UINT *pNumRows,
      						_Out_writes_opt_(NumSubresources) UINT64 *pRowSizeInBytes, _Out_opt_ UINT64 *pTotalBytes)
{
    m_pDevice8->GetCopyableFootprints1(pResourceDesc, FirstSubresource, NumSubresources, BaseOffset, 
                        pLayouts, pNumRows, pRowSizeInBytes, pTotalBytes);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateShaderCacheSession(_In_ const D3D12_SHADER_CACHE_SESSION_DESC *pDesc, REFIID riid,
                           _COM_Outptr_opt_ void **ppvSession)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice9->CreateShaderCacheSession(pDesc, riid, ppvSession);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::ShaderCacheControl(D3D12_SHADER_CACHE_KIND_FLAGS Kinds, D3D12_SHADER_CACHE_CONTROL_FLAGS Control)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice9->ShaderCacheControl(Kinds, Control);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateCommandQueue1(const D3D12_COMMAND_QUEUE_DESC *pDesc,
                                                const IID &CreatorID, const IID &riid,
                                                void **ppCommandQueue) 
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);

    HRESULT result = m_pDevice9->CreateCommandQueue1(pDesc, CreatorID, riid, ppCommandQueue);
    if (SUCCEEDED(result) && ppCommandQueue != nullptr && (*ppCommandQueue != nullptr))
    {
        D3D12_WRAPPER_DEBUG("Real command queue pointer: {}", *ppCommandQueue);
        if(riid == __uuidof(ID3D12CommandQueue))
        {
            auto *real_queue = static_cast<ID3D12CommandQueue *>(*ppCommandQueue);
            auto *wrapped_command_queue = gfxshim::D3D12HookManager::GetInstance().ConstructResource<WrappedID3D12CommandQueue>(real_queue, this);
            *ppCommandQueue = wrapped_command_queue;
            D3D12_WRAPPER_DEBUG("Wrapped command queue pointer: {}", reinterpret_cast<void *>(wrapped_command_queue));
        }
    }

    return result;
}


HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateCommittedResource3( 
            				_In_  const D3D12_HEAP_PROPERTIES *pHeapProperties,
            				D3D12_HEAP_FLAGS HeapFlags,
            				_In_  const D3D12_RESOURCE_DESC1 *pDesc,
            				D3D12_BARRIER_LAYOUT InitialLayout,
            				_In_opt_  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
            				_In_opt_  ID3D12ProtectedResourceSession *pProtectedSession,
            				UINT32 NumCastableFormats,
            				_In_opt_count_(NumCastableFormats) const DXGI_FORMAT *pCastableFormats,
            				REFIID riidResource,
            				_COM_Outptr_opt_  void **ppvResource)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice10->CreateCommittedResource3(pHeapProperties, HeapFlags, pDesc, InitialLayout, 
                pOptimizedClearValue, pProtectedSession, NumCastableFormats, pCastableFormats, riidResource, ppvResource);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreatePlacedResource2( 
            					_In_  ID3D12Heap *pHeap,
            					UINT64 HeapOffset,
            					_In_  const D3D12_RESOURCE_DESC1 *pDesc,
            					D3D12_BARRIER_LAYOUT InitialLayout,
            					_In_opt_  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
            					UINT32 NumCastableFormats,
            					_In_opt_count_(NumCastableFormats) const DXGI_FORMAT *pCastableFormats,
            					REFIID riid,
            					_COM_Outptr_opt_  void **ppvResource)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice10->CreatePlacedResource2(pHeap, HeapOffset, pDesc, InitialLayout, pOptimizedClearValue, 
                NumCastableFormats, pCastableFormats, riid, ppvResource);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateReservedResource2( 
            					_In_  const D3D12_RESOURCE_DESC *pDesc,
            					D3D12_BARRIER_LAYOUT InitialLayout,
            					_In_opt_  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
            					_In_opt_  ID3D12ProtectedResourceSession *pProtectedSession,
            					UINT32 NumCastableFormats,
            					_In_opt_count_(NumCastableFormats) const DXGI_FORMAT *pCastableFormats,
            					REFIID riid,
            					_COM_Outptr_opt_  void **ppvResource)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice10->CreateReservedResource2(pDesc, InitialLayout, pOptimizedClearValue, pProtectedSession, 
                NumCastableFormats, pCastableFormats, riid, ppvResource);
}

void STDMETHODCALLTYPE WrappedID3D12Device::CreateSampler2(_In_  const D3D12_SAMPLER_DESC2 *pDesc, _In_  D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    m_pDevice11->CreateSampler2(pDesc, DestDescriptor);
}

D3D12_RESOURCE_ALLOCATION_INFO STDMETHODCALLTYPE WrappedID3D12Device::GetResourceAllocationInfo3(
        UINT visibleMask,
        UINT numResourceDescs,
        _In_reads_(numResourceDescs)  const D3D12_RESOURCE_DESC1 *pResourceDescs,
        _In_opt_count_(numResourceDescs)  const UINT32 *pNumCastableFormats,
        _In_opt_count_(numResourceDescs)  const DXGI_FORMAT *const *ppCastableFormats,
        _Out_writes_opt_(numResourceDescs)  D3D12_RESOURCE_ALLOCATION_INFO1 *pResourceAllocationInfo1)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice12->GetResourceAllocationInfo3(visibleMask, numResourceDescs, pResourceDescs, pNumCastableFormats, ppCastableFormats, pResourceAllocationInfo1);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::OpenExistingHeapFromAddress1(
        _In_  const void *pAddress,
        SIZE_T size,
        REFIID riid,
        _COM_Outptr_  void **ppvHeap)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice13->OpenExistingHeapFromAddress1(pAddress, size, riid, ppvHeap);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateRootSignatureFromSubobjectInLibrary(
        _In_  UINT nodeMask,
        _In_reads_(blobLengthInBytes)  const void *pLibraryBlob,
        _In_  SIZE_T blobLengthInBytes,
        _In_opt_  LPCWSTR subobjectName,
        REFIID riid,
        _COM_Outptr_  void **ppvRootSignature)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_pDevice14->CreateRootSignatureFromSubobjectInLibrary(nodeMask, pLibraryBlob, blobLengthInBytes, subobjectName, riid, ppvRootSignature);
}

extern "C" __declspec(dllexport) HRESULT QueryRealDevice(IUnknown *wrapped_device_pointer, IUnknown **real_device_pointer)
{
    if (const auto *wrapped_device = dynamic_cast<WrappedID3D12Device *>(wrapped_device_pointer))
    {
        *real_device_pointer = wrapped_device->GetReal();
        return S_OK;
    }
    return E_FAIL;
}