#include <d3d12/core/d3d12_command_list_wrap.h>

HRESULT STDMETHODCALLTYPE WrappedID3D12DebugCommandList::QueryInterface(REFIID riid, void **ppvObject)
{
    if(riid == __uuidof(ID3D12DebugCommandList))
    {
        *ppvObject = (ID3D12DebugCommandList *)this;
        AddRef();
        return S_OK;
    }
    else if(riid == __uuidof(ID3D12DebugCommandList1))
    {
        *ppvObject = (ID3D12DebugCommandList1 *)this;
        AddRef();
        return S_OK;
    }
    else if(riid == __uuidof(ID3D12DebugCommandList2))
    {
        *ppvObject = (ID3D12DebugCommandList2 *)this;
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE WrappedID3D12DebugCommandList::AddRef()
{
    if (m_pList)
    {
        m_pList->AddRef();
    }
    return 1;
}

ULONG STDMETHODCALLTYPE WrappedID3D12DebugCommandList::Release()
{
    if (m_pList)
    {
        m_pList->Release();
    }
    return 1;
}

BOOL STDMETHODCALLTYPE WrappedID3D12DebugCommandList::AssertResourceState(ID3D12Resource *pResource, UINT Subresource, UINT State)
{
    if (m_pDebugList)
    {
        return m_pDebugList->AssertResourceState(pResource, Subresource, State);
    }
    return TRUE;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12DebugCommandList::SetFeatureMask(D3D12_DEBUG_FEATURE Mask)
{
    if (m_pDebugList)
    {
        return m_pDebugList->SetFeatureMask(Mask);
    }
    return S_OK;
}

D3D12_DEBUG_FEATURE STDMETHODCALLTYPE WrappedID3D12DebugCommandList::GetFeatureMask()
{
    if (m_pDebugList)
    {
        return m_pDebugList->GetFeatureMask();
    }
    return D3D12_DEBUG_FEATURE_NONE;
}

HRESULT STDMETHODCALLTYPE WrappedID3D12DebugCommandList::SetDebugParameter(D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
                                            	const void *pData, UINT DataSize)
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