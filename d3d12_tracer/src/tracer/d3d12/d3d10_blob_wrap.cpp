//
// Created by ZZK on 2024/11/24.
//

#include <tracer/d3d12/d3d10_blob_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	ID3D10BlobWrapper::ID3D10BlobWrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D10BlobWrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D10BlobWrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D10BlobWrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D10BlobWrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D10BlobWrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D10BlobWrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D10BlobWrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D10BlobWrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D10Blob
	LPVOID STDMETHODCALLTYPE ID3D10BlobWrapper::GetBufferPointer()
	{
		const auto result = GetWrappedObjectAs<ID3D10Blob>()->GetBufferPointer();
		return result;
	}

	SIZE_T STDMETHODCALLTYPE ID3D10BlobWrapper::GetBufferSize()
	{
		const auto result = GetWrappedObjectAs<ID3D10Blob>()->GetBufferSize();
		return result;
	}

}