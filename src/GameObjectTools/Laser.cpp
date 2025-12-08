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

#include <cmath>

namespace game
{

Laser::Laser(GameObject * owner, GameMap * gm, const sgl::graphic::ParticlesManager *partMan)
    : Weapon(owner, gm, partMan)
    , mPartUpdater(static_cast<UpdaterSingleLaser *>(partMan->GetUpdater(PU_SINGLE_LASER)))
{
    using namespace sgl;

    auto tm = graphic::TextureManager::Instance();

    const PlayerFaction faction = owner->GetFaction();
    const unsigned int texInd = SpriteIdUnitsParticles::IND_UPAR_LASER_F1 + faction;
    mTex = tm->GetSprite(SpriteFileUnitsParticles, texInd);
}

void Laser::Shoot(float x0, float y0, GameObject * target)
{
    GameObject * owner = GetOwner();

    const IsoObject * isoTarget = target->GetIsoObject();
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

    const float maxDamage = 20.f;
    const float damage = maxDamage * owner->GetAttribute(OBJ_ATT_FIRE_POWER) / MAX_STAV_VAL;

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

    const DataParticleSingleLaser pd =
    {
        mTex,
        GetGameMap(),
        target,
        angle,
        x0,
        y0,
        tX,
        tY,
        speed,
        damage,
        owner->GetFaction()
    };

    mPartUpdater->AddParticle(pd);

    // consume owner's energy
    owner->ActionStepCompleted(ATTACK);
}

} // namespace game
