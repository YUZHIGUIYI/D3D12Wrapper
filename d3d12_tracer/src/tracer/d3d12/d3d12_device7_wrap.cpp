//
// Created by ZZK on 2024/7/20.
//

#include <tracer/d3d12/d3d12_device7_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
    ID3D12Device7Wrapper::ID3D12Device7Wrapper(const IID &riid, IUnknown *object)
    : ID3D12Device6Wrapper(riid, object)
    {

    }

    ID3D12Device7Wrapper::~ID3D12Device7Wrapper() = default;

    HRESULT STDMETHODCALLTYPE ID3D12Device7Wrapper::AddToStateObject(
            const D3D12_STATE_OBJECT_DESC* pAddition,
            ID3D12StateObject* pStateObjectToGrowFrom,
            REFIID riid,
            void** ppNewStateObject)
    {
		// TODO: unwrap state object desc
        const auto result = GetWrappedObjectAs<ID3D12Device7>()->AddToStateObject(pAddition, encode::GetWrappedObject<ID3D12StateObject>(pStateObjectToGrowFrom),
																							riid, ppNewStateObject);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppNewStateObject);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device7Wrapper::CreateProtectedResourceSession1(
            const D3D12_PROTECTED_RESOURCE_SESSION_DESC1* pDesc,
            REFIID riid,
            void** ppSession)
    {
        const auto result = GetWrappedObjectAs<ID3D12Device7>()->CreateProtectedResourceSession1(pDesc, riid, ppSession);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppSession);
		}
		return result;
    }
}