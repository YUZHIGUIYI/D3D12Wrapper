//
// Created by ZZK on 2024/7/20.
//

#include <tracer/d3d12/d3d12_device5_wrap.h>
#include <tracer/core/wrapper_creators.h>
#include <tracer/common/logger.h>

namespace gfxshim
{
    ID3D12Device5Wrapper::ID3D12Device5Wrapper(const IID &riid, IUnknown *object)
    : ID3D12Device4Wrapper(riid, object)
    {

    }

    ID3D12Device5Wrapper::~ID3D12Device5Wrapper() = default;

    HRESULT STDMETHODCALLTYPE ID3D12Device5Wrapper::CreateLifetimeTracker(
            ID3D12LifetimeOwner* pOwner,
            REFIID riid,
            void** ppvTracker)
    {
        const auto result = GetWrappedObjectAs<ID3D12Device5>()->CreateLifetimeTracker(encode::GetWrappedObject<ID3D12LifetimeOwner>(pOwner), riid, ppvTracker);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppvTracker);
		}
		return result;
    }

    void STDMETHODCALLTYPE ID3D12Device5Wrapper::RemoveDevice()
    {
        GetWrappedObjectAs<ID3D12Device5>()->RemoveDevice();
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device5Wrapper::EnumerateMetaCommands(
            UINT* pNumMetaCommands,
            D3D12_META_COMMAND_DESC* pDescs)
    {
        return GetWrappedObjectAs<ID3D12Device5>()->EnumerateMetaCommands(pNumMetaCommands, pDescs);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device5Wrapper::EnumerateMetaCommandParameters(
            REFGUID CommandId,
            D3D12_META_COMMAND_PARAMETER_STAGE Stage,
            UINT* pTotalStructureSizeInBytes,
            UINT* pParameterCount,
            D3D12_META_COMMAND_PARAMETER_DESC* pParameterDescs)
    {
        return GetWrappedObjectAs<ID3D12Device5>()->EnumerateMetaCommandParameters(CommandId, Stage, pTotalStructureSizeInBytes, pParameterCount, pParameterDescs);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device5Wrapper::CreateMetaCommand(
            REFGUID CommandId,
            UINT NodeMask,
            const void* pCreationParametersData,
            SIZE_T CreationParametersDataSizeInBytes,
            REFIID riid,
            void** ppMetaCommand)
    {
        const auto result = GetWrappedObjectAs<ID3D12Device5>()->CreateMetaCommand(CommandId, NodeMask, pCreationParametersData,
                                                                        CreationParametersDataSizeInBytes, riid, ppMetaCommand);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppMetaCommand);
		}
		return result;
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device5Wrapper::CreateStateObject(
            const D3D12_STATE_OBJECT_DESC* pDesc,
            REFIID riid,
            void** ppStateObject)
    {
		// TODO: unwrap state object desc
		D3D12_WRAPPER_ERROR("Currently do not unwrap D3D12_STATE_OBJECT_DESC, DXR is not supported");
		if (pDesc != nullptr && pDesc->NumSubobjects > 0U && pDesc->pSubobjects != nullptr)
		{
			D3D12_STATE_OBJECT_DESC unwrapped_state_object_desc = *pDesc;
			std::vector<D3D12_STATE_SUBOBJECT> unwrapped_state_sub_objects(pDesc->NumSubobjects);
			std::memcpy(unwrapped_state_sub_objects.data(), pDesc->pSubobjects, sizeof(D3D12_STATE_SUBOBJECT) * pDesc->NumSubobjects);
			encode::UnwrapStructObjects(unwrapped_state_sub_objects, std::span{ pDesc->pSubobjects, pDesc->NumSubobjects });
			unwrapped_state_object_desc.pSubobjects = unwrapped_state_sub_objects.data();
			const auto result = GetWrappedObjectAs<ID3D12Device5>()->CreateStateObject(&unwrapped_state_object_desc, riid, ppStateObject);
			if (SUCCEEDED(result))
			{
				encode::WrapObject(riid, ppStateObject);
			}
			return result;
		}

        const auto result = GetWrappedObjectAs<ID3D12Device5>()->CreateStateObject(pDesc, riid, ppStateObject);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppStateObject);
		}
		return result;
    }

    void STDMETHODCALLTYPE ID3D12Device5Wrapper::GetRaytracingAccelerationStructurePrebuildInfo(
            const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS* pDesc,
            D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO* pInfo)
    {
        GetWrappedObjectAs<ID3D12Device5>()->GetRaytracingAccelerationStructurePrebuildInfo(pDesc, pInfo);
    }

    D3D12_DRIVER_MATCHING_IDENTIFIER_STATUS STDMETHODCALLTYPE ID3D12Device5Wrapper::CheckDriverMatchingIdentifier(
            D3D12_SERIALIZED_DATA_TYPE SerializedDataType,
            const D3D12_SERIALIZED_DATA_DRIVER_MATCHING_IDENTIFIER* pIdentifierToCheck)
    {
        return GetWrappedObjectAs<ID3D12Device5>()->CheckDriverMatchingIdentifier(SerializedDataType, pIdentifierToCheck);
    }
}