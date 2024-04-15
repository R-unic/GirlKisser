#pragma once
#include "../ModuleBase.h"

static GKSliderInt __regen_percent = GKSliderInt("Regeneration Percent", 10, 1, 100);

static GKModule __armor_regen = { "Armor Regeneration", PLAYER, 0x0, false, { (GKSetting<>*)& __regen_percent } };

class ModuleArmorRegen : ModuleBase
{
public:
    ModuleArmorRegen() : ModuleBase(&__armor_regen) {}

    void do_module(void* arg) override
    {
        set_float(arg, Offsets::armorRegenerationPercent, __regen_percent.value); // armorRegenerationPercent
        set_bool(arg, Offsets::isArmorRegeneration, true); // isArmorRegeneration
    }
};