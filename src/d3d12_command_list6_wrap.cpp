#include "d3d12_command_list.h"

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::DispatchMesh(UINT ThreadGroupCountX, UINT ThreadGroupCountY,
                                UINT ThreadGroupCountZ)
{
    m_pList6->DispatchMesh(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
}

