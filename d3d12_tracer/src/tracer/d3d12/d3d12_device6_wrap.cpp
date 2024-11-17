//
// Created by ZZK on 2024/7/20.
//

#include <tracer/d3d12/d3d12_device6_wrap.h>

namespace gfxshim
{
    ID3D12Device6Wrapper::ID3D12Device6Wrapper(const IID &riid, IUnknown *object)
    : ID3D12Device5Wrapper(riid, object)
    {

    }

    ID3D12Device6Wrapper::~ID3D12Device6Wrapper() = default;

    HRESULT STDMETHODCALLTYPE ID3D12Device6Wrapper::SetBackgroundProcessingMode(
            D3D12_BACKGROUND_PROCESSING_MODE Mode,
            D3D12_MEASUREMENTS_ACTION MeasurementsAction,
            HANDLE hEventToSignalUponCompletion,
            BOOL* pbFurtherMeasurementsDesired)
    {
        return GetWrappedObjectAs<ID3D12Device6>()->SetBackgroundProcessingMode(Mode, MeasurementsAction, hEventToSignalUponCompletion, pbFurtherMeasurementsDesired);
    }
}