//
// Created by ZZK on 2024/11/25.
//

#include <tracer/d3d12/d3d12_tools_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
	ID3D12ToolsWrapper::ID3D12ToolsWrapper(const IID &riid, IUnknown *object)
	: m_riid(riid), m_object(object, false), m_ref_count(1)
	{

	}

	// Helper functions
	REFIID ID3D12ToolsWrapper::GetRiid() const
	{
		return m_riid;
	}

	IUnknown* ID3D12ToolsWrapper::GetWrappedObject()
	{
		return m_object;
	}

	const IUnknown* ID3D12ToolsWrapper::GetWrappedObject() const
	{
		return m_object;
	}

	uint32_t ID3D12ToolsWrapper::GetRefCount() const
	{
		return m_ref_count.load(std::memory_order_seq_cst);
	}

	// IUnknown
	HRESULT STDMETHODCALLTYPE ID3D12ToolsWrapper::QueryInterface(REFIID riid, void** object)
	{
		// TODO: check wrap
		const auto result = m_object->QueryInterface(riid, object);
		if (FAILED(result) && IsEqualIID(riid, IID_IUnknown_Wrapper))
		{
			*object = GetWrappedObject();
			return S_OK;
		}
		encode::WrapObject(riid, object);
		D3D12_WRAPPER_DEBUG("Invoke ID3D12ToolsWrapper::QueryInterface, get wrapped object");
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12ToolsWrapper::AddRef()
	{
		const auto result = ++m_ref_count;
		return result;
	}

	ULONG STDMETHODCALLTYPE ID3D12ToolsWrapper::Release()
	{
		const auto result = --m_ref_count;
		return result;
	}

	// ID3D12Tools
	void STDMETHODCALLTYPE ID3D12ToolsWrapper::EnableShaderInstrumentation(BOOL bEnable)
	{
		GetWrappedObjectAs<ID3D12Tools>()->EnableShaderInstrumentation(bEnable);
	}

	BOOL STDMETHODCALLTYPE ID3D12ToolsWrapper::ShaderInstrumentationEnabled()
	{
		const auto result = GetWrappedObjectAs<ID3D12Tools>()->ShaderInstrumentationEnabled();
		return result;
	}

}