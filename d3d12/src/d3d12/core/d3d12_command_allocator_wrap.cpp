//
// Created by ZZK on 2024/7/21.
//

#include <d3d12/core/d3d12_command_allocator_wrap.h>
#include <d3d12/core/d3d12_device_wrap.h>

WrappedID3D12CommandAllocator::WrappedID3D12CommandAllocator(ID3D12CommandAllocator *real_command_allocator, WrappedID3D12Device *wrapped_device)
: m_command_allocator(real_command_allocator), m_wrapped_device(wrapped_device)
{
    m_command_allocator->AddRef();
}

WrappedID3D12CommandAllocator::~WrappedID3D12CommandAllocator() = default;

ID3D12CommandAllocator *WrappedID3D12CommandAllocator::GetReal()
{
    return m_command_allocator;
}

ULONG STDMETHODCALLTYPE WrappedID3D12CommandAllocator::AddRef()
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_command_allocator->AddRef();
}

ULONG STDMETHODCALLTYPE WrappedID3D12CommandAllocator::Release()
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_command_allocator->Release();
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandAllocator::QueryInterface(REFIID riid, void **ppvObject)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    return m_command_allocator->QueryInterface(riid, ppvObject);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandAllocator::GetPrivateData(REFGUID guid, UINT *pDataSize, void *pData)
{
    // TODO: check
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
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    HRESULT result = m_command_allocator->SetName(Name);
    return result;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandAllocator::GetDevice(REFIID riid, void** ppvDevice)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    HRESULT result = m_wrapped_device->GetDevice(riid, ppvDevice);
    return result;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandAllocator::Reset()
{
    return m_command_allocator->Reset();
}