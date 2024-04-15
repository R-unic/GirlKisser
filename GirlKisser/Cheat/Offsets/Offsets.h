#pragma once
#include <cstdint>

class Offsets
{
public:
    // Functions
    static inline uint64_t PlayerMoveCUpdate = 0x1B677D0;
    static inline uint64_t WeaponSoundsUpdate = 0x7F0070;
    static inline uint64_t SetNextCriticalHit = 0x7E91C0;
    static inline uint64_t MakeInvisibleForSeconds = 0x1AC54B0;
    static inline uint64_t AddHealthFromWeaponOnline = 0x1AABE00;
    static inline uint64_t AddAmmoFromWeaponOnline = 0x1AABC70;
    static inline uint64_t InfiniteGemClaim = 0x4BBE80;
    static inline uint64_t SetTimeScale = 0x436A560;
    static inline uint64_t RapidFire = 0x111B350;
    static inline uint64_t TextMeshGetText = 0x4446960;
    static inline uint64_t Speed = 0x11383E0;
    static inline uint64_t GetFov = 0x433C5C0;
    static inline uint64_t SetFov = 0x433CEE0;
    static inline uint64_t OnPreRender = 0x42D0540;
    static inline uint64_t TextMeshGetColor = 0x4446700;
    static inline uint64_t WorldToScreenPoint = 0x433BEC0;
    static inline uint64_t ComponentGetTransform = 0x435D760;
    static inline uint64_t TransformGetRotation = 0x43726E0;
    static inline uint64_t TransformGetPosition = 0x4372570;
    static inline uint64_t TransformLookAt = 0x43706E0;
    static inline uint64_t PhysicsRayCast = 0x43CFE70;
    static inline uint64_t ObjectGetInstanceID = 0x4364DC0;
    static inline uint64_t OnSceneUnload = 0x414C1B0;
    static inline uint64_t PriceModifier = 0x781F00;
    static inline uint64_t PlayerMoveCFixedUpdate = 0x1AC4C70;
    static inline uint64_t RewardMultiplier = 0xC326E0;
    static inline uint64_t DoubleRewards = 0xC33660;
    static inline uint64_t PremiumPass = 0x18881E0;

    // Fields
    static inline uint64_t scopeSpeed = 0xF8;
    static inline uint64_t zoomXray = 0xC6;
    static inline uint64_t shootDelay = 0x1B0;
    static inline uint64_t bulletDelay = 0x1AC;
    static inline uint64_t delayInBurstShooting = 0x5D8;
    static inline uint64_t isSectorsAOE = 0x3C0;
    static inline uint64_t flamethrower = 0x34C;
    static inline uint64_t railgun = 0x1B4;
    static inline uint64_t bazooka = 0x12B;
    static inline uint64_t harpoon = 0x2B8;
    static inline uint64_t sectorsAOEAngleBack = 0x3C8;
    static inline uint64_t sectorsAOEAngleFront = 0x3C4;
    static inline uint64_t sectorsAOEDamageMultiplierBack = 0x3D4;
    static inline uint64_t sectorsAOEDamageMultiplierFront = 0x3CC;
    static inline uint64_t sectorsAOEDamageMultiplierSide = 0x3D0;
    static inline uint64_t sectorsAOERadiusSectorsAoE = 0x3D8;
    static inline uint64_t isCharm = 0x274;
    static inline uint64_t isCursing = 0x214;
    static inline uint64_t curseTime = 0x218;
    static inline uint64_t curseDamageMultiplier = 0x21C;
    static inline uint64_t isLightning = 0x155;
    static inline uint64_t isPoisoning = 0x1F8;
    static inline uint64_t poisonCount = 0x1FC;
    static inline uint64_t isStun = 0x238;
    static inline uint64_t stunCoeff = 0x23C;
    static inline uint64_t stunTime = 0x240;
    static inline uint64_t stunRadius = 0x244;
    static inline uint64_t isBlindEffect = 0x268;
    static inline uint64_t isBlindEffectTime = 0x270;
    static inline uint64_t isSlowdown = 0x224;
    static inline uint64_t slowdownCoeff = 0x228;
    static inline uint64_t slowdownTime = 0x22C;
    static inline uint64_t isSlowdownStack = 0x230;
    static inline uint64_t firstKillCritical = 0x388;
    static inline uint64_t isInvisibleAfterRespawn = 0x389;
    static inline uint64_t invisibleAfterRespawnTime = 0x38C;
    static inline uint64_t isFrostSword = 0x369;
    static inline uint64_t isFrostSwordUseAngle = 0x374;
    static inline uint64_t frostRadius = 0x370;
    static inline uint64_t frostDamageMultiplier = 0x36C;
    static inline uint64_t frostSwordAngle = 0x378;
    static inline uint64_t frostSwordnTime = 0x37C;
    static inline uint64_t range = 0x658;
    static inline uint64_t recoilCoeff = 0xC0;
    static inline uint64_t recoilCoeffZoom = 0x124;
    static inline uint64_t moveScatterCoeff = 0xB8;
    static inline uint64_t moveScatterCoeffZoom = 0x11C;
    static inline uint64_t fieldOfViewZomm = 0xD8;
    static inline uint64_t scopeCircleRadius = 0xE0;
    static inline uint64_t scopeMovementSpeed = 0xE8;
    static inline uint64_t buffPointsKillDesigner = 0x3A0;
    static inline uint64_t buffPointsAssistDesigner = 0x3A8;
    static inline uint64_t buffPointsRevengeDesigner = 0x398;
    static inline uint64_t buffPointsOther = 0x3AC;
    static inline uint64_t buffBonusPointsForKill = 0x39C;
    static inline uint64_t buffBonusPointsForAssist = 0x3A4;
    static inline uint64_t buffPointsRevenge = 0x394;
    static inline uint64_t isBuffPoints = 0x390;
    static inline uint64_t chargeTime = 0x1E4;
    static inline uint64_t chargeMax = 0x1E0;
    static inline uint64_t chargeLoop = 0x1D8;
    static inline uint64_t isCharging = 0x1CA;
    static inline uint64_t isHeadshotDamageIncreased = 0x284;
    static inline uint64_t increasedHeadshotDamageMultiplier = 0x288;
    static inline uint64_t isRecudedHeadshotDamage = 0x28c;
    static inline uint64_t reducedHeadshotDamageMultiplier = 0x290;
    static inline uint64_t isDoubleJump = 0x477;
    static inline uint64_t armorRegenerationPercent = 0x3F0;
    static inline uint64_t isArmorRegeneration = 0x3EC;
    static inline uint64_t playerMoveCPlayerDamageable = 0x650;
    static inline uint64_t nickLabel = 0x3B8;
    static inline uint64_t weaponSoundsPlayerMoveC = 0x500;
    static inline uint64_t myPlayerTransform = 0x3A0;
    static inline uint64_t headCollider = 0x128;
    static inline uint64_t maxKoofZoom = 0x104;
    static inline uint64_t upKoofFireZoom = 0x108;
    static inline uint64_t downKoofFirstZoom = 0x10C;
    static inline uint64_t downKoofZoom = 0x110;
    static inline uint64_t maxKoof = 0x8C;
    static inline uint64_t tekKoof = 0x90;
    static inline uint64_t upKoofFire = 0x94;
    static inline uint64_t downKoofFirst = 0x98;
    static inline uint64_t downKoof = 0x9C;
    static inline uint64_t poisonDamageMultiplier = 0x200;
    static inline uint64_t poisonTime = 0x204;
    static inline uint64_t ignoreBarrier = 0x128;
    static inline uint64_t ignoreSlyWolf = 0x129;
    static inline uint64_t ignoreReflector = 0x12A;
};