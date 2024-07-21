#include <d3d12/core/d3d12_command_list6_wrap.h>

namespace gfxshim
{
    ID3D12GraphicsCommandList6Wrapper::ID3D12GraphicsCommandList6Wrapper(const IID &riid, IUnknown *object)
    : ID3D12GraphicsCommandList5Wrapper(riid, object)
    {

    }

    ID3D12GraphicsCommandList6Wrapper::~ID3D12GraphicsCommandList6Wrapper() = default;

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList6Wrapper::DispatchMesh(
            UINT ThreadGroupCountX,
            UINT ThreadGroupCountY,
            UINT ThreadGroupCountZ)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList6>()->DispatchMesh(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
    }
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::DispatchMesh(UINT ThreadGroupCountX, UINT ThreadGroupCountY,
                                UINT ThreadGroupCountZ)
{
    m_pList6->DispatchMesh(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
}

