#pragma once
#include "../ModuleBase.h"

static GKSlider __aoe_range = GKSlider("Range",  9999, 0, 9999);
static GKSlider __aoe_damage = GKSlider("Damage",  5, 0, 100, "High damage values may cause kicks!");
static GKModule __aoe_bullets = { "AOE Bullets", COMBAT, 0x0, false, {(GKSetting<>*) & __aoe_range, (GKSetting<>*) &__aoe_damage} };

class ModuleAOEBullets : ModuleBase
{
public:
    ModuleAOEBullets() : ModuleBase(&__aoe_bullets) {}
    
    void do_module(void* arg) override
    {
        set_bool(arg, Offsets::isSectorsAOE, true); // isSectorsAOE
        set_bool(arg, Offsets::flamethrower, false); // flamethrower
        set_bool(arg, Offsets::railgun, false); // railgun
        set_bool(arg, Offsets::bazooka, false); // bazooka
        set_bool(arg, Offsets::harpoon, false); // harpoon
        set_float(arg, Offsets::sectorsAOEAngleBack, 360); // sectorsAOEAngleBack
        set_float(arg, Offsets::sectorsAOEAngleFront, 360); // sectorsAOEAngleFront
        set_float(arg, Offsets::sectorsAOEDamageMultiplierBack, __aoe_damage.value); // sectorsAOEDamageMultiplierBack
        set_float(arg, Offsets::sectorsAOEDamageMultiplierFront, __aoe_damage.value); // sectorsAOEDamageMultiplierFront
        set_float(arg, Offsets::sectorsAOEDamageMultiplierSide, __aoe_damage.value); // sectorsAOEDamageMultiplierSide
        set_float(arg, Offsets::sectorsAOERadiusSectorsAoE, __aoe_range.value); // sectorsAOERadiusSectorsAoE
    }
};
