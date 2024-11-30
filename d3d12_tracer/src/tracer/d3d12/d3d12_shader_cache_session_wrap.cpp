//
// Created by ZZK on 2024/11/24.
//

#include <tracer/d3d12/d3d12_shader_cache_session_wrap.h>

namespace gfxshim
{
	ID3D12ShaderCacheSessionWrapper::ID3D12ShaderCacheSessionWrapper(const IID &riid, IUnknown *object)
	: ID3D12DeviceChildWrapper(riid, object)
	{

	}

	HRESULT STDMETHODCALLTYPE ID3D12ShaderCacheSessionWrapper::FindValue(const void *pKey, UINT KeySize, void *pValue, UINT *pValueSize)
	{
		const auto result = GetWrappedObjectAs<ID3D12ShaderCacheSession>()->FindValue(pKey, KeySize, pValue, pValueSize);
		return result;
	}

	HRESULT STDMETHODCALLTYPE ID3D12ShaderCacheSessionWrapper::StoreValue(const void *pKey, UINT KeySize, const void *pValue, UINT ValueSize)
	{
		const auto result = GetWrappedObjectAs<ID3D12ShaderCacheSession>()->StoreValue(pKey, KeySize, pValue, ValueSize);
		return result;
	}

	void STDMETHODCALLTYPE ID3D12ShaderCacheSessionWrapper::SetDeleteOnDestroy()
	{
		GetWrappedObjectAs<ID3D12ShaderCacheSession>()->SetDeleteOnDestroy();
	}

	D3D12_SHADER_CACHE_SESSION_DESC STDMETHODCALLTYPE ID3D12ShaderCacheSessionWrapper::GetDesc()
	{
		const auto result = GetWrappedObjectAs<ID3D12ShaderCacheSession>()->GetDesc();
		return result;
	}

}