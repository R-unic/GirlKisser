#pragma once
#include "../ModuleBase.h"

static GKCheckbox __blind = GKCheckbox("Blind", false);
static GKSlider __blind_duration = GKSlider("Blind Duration", 9999, 0, 9999);

static GKCheckbox __charm = GKCheckbox("Charm", false);

static GKCheckbox __curse = GKCheckbox("Curse", false);
static GKSlider __curse_duration = GKSlider("Curse Duration", 9999, 0, 9999);
static GKSlider __curse_damage = GKSlider("Curse Damage", 10, 0, 100);

static GKCheckbox __lightning = GKCheckbox("Lightning", false);

static GKCheckbox __poison = GKCheckbox("Poison", false);
static GKSliderInt __poison_amount = GKSliderInt("Poison Amount", 9999, 0, 9999);
static GKSlider __poison_time = GKSlider("Poison Time", 9999, 0, 9999);
static GKSlider __poison_multi = GKSlider("Poison Multiplier", 9999, 0, 9999, "This may or may not work!");

static GKCheckbox __slow = GKCheckbox("Slow", false);
static GKSlider __slow_duration = GKSlider("Slow Duration", 9999, 0, 9999);
static GKSlider __slow_factor = GKSlider("Slow Factor", 0.001f, 0.001f, 10);

static GKCheckbox __stun = GKCheckbox{ "Stun", false };
static GKSlider __stun_duration = GKSlider("Stun Duration", 9999, 0, 9999);
static GKSlider __stun_factor = GKSlider("Stun Factor", 10, 0.001f, 10);
static GKSlider __stun_radius = GKSlider("Stun Radius", 9999, 0, 9999);

static GKModule __debuffer = { "Debuffer", COMBAT, 0x0, false, {(GKSetting<>*) &__blind, (GKSetting<>*) &__blind_duration, (GKSetting<>*) &__charm, (GKSetting<>*) &__curse, (GKSetting<>*) &__curse_duration, (GKSetting<>*) &__curse_damage, (GKSetting<>*) &__lightning, (GKSetting<>*) &__poison, (GKSetting<>*) &__poison_amount, (GKSetting<>*) &__slow, (GKSetting<>*) &__slow_duration, (GKSetting<>*) &__slow_factor, (GKSetting<>*) &__stun, (GKSetting<>*) &__stun_duration, (GKSetting<>*) &__stun_factor, (GKSetting<>*) &__stun_radius} };

class ModuleDebuffer : ModuleBase
{
public:
    ModuleDebuffer() : ModuleBase(&__debuffer) {}
    
    void do_module(void* arg) override
    {
        if (__blind.enabled)
        {
            set_bool(arg, Offsets::isBlindEffect, true); // isBlindEffect
            set_float(arg, Offsets::isBlindEffectTime, __blind_duration.value); // isBlindEffectTime
        }

        if (__charm.enabled)
        {
            set_bool(arg, Offsets::isCharm, true); // isCharm
        }

        if (__curse.enabled)
        {
            set_bool(arg, Offsets::isCursing, true); // isCursing
            set_float(arg, Offsets::curseTime, __curse_duration.value); // curseTime
            set_float(arg, Offsets::curseDamageMultiplier, __curse_damage.value); // curseDamageMultiplier
        }

        if (__lightning.enabled)
        {
            set_bool(arg, Offsets::isLightning, true); // isLightning
        }

        if (__poison.enabled)
        {
            set_bool(arg, Offsets::isPoisoning, true); // isPoisoning
            set_int(arg, Offsets::poisonCount, __poison_amount.value); // poisonCount
            set_float(arg, Offsets::poisonDamageMultiplier, __poison_multi.value); // poisonDamageMultiplier
            set_float(arg, Offsets::poisonTime, __poison_time.value); // poisonTime
        }

        if (__slow.enabled)
        {
            set_bool(arg, Offsets::isSlowdown, true); // isSlowdown
            set_float(arg, Offsets::slowdownCoeff, __slow_factor.value); // slowdownCoeff
            set_float(arg, Offsets::slowdownTime, __slow_duration.value); // slowdownTime
            set_bool(arg, Offsets::isSlowdownStack, true); // isSlowdownStack
        }

        if (__stun.enabled)
        {
            set_bool(arg, Offsets::isStun, true); // isStun
            set_float(arg, Offsets::stunCoeff, __stun_factor.value); // stunCoeff
            set_float(arg, Offsets::stunTime, __stun_duration.value); // stunTime
            set_float(arg, Offsets::stunRadius, __stun_radius.value); // stunRadius
        }
    }
};
