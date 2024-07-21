//
// Created by ZZK on 2024/7/20.
//

#pragma once

#include <d3d12/core/d3d12_command_list3_wrap.h>

namespace gfxshim
{
    class ID3D12GraphicsCommandList4Wrapper : public ID3D12GraphicsCommandList3Wrapper
    {
    public:
        ID3D12GraphicsCommandList4Wrapper(REFIID riid, IUnknown *object);

        ~ID3D12GraphicsCommandList4Wrapper() override;

        virtual void STDMETHODCALLTYPE BeginRenderPass(
                UINT NumRenderTargets,
                const D3D12_RENDER_PASS_RENDER_TARGET_DESC* pRenderTargets,
                const D3D12_RENDER_PASS_DEPTH_STENCIL_DESC* pDepthStencil,
                D3D12_RENDER_PASS_FLAGS Flags);

        virtual void STDMETHODCALLTYPE EndRenderPass();

        virtual void STDMETHODCALLTYPE InitializeMetaCommand(
                ID3D12MetaCommand* pMetaCommand,
                const void* pInitializationParametersData,
                SIZE_T InitializationParametersDataSizeInBytes);

        virtual void STDMETHODCALLTYPE ExecuteMetaCommand(
                ID3D12MetaCommand* pMetaCommand,
                const void* pExecutionParametersData,
                SIZE_T ExecutionParametersDataSizeInBytes);

        virtual void STDMETHODCALLTYPE BuildRaytracingAccelerationStructure(
                const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC* pDesc,
                UINT NumPostbuildInfoDescs,
                const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC* pPostbuildInfoDescs);

        virtual void STDMETHODCALLTYPE EmitRaytracingAccelerationStructurePostbuildInfo(
                const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC* pDesc,
                UINT NumSourceAccelerationStructures,
                const D3D12_GPU_VIRTUAL_ADDRESS* pSourceAccelerationStructureData);

        virtual void STDMETHODCALLTYPE CopyRaytracingAccelerationStructure(
                D3D12_GPU_VIRTUAL_ADDRESS DestAccelerationStructureData,
                D3D12_GPU_VIRTUAL_ADDRESS SourceAccelerationStructureData,
                D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE Mode);

        virtual void STDMETHODCALLTYPE SetPipelineState1(
                ID3D12StateObject* pStateObject);

        virtual void STDMETHODCALLTYPE DispatchRays(
                const D3D12_DISPATCH_RAYS_DESC* pDesc);
    };
}
