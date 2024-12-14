//
// Created by ZZK on 2024/11/24.
//

#include <tracer/d3d12/d3d12_fence_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	// Wrap ID3D12Fence
	ID3D12FenceWrapper::ID3D12FenceWrapper(const IID &riid, IUnknown *object)
	: ID3D12PageableWrapper(riid, object)
	{

	}

	UINT64 STDMETHODCALLTYPE ID3D12FenceWrapper::GetCompletedValue()
	{
		const auto result = GetWrappedObjectAs<ID3D12Fence>()->GetCompletedValue();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12FenceWrapper::SetEventOnCompletion(UINT64 Value, HANDLE hEvent)
	{
		const auto result = GetWrappedObjectAs<ID3D12Fence>()->SetEventOnCompletion(Value, hEvent);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12FenceWrapper::Signal(UINT64 Value)
	{
		const auto result = GetWrappedObjectAs<ID3D12Fence>()->Signal(Value);
		return result;
	}

	// Wrap ID3D12Fence1
	ID3D12Fence1Wrapper::ID3D12Fence1Wrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12Fence1Wrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12Fence1Wrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12Fence1Wrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12Fence1Wrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12Fence1Wrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12Fence1Wrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12Fence1Wrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12Fence1Wrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12Object
	HRESULT STDMETHODCALLTYPE ID3D12Fence1Wrapper::GetPrivateData(const GUID &guid, UINT *pDataSize, void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->GetPrivateData(guid, pDataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12Fence1Wrapper::SetPrivateData(const GUID &guid, UINT DataSize, const void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateData(guid, DataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12Fence1Wrapper::SetPrivateDataInterface(const GUID &guid, const IUnknown *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateDataInterface(guid, encode::GetWrappedObject<IUnknown>(pData));
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12Fence1Wrapper::SetName(LPCWSTR Name)
	{
		return GetWrappedObjectAs<ID3D12Object>()->SetName(Name);
	}

	// ID3D12DeviceChild
	HRESULT STDMETHODCALLTYPE ID3D12Fence1Wrapper::GetDevice(const IID &riid, void **ppvDevice)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceChild>()->GetDevice(riid, ppvDevice);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvDevice);
		}
		return result;
	}

	// ID3D12Fence
	UINT64 STDMETHODCALLTYPE ID3D12Fence1Wrapper::GetCompletedValue()
	{
		const auto result = GetWrappedObjectAs<ID3D12Fence>()->GetCompletedValue();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12Fence1Wrapper::SetEventOnCompletion(UINT64 Value, HANDLE hEvent)
	{
		const auto result = GetWrappedObjectAs<ID3D12Fence>()->SetEventOnCompletion(Value, hEvent);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12Fence1Wrapper::Signal(UINT64 Value)
	{
		const auto result = GetWrappedObjectAs<ID3D12Fence>()->Signal(Value);
		return result;
	}

	// ID3D12Fence1
	D3D12_FENCE_FLAGS STDMETHODCALLTYPE ID3D12Fence1Wrapper::GetCreationFlags()
	{
		const auto result = GetWrappedObjectAs<ID3D12Fence1>()->GetCreationFlags();
		return result;
	}
}