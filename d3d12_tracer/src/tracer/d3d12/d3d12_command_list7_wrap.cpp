#include <tracer/d3d12/d3d12_command_list_wrap.h>

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::Barrier(UINT32 NumBarrierGroups,
                        const D3D12_BARRIER_GROUP *pBarrierGroups)
{
    m_pList7->Barrier(NumBarrierGroups, pBarrierGroups);
}