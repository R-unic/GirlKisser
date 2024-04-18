#pragma once
#include "../ModuleBase.h"

static GKModule __criticals = { "Criticals", COMBAT, 0x0, ImGuiKey_None, false, {} };

class ModuleCriticals : ModuleBase
{
public:
    ModuleCriticals() : ModuleBase(&__criticals) {}
    
    void do_module(void* arg) override
    {
        set_bool(arg, Offsets::firstKillCritical, true); // firstKillCritical
        Functions::SetNextHitCritical(arg, true);
    }
};
