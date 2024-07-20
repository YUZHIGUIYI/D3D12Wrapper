//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include "d3d12_device4_wrap.h"

namespace gfxshim
{
    class ID3D12Device5Wrapper : public ID3D12Device4Wrapper
    {
    public:
        ID3D12Device5Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12Device5Wrapper() override;

        virtual HRESULT STDMETHODCALLTYPE CreateLifetimeTracker(
                ID3D12LifetimeOwner* pOwner,
                REFIID riid,
                void** ppvTracker);

        virtual void STDMETHODCALLTYPE RemoveDevice();

        virtual HRESULT STDMETHODCALLTYPE EnumerateMetaCommands(
                UINT* pNumMetaCommands,
                D3D12_META_COMMAND_DESC* pDescs);

        virtual HRESULT STDMETHODCALLTYPE EnumerateMetaCommandParameters(
                REFGUID CommandId,
                D3D12_META_COMMAND_PARAMETER_STAGE Stage,
                UINT* pTotalStructureSizeInBytes,
                UINT* pParameterCount,
                D3D12_META_COMMAND_PARAMETER_DESC* pParameterDescs);

        virtual HRESULT STDMETHODCALLTYPE CreateMetaCommand(
                REFGUID CommandId,
                UINT NodeMask,
                const void* pCreationParametersData,
                SIZE_T CreationParametersDataSizeInBytes,
                REFIID riid,
                void** ppMetaCommand);

        virtual HRESULT STDMETHODCALLTYPE CreateStateObject(
                const D3D12_STATE_OBJECT_DESC* pDesc,
                REFIID riid,
                void** ppStateObject);

        virtual void STDMETHODCALLTYPE GetRaytracingAccelerationStructurePrebuildInfo(
                const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS* pDesc,
                D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO* pInfo);

        virtual D3D12_DRIVER_MATCHING_IDENTIFIER_STATUS STDMETHODCALLTYPE CheckDriverMatchingIdentifier(
                D3D12_SERIALIZED_DATA_TYPE SerializedDataType,
                const D3D12_SERIALIZED_DATA_DRIVER_MATCHING_IDENTIFIER* pIdentifierToCheck);
    };
}
