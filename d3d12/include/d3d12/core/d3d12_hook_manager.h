//
// Created by ZZK on 2024/7/25.
//

#include <d3d12/common/d3d12_wrap_common.h>

namespace gfxshim
{
    struct D3D12DispatchTable
    {
        // NOTE: There is no typedef in d3d12.h for D3D12EnableExperimentalFeatures.
        using PFN_D3D12_ENABLE_EXPERIMENTAL_FEATURES = HRESULT(WINAPI *)(
                UINT                                   NumFeatures,
                _In_count_(NumFeatures) const IID*     pIIDs,
                _In_opt_count_(NumFeatures) void*      pConfigurationStructs,
                _In_opt_count_(NumFeatures) UINT*      pConfigurationStructSizes);

        // Functions processed for capture.  These are the D3D12 functions exported by d3d12.dll and documented on MSDN.
        PFN_D3D12_CREATE_DEVICE                                D3D12CreateDevice = nullptr ;
        PFN_D3D12_CREATE_ROOT_SIGNATURE_DESERIALIZER           D3D12CreateRootSignatureDeserializer = nullptr;
        PFN_D3D12_CREATE_VERSIONED_ROOT_SIGNATURE_DESERIALIZER D3D12CreateVersionedRootSignatureDeserializer = nullptr;
        PFN_D3D12_GET_DEBUG_INTERFACE                          D3D12GetDebugInterface = nullptr;
        PFN_D3D12_SERIALIZE_ROOT_SIGNATURE                     D3D12SerializeRootSignature = nullptr;
        PFN_D3D12_SERIALIZE_VERSIONED_ROOT_SIGNATURE           D3D12SerializeVersionedRootSignature = nullptr;
        PFN_D3D12_GET_INTERFACE                                D3D12GetInterface = nullptr;
        PFN_D3D12_ENABLE_EXPERIMENTAL_FEATURES                 D3D12EnableExperimentalFeatures = nullptr;
    };

    struct D3D12HookManager
    {
    private:
        HMODULE d3d12_module = nullptr;
        D3D12DispatchTable dispatch_table{};

    private:
        D3D12HookManager();

    public:
        static D3D12HookManager &GetInstance();

        ~D3D12HookManager();

        [[nodiscard]] const D3D12DispatchTable &DispatchTable() const;

        D3D12HookManager(const D3D12HookManager &) = delete;
        D3D12HookManager &operator=(const D3D12HookManager &) = delete;
        D3D12HookManager(D3D12HookManager &&) = delete;
        D3D12HookManager &operator=(D3D12HookManager &&) = delete;
    };
}