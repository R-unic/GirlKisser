#pragma once
#include "../ModuleBase.h"
#include "../../Offsets/Offsets.h"

static GKCheckbox __immunity_poison = GKCheckbox{ "Poison", true };

static GKCheckbox __immunity_bleeding = GKCheckbox{ "Slow", true };

static GKCheckbox __immunity_toxic = GKCheckbox{ "Stun", true };

static GKModule __immunity = { "Immunity", PLAYER, 0x0, ImGuiKey_5, true, {(GKSetting<int>*)&__immunity_poison, (GKSetting<int>*)&__immunity_bleeding, (GKSetting<int>*)&__immunity_toxic} };


class ModuleImmunity : ModuleBase
{
public:
    ModuleImmunity() : ModuleBase(&__immunity) {}
    
    void do_module(void* arg) override
    {
        if (__immunity_poison.enabled) set_bool(arg, Offsets::fireImmunity, true); // fireImmunity
        if (__immunity_bleeding.enabled) set_bool(arg, Offsets::bleedingImmunity, true); // bleedingImmunity
        if (__immunity_toxic.enabled) set_bool(arg, Offsets::toxicImmunity, true); // toxicImmunity
    }
};
