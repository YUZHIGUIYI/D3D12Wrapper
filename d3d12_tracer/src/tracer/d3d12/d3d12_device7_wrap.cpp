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
		D3D12_WRAPPER_ERROR("Currently do not unwrap D3D12_STATE_OBJECT_DESC, DXR is not supported");
		if (pAddition != nullptr && pAddition->NumSubobjects > 0U && pAddition->pSubobjects != nullptr)
		{
		    D3D12_STATE_OBJECT_DESC unwrapped_state_object_desc = *pAddition;
		    std::vector<D3D12_STATE_SUBOBJECT> unwrapped_state_sub_objects(pAddition->NumSubobjects);
		    std::memcpy(unwrapped_state_sub_objects.data(), pAddition->pSubobjects, sizeof(D3D12_STATE_SUBOBJECT) * pAddition->NumSubobjects);
		    encode::UnwrapStructObjects(unwrapped_state_sub_objects, std::span{ pAddition->pSubobjects, pAddition->NumSubobjects });
		    unwrapped_state_object_desc.pSubobjects = unwrapped_state_sub_objects.data();
			const auto result = GetWrappedObjectAs<ID3D12Device7>()->AddToStateObject(&unwrapped_state_object_desc, encode::GetWrappedObject<ID3D12StateObject>(pStateObjectToGrowFrom),
																							riid, ppNewStateObject);
		    if (SUCCEEDED(result))
		    {
				encode::WrapObject(riid, ppNewStateObject);
		    }
		    return result;
		}

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