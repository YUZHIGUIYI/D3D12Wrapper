#include <tracer/d3d12/d3d12_command_list3_wrap.h>

namespace gfxshim
{
    ID3D12GraphicsCommandList3Wrapper::ID3D12GraphicsCommandList3Wrapper(const IID &riid, IUnknown *object)
    : ID3D12GraphicsCommandList2Wrapper(riid, object)
    {

    }

    ID3D12GraphicsCommandList3Wrapper::~ID3D12GraphicsCommandList3Wrapper() = default;

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList3Wrapper::SetProtectedResourceSession(
            ID3D12ProtectedResourceSession* pProtectedResourceSession)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList3>()->SetProtectedResourceSession(pProtectedResourceSession);
    }
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::SetProtectedResourceSession(
                		ID3D12ProtectedResourceSession *pProtectedResourceSession)
{
    m_pList3->SetProtectedResourceSession(pProtectedResourceSession);
}

