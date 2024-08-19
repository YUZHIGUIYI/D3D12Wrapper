#include <d3d12/core/d3d12_command_list_wrap.h>

WrappedID3D12DebugCommandList::WrappedID3D12DebugCommandList(ID3D12DebugCommandList *real_command_list)
: m_pDebugList(real_command_list)
{
    if (m_pDebugList)
    {
        m_pDebugList->QueryInterface(__uuidof(ID3D12DebugCommandList1), (void **)&m_pDebugList1);
        m_pDebugList->QueryInterface(__uuidof(ID3D12DebugCommandList2), (void **)&m_pDebugList2);
        m_pDebugList->AddRef();
    }
}
WrappedID3D12DebugCommandList::~WrappedID3D12DebugCommandList() = default;

HRESULT STDMETHODCALLTYPE WrappedID3D12DebugCommandList::QueryInterface(REFIID riid, void **ppvObject)
{
    if(riid == __uuidof(ID3D12DebugCommandList) || riid == __uuidof(ID3D12DebugCommandList1) || riid == __uuidof(ID3D12DebugCommandList2))
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE WrappedID3D12DebugCommandList::AddRef()
{
    return m_pDebugList->AddRef();
}

ULONG STDMETHODCALLTYPE WrappedID3D12DebugCommandList::Release()
{
    return m_pDebugList->Release();
}

BOOL STDMETHODCALLTYPE WrappedID3D12DebugCommandList::AssertResourceState(ID3D12Resource *pResource, UINT Subresource, UINT State)
{
    return m_pDebugList->AssertResourceState(pResource, Subresource, State);
}

HRESULT STDMETHODCALLTYPE WrappedID3D12DebugCommandList::SetFeatureMask(D3D12_DEBUG_FEATURE Mask)
{
    return m_pDebugList->SetFeatureMask(Mask);
}

D3D12_DEBUG_FEATURE STDMETHODCALLTYPE WrappedID3D12DebugCommandList::GetFeatureMask()
{
    return m_pDebugList->GetFeatureMask();
}

HRESULT STDMETHODCALLTYPE WrappedID3D12DebugCommandList::SetDebugParameter(D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type, const void *pData, UINT DataSize)
{
    if (m_pDebugList1)
    {
        return m_pDebugList1->SetDebugParameter(Type, pData, DataSize);
    }
    if (m_pDebugList2)
    {
        return m_pDebugList2->SetDebugParameter(Type, pData, DataSize);
    }
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12DebugCommandList::GetDebugParameter(D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
                                                void *pData, UINT DataSize)
{
    if (m_pDebugList1)
    {
        return m_pDebugList1->GetDebugParameter(Type, pData, DataSize);
    }
    if (m_pDebugList2)
    {
        return m_pDebugList2->GetDebugParameter(Type, pData, DataSize);
    }
    return S_OK;
}