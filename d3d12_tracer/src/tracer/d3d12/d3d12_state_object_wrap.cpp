//
// Created by ZZK on 2024/11/25.
//

#include <tracer/d3d12/d3d12_state_object_wrap.h>

namespace gfxshim
{
	// Wrap ID3D12StateObject
	ID3D12StateObjectWrapper::ID3D12StateObjectWrapper(REFIID riid, IUnknown *object)
	: ID3D12PageableWrapper(riid, object)
	{

	}

	// Wrap ID3D12StateObjectProperties
	ID3D12StateObjectPropertiesWrapper::ID3D12StateObjectPropertiesWrapper(const IID &riid, IUnknown *object)
	: IUnknownWrapper(riid, object)
	{

	}

	void *STDMETHODCALLTYPE ID3D12StateObjectPropertiesWrapper::GetShaderIdentifier(LPCWSTR pExportName)
	{
		auto *result = GetWrappedObjectAs<ID3D12StateObjectProperties>()->GetShaderIdentifier(pExportName);
		return result;
	}

	UINT64 STDMETHODCALLTYPE ID3D12StateObjectPropertiesWrapper::GetShaderStackSize(LPCWSTR pExportName)
	{
		const auto result = GetWrappedObjectAs<ID3D12StateObjectProperties>()->GetShaderStackSize(pExportName);
		return result;
	}

	UINT64 STDMETHODCALLTYPE ID3D12StateObjectPropertiesWrapper::GetPipelineStackSize()
	{
		const auto result = GetWrappedObjectAs<ID3D12StateObjectProperties>()->GetPipelineStackSize();
		return result;
	}

	void STDMETHODCALLTYPE ID3D12StateObjectPropertiesWrapper::SetPipelineStackSize(UINT64 PipelineStackSizeInBytes)
	{
		GetWrappedObjectAs<ID3D12StateObjectProperties>()->SetPipelineStackSize(PipelineStackSizeInBytes);
	}

}