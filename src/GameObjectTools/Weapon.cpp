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
    // TODO
    const int ownerRowBR = mOwner->GetRow0();
    const int ownerColBR = mOwner->GetCol0();
    const int ownerRowTL = mOwner->GetRow1();
    const int ownerColTL = mOwner->GetCol1();

    const int targetRowBR = target->GetRow0();
    const int targetColBR = target->GetCol0();
    const int targetRowTL = target->GetRow1();
    const int targetColTL = target->GetCol1();

    return 0.5f;
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
