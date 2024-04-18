#pragma once
#include "../ModuleBase.h"

static GKCheckbox __season_pass_premium = { "Spoof Premium", true, "Only lasts while enabled." };
static GKModule __season_pass = { "Season Pass", EXPLOIT, 0x0, ImGuiKey_None, true, { (GKSetting<>*) & __season_pass_premium}};

class ModuleSeasonPass : ModuleBase
{
public:
    ModuleSeasonPass() : ModuleBase(&__season_pass) {}

    void do_module(void* arg) override
    {
    }

    bool spoof_premium()
    {
        return __season_pass_premium.enabled;
    }
};