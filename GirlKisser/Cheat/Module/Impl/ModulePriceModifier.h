#pragma once
#include "../ModuleBase.h"

static GKSliderInt __price_modifier_price = GKSliderInt("Price",  0, -100000, 0, "Only works for lottery boxes and pet training.");
static GKModule __price_modifier = { "Price Modifier", REWARDS, 0x0, false, {(GKSetting<>*) &__price_modifier_price} };

class ModulePriceModifier : ModuleBase
{
public:
    ModulePriceModifier() : ModuleBase(&__price_modifier) {}
    
    void do_module(void* arg) override
    {
        
    }

    int get_price()
    {
        return __price_modifier_price.value;
    }
};
