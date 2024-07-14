#include "hooks.h"
#include <Windows.h>

//static bool add_hooks()
//{
//    LibraryHookManager::register_hooks();
//    return true;
//}
//
//static bool remove_hooks()
//{
//    LibraryHookManager::remove_hooks();
//    return true;
//}
//
//BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
//{
//    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
//    {
//        bool result = add_hooks();
//        return result;
//    } else if(ul_reason_for_call == DLL_PROCESS_DETACH)
//    {
//        bool result = remove_hooks();
//        return result;
//    }
//
//    return TRUE;
//}