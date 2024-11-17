#include <tracer/d3d12/d3d12_command_list7_wrap.h>

namespace gfxshim
{
    ID3D12GraphicsCommandList7Wrapper::ID3D12GraphicsCommandList7Wrapper(const IID &riid, IUnknown *object)
    : ID3D12GraphicsCommandList6Wrapper(riid, object)
    {

    }

    ID3D12GraphicsCommandList7Wrapper::~ID3D12GraphicsCommandList7Wrapper() = default;

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList7Wrapper::Barrier(
            UINT32 NumBarrierGroups,
            const D3D12_BARRIER_GROUP* pBarrierGroups)
    {
        GetWrappedObjectAs<ID3D12GraphicsCommandList7>()->Barrier(NumBarrierGroups, pBarrierGroups);
    }
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::Barrier(UINT32 NumBarrierGroups,
                        const D3D12_BARRIER_GROUP *pBarrierGroups)
{
    m_pList7->Barrier(NumBarrierGroups, pBarrierGroups);
}