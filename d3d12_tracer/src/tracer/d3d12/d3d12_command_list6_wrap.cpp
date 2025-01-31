#include <tracer/d3d12/d3d12_command_list_wrap.h>

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::DispatchMesh(UINT ThreadGroupCountX, UINT ThreadGroupCountY,
                                UINT ThreadGroupCountZ)
{
    m_pList6->DispatchMesh(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
}

