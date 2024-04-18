#pragma once
#include "../ModuleBase.h"
#include "../../Hooks/Hooks.h"

static GKSlider __ahs_multi = GKSlider("Damage Multiplier", 0, -15, 1);
static GKModule __anti_hs = { "AntiHeadshot", PLAYER, 0x0, ImGuiKey_None, false, {(GKSetting<>*) &__ahs_multi} };

class ModuleAntiHeadshot : ModuleBase
{
public:
    ModuleAntiHeadshot() : ModuleBase(&__anti_hs) {}
    
    void do_module(void* arg) override
    {
        set_bool(arg, Offsets::isRecudedHeadshotDamage, true); // isReducedHeadshotDamage
        set_float(arg, Offsets::reducedHeadshotDamageMultiplier, __ahs_multi.value); // reducedHeadshotDamageMultiplier
    }
};
