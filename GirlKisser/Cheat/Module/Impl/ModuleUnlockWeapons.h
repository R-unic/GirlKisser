﻿#pragma once
#include <stdbool.h>

#include "../ModuleBase.h"
#include "../../Gui/imgui_hooker.h"

static GKDropdown __weapon_list = { "Weapon Selector", weapons_names[0], weapons_names, "THIS IS A VOLATILE MODULE, AND HAS A POSSIBILITY TO BAN DEPENDING ON HOW YOU USE IT", true };
static GKCheckbox __unlock_weapons_dev = {"Spoof Developer", true, "Tries to add the weapon through developer mode, less consistent but safer."};
static GKCheckbox __unlock_weapons_all = {"Unlock All", false, "WARNING, THIS ONLY WORKS FROM THE LOTTERY SUPERCHEST AND WILL CRASH THE GAME, BUT YOU SHOULD HAVE ALL THE WEAPONS AFTERWARDS"};
static GKModule __unlock_weapons = { "Weapon Unlock", UNLOCKABLES, 0x0, ImGuiKey_None, false, { (GKSetting<int>*)&__weapon_list, (GKSetting<int>*)&__unlock_weapons_dev, (GKSetting<int>*)&__unlock_weapons_all } };

class ModuleUnlockWeapons : ModuleBase
{
public:
    ModuleUnlockWeapons() : ModuleBase(&__unlock_weapons) {}
    
    void do_module(void* arg) override
    {
        
    }

    bool all()
    {
        return __unlock_weapons_all.enabled;
    }

    void lock()
    {
        __unlock_weapons.enabled = false;
    }

    std::string to_unlock()
    {
        return __weapon_list.current_value;
    }

    bool dev()
    {
        return __unlock_weapons_dev.enabled;
    }
};
