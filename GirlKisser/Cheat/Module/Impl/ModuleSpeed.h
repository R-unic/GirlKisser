#pragma once
#include "../ModuleBase.h"

static GKSlider __speed_amount = GKSlider("Amount",  1, 0.01f, 100);
static GKModule __speed = { "Speed", MOVEMENT, 0x0, ImGuiKey_None, false, {(GKSetting<>*) &__speed_amount} };

class ModuleSpeed : ModuleBase
{
public:
    ModuleSpeed() : ModuleBase(&__speed) {}
    
    void do_module(void* arg) override
    {
    }

    float get_amount()
    {
        return __speed_amount.value;
    }
};
