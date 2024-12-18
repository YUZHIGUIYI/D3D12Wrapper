//
// Created by ZZK on 2024/11/24.
//

#include <tracer/d3d12/d3d12_resource_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	// Wrap ID3D12Resource
	ID3D12ResourceWrapper::ID3D12ResourceWrapper(const IID &riid, IUnknown *object)
	: ID3D12PageableWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE ID3D12ResourceWrapper::Map(UINT Subresource, const D3D12_RANGE *pReadRange, void **ppData)
	{
		// TODO: map trace
		const auto result = GetWrappedObjectAs<ID3D12Resource>()->Map(Subresource, pReadRange, ppData);
		return result;
	}

	void STDMETHODCALLTYPE ID3D12ResourceWrapper::Unmap(UINT Subresource, const D3D12_RANGE *pWrittenRange)
	{
		// TODO: unmap trace
		GetWrappedObjectAs<ID3D12Resource>()->Unmap(Subresource, pWrittenRange);
	}

	D3D12_RESOURCE_DESC STDMETHODCALLTYPE ID3D12ResourceWrapper::GetDesc()
	{
		const auto result = GetWrappedObjectAs<ID3D12Resource>()->GetDesc();
		return result;
	}

	D3D12_GPU_VIRTUAL_ADDRESS STDMETHODCALLTYPE ID3D12ResourceWrapper::GetGPUVirtualAddress()
	{
		const auto result = GetWrappedObjectAs<ID3D12Resource>()->GetGPUVirtualAddress();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12ResourceWrapper::WriteToSubresource(UINT DstSubresource, const D3D12_BOX *pDstBox,
																		const void *pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch)
	{
		const auto result = GetWrappedObjectAs<ID3D12Resource>()->WriteToSubresource(DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12ResourceWrapper::ReadFromSubresource(void *pDstData, UINT DstRowPitch, UINT DstDepthPitch,
																		UINT SrcSubresource, const D3D12_BOX *pSrcBox)
	{
		const auto result = GetWrappedObjectAs<ID3D12Resource>()->ReadFromSubresource(pDstData, DstRowPitch, DstDepthPitch, SrcSubresource, pSrcBox);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12ResourceWrapper::GetHeapProperties(D3D12_HEAP_PROPERTIES *pHeapProperties,
																		D3D12_HEAP_FLAGS *pHeapFlags)
	{
		const auto result = GetWrappedObjectAs<ID3D12Resource>()->GetHeapProperties(pHeapProperties, pHeapFlags);
		return result;
	}

	// Wrap ID3D12Resource1
	ID3D12Resource1Wrapper::ID3D12Resource1Wrapper(const IID &riid, IUnknown *object)
	: ID3D12ResourceWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE ID3D12Resource1Wrapper::GetProtectedResourceSession(const IID &riid, void **ppProtectedSession)
	{
		const auto result = GetWrappedObjectAs<ID3D12Resource1>()->GetProtectedResourceSession(riid, ppProtectedSession);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppProtectedSession);
		}
		return result;
	}

	// New Wrapped ID3D12Resource2
	ID3D12Resource2Wrapper::ID3D12Resource2Wrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12Resource2Wrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12Resource2Wrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12Resource2Wrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12Resource2Wrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12Resource2Wrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		if (SUCCEEDED(result) && (IsEqualGUID(riid, __uuidof(IUnknown)) || IsEqualGUID(riid, m_riid)))
		{
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12Resource2Wrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12Resource2Wrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12Resource2Wrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12Object
	HRESULT STDMETHODCALLTYPE ID3D12Resource2Wrapper::GetPrivateData(const GUID &guid, UINT *pDataSize, void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->GetPrivateData(guid, pDataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12Resource2Wrapper::SetPrivateData(const GUID &guid, UINT DataSize, const void *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateData(guid, DataSize, pData);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12Resource2Wrapper::SetPrivateDataInterface(const GUID &guid, const IUnknown *pData)
	{
		const auto result = GetWrappedObjectAs<ID3D12Object>()->SetPrivateDataInterface(guid, encode::GetWrappedObject<IUnknown>(pData));
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12Resource2Wrapper::SetName(LPCWSTR Name)
	{
		return GetWrappedObjectAs<ID3D12Object>()->SetName(Name);
	}

	// ID3D12DeviceChild
	HRESULT STDMETHODCALLTYPE ID3D12Resource2Wrapper::GetDevice(const IID &riid, void **ppvDevice)
	{
		const auto result = GetWrappedObjectAs<ID3D12DeviceChild>()->GetDevice(riid, ppvDevice);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvDevice);
		}
		return result;
	}

	// ID3D12Resource
	HRESULT STDMETHODCALLTYPE ID3D12Resource2Wrapper::Map(UINT Subresource, const D3D12_RANGE *pReadRange, void **ppData)
	{
		// TODO: map trace
		const auto result = GetWrappedObjectAs<ID3D12Resource>()->Map(Subresource, pReadRange, ppData);
		return result;
	}

	void STDMETHODCALLTYPE ID3D12Resource2Wrapper::Unmap(UINT Subresource, const D3D12_RANGE *pWrittenRange)
	{
		// TODO: unmap trace
		GetWrappedObjectAs<ID3D12Resource>()->Unmap(Subresource, pWrittenRange);
	}

	D3D12_RESOURCE_DESC STDMETHODCALLTYPE ID3D12Resource2Wrapper::GetDesc()
	{
		const auto result = GetWrappedObjectAs<ID3D12Resource>()->GetDesc();
		return result;
	}

	D3D12_GPU_VIRTUAL_ADDRESS STDMETHODCALLTYPE ID3D12Resource2Wrapper::GetGPUVirtualAddress()
	{
		const auto result = GetWrappedObjectAs<ID3D12Resource>()->GetGPUVirtualAddress();
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12Resource2Wrapper::WriteToSubresource(UINT DstSubresource, const D3D12_BOX *pDstBox,
																		const void *pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch)
	{
		const auto result = GetWrappedObjectAs<ID3D12Resource>()->WriteToSubresource(DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12Resource2Wrapper::ReadFromSubresource(void *pDstData, UINT DstRowPitch, UINT DstDepthPitch,
																		UINT SrcSubresource, const D3D12_BOX *pSrcBox)
	{
		const auto result = GetWrappedObjectAs<ID3D12Resource>()->ReadFromSubresource(pDstData, DstRowPitch, DstDepthPitch, SrcSubresource, pSrcBox);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12Resource2Wrapper::GetHeapProperties(D3D12_HEAP_PROPERTIES *pHeapProperties,
																		D3D12_HEAP_FLAGS *pHeapFlags)
	{
		const auto result = GetWrappedObjectAs<ID3D12Resource>()->GetHeapProperties(pHeapProperties, pHeapFlags);
		return result;
	}

	// ID3D12Resource1
	HRESULT STDMETHODCALLTYPE ID3D12Resource2Wrapper::GetProtectedResourceSession(const IID &riid, void **ppProtectedSession)
	{
		const auto result = GetWrappedObjectAs<ID3D12Resource1>()->GetProtectedResourceSession(riid, ppProtectedSession);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppProtectedSession);
		}
		return result;
	}

	// ID3D12Resource2
	D3D12_RESOURCE_DESC1 STDMETHODCALLTYPE ID3D12Resource2Wrapper::GetDesc1()
	{
		const auto result = GetWrappedObjectAs<ID3D12Resource2>()->GetDesc1();
		return result;
	}
}