//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12StateObjectWrapper : ID3D12PageableWrapper
	{
	public:
		ID3D12StateObjectWrapper(REFIID riid, IUnknown *object);

		~ID3D12StateObjectWrapper() override = default;
	};

	struct ID3D12StateObjectPropertiesWrapper : IUnknownWrapper
	{
	public:
		ID3D12StateObjectPropertiesWrapper(REFIID riid, IUnknown *object);

		~ID3D12StateObjectPropertiesWrapper() override = default;

		virtual void* STDMETHODCALLTYPE GetShaderIdentifier(LPCWSTR pExportName);

		virtual UINT64 STDMETHODCALLTYPE GetShaderStackSize(LPCWSTR pExportName);

		virtual UINT64 STDMETHODCALLTYPE GetPipelineStackSize();

		virtual void STDMETHODCALLTYPE SetPipelineStackSize(UINT64 PipelineStackSizeInBytes);
	};
}
