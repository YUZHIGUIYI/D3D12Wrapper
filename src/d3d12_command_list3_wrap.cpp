#include "d3d12_command_list.h"

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetProtectedResourceSession(
                		ID3D12ProtectedResourceSession *pProtectedResourceSession)
{
    m_pList3->SetProtectedResourceSession(pProtectedResourceSession);
}

