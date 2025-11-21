#include "ObjectData.h"

#include "GameConstants.h"
#include "GameObjects/GameObject.h"

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

const char * ObjectData::STR_ATTRIBUTES[NUM_OBJ_ATTRIBUTES] =
{
    "ENERGY",
    "VIEW RANGE",
    "FIRE POWER",
    "FIRE ACCURACY",
    "FIRE RANGE",
    "REGENERATION",
    "RESISTANCE",
    "SHIELD",
    "SPEED",
    "CONSTRUCTION",
    "CONQUEST",
    "HEALING RANGE",
    "HEALING POWER",
    "SPAWNING",
    "STORAGE"
};

const ObjectData ObjectData::NullObj({}, {}, {}, nullptr, GameObject::TYPE_NULL,
                                     OC_NULL, OCAT_UNDEFINED, 0, 0);

unsigned int ObjectData::GetIconTexId(PlayerFaction f) const
{
    if(f < mIconTexIds.size())
        return mIconTexIds[f];
    else
        return mIconTexIds.back();
}

} // namespace game
