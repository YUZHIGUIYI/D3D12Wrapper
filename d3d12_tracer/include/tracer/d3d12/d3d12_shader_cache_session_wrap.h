//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12ShaderCacheSessionWrapper : ID3D12DeviceChildWrapper
	{
	public:
		ID3D12ShaderCacheSessionWrapper(REFIID riid, IUnknown *object);

		~ID3D12ShaderCacheSessionWrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE FindValue(
						const void* pKey,
						UINT KeySize,
						void* pValue,
						UINT* pValueSize);

		virtual HRESULT STDMETHODCALLTYPE StoreValue(
						const void* pKey,
						UINT KeySize,
						const void* pValue,
						UINT ValueSize);

		virtual void STDMETHODCALLTYPE SetDeleteOnDestroy();

		virtual D3D12_SHADER_CACHE_SESSION_DESC STDMETHODCALLTYPE GetDesc();
	};
}
