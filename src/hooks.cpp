#include "hooks.h"
#include <vector>

static std::vector<LibraryHook *> &get_library_list()
{
    static std::vector<LibraryHook *> libraries;
    return libraries;
}

void LibraryHookManager::register_hooks()
{
    for (auto *library_hook : get_library_list())
    {
        library_hook->register_hooks();
    }
}

void LibraryHookManager::remove_hooks()
{
    for (auto *library_hook : get_library_list())
    {
        library_hook->remove_hooks();
    }
}

LibraryHook::LibraryHook()
{
    get_library_list().push_back(this);
}