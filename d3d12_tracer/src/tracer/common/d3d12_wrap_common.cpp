//
// Created by ZZK on 2024/7/17.
//

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
    // IUnknownWrapper
    IUnknownWrapper::IUnknownWrapper(const IID &riid, IUnknown *wrapper_object)
    : m_riid(riid), m_object(wrapper_object), m_ref_count(1)
    {

    }

    HRESULT STDMETHODCALLTYPE IUnknownWrapper::QueryInterface(REFIID riid, void** object)
    {
        return m_object->QueryInterface(riid, object);
    }

    ULONG STDMETHODCALLTYPE IUnknownWrapper::AddRef()
    {
        auto result = ++m_ref_count;
        if (m_object != nullptr)
        {
            result = m_object->AddRef();
        }
        return result;
    }

    ULONG STDMETHODCALLTYPE IUnknownWrapper::Release()
    {
        auto result = --m_ref_count;
        if (m_object != nullptr)
        {
            result = m_object->Release();
        }
        return result;
    }

    REFIID IUnknownWrapper::GetRiid() const
    {
        return m_riid;
    }

    IUnknown* IUnknownWrapper::GetWrappedObject()
    {
        return m_object;
    }

    const IUnknown* IUnknownWrapper::GetWrappedObject() const
    {
        return m_object;
    }

    uint32_t IUnknownWrapper::GetRefCount() const
    {
        return m_ref_count.load(std::memory_order_seq_cst);
    }

    IUnknownWrapper::~IUnknownWrapper()
    {
        m_object = nullptr;
        m_ref_count.store(0, std::memory_order_release);
    }

    // ID3D12ObjectWrapper
    ID3D12ObjectWrapper::ID3D12ObjectWrapper(const IID &riid, IUnknown *object)
    : IUnknownWrapper(riid, object)
    {

    }

    HRESULT STDMETHODCALLTYPE ID3D12ObjectWrapper::GetPrivateData(const GUID &guid, UINT *pDataSize, void *pData)
    {
        return GetWrappedObjectAs<ID3D12Object>()->GetPrivateData(guid, pDataSize, pData);
    }

    HRESULT STDMETHODCALLTYPE ID3D12ObjectWrapper::SetPrivateData(const GUID &guid, UINT DataSize, const void *pData)
    {
        return GetWrappedObjectAs<ID3D12Object>()->SetPrivateData(guid, DataSize, pData);
    }

    HRESULT STDMETHODCALLTYPE ID3D12ObjectWrapper::SetPrivateDataInterface(const GUID &guid, const IUnknown *pData)
    {
        return GetWrappedObjectAs<ID3D12Object>()->SetPrivateDataInterface(guid, pData);
    }

    HRESULT STDMETHODCALLTYPE ID3D12ObjectWrapper::SetName(LPCWSTR Name)
    {
        return GetWrappedObjectAs<ID3D12Object>()->SetName(Name);
    }

    // ID3D12DeviceChildWrapper
    ID3D12DeviceChildWrapper::ID3D12DeviceChildWrapper(const IID &riid, IUnknown *object)
    : ID3D12ObjectWrapper(riid, object)
    {

    }

    HRESULT STDMETHODCALLTYPE ID3D12DeviceChildWrapper::GetDevice(const IID &riid, void **ppvDevice)
    {
        return GetWrappedObjectAs<ID3D12DeviceChild>()->GetDevice(riid, ppvDevice);
    }

    // ID3D12PageableWrapper
    ID3D12PageableWrapper::ID3D12PageableWrapper(const IID &riid, IUnknown *object)
    : ID3D12DeviceChildWrapper(riid, object)
    {

    }

}











