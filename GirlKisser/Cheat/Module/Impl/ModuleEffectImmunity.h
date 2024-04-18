#pragma once
#include "../ModuleBase.h"

static GKCheckbox __immunity_fire = GKCheckbox { "Fire", true };

static GKCheckbox __immunity_bleeding = GKCheckbox { "Bleeding", true };

static GKCheckbox __immunity_toxic = GKCheckbox { "Poison", true };

static GKModule __immunity = { "Effect Immunity", PLAYER, 0x0, ImGuiKey_None, true, {(GKSetting<>*)&__immunity_fire, (GKSetting<>*)&__immunity_bleeding, (GKSetting<>*)&__immunity_toxic} };


class ModuleEffectImmunity : ModuleBase
{
public:
    ModuleEffectImmunity() : ModuleBase(&__immunity) {}

    void do_module(void* arg) override
    {
        if (__immunity_fire.enabled) set_bool(arg, 0x248, true); // fireImmunity
        if (__immunity_bleeding.enabled) set_bool(arg, 0x249, true); // bleedingImmunity
        if (__immunity_toxic.enabled) set_bool(arg, 0x24A, true); // toxicImmunity
    }
};