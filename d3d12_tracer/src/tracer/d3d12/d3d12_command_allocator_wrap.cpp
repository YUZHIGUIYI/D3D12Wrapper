//
// Created by ZZK on 2024/7/21.
//

#include <tracer/d3d12/d3d12_command_allocator_wrap.h>
#include <tracer/d3d12/d3d12_device_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	ID3D12CommandAllocatorWrapper::ID3D12CommandAllocatorWrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12CommandAllocatorWrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12CommandAllocatorWrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12CommandAllocatorWrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12CommandAllocatorWrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12CommandAllocatorWrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12CommandAllocatorWrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12CommandAllocatorWrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12CommandAllocatorWrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12Object
	HRESULT STDMETHODCALLTYPE ID3D12CommandAllocatorWrapper::GetPrivateData(const GUID &guid, UINT *pDataSize, void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->GetPrivateData(guid, pDataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12CommandAllocatorWrapper::SetPrivateData(const GUID &guid, UINT DataSize, const void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateData(guid, DataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12CommandAllocatorWrapper::SetPrivateDataInterface(const GUID &guid, const IUnknown *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateDataInterface(guid, encode::GetWrappedObject<IUnknown>(pData));
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12CommandAllocatorWrapper::SetName(LPCWSTR Name)
	{
		return GetWrappedObjectAs<ID3D12Object>()->SetName(Name);
	}

	// ID3D12DeviceChild
	HRESULT STDMETHODCALLTYPE ID3D12CommandAllocatorWrapper::GetDevice(const IID &riid, void **ppvDevice)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceChild>()->GetDevice(riid, ppvDevice);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvDevice);
		}
		return result;
	}

	// ID3D12CommandAllocator
	HRESULT STDMETHODCALLTYPE ID3D12CommandAllocatorWrapper::Reset()
	{
		const auto result = GetWrappedObjectAs<ID3D12CommandAllocator>()->Reset();
		return result;
	}
}

WrappedID3D12CommandAllocator::WrappedID3D12CommandAllocator(ID3D12CommandAllocator *real_command_allocator, WrappedID3D12Device *wrapped_device)
: m_command_allocator(real_command_allocator), m_wrapped_device(wrapped_device)
{
    m_command_allocator->AddRef();
}

WrappedID3D12CommandAllocator::~WrappedID3D12CommandAllocator() = default;

ID3D12CommandAllocator *WrappedID3D12CommandAllocator::GetReal() const
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
    const auto result = m_command_allocator->QueryInterface(riid, ppvObject);
    return result;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandAllocator::GetPrivateData(REFGUID guid, UINT *pDataSize, void *pData)
{
    // TODO: check
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    const HRESULT result =  m_command_allocator->GetPrivateData(guid, pDataSize, pData);
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
    const HRESULT result = m_command_allocator->SetName(Name);
    return result;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandAllocator::GetDevice(REFIID riid, void** ppvDevice)
{
    D3D12_WRAPPER_DEBUG("Invoke {}", SHIM_FUNC_SIGNATURE);
    const HRESULT result = m_wrapped_device->GetDevice(riid, ppvDevice);
    return result;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12CommandAllocator::Reset()
{
    return m_command_allocator->Reset();
}