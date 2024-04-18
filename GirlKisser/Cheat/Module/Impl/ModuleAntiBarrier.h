#pragma once
#include "../ModuleBase.h"

static GKModule __anti_barrier = { "Anti Barrier", PLAYER, 0x0, ImGuiKey_None, true, {} };

class ModuleAntiBarrier : ModuleBase
{
public:
    ModuleAntiBarrier() : ModuleBase(&__anti_barrier) {}

    void do_module(void* arg) override
    {
        set_bool(arg, 0x128, true); // ignoreBarrier
        set_bool(arg, 0x129, true); // ignoreSlyWolf
        set_bool(arg, 0x12A, true); // ignoreReflector
    }
};