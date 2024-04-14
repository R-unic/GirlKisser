#pragma once
#include "../ModuleBase.h"
#include "../../Gui/imgui_hooker.h"

class ModuleBase;
static GKSliderInt __rewards_multiplier_amount = GKSliderInt("Amount", 3, 1, 50000);
static GKModule __rewards_multiplier = { "Rewards Multiplier", REWARDS, 0x0, true, {(GKSetting<>*) &__rewards_multiplier_amount} };

class ModuleRewardsMultiplier : ModuleBase
{
public:
    ModuleRewardsMultiplier() : ModuleBase(&__rewards_multiplier) {}
    
    void do_module(void* arg) override
    {
        
    }

    int get_amount()
    {
        return __rewards_multiplier_amount.value;
    }
};
