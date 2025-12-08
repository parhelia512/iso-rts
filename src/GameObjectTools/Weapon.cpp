#include "GameObjectTools/Weapon.h"

namespace game
{

Weapon::Weapon(GameObject * owner, GameMap * gm, const sgl::graphic::ParticlesManager * partMan)
    : mOwner(owner)
    , mGameMap(gm)
    , mPartMan(partMan)
{
}

} // namespace game
