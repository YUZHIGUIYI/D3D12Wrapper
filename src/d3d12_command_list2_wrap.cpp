#include "d3d12_command_list.h"

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::WriteBufferImmediate(UINT Count,
                                        const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER *pParams,
                                        const D3D12_WRITEBUFFERIMMEDIATE_MODE *pModes)
{
    m_pList2->WriteBufferImmediate(Count, pParams, pModes);
}

