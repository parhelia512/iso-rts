#include "GameObjectTools/Laser.h"

#include "GameConstants.h"
#include "GameData.h"
#include "IsoObject.h"
#include "GameObjects/GameObject.h"
#include "Particles/DataParticleSingleLaser.h"
#include "Particles/UpdaterSingleLaser.h"

#include <sgl/core/Math.h>
#include <sgl/graphic/ParticlesManager.h>
#include <sgl/graphic/Texture.h>
#include <sgl/graphic/TextureManager.h>
#include <sgl/utilities/UniformRealDistribution.h>

#include <cmath>

#include <iostream>

namespace game
{

Laser::Laser(const WeaponData & data, GameObject * owner, GameMap * gm,
             const sgl::graphic::ParticlesManager *partMan)
    : Weapon(data, owner, gm, partMan)
    , mPartUpdater(static_cast<UpdaterSingleLaser *>(partMan->GetUpdater(PU_SINGLE_LASER)))
{
    using namespace sgl;

    auto tm = graphic::TextureManager::Instance();

    const PlayerFaction faction = owner->GetFaction();
    const unsigned int texInd = SpriteIdUnitsParticles::IND_UPAR_LASER_F1 + faction;
    mTex = tm->GetSprite(SpriteFileUnitsParticles, texInd);
}

int Laser::GetCostEnergy() const
{
    const int costSingleShot = GetCostEnergyPerShot();

    if(GetAttackMode() == ATT_BURST_SHOT)
        return costSingleShot * GetBurstShots();
    else
        return costSingleShot;
}

int Laser::GetCostEnergyPerShot() const
{
    switch (GetAttackMode())
    {
        case ATT_QUICK_SHOT: return 10; break;

        case ATT_AIMED_SHOT: return 20; break;

        case ATT_BURST_SHOT:  return 5; break;

        default: return 0; break;
    }
}

void Laser::OnShoot(float x0, float y0)
{
    GameObject * owner = GetOwner();

    const IsoObject * isoTarget = mTarget->GetIsoObject();
    const float tX = isoTarget->GetX() + (isoTarget->GetWidth() - mTex->GetWidth()) * 0.5f;
    const float tY = isoTarget->GetY() + (isoTarget->GetHeight() - mTex->GetHeight()) * 0.5f;
    const float speed = 400.f;

    const float rad2deg = 180.f / sgl::core::Math::PIf;
    const float dy0 = tY - y0;
    const float dx1 = tX - x0;
    const float dy1 = dy0;
    const float s = dy0 / sqrtf(dx1 * dx1 + dy1 * dy1);
    const float as = asinf(s);
    const double angleDeg = as * rad2deg;
    double angle;

    if(dx1 < 0.f)
    {
        // bottom left
        if(dy1 > 0.f)
            angle = 180.f - angleDeg;
        // top left
        else
            angle = 180.f - angleDeg;
    }
    else
    {
        // bottom right
        if(dy1 > 0.f)
            angle = angleDeg;
        // top right
        else
            angle = 360.f + angleDeg;
    }

    // decide if hit or miss
    const float maxProb = 100.f;
    const float probHit = GetProbabilityHit(mTarget);

    auto dist = sgl::utilities::UniformRealDistribution(0.f, maxProb);
    const float valHit = dist.GetNextValue();

    // 0 damage is miss
    float damage = 0.f;
    bool fatal = false;

    std::cout << "Laser::OnShoot - valHit: " << valHit << " / probHit: " << probHit << std::endl;

    // hit
    if(valHit < probHit)
    {
        const float maxDamage = 20.f;
        damage = maxDamage * owner->GetAttribute(OBJ_ATT_ATTACK_POWER) / MAX_STAV_VAL;

        // check for fatal hit
        const float probFatal = GetProbabilityFatalHit(mTarget);
        const float valFatal = dist.GetNextValue();

        fatal = valFatal < probFatal;

        std::cout << "Laser::OnShoot - valFatal: " << valFatal << " / probFatal: " << probFatal << std::endl;
    }

    const DataParticleSingleLaser pd =
    {
        mTex,
        GetGameMap(),
        mTarget,
        angle,
        x0,
        y0,
        tX,
        tY,
        speed,
        damage,
        owner,
        fatal
    };

    mPartUpdater->AddParticle(pd);

    // consume owner's energy
    owner->ActionStepCompleted(ATTACK);
}

} // namespace game
