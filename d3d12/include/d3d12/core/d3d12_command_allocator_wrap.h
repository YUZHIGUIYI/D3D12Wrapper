//
// Created by ZZK on 2024/7/21.
//

#pragma once

#include <d3d12/common/d3d12_wrap_common.h>

class WrappedID3D12Device;

class WrappedID3D12CommandAllocator : public ID3D12CommandAllocator
{
private:
    ID3D12CommandAllocator *m_command_allocator = nullptr;
    WrappedID3D12Device *m_wrapped_device = nullptr;

public:
    WrappedID3D12CommandAllocator(ID3D12CommandAllocator *real_command_allocator, WrappedID3D12Device *wrapped_device);

    virtual ~WrappedID3D12CommandAllocator();

    [[nodiscard]] ID3D12CommandAllocator *GetReal() const;

    // Implement IUnknown
    ULONG STDMETHODCALLTYPE AddRef() final;

    ULONG STDMETHODCALLTYPE Release() final;

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) final;

    // Implement ID3D12Object
    HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID guid, UINT *pDataSize, void *pData) final;

    HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID guid, UINT DataSize, const void *pData) final;

    HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID guid, const IUnknown *pData) final;

    HRESULT STDMETHODCALLTYPE SetName(LPCWSTR Name) final;

    // Implement ID3D12DeviceChild
    HRESULT STDMETHODCALLTYPE GetDevice(REFIID riid, void** ppvDevice) final;

    // Implement ID3D12CommandAllocator
    HRESULT STDMETHODCALLTYPE Reset() final;
};
