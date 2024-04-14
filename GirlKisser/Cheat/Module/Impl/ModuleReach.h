#pragma once
#include <iostream>
#include <ostream>

#include "../ModuleBase.h"

static GKSlider __reach_range = GKSlider("Range", 100, 0, 99999, "Low range values will disable range based weapons! (ex. Flamethrowers & Melee)");
static GKModule __reach = { "Reach", PLAYER, 0x0, false, { (GKSetting<>*) &__reach_range } };

class ModuleReach : ModuleBase
{
public:
    ModuleReach() : ModuleBase(&__reach) {}
    
    void do_module(void* arg) override
    {
        set_float(arg, 0x658, __reach_range.value); // reach
    }
};
