#include "GameObjects/ObjectsDataRegistry.h"

#include "GameData.h"
#include "GameObject.h"

namespace game
{

ObjectsDataRegistry::ObjectsDataRegistry()
{
    InitObjectData();
}


const ObjectData & ObjectsDataRegistry::GetObjectData(GameObjectTypeId type) const
{
    auto res = mData.find(type);

    if(res != mData.end())
        return res->second;
    else
        return ObjectData::NullObj;
}

void ObjectsDataRegistry::InitObjectData()
{
    mData.emplace(GameObject::TYPE_BARRACKS,
                  ObjectData({ {OBJ_ATT_ENERGY, 5}, {OBJ_ATT_VIEW_RANGE, 4},
                               {OBJ_ATT_REGENERATION, 5}, {OBJ_ATT_RESISTANCE, 4},
                               {OBJ_ATT_SHIELD, 3}, {OBJ_ATT_CONSTRUCTION, 5}, {OBJ_ATT_HEALTH, 5} },
                             { 500, 500, 0, 0 },
                             { ID_STRUCT_BARRACKS_F1, ID_STRUCT_BARRACKS_F2,
                               ID_STRUCT_BARRACKS_F3, ID_STRUCT_BARRACKS},  SpriteFileStructures,
                             GameObject::TYPE_BARRACKS, GameObject::CAT_STRUCTURE,
                             OCS_BARRACKS, OCAT_GENERIC, 2, 2));

    mData.emplace(GameObject::TYPE_BASE,
                  ObjectData({ {OBJ_ATT_ENERGY, 6}, {OBJ_ATT_VIEW_RANGE, 6}, {OBJ_ATT_FIRE_POWER, 5},
                               {OBJ_ATT_FIRE_ACCURACY, 4}, {OBJ_ATT_FIRE_RANGE, 5}, {OBJ_ATT_REGENERATION, 5},
                               {OBJ_ATT_RESISTANCE, 6}, {OBJ_ATT_SHIELD, 6}, {OBJ_ATT_CONSTRUCTION, 6},
                               {OBJ_ATT_HEALTH, 8} },
                             { 1000, 1000, 0, 0 },
                             { ID_STRUCT_BASE_L1_F1, ID_STRUCT_BASE_L1_F2, ID_STRUCT_BASE_L1_F3,
                               ID_STRUCT_BASE_L1}, SpriteFileStructures,
                             GameObject::TYPE_BASE, GameObject::CAT_STRUCTURE,
                             OCS_BASE, OCAT_GENERIC, 3, 3));

    mData.emplace(GameObject::TYPE_BASE_SPOT,
                  ObjectData({}, {}, { ID_STRUCT_BASE_L1 }, SpriteFileStructures,
                             GameObject::TYPE_BASE_SPOT, GameObject::CAT_STRUCTURE,
                             OCS_BASE, OCAT_GENERIC, 3, 3));

    mData.emplace(GameObject::TYPE_BLOBS,
                  ObjectData({ {OBJ_ATT_ENERGY, 1}, {OBJ_ATT_HEALTH, 1} }, {}, { BLOBS_1 },
                             SpriteCollectiblesFile, GameObject::TYPE_BLOBS, GameObject::CAT_COLLECTABLE,
                             OCO_COLLECTABLE, OCAT_UNDEFINED, 1, 1));

    mData.emplace(GameObject::TYPE_BUNKER,
                  ObjectData({ {OBJ_ATT_ENERGY, 4}, {OBJ_ATT_VIEW_RANGE, 3}, {OBJ_ATT_FIRE_POWER, 3},
                               {OBJ_ATT_FIRE_ACCURACY, 4}, {OBJ_ATT_FIRE_RANGE, 3}, {OBJ_ATT_REGENERATION, 4},
                               {OBJ_ATT_RESISTANCE, 5}, {OBJ_ATT_SHIELD, 5}, {OBJ_ATT_HEALTH, 7} },
                             { 150, 200, 0, 0 },
                             { ID_STRUCT_BUNKER_F1, ID_STRUCT_BUNKER_F2,
                               ID_STRUCT_BUNKER_F3, ID_STRUCT_BUNKER }, SpriteFileStructures,
                             GameObject::TYPE_BUNKER, GameObject::CAT_STRUCTURE,
                             OCS_TOWER, OCAT_DEFENSE, 1, 1));

    mData.emplace(GameObject::TYPE_DEFENSIVE_TOWER,
                  ObjectData({ {OBJ_ATT_ENERGY, 5}, {OBJ_ATT_VIEW_RANGE, 4}, {OBJ_ATT_FIRE_POWER, 4},
                               {OBJ_ATT_FIRE_ACCURACY, 4}, {OBJ_ATT_FIRE_RANGE, 5}, {OBJ_ATT_REGENERATION, 5},
                               {OBJ_ATT_RESISTANCE, 5}, {OBJ_ATT_SHIELD, 5}, {OBJ_ATT_HEALTH, 7} },
                             { 250, 300, 0, 0 },
                             { ID_STRUCT_DTOWER_L1_F1, ID_STRUCT_DTOWER_L1_F2,
                               ID_STRUCT_DTOWER_L1_F3, ID_STRUCT_DTOWER_L1 }, SpriteFileStructures,
                             GameObject::TYPE_DEFENSIVE_TOWER, GameObject::CAT_STRUCTURE,
                             OCS_TOWER, OCAT_DEFENSE, 1, 1));

    mData.emplace(GameObject::TYPE_DIAMONDS,
                  ObjectData({ {OBJ_ATT_ENERGY, 1}, {OBJ_ATT_HEALTH, 1} }, {}, { DIAMONDS_1 },
                             SpriteCollectiblesFile, GameObject::TYPE_DIAMONDS, GameObject::CAT_COLLECTABLE,
                             OCO_COLLECTABLE, OCAT_UNDEFINED, 1, 1));

    mData.emplace(GameObject::TYPE_HOSPITAL,
                  ObjectData({ {OBJ_ATT_ENERGY, 5}, {OBJ_ATT_VIEW_RANGE, 4}, {OBJ_ATT_REGENERATION, 5},
                               {OBJ_ATT_RESISTANCE, 3}, {OBJ_ATT_SHIELD, 2}, {OBJ_ATT_HEALING_RANGE, 5},
                               {OBJ_ATT_HEALING_POWER, 6}, {OBJ_ATT_CONSTRUCTION, 4}, {OBJ_ATT_HEALTH, 5} },
                             { 1000, 500, 0, 0 },
                             { ID_STRUCT_HOSPITAL_F1, ID_STRUCT_HOSPITAL_F2,
                               ID_STRUCT_HOSPITAL_F3, ID_STRUCT_HOSPITAL}, SpriteFileStructures,
                             GameObject::TYPE_HOSPITAL, GameObject::CAT_STRUCTURE,
                             OCS_HOSPITAL, OCAT_GENERIC, 2, 2));

    mData.emplace(GameObject::TYPE_LOOTBOX,
                  ObjectData({ {OBJ_ATT_ENERGY, 1}, {OBJ_ATT_HEALTH, 1}}, {}, { IND_LOOTBOX },
                             SpriteCollectiblesFile, GameObject::TYPE_LOOTBOX, GameObject::CAT_COLLECTABLE,
                             OCO_COLLECTABLE, OCAT_UNDEFINED, 1, 1));

    mData.emplace(GameObject::TYPE_MINI_UNIT1,
                  ObjectData({ {OBJ_ATT_ENERGY, 4}, {OBJ_ATT_VIEW_RANGE, 5}, {OBJ_ATT_FIRE_POWER, 3},
                               {OBJ_ATT_FIRE_ACCURACY, 4}, {OBJ_ATT_FIRE_RANGE, 3}, {OBJ_ATT_REGENERATION, 3},
                               {OBJ_ATT_RESISTANCE, 3}, {OBJ_ATT_SHIELD, 2},  {OBJ_ATT_SPEED, 8},
                               {OBJ_ATT_HEALTH, 5} },
                             { 20, 20, 0, 0 },
                             { SID_MUNIT_01_5X_F1, SID_MUNIT_01_5X_F2, SID_MUNIT_01_5X_F3 }, SpriteFileMiniUnits,
                             GameObject::TYPE_MINI_UNIT1, GameObject::CAT_MINI_UNIT,
                             OCMU_SOLDIER, OCAT_MINI_UNIT, 1, 1));

    mData.emplace(GameObject::TYPE_MOUNTAINS,
                  ObjectData({ {OBJ_ATT_ENERGY, 1}, {OBJ_ATT_HEALTH, 9} }, {}, { ID_SCENE_MOUNTAIN_1 },
                             SpriteFileSceneElements, GameObject::TYPE_MOUNTAINS, GameObject::CAT_SCENE_OBJ,
                             OCO_SCENE, OCAT_UNDEFINED, 2, 2));

    mData.emplace(GameObject::TYPE_PRACTICE_TARGET,
                  ObjectData({ {OBJ_ATT_ENERGY, 1}, {OBJ_ATT_VIEW_RANGE, 2}, {OBJ_ATT_REGENERATION, 5},
                               {OBJ_ATT_RESISTANCE, 8}, {OBJ_ATT_SHIELD, 8}, {OBJ_ATT_HEALTH, 9} },
                             { 100, 250, 0, 0 },
                             { ID_PRACTICE_TARGET }, SpriteFileStructures,
                             GameObject::TYPE_PRACTICE_TARGET, GameObject::CAT_STRUCTURE,
                             OCS_TARGET, OCAT_GENERIC, 1, 1));

    mData.emplace(GameObject::TYPE_RADAR_STATION,
                  ObjectData({ {OBJ_ATT_ENERGY, 5}, {OBJ_ATT_VIEW_RANGE, 8}, {OBJ_ATT_REGENERATION, 4},
                               {OBJ_ATT_RESISTANCE, 5}, {OBJ_ATT_SHIELD, 3}, {OBJ_ATT_HEALTH, 4} },
                             { 250, 150, 0, 0 },
                             { ID_STRUCT_RADAR_F1, ID_STRUCT_RADAR_F2, ID_STRUCT_RADAR_F3,
                               ID_STRUCT_RADAR }, SpriteFileStructures,
                             GameObject::TYPE_RADAR_STATION, GameObject::CAT_STRUCTURE,
                              OCS_RADAR, OCAT_TECHNOLOGY, 2, 2));

    mData.emplace(GameObject::TYPE_RADAR_TOWER,
                  ObjectData({ {OBJ_ATT_ENERGY, 3}, {OBJ_ATT_VIEW_RANGE, 6}, {OBJ_ATT_REGENERATION, 3},
                               {OBJ_ATT_RESISTANCE, 4}, {OBJ_ATT_SHIELD, 2}, {OBJ_ATT_HEALTH, 3} },
                             { 150, 100, 0, 0 },
                             { ID_STRUCT_RADAR_TOWER_F1, ID_STRUCT_RADAR_TOWER_F2,
                               ID_STRUCT_RADAR_TOWER_F3, ID_STRUCT_RADAR_TOWER }, SpriteFileStructures,
                             GameObject::TYPE_RADAR_STATION, GameObject::CAT_STRUCTURE,
                             OCS_RADAR, OCAT_TECHNOLOGY, 1, 1));

    mData.emplace(GameObject::TYPE_RESEARCH_CENTER,
                  ObjectData({ {OBJ_ATT_ENERGY, 5}, {OBJ_ATT_VIEW_RANGE, 4}, {OBJ_ATT_REGENERATION, 4},
                               {OBJ_ATT_RESISTANCE, 3}, {OBJ_ATT_SHIELD, 2}, {OBJ_ATT_HEALTH, 4} },
                             { 1000, 500, 100, 100 },
                             { ID_STRUCT_RESEARCH_CENTER_F1, ID_STRUCT_RESEARCH_CENTER_F2,
                              ID_STRUCT_RESEARCH_CENTER_F3, ID_STRUCT_RESEARCH_CENTER }, SpriteFileStructures,
                             GameObject::TYPE_RESEARCH_CENTER, GameObject::CAT_STRUCTURE,
                             OCS_RESEARCH, OCAT_TECHNOLOGY, 2, 2));

    mData.emplace(GameObject::TYPE_RES_GEN_ENERGY,
                  ObjectData({ {OBJ_ATT_ENERGY, 9}, {OBJ_ATT_VIEW_RANGE, 4}, {OBJ_ATT_REGENERATION, 3},
                               {OBJ_ATT_RESISTANCE, 2}, {OBJ_ATT_SHIELD, 1}, {OBJ_ATT_HEALTH, 5} },
                             { 0, 0, 0, 0 },
                             { ID_STRUCT_GEN_ENERGY_F1, ID_STRUCT_GEN_ENERGY_F2,
                               ID_STRUCT_GEN_ENERGY_F3, ID_STRUCT_GEN_ENERGY }, SpriteFileStructures,
                              GameObject::TYPE_RES_GEN_ENERGY, GameObject::CAT_RES_GENERATOR,
                             OCS_GENERATOR, OCAT_RESOURCES, 2, 2));

    mData.emplace(GameObject::TYPE_RES_GEN_ENERGY_SOLAR,
                  ObjectData({ {OBJ_ATT_ENERGY, 4}, {OBJ_ATT_VIEW_RANGE, 2}, {OBJ_ATT_REGENERATION, 2},
                               {OBJ_ATT_RESISTANCE, 2}, {OBJ_ATT_SHIELD, 2}, {OBJ_ATT_HEALTH, 4} },
                             { 250, 250, 0, 0 },
                             { ID_STRUCT_SOLAR_PANEL_F1, ID_STRUCT_SOLAR_PANEL_F2,
                               ID_STRUCT_SOLAR_PANEL_F3, ID_STRUCT_SOLAR_PANEL }, SpriteFileStructures,
                             GameObject::TYPE_RES_GEN_ENERGY_SOLAR, GameObject::CAT_RES_GENERATOR,
                             OCS_GENERATOR, OCAT_RESOURCES, 1, 1));

    mData.emplace(GameObject::TYPE_RES_GEN_MATERIAL,
                  ObjectData({ {OBJ_ATT_ENERGY, 9}, {OBJ_ATT_VIEW_RANGE, 4}, {OBJ_ATT_REGENERATION, 3},
                               {OBJ_ATT_RESISTANCE, 2}, {OBJ_ATT_SHIELD, 1}, {OBJ_ATT_HEALTH, 5} },
                             { 0, 0, 0, 0 },
                             { ID_STRUCT_GEN_MATERIAL_F1, ID_STRUCT_GEN_MATERIAL_F2,
                               ID_STRUCT_GEN_MATERIAL_F3, ID_STRUCT_GEN_MATERIAL}, SpriteFileStructures,
                             GameObject::TYPE_RES_GEN_MATERIAL, GameObject::CAT_RES_GENERATOR,
                             OCS_GENERATOR, OCAT_RESOURCES, 2, 2));

    mData.emplace(GameObject::TYPE_RES_GEN_MATERIAL_EXTRACT,
                  ObjectData({ {OBJ_ATT_ENERGY, 4}, {OBJ_ATT_VIEW_RANGE, 2}, {OBJ_ATT_REGENERATION, 2},
                               {OBJ_ATT_RESISTANCE, 2}, {OBJ_ATT_SHIELD, 2}, {OBJ_ATT_HEALTH, 4} },
                             { 250, 250, 10, 10 },
                             { ID_MATERIAL_EXTRACTOR_F1, ID_MATERIAL_EXTRACTOR_F2,
                               ID_MATERIAL_EXTRACTOR_F3, ID_MATERIAL_EXTRACTOR }, SpriteFileStructures,
                             GameObject::TYPE_RES_GEN_MATERIAL_EXTRACT, GameObject::CAT_RES_GENERATOR,
                             OCS_GENERATOR, OCAT_RESOURCES, 2, 2));

    mData.emplace(GameObject::TYPE_RES_STORAGE_BLOBS,
                  ObjectData({ {OBJ_ATT_ENERGY, 3}, {OBJ_ATT_VIEW_RANGE, 2}, {OBJ_ATT_REGENERATION, 2},
                               {OBJ_ATT_RESISTANCE, 3}, {OBJ_ATT_SHIELD, 4}, {OBJ_ATT_STORAGE, 4},
                               {OBJ_ATT_HEALTH, 4} },
                             { 100, 100, 0, 0 },
                             { ID_STRUCT_STORAGE_BLOBS_F1, ID_STRUCT_STORAGE_BLOBS_F2,
                               ID_STRUCT_STORAGE_BLOBS_F3, ID_STRUCT_STORAGE_BLOBS }, SpriteFileStructures,
                             GameObject::TYPE_RES_STORAGE_BLOBS, GameObject::CAT_RES_STORAGE,
                             OCS_STORAGE, OCAT_RESOURCES, 1, 1));

    mData.emplace(GameObject::TYPE_RES_STORAGE_DIAMONDS,
                  ObjectData({ {OBJ_ATT_ENERGY, 3}, {OBJ_ATT_VIEW_RANGE, 2}, {OBJ_ATT_REGENERATION, 2},
                               {OBJ_ATT_RESISTANCE, 3}, {OBJ_ATT_SHIELD, 4}, {OBJ_ATT_STORAGE, 4},
                               {OBJ_ATT_HEALTH, 4} },
                             { 100, 100, 0, 0 },
                             { ID_STRUCT_STORAGE_DIAMONDS_F1, ID_STRUCT_STORAGE_DIAMONDS_F2,
                               ID_STRUCT_STORAGE_DIAMONDS_F3, ID_STRUCT_STORAGE_DIAMONDS }, SpriteFileStructures,
                             GameObject::TYPE_RES_STORAGE_DIAMONDS, GameObject::CAT_RES_STORAGE,
                             OCS_STORAGE, OCAT_RESOURCES, 1, 1));

    mData.emplace(GameObject::TYPE_RES_STORAGE_ENERGY,
                  ObjectData({ {OBJ_ATT_ENERGY, 3}, {OBJ_ATT_VIEW_RANGE, 2}, {OBJ_ATT_REGENERATION, 2},
                               {OBJ_ATT_RESISTANCE, 3}, {OBJ_ATT_SHIELD, 4}, {OBJ_ATT_STORAGE, 6},
                               {OBJ_ATT_HEALTH, 5} },
                             { 100, 100, 0, 0 },
                             { ID_STRUCT_STORAGE_ENERGY_F1, ID_STRUCT_STORAGE_ENERGY_F2,
                               ID_STRUCT_STORAGE_ENERGY_F3, ID_STRUCT_STORAGE_ENERGY }, SpriteFileStructures,
                             GameObject::TYPE_RES_STORAGE_ENERGY, GameObject::CAT_RES_STORAGE,
                             OCS_STORAGE, OCAT_RESOURCES, 1, 1));

    mData.emplace(GameObject::TYPE_RES_STORAGE_MATERIAL,
                  ObjectData({ {OBJ_ATT_ENERGY, 3}, {OBJ_ATT_VIEW_RANGE, 2}, {OBJ_ATT_REGENERATION, 2},
                               {OBJ_ATT_RESISTANCE, 3}, {OBJ_ATT_SHIELD, 4}, {OBJ_ATT_STORAGE, 5},
                               {OBJ_ATT_HEALTH, 4} },
                             { 100, 100, 0, 0 },
                             { ID_STRUCT_STORAGE_MATERIAL_F1, ID_STRUCT_STORAGE_MATERIAL_F2,
                               ID_STRUCT_STORAGE_MATERIAL_F3, ID_STRUCT_STORAGE_MATERIAL }, SpriteFileStructures,
                             GameObject::TYPE_RES_STORAGE_MATERIAL, GameObject::CAT_RES_STORAGE,
                             OCS_STORAGE, OCAT_RESOURCES, 1, 1));

    mData.emplace(GameObject::TYPE_ROCKS,
                  ObjectData({ {OBJ_ATT_ENERGY, 1}, {OBJ_ATT_HEALTH, 6} }, {}, { ROCKS_ROW_1 }, SpriteRocksFile,
                             GameObject::TYPE_ROCKS, GameObject::CAT_SCENE_OBJ,
                             OCO_SCENE, OCAT_UNDEFINED, 1, 1));

    mData.emplace(GameObject::TYPE_SPAWN_TOWER,
                  ObjectData({ {OBJ_ATT_ENERGY, 6}, {OBJ_ATT_VIEW_RANGE, 4}, {OBJ_ATT_REGENERATION, 3},
                              {OBJ_ATT_RESISTANCE, 4}, {OBJ_ATT_SHIELD, 5}, {OBJ_ATT_HEALTH, 6},
                              {OBJ_ATT_SPAWNING, 6} },
                             { 750, 500, 50, 50 },
                             { ID_STRUCT_SPAWN_TOWER_F1, ID_STRUCT_SPAWN_TOWER_F2, ID_STRUCT_SPAWN_TOWER_F3,
                              ID_STRUCT_SPAWN_TOWER }, SpriteFileStructures,
                             GameObject::TYPE_SPAWN_TOWER, GameObject::CAT_STRUCTURE,
                             OCS_TOWER, OCAT_GENERIC, 2, 2));

    mData.emplace(GameObject::TYPE_TEMPLE,
                  ObjectData({ {OBJ_ATT_ENERGY, 4}, {OBJ_ATT_VIEW_RANGE, 4}, {OBJ_ATT_REGENERATION, 1},
                               {OBJ_ATT_RESISTANCE, 1}, {OBJ_ATT_SHIELD, 1}, {OBJ_ATT_HEALTH, 3} },
                             { 0, 0, 0, 0 },
                             { ID_STRUCT_TEMPLE_F1, ID_STRUCT_TEMPLE_F2, ID_STRUCT_TEMPLE_F3,
                               ID_STRUCT_TEMPLE}, SpriteFileStructures,
                             GameObject::TYPE_TEMPLE, GameObject::CAT_STRUCTURE,
                              OCS_RELICS, OCAT_GENERIC, 3, 3));

    // GENERIC
    mData.emplace(GameObject::TYPE_TRADING_POST,
                  ObjectData({ {OBJ_ATT_ENERGY, 5}, {OBJ_ATT_VIEW_RANGE, 4}, {OBJ_ATT_REGENERATION, 4},
                               {OBJ_ATT_RESISTANCE, 2}, {OBJ_ATT_SHIELD, 2}, {OBJ_ATT_HEALTH, 5} },
                             { 1000, 500, 0, 0 },
                             { ID_STRUCT_TRADING_POST_F1, ID_STRUCT_TRADING_POST_F2,
                              ID_STRUCT_TRADING_POST_F3, ID_STRUCT_TRADING_POST}, SpriteFileStructures,
                             GameObject::TYPE_TRADING_POST, GameObject::CAT_STRUCTURE,
                             OCS_TRADING, OCAT_GENERIC, 3, 3));

    mData.emplace(GameObject::TYPE_TREES,
                  ObjectData({ {OBJ_ATT_ENERGY, 1}, {OBJ_ATT_HEALTH, 1} }, {}, { TREE1_1T_1 }, SpriteFileTrees,
                             GameObject::TYPE_TREES, GameObject::CAT_SCENE_OBJ,
                             OCO_SCENE, OCAT_UNDEFINED, 1, 1));

    mData.emplace(GameObject::TYPE_UNIT_MEDIC1,
                  ObjectData({ {OBJ_ATT_ENERGY, 5}, {OBJ_ATT_VIEW_RANGE, 5}, {OBJ_ATT_REGENERATION, 6},
                               {OBJ_ATT_RESISTANCE, 4}, {OBJ_ATT_SHIELD, 4},  {OBJ_ATT_SPEED, 2},
                               {OBJ_ATT_HEALING_RANGE, 3}, {OBJ_ATT_HEALING_POWER, 5}, {OBJ_ATT_HEALTH, 6} } ,
                             { 500, 500, 0, 0 },
                             { SPR_UNIT_05_F1, SPR_UNIT_05_F2, SPR_UNIT_05_F3}, SpriteFileUnits,
                             GameObject::TYPE_UNIT_MEDIC1, GameObject::CAT_UNIT,
                             OCU_MEDIC, OCAT_UNIT, 1, 1));

    mData.emplace(GameObject::TYPE_UNIT_SCOUT1,
                  ObjectData({ {OBJ_ATT_ENERGY, 5}, {OBJ_ATT_VIEW_RANGE, 4}, {OBJ_ATT_FIRE_POWER, 1},
                               {OBJ_ATT_FIRE_ACCURACY, 2}, {OBJ_ATT_FIRE_RANGE, 2}, {OBJ_ATT_REGENERATION, 4},
                               {OBJ_ATT_RESISTANCE, 2}, {OBJ_ATT_SHIELD, 2}, {OBJ_ATT_SPEED, 5},
                               {OBJ_ATT_CONSTRUCTION, 2}, {OBJ_ATT_CONQUEST, 5}, {OBJ_ATT_HEALTH, 6} },
                             { 300, 300, 0, 0 },
                             { SPR_UNIT_04_F1, SPR_UNIT_04_F2, SPR_UNIT_04_F3}, SpriteFileUnits,
                             GameObject::TYPE_UNIT_SCOUT1, GameObject::CAT_UNIT,
                             OCU_SOLDIER, OCAT_UNIT, 1, 1));

    mData.emplace(GameObject::TYPE_UNIT_SOLDIER1,
                  ObjectData({ {OBJ_ATT_ENERGY, 3}, {OBJ_ATT_VIEW_RANGE, 5}, {OBJ_ATT_FIRE_POWER, 4},
                               {OBJ_ATT_FIRE_ACCURACY, 5}, {OBJ_ATT_FIRE_RANGE, 4}, {OBJ_ATT_REGENERATION, 3},
                               {OBJ_ATT_RESISTANCE, 3}, {OBJ_ATT_SHIELD, 2}, {OBJ_ATT_SPEED, 4},
                               {OBJ_ATT_CONQUEST, 3}, {OBJ_ATT_HEALTH, 4} },
                             { 200, 200, 0, 0 },
                             { SPR_UNIT_02_F1, SPR_UNIT_02_F2, SPR_UNIT_02_F3 }, SpriteFileUnits,
                             GameObject::TYPE_UNIT_SOLDIER1, GameObject::CAT_UNIT,
                             OCU_SOLDIER, OCAT_UNIT, 1, 1));

    mData.emplace(GameObject::TYPE_UNIT_SOLDIER2,
                  ObjectData({ {OBJ_ATT_ENERGY, 4}, {OBJ_ATT_VIEW_RANGE, 5}, {OBJ_ATT_FIRE_POWER, 5},
                               {OBJ_ATT_FIRE_ACCURACY, 4}, {OBJ_ATT_FIRE_RANGE, 5}, {OBJ_ATT_REGENERATION, 4},
                               {OBJ_ATT_RESISTANCE, 5}, {OBJ_ATT_SHIELD, 6}, {OBJ_ATT_SPEED, 3},
                               {OBJ_ATT_CONQUEST, 2}, {OBJ_ATT_HEALTH, 5} },
                             { 400, 400, 0, 0 },
                             { SPR_UNIT_03_F1, SPR_UNIT_03_F2, SPR_UNIT_03_F3 }, SpriteFileUnits,
                             GameObject::TYPE_UNIT_SOLDIER2, GameObject::CAT_UNIT,
                             OCU_SOLDIER, OCAT_UNIT, 1, 1));

    mData.emplace(GameObject::TYPE_UNIT_SPAWNER1,
                  ObjectData({ {OBJ_ATT_ENERGY, 5}, {OBJ_ATT_VIEW_RANGE, 5}, {OBJ_ATT_REGENERATION, 4},
                               {OBJ_ATT_RESISTANCE, 3}, {OBJ_ATT_SHIELD, 3},  {OBJ_ATT_SPEED, 4},
                               {OBJ_ATT_SPAWNING, 3}, {OBJ_ATT_HEALTH, 5} },
                             { 200, 200, 5, 5 },
                             { SPR_UNIT_06_F1, SPR_UNIT_06_F2, SPR_UNIT_06_F3 }, SpriteFileUnits,
                             GameObject::TYPE_UNIT_SPAWNER1, GameObject::CAT_UNIT,
                             OCU_SPAWNER, OCAT_UNIT, 1, 1));

    mData.emplace(GameObject::TYPE_UNIT_SPAWNER2,
                  ObjectData({ {OBJ_ATT_ENERGY, 6}, {OBJ_ATT_VIEW_RANGE, 6}, {OBJ_ATT_REGENERATION, 5},
                              {OBJ_ATT_RESISTANCE, 4}, {OBJ_ATT_SHIELD, 4},  {OBJ_ATT_SPEED, 3},
                              {OBJ_ATT_SPAWNING, 4}, {OBJ_ATT_HEALTH, 6} },
                             { 300, 300, 25, 25 },
                             { SPR_UNIT_07_F1, SPR_UNIT_07_F2, SPR_UNIT_07_F3 }, SpriteFileUnits,
                             GameObject::TYPE_UNIT_SPAWNER2, GameObject::CAT_UNIT,
                             OCU_SPAWNER, OCAT_UNIT, 1, 1));

    mData.emplace(GameObject::TYPE_UNIT_WORKER1,
                  ObjectData({ {OBJ_ATT_ENERGY, 4}, {OBJ_ATT_VIEW_RANGE, 6}, {OBJ_ATT_FIRE_POWER, 1},
                               {OBJ_ATT_FIRE_ACCURACY, 1}, {OBJ_ATT_FIRE_RANGE, 1}, {OBJ_ATT_REGENERATION, 4},
                               {OBJ_ATT_RESISTANCE, 3}, {OBJ_ATT_SHIELD, 2}, {OBJ_ATT_SPEED, 4},
                               {OBJ_ATT_CONSTRUCTION, 5}, {OBJ_ATT_CONQUEST, 3}, {OBJ_ATT_HEALTH, 5} } ,
                             { 150, 150, 0, 0 },
                             { SPR_UNIT_01_F1, SPR_UNIT_01_F2, SPR_UNIT_01_F3 }, SpriteFileUnits,
                             GameObject::TYPE_UNIT_WORKER1, GameObject::CAT_UNIT,
                             OCU_WORKER, OCAT_UNIT, 1, 1));

    mData.emplace(GameObject::TYPE_WALL,
                  ObjectData({ {OBJ_ATT_ENERGY, 1}, {OBJ_ATT_VIEW_RANGE, 2}, {OBJ_ATT_REGENERATION, 5},
                               {OBJ_ATT_RESISTANCE, 6}, {OBJ_ATT_SHIELD, 6}, {OBJ_ATT_HEALTH, 7} },
                             { 100, 100, 0, 0 },
                             { WALL_L1_F1_HORIZ, WALL_L1_F2_HORIZ, WALL_L1_F3_HORIZ },
                             SpriteFileWalls, GameObject::TYPE_WALL, GameObject::CAT_STRUCTURE,
                             OCS_WALL, OCAT_DEFENSE, 1, 1));

    mData.emplace(GameObject::TYPE_WALL_GATE,
                  ObjectData({ {OBJ_ATT_ENERGY, 3}, {OBJ_ATT_VIEW_RANGE, 2}, {OBJ_ATT_REGENERATION, 6},
                               {OBJ_ATT_RESISTANCE, 5}, {OBJ_ATT_SHIELD, 5}, {OBJ_ATT_HEALTH, 7} },
                             { 100, 100, 0, 0 },
                             { WALL_GATE_L1_F1_HORIZ_CLOSED, WALL_GATE_L1_F2_HORIZ_CLOSED,
                               WALL_GATE_L1_F3_HORIZ_CLOSED }, SpriteFileWalls,
                             GameObject::TYPE_WALL_GATE, GameObject::CAT_STRUCTURE,
                             OCS_WALL, OCAT_DEFENSE, 1, 1));
}

} // namespace game
