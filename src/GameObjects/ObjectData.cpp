#include "ObjectData.h"

#include "GameConstants.h"
#include "GameObjects/GameObject.h"
#include "GameObjectTools/WeaponData.h"

namespace game
{
using h = std::hash<std::string>;

// -- OBJECT TYPE --
const std::string ObjectData::TYPE_STR_BARRACKS("BARRACKS");
const std::string ObjectData::TYPE_STR_BASE("BASE");
const std::string ObjectData::TYPE_STR_BASE_SPOT("BASE_SPOT");
const std::string ObjectData::TYPE_STR_BLOBS("BLOBS");
const std::string ObjectData::TYPE_STR_BUNKER("BUNKER");
const std::string ObjectData::TYPE_STR_DEFENSIVE_TOWER("DEF_TOWER");
const std::string ObjectData::TYPE_STR_DIAMONDS("DIAMONDS");
const std::string ObjectData::TYPE_STR_HOSPITAL("HOSPITAL");
const std::string ObjectData::TYPE_STR_LOOTBOX("LOOTBOX");
const std::string ObjectData::TYPE_STR_MINI_UNIT1("MINIUNIT1");
const std::string ObjectData::TYPE_STR_MINI_UNIT2("MINIUNIT2");
const std::string ObjectData::TYPE_STR_MOUNTAINS("MOUNTAINS");
const std::string ObjectData::TYPE_STR_PRACTICE_TARGET("TARGET");
const std::string ObjectData::TYPE_STR_RADAR_STATION("RADAR_STATION");
const std::string ObjectData::TYPE_STR_RADAR_TOWER("RADAR_TOWER");
const std::string ObjectData::TYPE_STR_RESEARCH_CENTER("RESEARCH_CENTER");
const std::string ObjectData::TYPE_STR_RES_GEN_ENERGY("RESGEN_ENER");
const std::string ObjectData::TYPE_STR_RES_GEN_ENERGY_SOLAR("RESGEN_SOLAR");
const std::string ObjectData::TYPE_STR_RES_GEN_MATERIAL("RESGEN_MAT");
const std::string ObjectData::TYPE_STR_RES_GEN_MATERIAL_EXTRACT("RESGEN_MAT_EXT");
const std::string ObjectData::TYPE_STR_RES_STORAGE_BLOBS("RESSTOR_BLOBS");
const std::string ObjectData::TYPE_STR_RES_STORAGE_DIAMONDS("RESSTOR_DIAM");
const std::string ObjectData::TYPE_STR_RES_STORAGE_ENERGY("RESSTOR_ENER");
const std::string ObjectData::TYPE_STR_RES_STORAGE_MATERIAL("RESSTOR_MAT");
const std::string ObjectData::TYPE_STR_ROCKS("ROCKS");
const std::string ObjectData::TYPE_STR_SPAWN_TOWER("SPAWN_TOWER");
const std::string ObjectData::TYPE_STR_TEMPLE("TEMPLE");
const std::string ObjectData::TYPE_STR_TRADING_POST("TRADING_POST");
const std::string ObjectData::TYPE_STR_TREES("TREES");
const std::string ObjectData::TYPE_STR_UNIT_MEDIC1("UNIT_MEDIC1");
const std::string ObjectData::TYPE_STR_UNIT_SCOUT1("UNIT_SCOUT1");
const std::string ObjectData::TYPE_STR_UNIT_SOLDIER1("UNIT_SOLDIER1");
const std::string ObjectData::TYPE_STR_UNIT_SOLDIER2("UNIT_SOLDIER2");
const std::string ObjectData::TYPE_STR_UNIT_SPAWNER1("UNIT_SPAWNER1");
const std::string ObjectData::TYPE_STR_UNIT_SPAWNER2("UNIT_SPAWNER2");
const std::string ObjectData::TYPE_STR_UNIT_WORKER1("UNIT_WORKER1");
const std::string ObjectData::TYPE_STR_WALL("WALL");
const std::string ObjectData::TYPE_STR_WALL_GATE("WALL_GATE");

const GameObjectTypeId ObjectData::TYPE_NULL = 0;

const GameObjectTypeId ObjectData::TYPE_BARRACKS = h{}(TYPE_STR_BARRACKS);
const GameObjectTypeId ObjectData::TYPE_BASE = h{}(TYPE_STR_BASE);
const GameObjectTypeId ObjectData::TYPE_BASE_SPOT = h{}(TYPE_STR_BASE_SPOT);
const GameObjectTypeId ObjectData::TYPE_BLOBS = h{}(TYPE_STR_BLOBS);
const GameObjectTypeId ObjectData::TYPE_BUNKER = h{}(TYPE_STR_BUNKER);
const GameObjectTypeId ObjectData::TYPE_DEFENSIVE_TOWER = h{}(TYPE_STR_DEFENSIVE_TOWER);
const GameObjectTypeId ObjectData::TYPE_DIAMONDS = h{}(TYPE_STR_DIAMONDS);
const GameObjectTypeId ObjectData::TYPE_HOSPITAL = h{}(TYPE_STR_HOSPITAL);
const GameObjectTypeId ObjectData::TYPE_LOOTBOX = h{}(TYPE_STR_LOOTBOX);
const GameObjectTypeId ObjectData::TYPE_MINI_UNIT1 = h{}(TYPE_STR_MINI_UNIT1);
const GameObjectTypeId ObjectData::TYPE_MINI_UNIT2 = h{}(TYPE_STR_MINI_UNIT2);
const GameObjectTypeId ObjectData::TYPE_MOUNTAINS = h{}(TYPE_STR_MOUNTAINS);
const GameObjectTypeId ObjectData::TYPE_PRACTICE_TARGET = h{}(TYPE_STR_PRACTICE_TARGET);
const GameObjectTypeId ObjectData::TYPE_RADAR_STATION = h{}(TYPE_STR_RADAR_STATION);
const GameObjectTypeId ObjectData::TYPE_RADAR_TOWER = h{}(TYPE_STR_RADAR_TOWER);
const GameObjectTypeId ObjectData::TYPE_RESEARCH_CENTER = h{}(TYPE_STR_RESEARCH_CENTER);
const GameObjectTypeId ObjectData::TYPE_RES_GEN_ENERGY = h{}(TYPE_STR_RES_GEN_ENERGY);
const GameObjectTypeId ObjectData::TYPE_RES_GEN_ENERGY_SOLAR = h{}(TYPE_STR_RES_GEN_ENERGY_SOLAR);
const GameObjectTypeId ObjectData::TYPE_RES_GEN_MATERIAL = h{}(TYPE_STR_RES_GEN_MATERIAL);
const GameObjectTypeId ObjectData::TYPE_RES_GEN_MATERIAL_EXTRACT = h{}(TYPE_STR_RES_GEN_MATERIAL_EXTRACT);
const GameObjectTypeId ObjectData::TYPE_RES_STORAGE_BLOBS = h{}(TYPE_STR_RES_STORAGE_BLOBS);
const GameObjectTypeId ObjectData::TYPE_RES_STORAGE_DIAMONDS = h{}(TYPE_STR_RES_STORAGE_DIAMONDS);
const GameObjectTypeId ObjectData::TYPE_RES_STORAGE_ENERGY = h{}(TYPE_STR_RES_STORAGE_ENERGY);
const GameObjectTypeId ObjectData::TYPE_RES_STORAGE_MATERIAL = h{}(TYPE_STR_RES_STORAGE_MATERIAL);
const GameObjectTypeId ObjectData::TYPE_ROCKS = h{}(TYPE_STR_ROCKS);
const GameObjectTypeId ObjectData::TYPE_SPAWN_TOWER = h{}(TYPE_STR_SPAWN_TOWER);
const GameObjectTypeId ObjectData::TYPE_TEMPLE = h{}(TYPE_STR_TEMPLE);
const GameObjectTypeId ObjectData::TYPE_TRADING_POST = h{}(TYPE_STR_TRADING_POST);
const GameObjectTypeId ObjectData::TYPE_TREES = h{}(TYPE_STR_TREES);
const GameObjectTypeId ObjectData::TYPE_UNIT_MEDIC1 = h{}(TYPE_STR_UNIT_MEDIC1);
const GameObjectTypeId ObjectData::TYPE_UNIT_SCOUT1 = h{}(TYPE_STR_UNIT_SCOUT1);
const GameObjectTypeId ObjectData::TYPE_UNIT_SOLDIER1 = h{}(TYPE_STR_UNIT_SOLDIER1);
const GameObjectTypeId ObjectData::TYPE_UNIT_SOLDIER2 = h{}(TYPE_STR_UNIT_SOLDIER2);
const GameObjectTypeId ObjectData::TYPE_UNIT_SPAWNER1 = h{}(TYPE_STR_UNIT_SPAWNER1);
const GameObjectTypeId ObjectData::TYPE_UNIT_SPAWNER2 = h{}(TYPE_STR_UNIT_SPAWNER2);
const GameObjectTypeId ObjectData::TYPE_UNIT_WORKER1 = h{}(TYPE_STR_UNIT_WORKER1);
const GameObjectTypeId ObjectData::TYPE_WALL = h{}(TYPE_STR_WALL);
const GameObjectTypeId ObjectData::TYPE_WALL_GATE = h{}(TYPE_STR_WALL_GATE);

const std::unordered_map<GameObjectTypeId, std::string> ObjectData::TYPE_STR_MAP =
    {
        { ObjectData::TYPE_BARRACKS, TYPE_STR_BARRACKS},
        { ObjectData::TYPE_BASE, TYPE_STR_BASE},
        { ObjectData::TYPE_BASE_SPOT, TYPE_STR_BASE_SPOT},
        { ObjectData::TYPE_BUNKER, TYPE_STR_BUNKER},
        { ObjectData::TYPE_DEFENSIVE_TOWER, TYPE_STR_DEFENSIVE_TOWER },
        { ObjectData::TYPE_HOSPITAL, TYPE_STR_HOSPITAL },
        { ObjectData::TYPE_LOOTBOX, TYPE_STR_LOOTBOX },
        { ObjectData::TYPE_MINI_UNIT1, TYPE_STR_MINI_UNIT1 },
        { ObjectData::TYPE_MINI_UNIT2, TYPE_STR_MINI_UNIT2 },
        { ObjectData::TYPE_MOUNTAINS, TYPE_STR_MOUNTAINS },
        { ObjectData::TYPE_PRACTICE_TARGET, TYPE_STR_PRACTICE_TARGET },
        { ObjectData::TYPE_RADAR_STATION, TYPE_STR_RADAR_STATION },
        { ObjectData::TYPE_RADAR_TOWER, TYPE_STR_RADAR_TOWER },
        { ObjectData::TYPE_RESEARCH_CENTER, TYPE_STR_RESEARCH_CENTER },
        { ObjectData::TYPE_RES_GEN_ENERGY, TYPE_STR_RES_GEN_ENERGY },
        { ObjectData::TYPE_RES_GEN_ENERGY_SOLAR, TYPE_STR_RES_GEN_ENERGY_SOLAR },
        { ObjectData::TYPE_RES_GEN_MATERIAL, TYPE_STR_RES_GEN_MATERIAL },
        { ObjectData::TYPE_RES_GEN_MATERIAL_EXTRACT, TYPE_STR_RES_GEN_MATERIAL_EXTRACT },
        { ObjectData::TYPE_RES_STORAGE_BLOBS, TYPE_STR_RES_STORAGE_BLOBS },
        { ObjectData::TYPE_RES_STORAGE_DIAMONDS, TYPE_STR_RES_STORAGE_DIAMONDS },
        { ObjectData::TYPE_RES_STORAGE_ENERGY, TYPE_STR_RES_STORAGE_ENERGY },
        { ObjectData::TYPE_RES_STORAGE_MATERIAL, TYPE_STR_RES_STORAGE_MATERIAL },
        { ObjectData::TYPE_ROCKS, TYPE_STR_ROCKS },
        { ObjectData::TYPE_SPAWN_TOWER, TYPE_STR_SPAWN_TOWER },
        { ObjectData::TYPE_TEMPLE, TYPE_STR_TEMPLE },
        { ObjectData::TYPE_TREES, TYPE_STR_TREES },
        { ObjectData::TYPE_TRADING_POST, TYPE_STR_TRADING_POST },
        { ObjectData::TYPE_UNIT_MEDIC1, TYPE_STR_UNIT_MEDIC1 },
        { ObjectData::TYPE_UNIT_SCOUT1, TYPE_STR_UNIT_SCOUT1 },
        { ObjectData::TYPE_UNIT_SOLDIER1, TYPE_STR_UNIT_SOLDIER1 },
        { ObjectData::TYPE_UNIT_SOLDIER2, TYPE_STR_UNIT_SOLDIER2 },
        { ObjectData::TYPE_UNIT_SPAWNER1, TYPE_STR_UNIT_SPAWNER1 },
        { ObjectData::TYPE_UNIT_SPAWNER2, TYPE_STR_UNIT_SPAWNER2 },
        { ObjectData::TYPE_UNIT_WORKER1, TYPE_STR_UNIT_WORKER1 },
        { ObjectData::TYPE_WALL, TYPE_STR_WALL },
        { ObjectData::TYPE_WALL_GATE, TYPE_STR_WALL_GATE }
};


std::string ObjectData::GetObjectTypeStr(const GameObjectTypeId type)
{
    static const std::string noStr;

    auto it = TYPE_STR_MAP.find(type);

    if(it != TYPE_STR_MAP.end())
        return it->second;
    else
        return noStr;
}

const std::unordered_map<GameObjectTypeId, std::string> ObjectData::TITLES =
    {
        { ObjectData::TYPE_BARRACKS, "BARRACKS"},
        { ObjectData::TYPE_BASE, "BASE"},
        { ObjectData::TYPE_BASE_SPOT, "BASE SPOT"},
        { ObjectData::TYPE_BUNKER, "BUNKER"},
        { ObjectData::TYPE_DEFENSIVE_TOWER, "DEFENSIVE TOWER"},
        { ObjectData::TYPE_HOSPITAL, "HOSPITAL"},
        { ObjectData::TYPE_LOOTBOX, "LOOT BOX"},
        { ObjectData::TYPE_MINI_UNIT1, "MINI UNIT 1"},
        { ObjectData::TYPE_MINI_UNIT2, "MINI UNIT 2"},
        { ObjectData::TYPE_MOUNTAINS, "MOUNTAINS"},
        { ObjectData::TYPE_PRACTICE_TARGET, "PRACTICE TARGET"},
        { ObjectData::TYPE_RADAR_STATION, "RADAR STATION"},
        { ObjectData::TYPE_RADAR_TOWER, "RADAR TOWER"},
        { ObjectData::TYPE_RESEARCH_CENTER, "RESEARCH CENTER"},
        { ObjectData::TYPE_RES_GEN_ENERGY, "ENERGY GENERATOR"},
        { ObjectData::TYPE_RES_GEN_ENERGY_SOLAR, "SOLAR PANELS"},
        { ObjectData::TYPE_RES_GEN_MATERIAL, "MATERIAL GENERATOR"},
        { ObjectData::TYPE_RES_GEN_MATERIAL_EXTRACT, "MATERIAL EXTRACTOR"},
        { ObjectData::TYPE_RES_STORAGE_BLOBS, "BLOBS STORAGE"},
        { ObjectData::TYPE_RES_STORAGE_DIAMONDS, "DIAMONDS STORAGE"},
        { ObjectData::TYPE_RES_STORAGE_ENERGY, "ENERGY STORAGE"},
        { ObjectData::TYPE_RES_STORAGE_MATERIAL, "MATERIAL STORAGE"},
        { ObjectData::TYPE_ROCKS, "ROCKS"},
        { ObjectData::TYPE_SPAWN_TOWER, "SPAWNING TOWER"},
        { ObjectData::TYPE_TEMPLE, "TEMPLE"},
        { ObjectData::TYPE_TRADING_POST, "TRADING POST"},
        { ObjectData::TYPE_TREES, "TREES"},
        { ObjectData::TYPE_UNIT_MEDIC1, "MEDIC"},
        { ObjectData::TYPE_UNIT_SCOUT1, "SCOUT"},
        { ObjectData::TYPE_UNIT_SOLDIER1, "SOLDIER"},
        { ObjectData::TYPE_UNIT_SOLDIER2, "SOLDIER"},
        { ObjectData::TYPE_UNIT_SPAWNER1, "MINI SPAWNER"},
        { ObjectData::TYPE_UNIT_SPAWNER2, "SPAWNER"},
        { ObjectData::TYPE_UNIT_WORKER1, "WORKER"},
        { ObjectData::TYPE_WALL, "WALL"},
        { ObjectData::TYPE_WALL_GATE, "GATE"}
};

const std::unordered_map<GameObjectTypeId, std::string> ObjectData::DESCRIPTIONS =
{
        { ObjectData::TYPE_BARRACKS, "A structure that creates soldier units."},
        { ObjectData::TYPE_BASE, "A control center. It can create worker units."
                                "You need to defend it if you don't want to lose a territory."},
        { ObjectData::TYPE_BASE_SPOT, "This represents where a faction base will be placed. "
                                     "Numbers identify the factions in a map."},
        { ObjectData::TYPE_BUNKER, "A simple defense structure."},
        { ObjectData::TYPE_DEFENSIVE_TOWER, "A basic defensive tower."},
        { ObjectData::TYPE_HOSPITAL, "A structure that creates medics and that can heal units."},
        { ObjectData::TYPE_LOOTBOX, "A loot box that can be collected by a unit to obtain various resources."},
        { ObjectData::TYPE_MINI_UNIT1, "Basic mini units that explode when they reach their target and"
                                      " there's an enemy nearby."},
        { ObjectData::TYPE_MINI_UNIT2, "Mini units that shoot enemies close to their target position."},
        { ObjectData::TYPE_MOUNTAINS, "Some mountains"},
        { ObjectData::TYPE_PRACTICE_TARGET, "A practice target.\nIt can be used to train your units "
                                           "and to improve their attack skills."},
        { ObjectData::TYPE_RADAR_STATION, "A powerful radar that can show a big portion of the map."},
        { ObjectData::TYPE_RADAR_TOWER, "A compact radar that can show a small portion of the map."},
        { ObjectData::TYPE_RESEARCH_CENTER, "A building that will allow you to research and to develop new technologies and improvements."},
        { ObjectData::TYPE_RES_GEN_ENERGY, "A generator of energy.\nConnect it to your base to produce energy."},
        { ObjectData::TYPE_RES_GEN_ENERGY_SOLAR, "A solar panel.\nConnect it to your base to produce energy."},
        { ObjectData::TYPE_RES_GEN_MATERIAL, "A generator of material.\nConnect it to your base to mine material."},
        { ObjectData::TYPE_RES_GEN_MATERIAL_EXTRACT, "A mine that can extract material from the ground.\n"
                                                    "Connect it to your base to produce material."},
        { ObjectData::TYPE_RES_STORAGE_BLOBS, "Storage unit that can contain 100 units of blobs."},
        { ObjectData::TYPE_RES_STORAGE_DIAMONDS, "Storage unit that can contain 150 units of diamonds."},
        { ObjectData::TYPE_RES_STORAGE_ENERGY, "Storage unit that can contain 500 units of energy."},
        { ObjectData::TYPE_RES_STORAGE_MATERIAL, "Storage unit that can contain 250 units of material."},
        { ObjectData::TYPE_ROCKS, "Some rocks."},
        { ObjectData::TYPE_SPAWN_TOWER, "A structure that can generate up to 12 squads of automated mini units."},
        { ObjectData::TYPE_TEMPLE, "An ancient temple that can be explored."},
        { ObjectData::TYPE_TREES, "A single tree which will slowly grow into a forest."},
        { ObjectData::TYPE_TRADING_POST, "This structure allows you to buy and to sell resources."},
        { ObjectData::TYPE_UNIT_MEDIC1, "This unit is specialized in healing other units.\nIt's a bit slow, but effective."},
        { ObjectData::TYPE_UNIT_SCOUT1, "A light and fast unit ideal for exploring, but not for fighting."},
        { ObjectData::TYPE_UNIT_SOLDIER1, "A basic soldier unit.\nUseful for defense and exploration."},
        { ObjectData::TYPE_UNIT_SOLDIER2, "A slow, but versatile unit."},
        { ObjectData::TYPE_UNIT_SPAWNER1, "A smaller spawner unit that can generate up to 6 squads of automated mini units."},
        { ObjectData::TYPE_UNIT_SPAWNER2, "A spawner unit that can generate up to 8 squads of automated mini units."},
        { ObjectData::TYPE_UNIT_WORKER1, "A basic worker unit.\nIt is specialized in construction and conquest."},
        { ObjectData::TYPE_WALL, "A defensive wall."},
        { ObjectData::TYPE_WALL_GATE, "A gate that can be controlled to open a passage through a defensive wall."}
};

// -- OBJECT CATEGORY --
const GameObjectCategoryId ObjectData::CAT_NULL = 0;

const GameObjectCategoryId ObjectData::CAT_COLLECTABLE = h{}("COLLECTABLE");
const GameObjectCategoryId ObjectData::CAT_MINI_UNIT = h{}("MINI_UNIT");
const GameObjectCategoryId ObjectData::CAT_RES_GENERATOR = h{}("RES_GEN");
const GameObjectCategoryId ObjectData::CAT_RES_STORAGE = h{}("RES_STORAGE");
const GameObjectCategoryId ObjectData::CAT_SCENE_OBJ = h{}("SCENE_OBJ");
const GameObjectCategoryId ObjectData::CAT_STRUCTURE = h{}("STRUCTURE");
const GameObjectCategoryId ObjectData::CAT_UNIT = h{}("UNIT");


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
    // UNIT
    "SPEED",
    "CONSTRUCTION",
    "CONQUEST",
    "HEALING RANGE",
    "HEALING POWER",
    "SPAWNING",
    // RESOURCE STORAGE
    "STORAGE",
    // WEAPON
    "ATTACK ACCURACY",
    "ATTACK POWER",
    "ATTACK RANGE",
};

const ObjectData ObjectData::NullObj({}, {}, {}, nullptr, ObjectData::TYPE_NULL, ObjectData::CAT_NULL,
                                     OC_NULL, OCAT_UNDEFINED, WeaponData::TYPE_NULL, 0, 0);

unsigned int ObjectData::GetIconTexId(PlayerFaction f) const
{
    if(f < mIconTexIds.size())
        return mIconTexIds[f];
    else
        return mIconTexIds.back();
}

} // namespace game
