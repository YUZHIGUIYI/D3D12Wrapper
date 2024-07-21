//
// Created by ZZK on 2024/7/21.
//

#include <d3d12/core/d3d12_command_allocator_wrap.h>
#include <d3d12/core/d3d12_command_list_wrap.h>

WrappedID3D12CommandAllocator::WrappedID3D12CommandAllocator(ID3D12CommandAllocator *real_command_allocator, WrappedID3D12Device *wrapped_device)
: m_command_allocator(real_command_allocator), m_wrapped_device(wrapped_device)
{
    m_command_allocator->AddRef();
}

WrappedID3D12CommandAllocator::~WrappedID3D12CommandAllocator() = default;

ULONG STDMETHODCALLTYPE WrappedID3D12CommandAllocator::AddRef()
{
    return m_command_allocator->AddRef();
}

ULONG STDMETHODCALLTYPE WrappedID3D12CommandAllocator::Release()
{
    return m_command_allocator->Release();
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandAllocator::QueryInterface(REFIID riid, void **ppvObject)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_command_allocator->QueryInterface(riid, ppvObject);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandAllocator::GetPrivateData(REFGUID guid, UINT *pDataSize, void *pData)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    HRESULT result =  m_command_allocator->GetPrivateData(guid, pDataSize, pData);
    if (guid == __uuidof(ID3D12GraphicsCommandList))
    {
        D3D12_WRAPPER_DEBUG("Get command list");
    }
    return result;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandAllocator::SetPrivateData(REFGUID guid, UINT DataSize, const void *pData)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_command_allocator->SetPrivateData(guid, DataSize, pData);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandAllocator::SetPrivateDataInterface(REFGUID guid, const IUnknown *pData)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_command_allocator->SetPrivateDataInterface(guid, pData);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandAllocator::SetName(LPCWSTR Name)
{
    return m_command_allocator->SetName(Name);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandAllocator::GetDevice(REFIID riid, void** ppvDevice)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    HRESULT result = m_command_allocator->GetDevice(riid, ppvDevice);
    if(riid == __uuidof(ID3D12Device1) || riid == __uuidof(ID3D12Device2) || riid == __uuidof(ID3D12Device3) || riid == __uuidof(ID3D12Device4) ||
        riid == __uuidof(ID3D12Device5) || riid == __uuidof(ID3D12Device6) || riid == __uuidof(ID3D12Device7) || riid == __uuidof(ID3D12Device8) ||
        riid == __uuidof(ID3D12Device9) || riid == __uuidof(ID3D12Device10))
    {
        *ppvDevice = m_wrapped_device;
    }
    return result;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandAllocator::Reset()
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_command_allocator->Reset();
}