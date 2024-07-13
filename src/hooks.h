#pragma once

struct LibraryHookManager
{
    static void register_hooks();

    static void remove_hooks();
};

struct LibrayHook
{
    friend struct LibraryHookManager;

    LibrayHook();

    virtual ~LibrayHook() = default;
    
    virtual void register_hooks() = 0;

    virtual void remove_hooks() {}
};