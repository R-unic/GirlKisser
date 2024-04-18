#pragma once
#include "../ModuleBase.h"

static GKSlider __recoil_coeff = GKSlider("Recoil Coefficient", 0, -100, 100, "Recoil values too small/large may cause interesting effects!");
static GKModule __modify_recoil = { "No Recoil", COMBAT, 0x0, ImGuiKey_None, false, { (GKSetting<>*) &__recoil_coeff } };

class ModuleRecoil : ModuleBase
{
public:
    ModuleRecoil() : ModuleBase(&__modify_recoil) {}
    
    void do_module(void* arg) override
    {
        set_float(arg, Offsets::recoilCoeff, __recoil_coeff.value); // recoilCoeff
        set_float(arg, Offsets::recoilCoeffZoom, __recoil_coeff.value); // recoilCoeffZoom
    }
};
