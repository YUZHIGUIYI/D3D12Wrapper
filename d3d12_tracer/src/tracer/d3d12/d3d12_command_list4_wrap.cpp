#include <tracer/d3d12/d3d12_command_list_wrap.h>

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::BeginRenderPass(UINT NumRenderTargets,
                                const D3D12_RENDER_PASS_RENDER_TARGET_DESC *pRenderTargets,
                                const D3D12_RENDER_PASS_DEPTH_STENCIL_DESC *pDepthStencil,
                                D3D12_RENDER_PASS_FLAGS Flags)
{
    m_pList4->BeginRenderPass(NumRenderTargets, pRenderTargets, pDepthStencil, Flags);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::EndRenderPass()
{
    m_pList4->EndRenderPass();
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::InitializeMetaCommand(ID3D12MetaCommand *pMetaCommand,
                                        const void *pInitializationParametersData,
                                        SIZE_T InitializationParametersDataSizeInBytes)
{
    m_pList4->InitializeMetaCommand(pMetaCommand, pInitializationParametersData, InitializationParametersDataSizeInBytes);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::ExecuteMetaCommand(ID3D12MetaCommand *pMetaCommand,
                                    const void *pExecutionParametersData,
                                    SIZE_T ExecutionParametersDataSizeInBytes)
{
    m_pList4->ExecuteMetaCommand(pMetaCommand, pExecutionParametersData, ExecutionParametersDataSizeInBytes);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::BuildRaytracingAccelerationStructure(
            const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC *pDesc, UINT NumPostbuildInfoDescs,
            const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC *pPostbuildInfoDescs)
{
    m_pList4->BuildRaytracingAccelerationStructure(pDesc, NumPostbuildInfoDescs, pPostbuildInfoDescs);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::EmitRaytracingAccelerationStructurePostbuildInfo(
            const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC *pDesc,
            UINT NumSourceAccelerationStructures,
            const D3D12_GPU_VIRTUAL_ADDRESS *pSourceAccelerationStructureData)
{
    m_pList4->EmitRaytracingAccelerationStructurePostbuildInfo(pDesc, NumSourceAccelerationStructures, pSourceAccelerationStructureData);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::CopyRaytracingAccelerationStructure(
            D3D12_GPU_VIRTUAL_ADDRESS DestAccelerationStructureData,
            D3D12_GPU_VIRTUAL_ADDRESS SourceAccelerationStructureData,
            D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE Mode)
{
    m_pList4->CopyRaytracingAccelerationStructure(DestAccelerationStructureData, SourceAccelerationStructureData, Mode);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetPipelineState1(ID3D12StateObject *pStateObject)
{
    m_pList4->SetPipelineState1(pStateObject);
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::DispatchRays(const D3D12_DISPATCH_RAYS_DESC *pDesc)
{
    m_pList4->DispatchRays(pDesc);
}


