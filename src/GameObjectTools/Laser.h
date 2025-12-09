#pragma once

#include "Weapon.h"

namespace sgl
{
    namespace graphic { class Texture; }
}

namespace game
{

class UpdaterSingleLaser;

class Laser : public Weapon
{
public:
    Laser(const WeaponData & data, GameObject * owner, GameMap * gm,
          const sgl::graphic::ParticlesManager * partMan);

    void Shoot(float x0, float y0, GameObject * target) override;

private:
    UpdaterSingleLaser * mPartUpdater = nullptr;

    sgl::graphic::Texture * mTex = nullptr;
};

} // namespace game
