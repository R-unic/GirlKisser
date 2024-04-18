﻿#pragma once
#include <string>

#include "../Gui/imgui_hooker.h"
#include "../Offsets/Offsets.h"

class ModuleBase
{
public:
    ModuleBase(GKModule* m)
    {
        key = m->key;
        activationKey = m->activationKey; 
        name = m->name;
        module = m;
        GKImGuiHooker::modules.push_back(m);
    }
    
    WPARAM key = 0x00;
    ImGuiKey activationKey;
    std::string name;
    GKModule* module;
    
    void run(void* arg)
    {
        if (module->enabled) do_module(arg);
    }

    bool is_enabled()
    {
        return module->enabled;
    }
    
    void toggle()
    {
        module->enabled = !module->enabled;
    }

    void set_enabled(bool enabled)
    {
        module->enabled = enabled;
    }
    
    virtual void do_module(void* arg) = 0;

protected:
    static void set_bool(void* arg, uint64_t offset, bool value)
    {
        *(bool*)((uint64_t)arg + offset) = value;
    }

    static void set_float(void* arg, uint64_t offset, float value)
    {
        *(float*)((uint64_t)arg + offset) = value;
    }

    static void set_int(void* arg, uint64_t offset, int value)
    {
        *(int*)((uint64_t)arg + offset) = value;
    }
};
