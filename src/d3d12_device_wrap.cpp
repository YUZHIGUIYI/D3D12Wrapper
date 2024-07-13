#include "d3d12_device_wrap.h"
#include "d3d12_command_queue.h"
#include "d3d12_command_list.h"
#include <d3d12.h>
#include <winnt.h>

std::map<ID3D12Device *, WrappedID3D12Device *> WrappedID3D12Device::m_device_wrappers;

WrappedID3D12Device *WrappedID3D12Device::create(ID3D12Device *real_device)
{
    // TODO: mutex
    auto it = m_device_wrappers.find(real_device);
    if (it != m_device_wrappers.end())
    {
        it->second->AddRef();
        return it->second;
    }

    return new WrappedID3D12Device(real_device);
}

WrappedID3D12Device::WrappedID3D12Device(ID3D12Device *real_device)
: m_pDevice(real_device)
{
    if(m_pDevice)
    {
        m_pDevice->QueryInterface(__uuidof(ID3D12Device1), (void **)&m_pDevice1);
        m_pDevice->QueryInterface(__uuidof(ID3D12Device2), (void **)&m_pDevice2);
        m_pDevice->QueryInterface(__uuidof(ID3D12Device3), (void **)&m_pDevice3);
        m_pDevice->QueryInterface(__uuidof(ID3D12Device4), (void **)&m_pDevice4);
        m_pDevice->QueryInterface(__uuidof(ID3D12Device5), (void **)&m_pDevice5);
        m_pDevice->QueryInterface(__uuidof(ID3D12Device6), (void **)&m_pDevice6);
        m_pDevice->QueryInterface(__uuidof(ID3D12Device7), (void **)&m_pDevice7);
        m_pDevice->QueryInterface(__uuidof(ID3D12Device8), (void **)&m_pDevice8);
        m_pDevice->QueryInterface(__uuidof(ID3D12Device9), (void **)&m_pDevice9);
        m_pDevice->QueryInterface(__uuidof(ID3D12Device10), (void **)&m_pDevice10);
    }

    if (m_pDevice)
    {
        // using PFN_CREATE_DXGI_FACTORY =  HRESULT(WINAPI *)(REFIID, void **);
        // PFN_CREATE_DXGI_FACTORY create_dxgi_factory_func = (PFN_CREATE_DXGI_FACTORY)GetProcAddress(
        //     GetModuleHandleA("dxgi.dll"), "CreateDXGIFactory1");
    
        // IDXGIFactory1 *temp_factory = nullptr;
        // HRESULT result  = create_dxgi_factory_func(__uuidof(IDXGIFactory1), (void **)&temp_factory);

        // if (temp_factory)
        // {

        // }
    }

    {
        // TODO: mutex
        m_device_wrappers[m_pDevice] = this;
    }
}

ULONG STDMETHODCALLTYPE WrappedID3D12Device::AddRef()
{
    // TODO: fix
    return m_pDevice->AddRef();
}

ULONG STDMETHODCALLTYPE WrappedID3D12Device::Release()
{
    // TODO: fix
    return m_pDevice->Release();
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::QueryInterface(REFIID riid, void **ppvObject)
{
    // TODO: fix
    return m_pDevice->QueryInterface(riid, ppvObject);
}

// Don't need to wrap any of these functions below
HRESULT STDMETHODCALLTYPE WrappedID3D12Device::GetPrivateData(REFGUID guid, UINT *pDataSize, void *pData)
{
    return m_pDevice->GetPrivateData(guid, pDataSize, pData);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::SetPrivateData(REFGUID guid, UINT DataSize, const void *pData)
{
    return m_pDevice->SetPrivateData(guid, DataSize, pData);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::SetPrivateDataInterface(REFGUID guid, const IUnknown *pData)
{
    return m_pDevice->SetPrivateDataInterface(guid, pData);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::SetName(LPCWSTR Name)
{
    return m_pDevice->SetName(Name);
}

UINT STDMETHODCALLTYPE WrappedID3D12Device::GetNodeCount()
{
    return m_pDevice->GetNodeCount();
}

LUID WrappedID3D12Device::GetAdapterLuid()
{
    return m_pDevice->GetAdapterLuid();
}

// Wrap these functions below
HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateCommandQueue(const D3D12_COMMAND_QUEUE_DESC *pDesc, const IID &riid, void **ppCommandQueue)
{
    if (ppCommandQueue == nullptr)
    {
        return m_pDevice->CreateCommandQueue(pDesc, riid, ppCommandQueue);
    }

    if (riid != __uuidof(ID3D12CommandQueue))
    {
        return E_NOINTERFACE;
    }

    ID3D12CommandQueue *real_queue = nullptr;
    HRESULT result = m_pDevice->CreateCommandQueue(pDesc, riid, (void **)&real_queue);

    if (SUCCEEDED(result))
    {
        WrappedD3D12CommandQueue *wrapped_command_queue = new WrappedD3D12CommandQueue(real_queue, this);
        *ppCommandQueue = (ID3D12CommandQueue *)wrapped_command_queue;
    }

    return result;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE type, const IID &riid,
                                            void **ppCommandAllocator)
{
    return m_pDevice->CreateCommandAllocator(type, riid, ppCommandAllocator);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateGraphicsPipelineState(const D3D12_GRAPHICS_PIPELINE_STATE_DESC *pDesc, const IID &riid, void **ppPipelineState)
{
    return m_pDevice->CreateGraphicsPipelineState(pDesc, riid, ppPipelineState);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateComputePipelineState(const D3D12_COMPUTE_PIPELINE_STATE_DESC *pDesc, const IID &riid, void **ppPipelineState)
{
    return m_pDevice->CreateComputePipelineState(pDesc, riid, ppPipelineState);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateCommandList(UINT nodeMask, D3D12_COMMAND_LIST_TYPE type,
                                        	                ID3D12CommandAllocator *pCommandAllocator, ID3D12PipelineState *pInitialState, 
                                                            const IID &riid, void **ppCommandList)
{
    if (ppCommandList == nullptr)
    {
        return m_pDevice->CreateCommandList(nodeMask, type, pCommandAllocator, pInitialState, riid, nullptr);
    }

    if (riid != __uuidof(ID3D12GraphicsCommandList) && riid != __uuidof(ID3D12CommandList) &&
        riid != __uuidof(ID3D12GraphicsCommandList1) && riid != __uuidof(ID3D12GraphicsCommandList2) &&
        riid != __uuidof(ID3D12GraphicsCommandList3) && riid != __uuidof(ID3D12GraphicsCommandList4) &&
        riid != __uuidof(ID3D12GraphicsCommandList5) && riid != __uuidof(ID3D12GraphicsCommandList6) &&
        riid != __uuidof(ID3D12GraphicsCommandList7))
    {
        return E_NOINTERFACE;
    }
    
    void *real_ptr = nullptr;
    ID3D12GraphicsCommandList *real_command_list = nullptr;
    HRESULT result = m_pDevice->CreateCommandList(nodeMask, type, pCommandAllocator, pInitialState, riid, &real_ptr);

    if(riid == __uuidof(ID3D12CommandList))
    {
        real_command_list = (ID3D12GraphicsCommandList *)(ID3D12CommandList *)real_ptr;
    }
    else if(riid == __uuidof(ID3D12GraphicsCommandList))
    {
        real_command_list = (ID3D12GraphicsCommandList *)real_ptr;
    }
    else if(riid == __uuidof(ID3D12GraphicsCommandList1))
    {
        real_command_list = (ID3D12GraphicsCommandList1 *)real_ptr;
    }
    else if(riid == __uuidof(ID3D12GraphicsCommandList2))
    {
        real_command_list = (ID3D12GraphicsCommandList2 *)real_ptr;
    }
    else if(riid == __uuidof(ID3D12GraphicsCommandList3))
    {
        real_command_list = (ID3D12GraphicsCommandList3 *)real_ptr;
    }
    else if(riid == __uuidof(ID3D12GraphicsCommandList4))
    {
        real_command_list = (ID3D12GraphicsCommandList4 *)real_ptr;
    }
    else if(riid == __uuidof(ID3D12GraphicsCommandList5))
    {
        real_command_list = (ID3D12GraphicsCommandList5 *)real_ptr;
    }
    else if(riid == __uuidof(ID3D12GraphicsCommandList6))
    {
        real_command_list = (ID3D12GraphicsCommandList6 *)real_ptr;
    }
    else if(riid == __uuidof(ID3D12GraphicsCommandList7))
    {
        real_command_list = (ID3D12GraphicsCommandList7 *)real_ptr;
    }

    if (SUCCEEDED(result))
    {
        WrappedID3D12GraphicsCommandList *wrapped_command_list = new WrappedID3D12GraphicsCommandList(real_command_list, this);

        if(riid == __uuidof(ID3D12GraphicsCommandList))
        {
            *ppCommandList = (ID3D12GraphicsCommandList *)wrapped_command_list;
        }
        else if(riid == __uuidof(ID3D12GraphicsCommandList1))
        {
            *ppCommandList = (ID3D12GraphicsCommandList1 *)wrapped_command_list;
        }
        else if(riid == __uuidof(ID3D12GraphicsCommandList2))
        {
            *ppCommandList = (ID3D12GraphicsCommandList2 *)wrapped_command_list;
        }
        else if(riid == __uuidof(ID3D12GraphicsCommandList3))
        {
            *ppCommandList = (ID3D12GraphicsCommandList3 *)wrapped_command_list;
        }
        else if(riid == __uuidof(ID3D12GraphicsCommandList4))
        {
            *ppCommandList = (ID3D12GraphicsCommandList4 *)wrapped_command_list;
        }
        else if(riid == __uuidof(ID3D12GraphicsCommandList5))
        {
            *ppCommandList = (ID3D12GraphicsCommandList5 *)wrapped_command_list;
        }
        else if(riid == __uuidof(ID3D12GraphicsCommandList6))
        {
            *ppCommandList = (ID3D12GraphicsCommandList6 *)wrapped_command_list;
        }
        else if(riid == __uuidof(ID3D12GraphicsCommandList7))
        {
            *ppCommandList = (ID3D12GraphicsCommandList7 *)wrapped_command_list;
        }
    }

    return result;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CheckFeatureSupport(D3D12_FEATURE Feature, void *pFeatureSupportData, UINT FeatureSupportDataSize)
{
    return m_pDevice->CheckFeatureSupport(Feature, pFeatureSupportData, FeatureSupportDataSize);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateDescriptorHeap(const D3D12_DESCRIPTOR_HEAP_DESC *pDescriptorHeapDesc, const IID &riid, void **ppvHeap)
{
    return m_pDevice->CreateDescriptorHeap(pDescriptorHeapDesc, riid, ppvHeap);
}

UINT STDMETHODCALLTYPE WrappedID3D12Device::GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeapType)
{
    return m_pDevice->GetDescriptorHandleIncrementSize(DescriptorHeapType);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateRootSignature(UINT nodeMask, const void *pBlobWithRootSignature,
                                                SIZE_T blobLengthInBytes, const IID &riid, void **ppvRootSignature)
{
    return m_pDevice->CreateRootSignature(nodeMask, pBlobWithRootSignature, blobLengthInBytes, riid, ppvRootSignature);
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
}

void STDMETHODCALLTYPE WrappedID3D12Device::CreateRenderTargetView(ID3D12Resource *pResource,
                                                const D3D12_RENDER_TARGET_VIEW_DESC *pDesc,
                                                D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
{
    m_pDevice->CreateRenderTargetView(pResource, pDesc, DestDescriptor);
}

void STDMETHODCALLTYPE WrappedID3D12Device::CreateDepthStencilView(ID3D12Resource *pResource,
                                                const D3D12_DEPTH_STENCIL_VIEW_DESC *pDesc,
                                                D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
{
    m_pDevice->CreateDepthStencilView(pResource, pDesc, DestDescriptor);
}

void STDMETHODCALLTYPE WrappedID3D12Device::CreateSampler(const D3D12_SAMPLER_DESC *pDesc,
                                                        D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
{
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
    return m_pDevice->CreateCommittedResource(pHeapProperties, HeapFlags, pDesc, InitialResourceState, 
                                            pOptimizedClearValue, riidResource, ppvResource);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateHeap(const D3D12_HEAP_DESC *pDesc, const IID &riid, void **ppvHeap)
{
    return m_pDevice->CreateHeap(pDesc, riid, ppvHeap);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreatePlacedResource(ID3D12Heap *pHeap, UINT64 HeapOffset,
                                                        const D3D12_RESOURCE_DESC *pDesc,
                                                        D3D12_RESOURCE_STATES InitialState,
                                                        const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                        const IID &riid, void **ppvResource)
{
    return m_pDevice->CreatePlacedResource(pHeap, HeapOffset, pDesc, InitialState, pOptimizedClearValue, riid, ppvResource);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateReservedResource(const D3D12_RESOURCE_DESC *pDesc,
                                                    D3D12_RESOURCE_STATES InitialState,
                                                    const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                    const IID &riid, void **ppvResource)
{
    return m_pDevice->CreateReservedResource(pDesc, InitialState, pOptimizedClearValue, riid, ppvResource);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateSharedHandle(ID3D12DeviceChild *pObject,
                                            const SECURITY_ATTRIBUTES *pAttributes, DWORD Access,
                                            LPCWSTR Name, HANDLE *pHandle)
{
    return m_pDevice->CreateSharedHandle(pObject, pAttributes, Access, Name, pHandle);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::OpenSharedHandle(HANDLE NTHandle, const IID &riid, void **ppvObj)
{
    return m_pDevice->OpenSharedHandle(NTHandle, riid, ppvObj);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::OpenSharedHandleByName(LPCWSTR Name, DWORD Access, HANDLE *pNTHandle)
{
    return m_pDevice->OpenSharedHandleByName(Name, Access, pNTHandle);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::MakeResident(UINT NumObjects, ID3D12Pageable *const *ppObjects)
{
    return m_pDevice->MakeResident(NumObjects, ppObjects);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::Evict(UINT NumObjects, ID3D12Pageable *const *ppObjects)
{
    return m_pDevice->Evict(NumObjects, ppObjects);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateFence(UINT64 InitialValue, D3D12_FENCE_FLAGS Flags,
                                                    const IID &riid, void **ppFence)
{
    return m_pDevice->CreateFence(InitialValue, Flags, riid, ppFence);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::GetDeviceRemovedReason()
{
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
    return m_pDevice->CreateQueryHeap(pDesc, riid, ppvHeap);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::SetStablePowerState(BOOL Enable)
{
    return m_pDevice->SetStablePowerState(Enable);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateCommandSignature(const D3D12_COMMAND_SIGNATURE_DESC *pDesc,
                                                   ID3D12RootSignature *pRootSignature,
                                                   const IID &riid, void **ppvCommandSignature)
{
    return m_pDevice->CreateCommandSignature(pDesc, pRootSignature, riid, ppvCommandSignature);
}

void STDMETHODCALLTYPE WrappedID3D12Device::GetResourceTiling(ID3D12Resource *pTiledResource,
                                           	                UINT *pNumTilesForEntireResource,
                                           	                D3D12_PACKED_MIP_INFO *pPackedMipDesc,
                                           	                D3D12_TILE_SHAPE *pStandardTileShapeForNonPackedMips,
                                           	                UINT *pNumSubresourceTilings,
                                           	                UINT FirstSubresourceTilingToGet,
                                           	                D3D12_SUBRESOURCE_TILING *pSubresourceTilingsForNonPackedMips)
{
    m_pDevice->GetResourceTiling(pTiledResource, pNumTilesForEntireResource, pPackedMipDesc, 
    pStandardTileShapeForNonPackedMips, pNumSubresourceTilings, FirstSubresourceTilingToGet, pSubresourceTilingsForNonPackedMips);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreatePipelineLibrary(const void *pLibraryBlob, SIZE_T BlobLength,
                                                                const IID &riid, void **ppPipelineLibrary)
{
    return m_pDevice1->CreatePipelineLibrary(pLibraryBlob, BlobLength, riid, ppPipelineLibrary);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::SetEventOnMultipleFenceCompletion(ID3D12Fence *const *ppFences, const UINT64 *pFenceValues, UINT NumFences,
														D3D12_MULTIPLE_FENCE_WAIT_FLAGS Flags, HANDLE hEvent)
{
    return m_pDevice1->SetEventOnMultipleFenceCompletion(ppFences, pFenceValues, NumFences, Flags, hEvent);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::SetResidencyPriority(UINT NumObjects, ID3D12Pageable *const *ppObjects,
                                                 const D3D12_RESIDENCY_PRIORITY *pPriorities)
{
    return m_pDevice1->SetResidencyPriority(NumObjects, ppObjects, pPriorities);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreatePipelineState(const D3D12_PIPELINE_STATE_STREAM_DESC *pDesc,
                                                                const IID &riid, void **ppPipelineState)
{
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
    return m_pDevice3->EnqueueMakeResident(Flags, NumObjects, ppObjects, pFenceToSignal, FenceValueToSignal);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateCommandList1(UINT nodeMask, D3D12_COMMAND_LIST_TYPE type,
                                            	                D3D12_COMMAND_LIST_FLAGS flags, const IID &riid,
                                            	                void **ppCommandList)
{
    if (ppCommandList == nullptr)
    {
        return m_pDevice4->CreateCommandList1(nodeMask, type, flags, riid, nullptr);
    }

    void *real_ptr = nullptr;
    ID3D12GraphicsCommandList *real_command_list = nullptr;
    HRESULT result = m_pDevice4->CreateCommandList1(nodeMask, type, flags, riid, &real_ptr);

    if(riid == __uuidof(ID3D12CommandList))
    {
        real_command_list = (ID3D12GraphicsCommandList *)(ID3D12CommandList *)real_ptr;
    }
    else if(riid == __uuidof(ID3D12GraphicsCommandList))
    {
        real_command_list = (ID3D12GraphicsCommandList *)real_ptr;
    }
    else if(riid == __uuidof(ID3D12GraphicsCommandList1))
    {
        real_command_list = (ID3D12GraphicsCommandList1 *)real_ptr;
    }
    else if(riid == __uuidof(ID3D12GraphicsCommandList2))
    {
        real_command_list = (ID3D12GraphicsCommandList2 *)real_ptr;
    }
    else if(riid == __uuidof(ID3D12GraphicsCommandList3))
    {
        real_command_list = (ID3D12GraphicsCommandList3 *)real_ptr;
    }
    else if(riid == __uuidof(ID3D12GraphicsCommandList4))
    {
        real_command_list = (ID3D12GraphicsCommandList4 *)real_ptr;
    }
    else if(riid == __uuidof(ID3D12GraphicsCommandList5))
    {
        real_command_list = (ID3D12GraphicsCommandList5 *)real_ptr;
    }
    else if(riid == __uuidof(ID3D12GraphicsCommandList6))
    {
        real_command_list = (ID3D12GraphicsCommandList6 *)real_ptr;
    }
    else if(riid == __uuidof(ID3D12GraphicsCommandList7))
    {
        real_command_list = (ID3D12GraphicsCommandList7 *)real_ptr;
    }

    if (SUCCEEDED(result))
    {
        WrappedID3D12GraphicsCommandList *wrapped_command_list = new WrappedID3D12GraphicsCommandList(real_command_list, this);

        if(riid == __uuidof(ID3D12GraphicsCommandList))
        {
            *ppCommandList = (ID3D12GraphicsCommandList *)wrapped_command_list;
        }
        else if(riid == __uuidof(ID3D12GraphicsCommandList1))
        {
            *ppCommandList = (ID3D12GraphicsCommandList1 *)wrapped_command_list;
        }
        else if(riid == __uuidof(ID3D12GraphicsCommandList2))
        {
            *ppCommandList = (ID3D12GraphicsCommandList2 *)wrapped_command_list;
        }
        else if(riid == __uuidof(ID3D12GraphicsCommandList3))
        {
            *ppCommandList = (ID3D12GraphicsCommandList3 *)wrapped_command_list;
        }
        else if(riid == __uuidof(ID3D12GraphicsCommandList4))
        {
            *ppCommandList = (ID3D12GraphicsCommandList4 *)wrapped_command_list;
        }
        else if(riid == __uuidof(ID3D12GraphicsCommandList5))
        {
            *ppCommandList = (ID3D12GraphicsCommandList5 *)wrapped_command_list;
        }
        else if(riid == __uuidof(ID3D12GraphicsCommandList6))
        {
            *ppCommandList = (ID3D12GraphicsCommandList6 *)wrapped_command_list;
        }
        else if(riid == __uuidof(ID3D12GraphicsCommandList7))
        {
            *ppCommandList = (ID3D12GraphicsCommandList7 *)wrapped_command_list;
        }
    }

    return result;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateProtectedResourceSession(_In_ const D3D12_PROTECTED_RESOURCE_SESSION_DESC *pDesc,
                                 						_In_ REFIID riid, _COM_Outptr_ void **ppSession)
{
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
    return m_pDevice4->CreateCommittedResource1(pHeapProperties, HeapFlags, pDesc, 
                                                InitialResourceState, pOptimizedClearValue, pProtectedSession, 
                                                riidResource, ppvResource);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateHeap1(const D3D12_HEAP_DESC *pDesc,
                                            ID3D12ProtectedResourceSession *pProtectedSession,
                                            const IID &riid, void **ppvHeap)
{
    return m_pDevice4->CreateHeap1(pDesc, pProtectedSession, riid, ppvHeap);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateReservedResource1(const D3D12_RESOURCE_DESC *pDesc,
                                                D3D12_RESOURCE_STATES InitialState,
                                                const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                ID3D12ProtectedResourceSession *
                                                pProtectedSession, const IID &riid,
                                                void **ppvResource)
{
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
    return m_pDevice5->CreateLifetimeTracker(pOwner, riid, ppvTracker);
}

void STDMETHODCALLTYPE WrappedID3D12Device::RemoveDevice()
{
    m_pDevice5->RemoveDevice();
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::EnumerateMetaCommands(_Inout_ UINT *pNumMetaCommands,
                                            _Out_writes_opt_(*pNumMetaCommands) D3D12_META_COMMAND_DESC *pDescs)
{
    return m_pDevice5->EnumerateMetaCommands(pNumMetaCommands, pDescs);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::EnumerateMetaCommandParameters(
      										_In_ REFGUID CommandId, _In_ D3D12_META_COMMAND_PARAMETER_STAGE Stage,
      										_Out_opt_ UINT *pTotalStructureSizeInBytes, _Inout_ UINT *pParameterCount,
      										_Out_writes_opt_(*pParameterCount) D3D12_META_COMMAND_PARAMETER_DESC *pParameterDescs)
{
    return m_pDevice5->EnumerateMetaCommandParameters(CommandId, Stage, pTotalStructureSizeInBytes, pParameterCount, pParameterDescs);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateMetaCommand(const GUID &CommandId, UINT NodeMask,
                                              const void *pCreationParametersData,
                                              SIZE_T CreationParametersDataSizeInBytes,
                                              const IID &riid, void **ppMetaCommand)
{
    return m_pDevice5->CreateMetaCommand(CommandId, NodeMask, pCreationParametersData, CreationParametersDataSizeInBytes, riid, ppMetaCommand);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateStateObject(const D3D12_STATE_OBJECT_DESC *pDesc, const IID &riid,
                                              	void **ppStateObject)
{
    return m_pDevice5->CreateStateObject(pDesc, riid, ppStateObject);
}

void STDMETHODCALLTYPE WrappedID3D12Device::GetRaytracingAccelerationStructurePrebuildInfo(
      										_In_ const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS *pDesc,
      										_Out_ D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO *pInfo)
{
    return m_pDevice5->GetRaytracingAccelerationStructurePrebuildInfo(pDesc, pInfo);
}

D3D12_DRIVER_MATCHING_IDENTIFIER_STATUS STDMETHODCALLTYPE WrappedID3D12Device::CheckDriverMatchingIdentifier(
      										_In_ D3D12_SERIALIZED_DATA_TYPE SerializedDataType,
      										_In_ const D3D12_SERIALIZED_DATA_DRIVER_MATCHING_IDENTIFIER *pIdentifierToCheck)
{
    return m_pDevice5->CheckDriverMatchingIdentifier(SerializedDataType, pIdentifierToCheck);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::QueryVideoMemoryInfo(UINT NodeIndex, DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup,
                       							_Out_ DXGI_QUERY_VIDEO_MEMORY_INFO *pVideoMemoryInfo)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::SetBackgroundProcessingMode(
      						D3D12_BACKGROUND_PROCESSING_MODE Mode, D3D12_MEASUREMENTS_ACTION MeasurementsAction,
      						_In_opt_ HANDLE hEventToSignalUponCompletion, _Out_opt_ BOOL *pbFurtherMeasurementsDesired)
{
    return m_pDevice6->SetBackgroundProcessingMode(Mode, MeasurementsAction, hEventToSignalUponCompletion, pbFurtherMeasurementsDesired);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::AddToStateObject(const D3D12_STATE_OBJECT_DESC *pAddition,
                                             ID3D12StateObject *pStateObjectToGrowFrom,
                                             const IID &riid, void **ppNewStateObject)
{
    return m_pDevice7->AddToStateObject(pAddition, pStateObjectToGrowFrom, riid, ppNewStateObject);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateProtectedResourceSession1(_In_ const D3D12_PROTECTED_RESOURCE_SESSION_DESC1 *pDesc,
                                  							_In_ REFIID riid, _COM_Outptr_ void **ppSession)
{
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
    return m_pDevice8->CreateCommittedResource2(pHeapProperties, HeapFlags, pDesc, InitialResourceState, 
                    pOptimizedClearValue, pProtectedSession, riidResource, ppvResource);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreatePlacedResource1(ID3D12Heap *pHeap, UINT64 HeapOffset,
                                                  const D3D12_RESOURCE_DESC1 *pDesc,
                                                  D3D12_RESOURCE_STATES InitialState,
                                                  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
                                                  const IID &riid, void **ppvResource)
{
    return m_pDevice8->CreatePlacedResource1(pHeap, HeapOffset, pDesc, InitialState, pOptimizedClearValue, riid, ppvResource);
}

void STDMETHODCALLTYPE WrappedID3D12Device::CreateSamplerFeedbackUnorderedAccessView(
      						_In_opt_ ID3D12Resource *pTargetedResource, _In_opt_ ID3D12Resource *pFeedbackResource,
      						_In_ D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor)
{
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
    return m_pDevice9->CreateShaderCacheSession(pDesc, riid, ppvSession);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::ShaderCacheControl(D3D12_SHADER_CACHE_KIND_FLAGS Kinds, D3D12_SHADER_CACHE_CONTROL_FLAGS Control)
{
    return m_pDevice9->ShaderCacheControl(Kinds, Control);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateCommandQueue1(const D3D12_COMMAND_QUEUE_DESC *pDesc,
                                                const IID &CreatorID, const IID &riid,
                                                void **ppCommandQueue) 
{
    if (ppCommandQueue == nullptr)
    {
        return m_pDevice9->CreateCommandQueue1(pDesc, CreatorID, riid, ppCommandQueue);
    }

    if(riid != __uuidof(ID3D12CommandQueue))
    {
        return E_NOINTERFACE;
    }

    ID3D12CommandQueue *real_queue = nullptr;
    HRESULT result = m_pDevice9->CreateCommandQueue1(pDesc, CreatorID, riid, (void **)&real_queue);
    if (SUCCEEDED(result))
    {
        WrappedD3D12CommandQueue *wrapped_command_queue = new WrappedD3D12CommandQueue(real_queue, this);
        *ppCommandQueue = (ID3D12CommandQueue *)wrapped_command_queue;
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
            				_In_opt_count_(NumCastableFormats)  DXGI_FORMAT *pCastableFormats,
            				REFIID riidResource,
            				_COM_Outptr_opt_  void **ppvResource)
{
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
            					_In_opt_count_(NumCastableFormats)  DXGI_FORMAT *pCastableFormats,
            					REFIID riid,
            					_COM_Outptr_opt_  void **ppvResource)
{
    return m_pDevice10->CreatePlacedResource2(pHeap, HeapOffset, pDesc, InitialLayout, pOptimizedClearValue, 
                NumCastableFormats, pCastableFormats, riid, ppvResource);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12Device::CreateReservedResource2( 
            					_In_  const D3D12_RESOURCE_DESC *pDesc,
            					D3D12_BARRIER_LAYOUT InitialLayout,
            					_In_opt_  const D3D12_CLEAR_VALUE *pOptimizedClearValue,
            					_In_opt_  ID3D12ProtectedResourceSession *pProtectedSession,
            					UINT32 NumCastableFormats,
            					_In_opt_count_(NumCastableFormats)  DXGI_FORMAT *pCastableFormats,
            					REFIID riid,
            					_COM_Outptr_opt_  void **ppvResource)
{
    return m_pDevice10->CreateReservedResource2(pDesc, InitialLayout, pOptimizedClearValue, pProtectedSession, 
                NumCastableFormats, pCastableFormats, riid, ppvResource);
}
