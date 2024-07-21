#pragma once

struct LibraryHookManager
{
    static void register_hooks();

    static void remove_hooks();
};

struct LibraryHook
{
    friend struct LibraryHookManager;

    LibraryHook();

    virtual ~LibraryHook() = default;
    
    virtual void register_hooks() = 0;

    virtual void remove_hooks() {}
};