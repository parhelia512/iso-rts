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

private:
    void OnShoot(float x0, float y0) override;

private:
    UpdaterSingleLaser * mPartUpdater = nullptr;

    sgl::graphic::Texture * mTex = nullptr;
};

} // namespace game
