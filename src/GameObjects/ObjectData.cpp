#include "ObjectData.h"

#include "GameConstants.h"
#include "GameObjects/GameObject.h"
#include "GameObjectTools/WeaponData.h"

namespace game
{

const char * ObjectData::STR_CLASS[NUM_OBJ_CLASSES] =
{
    // STRUCTURES
    "BARRACKS",
    "BASE",
    "GENERATOR",
    "HOSPITAL",
    "RADAR",
    "RELICS",
    "RESEARCH",
    "STORAGE",
    "TARGET",
    "TOWER",
    "TRADING",
    "WALL",
    "GATE",

    // MINI UNITS
    "SOLDIER",

    // UNITS
    "GENERIC",
    "MEDIC",
    "SOLDIER",
    "SPAWNER",
    "WORKER",

    // OTHERS
    "COLLECTABLE",
    "SCENE"
};

// WEAPON
const char * ObjectData::STR_ATTRIBUTES[NUM_OBJ_ATTRIBUTES] =
{
    // GENERIC
    "ENERGY",
    "HEALTH",
    "VIEW RANGE",
    "REGENERATION",
    "RESISTANCE",
    "SHIELD",
    // WEAPON
    "ATTACK ACCURACY",
    "ATTACK POWER",
    "ATTACK RANGE",
    // UNIT
    "SPEED",
    "CONSTRUCTION",
    "CONQUEST",
    "HEALING RANGE",
    "HEALING POWER",
    "SPAWNING",
    // RESOURCE STORAGE
    "STORAGE"
};

const ObjectData ObjectData::NullObj({}, {}, {}, nullptr, GameObject::TYPE_NULL, GameObject::CAT_NULL,
                                     OC_NULL, OCAT_UNDEFINED, WeaponData::TYPE_NULL, 0, 0);

unsigned int ObjectData::GetIconTexId(PlayerFaction f) const
{
    if(f < mIconTexIds.size())
        return mIconTexIds[f];
    else
        return mIconTexIds.back();
}

} // namespace game
