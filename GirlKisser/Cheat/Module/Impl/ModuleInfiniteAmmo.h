#pragma once
#include "../ModuleBase.h"
#include "../../Internal/Functions.h"

static GKModule __infinite_ammo = { "Infinite Ammo", PLAYER, 0x0, ImGuiKey_None, false, {} };

class ModuleInfiniteAmmo : ModuleBase
{
public:
    ModuleInfiniteAmmo() : ModuleBase(&__infinite_ammo) {}
    
    void do_module(void* arg) override
    {
        Functions::AddAmmoFromWeaponOnline(arg, 100);
    }
};
