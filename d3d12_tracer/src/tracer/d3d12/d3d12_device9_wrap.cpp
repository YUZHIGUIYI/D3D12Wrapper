//
// Created by ZZK on 2024/7/20.
//

#include <tracer/d3d12/d3d12_device9_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
    ID3D12Device9Wrapper::ID3D12Device9Wrapper(const IID &riid, IUnknown *object)
    : ID3D12Device8Wrapper(riid, object)
    {

    }

    ID3D12Device9Wrapper::~ID3D12Device9Wrapper() = default;

    HRESULT STDMETHODCALLTYPE ID3D12Device9Wrapper::CreateShaderCacheSession(
            const D3D12_SHADER_CACHE_SESSION_DESC* pDesc,
            REFIID riid,
            void** ppvSession)
    {
        const auto result = GetWrappedObjectAs<ID3D12Device9>()->CreateShaderCacheSession(pDesc, riid, ppvSession);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvSession);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device9Wrapper::ShaderCacheControl(
            D3D12_SHADER_CACHE_KIND_FLAGS Kinds,
            D3D12_SHADER_CACHE_CONTROL_FLAGS Control)
    {
        const auto result = GetWrappedObjectAs<ID3D12Device9>()->ShaderCacheControl(Kinds, Control);
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device9Wrapper::CreateCommandQueue1(
            const D3D12_COMMAND_QUEUE_DESC* pDesc,
            REFIID CreatorID,
            REFIID riid,
            void** ppCommandQueue)
    {
        // TODO: implement
        const auto result = GetWrappedObjectAs<ID3D12Device9>()->CreateCommandQueue1(pDesc, CreatorID, riid, ppCommandQueue);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppCommandQueue);
		}
		return result;
    }
}