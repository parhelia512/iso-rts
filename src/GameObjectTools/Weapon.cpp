#include "GameObjectTools/Weapon.h"

#include "GameConstants.h"
#include "GameObjectTools/WeaponData.h"

namespace game
{

Weapon::Weapon(const WeaponData & data, GameObject * owner, GameMap * gm,
               const sgl::graphic::ParticlesManager * partMan)
    : mAttributes(data.GetAttributes())
    , mOwner(owner)
    , mGameMap(gm)
    , mPartMan(partMan)
{
    // set attack range converting attribute
    const int attRanges[] = { 0, 2, 3, 4, 5, 6, 8, 9, 10, 11, 13 };
    mRange = attRanges[mAttributes[OBJ_ATT_ATTACK_RANGE]];
}

} // namespace game
