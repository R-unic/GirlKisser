#pragma once
#include "../ModuleBase.h"

static GKModule __infinite_gem_claim = { "Infinite Gem Claim", REWARDS, 0x0, false, {} };

class ModuleInfiniteGemClaim : ModuleBase
{
public:
    ModuleInfiniteGemClaim() : ModuleBase(&__infinite_gem_claim) {}
    
    void do_module(void* arg) override
    {
    }
};
