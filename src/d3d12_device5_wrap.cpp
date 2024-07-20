//
// Created by ZZK on 2024/7/20.
//

#include "d3d12_device5_wrap.h"

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
        return GetWrappedObjectAs<ID3D12Device5>()->CreateLifetimeTracker(pOwner, riid, ppvTracker);
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
        return GetWrappedObjectAs<ID3D12Device5>()->CreateMetaCommand(CommandId, NodeMask, pCreationParametersData,
                                                                        CreationParametersDataSizeInBytes, riid, ppMetaCommand);
    }

    HRESULT STDMETHODCALLTYPE ID3D12Device5Wrapper::CreateStateObject(
            const D3D12_STATE_OBJECT_DESC* pDesc,
            REFIID riid,
            void** ppStateObject)
    {
        return GetWrappedObjectAs<ID3D12Device5>()->CreateStateObject(pDesc, riid, ppStateObject);
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