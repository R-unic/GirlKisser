#pragma once
#include "../ModuleBase.h"

static BKCSlider __speed_amount = BKCSlider("Amount",  1, 0.1f, 20);
static BKCModule __speed = { "Speed", MOVEMENT, 0x0, false, {(BKCSetting<>*) &__speed_amount} };

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
