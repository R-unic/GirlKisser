﻿#pragma once
#include "../ModuleBase.h"

static GKModule __double_jump = { "Double Jump", MOVEMENT, 0x0, ImGuiKey_None, true, { } };

class ModuleDoubleJump : ModuleBase
{
public:
    ModuleDoubleJump() : ModuleBase(&__double_jump) {}
    
    void do_module(void* arg) override
    {
        set_bool(arg, Offsets::isDoubleJump, true); // isDoubleJump
    }
};
