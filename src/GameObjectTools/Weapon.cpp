#include "GameObjectTools/Weapon.h"

#include "GameConstants.h"
#include "GameMap.h"
#include "GameObjects/GameObject.h"
#include "GameObjectTools/WeaponData.h"

#include <cstdlib>

namespace game
{

Weapon::Weapon(const WeaponData & data, GameObject * owner, GameMap * gm,
               const sgl::graphic::ParticlesManager * partMan)
    : mAttributes(data.GetAttributes())
    , mOwner(owner)
    , mGameMap(gm)
    , mPartMan(partMan)
    , mAttackMode(ATT_QUICK_SHOT)
    , mBurstShots(data.GetBurstShots())
    , mBurstToShoot(data.GetBurstShots())
    , mBurstDelay(data.GetBurstDelay())
{
    // set attack range converting attribute
    const int attRanges[] = { 0, 2, 3, 4, 5, 6, 8, 9, 10, 11, 13 };
    mRange = attRanges[mAttributes[OBJ_ATT_ATTACK_RANGE]];
}

bool Weapon::SetTarget(GameObject * obj)
{
    if(nullptr == obj || !IsTargetInRange(obj) || !obj->IsVisible() ||
       !mOwner->HasEnergyForActionStep(ATTACK) || obj == mOwner)
        return false;

    mTarget = obj;
    mTimerBurst = 0.f;

    mReadyToShoot = false;

    InitBurstShoot();

    return true;
}

bool Weapon::IsTargetInRange(const GameObject * obj) const
{
    const int r0 = mOwner->GetRow0();
    const int c0 = mOwner->GetCol0();

    for(int r = obj->GetRow1(); r <= obj->GetRow0(); ++r)
    {
        for(int c = obj->GetCol1(); c <= obj->GetCol0(); ++c)
        {
            if(std::abs(r0 - r) <= mRange && std::abs(c0 - c) <= mRange)
                return true;
        }
    }

    return false;
}

float Weapon::GetHitProbability(const GameObject * target) const
{
    const int maxDist = mRange * 2;
    const int dist = mGameMap->Distance(mOwner, target);
    const int targetSize = target->GetRows() * target->GetCols();

    const float maxProb = 100.f;
    // base probability is higher when closer to target up to 100% if next to it
    const float baseProb = (maxDist - dist + 1) * maxProb / static_cast<float>(maxDist);
    // fixed probability is part of base that's at least 50% and higher as target gets bigger
    const float fixedW = 0.5f + (0.5f - (0.5f / static_cast<float>(targetSize)));
    const float fixedProb = baseProb * fixedW;

    const float variableProb = (baseProb - fixedProb) * mAttributes.at(OBJ_ATT_ATTACK_ACCURACY) / MAX_STAV_VAL;
    const float finalProb = fixedProb + variableProb;

    // bonus/malus based on attack mode
    float bonusProb = 0.f;

    if(mAttackMode == ATT_BURST_SHOT)
    {
        const float bonus = -0.1;
        bonusProb = finalProb * bonus;
    }
    else if(mAttackMode == ATT_AIMED_SHOT)
    {
        const float missProb = maxProb - finalProb;
        const float bonus = 0.2;
        bonusProb = missProb * bonus;
    }
    else
    {
        const float bonus = -0.05;
        bonusProb = finalProb * bonus;
    }

    return finalProb + bonusProb;
}

float Weapon::GetFatalHitProbability(const GameObject * target) const
{

    // TODO
    return 0.01f;
}

void Weapon::Shoot(float x0, float y0)
{
    OnShoot(x0, y0);

    if(mAttackMode == ATT_BURST_SHOT)
    {
        --mBurstToShoot;

        if(mBurstToShoot == 0)
            mTarget = nullptr;
        else
            mTimerBurst = mBurstDelay;
    }
    // single shot
    else
        mTarget = nullptr;

    mReadyToShoot = false;
}

// returns TRUE when owner needs to shoot
bool Weapon::Update(float delta)
{
    // target already destroyed
    if(!mGameMap->HasObject(mTarget))
    {
        mTarget = nullptr;
        return false;
    }

    if(mAttackMode == ATT_BURST_SHOT)
    {
        mTimerBurst -= delta;

        if(mTimerBurst > 0.f)
            return true;

        mReadyToShoot = true;
    }
    // single shot
    else
        mReadyToShoot = true;

    return true;
}

} // namespace game
