#include <d3d12/core/d3d12_command_list2_wrap.h>

namespace gfxshim
{
    ID3D12GraphicsCommandList2Wrapper::ID3D12GraphicsCommandList2Wrapper(const IID &riid, IUnknown *object)
    : ID3D12GraphicsCommandList1Wrapper(riid, object)
    {

    }

    ID3D12GraphicsCommandList2Wrapper::~ID3D12GraphicsCommandList2Wrapper() = default;

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList2Wrapper::WriteBufferImmediate(
            UINT Count,
            const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER* pParams,
            const D3D12_WRITEBUFFERIMMEDIATE_MODE* pModes)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList2>()->WriteBufferImmediate(Count, pParams, pModes);
    }
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::WriteBufferImmediate(UINT Count,
                                        const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER *pParams,
                                        const D3D12_WRITEBUFFERIMMEDIATE_MODE *pModes)
{
    m_pList2->WriteBufferImmediate(Count, pParams, pModes);
}

