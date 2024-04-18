﻿#pragma once
#include "../ModuleBase.h"
#include "../../Hooks/Hooks.h"

static GKSlider __oshs_multi = GKSlider("Damage Multiplier", 1, 1, 10, "Multiplier values too high will cause kicks! (Depending on weapon)");
static GKModule __oshs = { "Headshot Modifier", COMBAT, 0x0, ImGuiKey_None, false, {(GKSetting<>*) &__oshs_multi} };

class ModuleHeadshotMultiplier : ModuleBase
{
public:
    ModuleHeadshotMultiplier() : ModuleBase(&__oshs) {}
    
    void do_module(void* arg) override
    {
        set_bool(arg, 0x284, true); // isHeadshotDamageIncreased (0x28c = isReducedHeadshotDamage, maybe applicable to enemies)
        set_float(arg, 0x288, __oshs_multi.value); // increasedHeadshotDamageMultiplier (0x290 = reducedHeadshotDamageMultiplier, maybe applicable to enemies)
    }
};
