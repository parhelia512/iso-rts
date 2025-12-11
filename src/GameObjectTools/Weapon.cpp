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
}

// returns TRUE when owner needs to shoot
bool Weapon::Update(float delta)
{
    // no target
    if(mTarget == nullptr)
        return false;

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
            return false;

        return true;
    }
    // single shot
    else
        return true;

    return false;
}

} // namespace game
