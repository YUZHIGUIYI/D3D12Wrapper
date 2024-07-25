//
// Created by ZZK on 2024/7/25.
//

#include <d3d12/core/d3d12_hook_manager.h>

namespace gfxshim
{
    D3D12HookManager::D3D12HookManager()
    {
        char system_directory[MAX_PATH];
        uint32_t result = GetSystemDirectory(system_directory, MAX_PATH);
        if (result == 0)
        {
            D3D12_WRAPPER_ERROR("Failed to retrieve system directory");
            return;
        }

        std::string core_lib_directory(system_directory);
        d3d12_module = LoadLibraryA((core_lib_directory + "\\d3d12.dll").c_str());
        if (d3d12_module == nullptr)
        {
            D3D12_WRAPPER_ERROR("Failed to load d3d12.dll");
            return;
        }

        dispatch_table.D3D12GetDebugInterface = (PFN_D3D12_GET_DEBUG_INTERFACE)GetProcAddress(d3d12_module, "D3D12GetDebugInterface");
        dispatch_table.D3D12GetInterface = (PFN_D3D12_GET_INTERFACE)GetProcAddress(d3d12_module, "D3D12GetInterface");
        dispatch_table.D3D12CreateDevice = (PFN_D3D12_CREATE_DEVICE)GetProcAddress(d3d12_module, "D3D12CreateDevice");
        dispatch_table.D3D12SerializeRootSignature = (PFN_D3D12_SERIALIZE_ROOT_SIGNATURE)GetProcAddress(d3d12_module, "D3D12SerializeRootSignature");
        dispatch_table.D3D12SerializeVersionedRootSignature = (PFN_D3D12_SERIALIZE_VERSIONED_ROOT_SIGNATURE)GetProcAddress(d3d12_module, "D3D12SerializeVersionedRootSignature");
        dispatch_table.D3D12CreateRootSignatureDeserializer = (PFN_D3D12_CREATE_ROOT_SIGNATURE_DESERIALIZER)GetProcAddress(d3d12_module, "D3D12CreateRootSignatureDeserializer");
        dispatch_table.D3D12CreateVersionedRootSignatureDeserializer = (PFN_D3D12_CREATE_VERSIONED_ROOT_SIGNATURE_DESERIALIZER)GetProcAddress(d3d12_module, "D3D12CreateVersionedRootSignatureDeserializer");
        dispatch_table.D3D12EnableExperimentalFeatures = (D3D12DispatchTable::PFN_D3D12_ENABLE_EXPERIMENTAL_FEATURES)GetProcAddress(d3d12_module, "D3D12EnableExperimentalFeatures");

        AllocConsole();
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
        D3D12_WRAPPER_DEBUG("Initialized D3D12 hook manager successfully");
    }

    D3D12HookManager::~D3D12HookManager()
    {
        if (d3d12_module)
        {
            FreeLibrary(d3d12_module);
            dispatch_table = {};
        }
    }

    const D3D12DispatchTable &D3D12HookManager::DispatchTable() const
    {
        return dispatch_table;
    }

    D3D12HookManager &D3D12HookManager::GetInstance()
    {
        static D3D12HookManager s_d3d12_hook_manager{};
        return s_d3d12_hook_manager;
    }
}