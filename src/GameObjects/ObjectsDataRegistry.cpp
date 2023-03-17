#include "GameObjects/ObjectsDataRegistry.h"

#include "GameData.h"
#include "Structure.h"
#include "Unit.h"

namespace game
{

ObjectsDataRegistry::ObjectsDataRegistry()
{
    InitStructures();
    InitUnits();
}

const ObjectData & ObjectsDataRegistry::GetStructure(PlayerFaction f, StructureType type) const
{
    auto res = mStructures[f].find(type);

    if(res != mStructures[f].end())
        return res->second;
    else
        return ObjectData::NullObj;
}

const ObjectData & ObjectsDataRegistry::GetUnit(PlayerFaction f, UnitType type) const
{
    auto res = mUnits[f].find(type);

    if(res != mUnits[f].end())
        return res->second;
    else
        return ObjectData::NullObj;

}

void ObjectsDataRegistry::InitStructures()
{
    // -- FACTION 1 --
    std::unordered_map<StructureType, ObjectData> & data1 = mStructures[FACTION_1];

    // target
    data1.emplace
    (   STRUCT_TARGET,
        ObjectData(std::vector<int>{ 8, 2, 0, 0, 0, 0, 5, 8, 8 },
                   std::vector<int>{ 50, 50, 0, 0 },
                   SpriteFileStructures, ID_PRACTICE_TARGET,
                   OCS_TARGET, OCAT_GENERIC, STRUCT_TARGET, 1, 1,
                   Structure::TITLES[STRUCT_TARGET],
                   Structure::DESCRIPTIONS[STRUCT_TARGET])
    );

    // radar
    data1.emplace
    (
        STRUCT_RADAR,
        ObjectData(std::vector<int>{ 4, 8, 0, 0, 0, 0, 4, 5, 3 },
                   std::vector<int>{ 100, 100, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_RADAR_F1,
                   OCS_RADAR, OCAT_TECHNOLOGY, STRUCT_RADAR, 2, 2,
                   Structure::TITLES[STRUCT_RADAR],
                   Structure::DESCRIPTIONS[STRUCT_RADAR])
    );

    // radar tower
    data1.emplace
    (
        STRUCT_RADAR_TOWER,
        ObjectData(std::vector<int>{ 3, 6, 0, 0, 0, 0, 3, 4, 2 },
                   std::vector<int>{ 100, 50, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_RADAR_TOWER_F1,
                   OCS_RADAR, OCAT_TECHNOLOGY, STRUCT_RADAR_TOWER, 1, 1,
                   Structure::TITLES[STRUCT_RADAR_TOWER],
                   Structure::DESCRIPTIONS[STRUCT_RADAR_TOWER])
    );

    // defensive tower
    data1.emplace
    (
        STRUCT_DEF_TOWER,
        ObjectData(std::vector<int>{ 5, 4, 2, 4, 4, 5, 5, 5, 5 },
                   std::vector<int>{ 150, 150, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_DTOWER_L1_F1,
                   OCS_TOWER, OCAT_DEFENSE, STRUCT_DEF_TOWER, 1, 1,
                   Structure::TITLES[STRUCT_DEF_TOWER],
                   Structure::DESCRIPTIONS[STRUCT_DEF_TOWER])
    );

    // material extractor
    data1.emplace
    (
        STRUCT_RES_GEN_MATERIAL_EXTRACTOR,
        ObjectData(std::vector<int>{ 4, 2, 0, 0, 0, 0, 2, 2, 2 },
                   std::vector<int>{ 150, 150, 10, 10 },
                   SpriteFileStructures, ID_MATERIAL_EXTRACTOR_F1,
                   OCS_GENERATOR, OCAT_RESOURCES, STRUCT_RES_GEN_MATERIAL_EXTRACTOR, 2, 2,
                   Structure::TITLES[STRUCT_RES_GEN_MATERIAL_EXTRACTOR],
                   Structure::DESCRIPTIONS[STRUCT_RES_GEN_MATERIAL_EXTRACTOR])
    );

    // solar panel
    data1.emplace
    (
        STRUCT_RES_GEN_SOLAR,
        ObjectData(std::vector<int>{ 4, 2, 0, 0, 0, 0, 2, 2, 2 },
                   std::vector<int>{ 150, 150, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_SOLAR_PANEL_F1,
                   OCS_GENERATOR, OCAT_RESOURCES, STRUCT_RES_GEN_SOLAR, 1, 1,
                   Structure::TITLES[STRUCT_RES_GEN_SOLAR],
                   Structure::DESCRIPTIONS[STRUCT_RES_GEN_SOLAR])
    );

    // storage energy
    data1.emplace
    (
        STRUCT_RES_STO_ENERGY,
        ObjectData(std::vector<int>{ 3, 2, 0, 0, 0, 0, 2, 3, 4 },
                   std::vector<int>{ 100, 100, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_STORAGE_ENERGY_F1,
                   OCS_STORAGE, OCAT_RESOURCES, STRUCT_RES_STO_ENERGY, 1, 1,
                   Structure::TITLES[STRUCT_RES_STO_ENERGY],
                   Structure::DESCRIPTIONS[STRUCT_RES_STO_ENERGY])
    );

    // storage material
    data1.emplace
    (
        STRUCT_RES_STO_MATERIAL,
        ObjectData(std::vector<int>{ 3, 2, 0, 0, 0, 0, 2, 3, 4 },
                   std::vector<int>{ 100, 100, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_STORAGE_MATERIAL_F1,
                   OCS_STORAGE, OCAT_RESOURCES, STRUCT_RES_STO_MATERIAL, 1, 1,
                   Structure::TITLES[STRUCT_RES_STO_MATERIAL],
                   Structure::DESCRIPTIONS[STRUCT_RES_STO_MATERIAL])
    );

    // storage diamonds
    data1.emplace
    (
        STRUCT_RES_STO_DIAMONDS,
        ObjectData(std::vector<int>{ 3, 2, 0, 0, 0, 0, 2, 3, 4 },
                   std::vector<int>{ 100, 100, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_STORAGE_DIAMONDS_F1,
                   OCS_STORAGE, OCAT_RESOURCES, STRUCT_RES_STO_DIAMONDS, 1, 1,
                   Structure::TITLES[STRUCT_RES_STO_DIAMONDS],
                   Structure::DESCRIPTIONS[STRUCT_RES_STO_DIAMONDS])
    );

    // storage blobs
    data1.emplace
    (
        STRUCT_RES_STO_BLOBS,
        ObjectData(std::vector<int>{ 3, 2, 0, 0, 0, 0, 2, 3, 4 },
                   std::vector<int>{ 100, 100, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_STORAGE_BLOBS_F1,
                   OCS_STORAGE, OCAT_RESOURCES, STRUCT_RES_STO_BLOBS, 1, 1,
                   Structure::TITLES[STRUCT_RES_STO_BLOBS],
                   Structure::DESCRIPTIONS[STRUCT_RES_STO_BLOBS])
    );

    // wall gate
    data1.emplace
    (
        STRUCT_WALL_GATE,
        ObjectData(std::vector<int>{ 5, 2, 0, 0, 0, 0, 5, 6, 6 },
                   std::vector<int>{ 100, 100, 0, 0 },
                   SpriteFileWalls, WALL_GATE_L1_F1_HORIZ_CLOSED,
                   OCS_WALL_GATE, OCAT_DEFENSE, STRUCT_WALL_GATE, 1, 1,
                   Structure::TITLES[STRUCT_WALL_GATE],
                   Structure::DESCRIPTIONS[STRUCT_WALL_GATE])
    );

    // -- FACTION 2 --
    std::unordered_map<StructureType, ObjectData> & data2 = mStructures[FACTION_2];

    // target
    data2.emplace
    (
        STRUCT_TARGET,
        ObjectData(std::vector<int>{ 8, 2, 0, 0, 0, 0, 5, 8, 8 },
                   std::vector<int>{ 50, 50, 0, 0 },
                   SpriteFileStructures, ID_PRACTICE_TARGET,
                   OCS_TARGET, OCAT_GENERIC, STRUCT_TARGET, 1, 1,
                   Structure::TITLES[STRUCT_TARGET],
                   Structure::DESCRIPTIONS[STRUCT_TARGET])
    );

    // radar
    data2.emplace
    (
        STRUCT_RADAR,
        ObjectData(std::vector<int>{ 4, 8, 0, 0, 0, 0, 4, 5, 3 },
                   std::vector<int>{ 100, 100, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_RADAR_F2,
                   OCS_RADAR, OCAT_TECHNOLOGY, STRUCT_RADAR, 2, 2,
                   Structure::TITLES[STRUCT_RADAR],
                   Structure::DESCRIPTIONS[STRUCT_RADAR])
    );

    // radar tower
    data2.emplace
    (
        STRUCT_RADAR_TOWER,
        ObjectData(std::vector<int>{ 3, 6, 0, 0, 0, 0, 3, 4, 2 },
                   std::vector<int>{ 100, 50, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_RADAR_TOWER_F2,
                   OCS_RADAR, OCAT_TECHNOLOGY, STRUCT_RADAR_TOWER, 1, 1,
                   Structure::TITLES[STRUCT_RADAR_TOWER],
                   Structure::DESCRIPTIONS[STRUCT_RADAR_TOWER])
    );

    // defensive tower
    data2.emplace
    (
        STRUCT_DEF_TOWER,
        ObjectData(std::vector<int>{ 5, 4, 2, 4, 4, 5, 5, 5, 5 },
                   std::vector<int>{ 150, 150, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_DTOWER_L1_F2,
                   OCS_TOWER, OCAT_DEFENSE, STRUCT_DEF_TOWER, 1, 1,
                   Structure::TITLES[STRUCT_DEF_TOWER],
                   Structure::DESCRIPTIONS[STRUCT_DEF_TOWER])
    );

    // material extractor
    data2.emplace
    (
        STRUCT_RES_GEN_MATERIAL_EXTRACTOR,
        ObjectData(std::vector<int>{ 4, 2, 0, 0, 0, 0, 2, 2, 2 },
                   std::vector<int>{ 150, 150, 10, 10 },
                   SpriteFileStructures, ID_MATERIAL_EXTRACTOR_F2,
                   OCS_GENERATOR, OCAT_RESOURCES, STRUCT_RES_GEN_MATERIAL_EXTRACTOR, 2, 2,
                   Structure::TITLES[STRUCT_RES_GEN_MATERIAL_EXTRACTOR],
                   Structure::DESCRIPTIONS[STRUCT_RES_GEN_MATERIAL_EXTRACTOR])
    );

    // solar panel
    data2.emplace
    (
        STRUCT_RES_GEN_SOLAR,
        ObjectData(std::vector<int>{ 4, 2, 0, 0, 0, 0, 2, 2, 2 },
                   std::vector<int>{ 150, 150, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_SOLAR_PANEL_F2,
                   OCS_GENERATOR, OCAT_RESOURCES, STRUCT_RES_GEN_SOLAR, 1, 1,
                   Structure::TITLES[STRUCT_RES_GEN_SOLAR],
                   Structure::DESCRIPTIONS[STRUCT_RES_GEN_SOLAR])
    );

    // storage energy
    data2.emplace
    (
        STRUCT_RES_STO_ENERGY,
        ObjectData(std::vector<int>{ 3, 2, 0, 0, 0, 0, 2, 3, 4 },
                   std::vector<int>{ 100, 100, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_STORAGE_ENERGY_F2,
                   OCS_STORAGE, OCAT_RESOURCES, STRUCT_RES_STO_ENERGY, 1, 1,
                   Structure::TITLES[STRUCT_RES_STO_ENERGY],
                   Structure::DESCRIPTIONS[STRUCT_RES_STO_ENERGY])
    );

    // storage material
    data2.emplace
    (
        STRUCT_RES_STO_MATERIAL,
        ObjectData(std::vector<int>{ 3, 2, 0, 0, 0, 0, 2, 3, 4 },
                   std::vector<int>{ 100, 100, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_STORAGE_MATERIAL_F2,
                   OCS_STORAGE, OCAT_RESOURCES, STRUCT_RES_STO_MATERIAL, 1, 1,
                   Structure::TITLES[STRUCT_RES_STO_MATERIAL],
                   Structure::DESCRIPTIONS[STRUCT_RES_STO_MATERIAL])
    );

    // storage diamonds
    data2.emplace
    (
        STRUCT_RES_STO_DIAMONDS,
        ObjectData(std::vector<int>{ 3, 2, 0, 0, 0, 0, 2, 3, 4 },
                   std::vector<int>{ 100, 100, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_STORAGE_DIAMONDS_F2,
                   OCS_STORAGE, OCAT_RESOURCES, STRUCT_RES_STO_DIAMONDS, 1, 1,
                   Structure::TITLES[STRUCT_RES_STO_DIAMONDS],
                   Structure::DESCRIPTIONS[STRUCT_RES_STO_DIAMONDS])
    );

    // storage blobs
    data2.emplace
    (
        STRUCT_RES_STO_BLOBS,
        ObjectData(std::vector<int>{ 3, 2, 0, 0, 0, 0, 2, 3, 4 },
                   std::vector<int>{ 100, 100, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_STORAGE_BLOBS_F2,
                   OCS_STORAGE, OCAT_RESOURCES, STRUCT_RES_STO_BLOBS, 1, 1,
                   Structure::TITLES[STRUCT_RES_STO_BLOBS],
                   Structure::DESCRIPTIONS[STRUCT_RES_STO_BLOBS])
    );

    // wall gate
    data2.emplace
    (
        STRUCT_WALL_GATE,
        ObjectData(std::vector<int>{ 5, 2, 0, 0, 0, 0, 5, 6, 6 },
                   std::vector<int>{ 100, 100, 0, 0 },
                   SpriteFileWalls, WALL_GATE_L1_F2_HORIZ_CLOSED,
                   OCS_WALL_GATE, OCAT_DEFENSE, STRUCT_WALL_GATE, 1, 1,
                   Structure::TITLES[STRUCT_WALL_GATE],
                   Structure::DESCRIPTIONS[STRUCT_WALL_GATE])
    );

    // -- FACTION 3 --
    std::unordered_map<StructureType, ObjectData> & data3 = mStructures[FACTION_3];

    // target
    data3.emplace
    (
        STRUCT_TARGET,
        ObjectData(std::vector<int>{ 8, 2, 0, 0, 0, 0, 5, 8, 8 },
                   std::vector<int>{ 50, 50, 0, 0 },
                   SpriteFileStructures, ID_PRACTICE_TARGET,
                   OCS_TARGET, OCAT_GENERIC, STRUCT_TARGET, 1, 1,
                   Structure::TITLES[STRUCT_TARGET],
                   Structure::DESCRIPTIONS[STRUCT_TARGET])
    );

    // radar tower
    data3.emplace
    (
        STRUCT_RADAR_TOWER,
        ObjectData(std::vector<int>{ 3, 6, 0, 0, 0, 0, 3, 4, 2 },
                   std::vector<int>{ 100, 50, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_RADAR_TOWER_F3,
                   OCS_RADAR, OCAT_TECHNOLOGY, STRUCT_RADAR_TOWER, 1, 1,
                   Structure::TITLES[STRUCT_RADAR_TOWER],
                   Structure::DESCRIPTIONS[STRUCT_RADAR_TOWER])
    );

    // radar
    data3.emplace
    (
        STRUCT_RADAR,
        ObjectData(std::vector<int>{ 4, 8, 0, 0, 0, 0, 4, 5, 3 },
                   std::vector<int>{ 100, 100, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_RADAR_F3,
                   OCS_RADAR, OCAT_TECHNOLOGY, STRUCT_RADAR, 2, 2,
                   Structure::TITLES[STRUCT_RADAR],
                   Structure::DESCRIPTIONS[STRUCT_RADAR])
    );

    // defensive tower
    data3.emplace
    (
        STRUCT_DEF_TOWER,
        ObjectData(std::vector<int>{ 5, 4, 2, 4, 4, 5, 5, 5, 5 },
                   std::vector<int>{ 150, 150, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_DTOWER_L1_F3,
                   OCS_TOWER, OCAT_DEFENSE, STRUCT_DEF_TOWER, 1, 1,
                   Structure::TITLES[STRUCT_DEF_TOWER],
                   Structure::DESCRIPTIONS[STRUCT_DEF_TOWER])
    );

    // material extractor
    data3.emplace
    (
        STRUCT_RES_GEN_MATERIAL_EXTRACTOR,
        ObjectData(std::vector<int>{ 4, 2, 0, 0, 0, 0, 2, 2, 2 },
                   std::vector<int>{ 150, 150, 10, 10 },
                   SpriteFileStructures, ID_MATERIAL_EXTRACTOR_F3,
                   OCS_GENERATOR, OCAT_RESOURCES, STRUCT_RES_GEN_MATERIAL_EXTRACTOR, 2, 2,
                   Structure::TITLES[STRUCT_RES_GEN_MATERIAL_EXTRACTOR],
                   Structure::DESCRIPTIONS[STRUCT_RES_GEN_MATERIAL_EXTRACTOR])
    );

    // solar panel
    data3.emplace
    (
        STRUCT_RES_GEN_SOLAR,
        ObjectData(std::vector<int>{ 4, 2, 0, 0, 0, 0, 2, 2, 2 },
                   std::vector<int>{ 150, 150, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_SOLAR_PANEL_F3,
                   OCS_GENERATOR, OCAT_RESOURCES, STRUCT_RES_GEN_SOLAR, 1, 1,
                   Structure::TITLES[STRUCT_RES_GEN_SOLAR],
                   Structure::DESCRIPTIONS[STRUCT_RES_GEN_SOLAR])
    );

    // storage energy
    data3.emplace
    (
        STRUCT_RES_STO_ENERGY,
        ObjectData(std::vector<int>{ 3, 2, 0, 0, 0, 0, 2, 3, 4 },
                   std::vector<int>{ 100, 100, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_STORAGE_ENERGY_F3,
                   OCS_STORAGE, OCAT_RESOURCES, STRUCT_RES_STO_ENERGY, 1, 1,
                   Structure::TITLES[STRUCT_RES_STO_ENERGY],
                   Structure::DESCRIPTIONS[STRUCT_RES_STO_ENERGY])
    );

    // storage material
    data3.emplace
    (
        STRUCT_RES_STO_MATERIAL,
        ObjectData(std::vector<int>{ 3, 2, 0, 0, 0, 0, 2, 3, 4 },
                   std::vector<int>{ 100, 100, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_STORAGE_MATERIAL_F3,
                   OCS_STORAGE, OCAT_RESOURCES, STRUCT_RES_STO_MATERIAL, 1, 1,
                   Structure::TITLES[STRUCT_RES_STO_MATERIAL],
                   Structure::DESCRIPTIONS[STRUCT_RES_STO_MATERIAL])
    );

    // storage diamonds
    data3.emplace
    (
        STRUCT_RES_STO_DIAMONDS,
        ObjectData(std::vector<int>{ 3, 2, 0, 0, 0, 0, 2, 3, 4 },
                   std::vector<int>{ 100, 100, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_STORAGE_DIAMONDS_F3,
                   OCS_STORAGE, OCAT_RESOURCES, STRUCT_RES_STO_DIAMONDS, 1, 1,
                   Structure::TITLES[STRUCT_RES_STO_DIAMONDS],
                   Structure::DESCRIPTIONS[STRUCT_RES_STO_DIAMONDS])
    );

    // storage blobs
    data3.emplace
    (
        STRUCT_RES_STO_BLOBS,
        ObjectData(std::vector<int>{ 3, 2, 0, 0, 0, 0, 2, 3, 4 },
                   std::vector<int>{ 100, 100, 0, 0 },
                   SpriteFileStructures, ID_STRUCT_STORAGE_BLOBS_F3,
                   OCS_STORAGE, OCAT_RESOURCES, STRUCT_RES_STO_BLOBS, 1, 1,
                   Structure::TITLES[STRUCT_RES_STO_BLOBS],
                   Structure::DESCRIPTIONS[STRUCT_RES_STO_BLOBS])
    );

    // wall gate
    data3.emplace
    (
        STRUCT_WALL_GATE,
        ObjectData(std::vector<int>{ 5, 2, 0, 0, 0, 0, 5, 6, 6 },
                   std::vector<int>{ 100, 100, 0, 0 },
                   SpriteFileWalls, WALL_GATE_L1_F3_HORIZ_CLOSED,
                   OCS_WALL_GATE, OCAT_DEFENSE, STRUCT_WALL_GATE, 1, 1,
                   Structure::TITLES[STRUCT_WALL_GATE],
                   Structure::DESCRIPTIONS[STRUCT_WALL_GATE])
    );
}

void ObjectsDataRegistry::InitUnits()
{
    // -- FACTION 1 --
    std::unordered_map<UnitType, ObjectData> & data1 = mUnits[FACTION_1];

    // unit 1
    data1.emplace
    (
        UNIT_1,
        ObjectData(std::vector<int>{ 4, 4, 1, 1, 1, 2, 4, 2, 2, 5, 6, 6 },
                   std::vector<int>{ 150, 150, 0, 0 },
                   SpriteFileUnits, SPR_UNIT_01_F1,
                   OCU_WORKER, OCAT_UNIT, UNIT_1, 1, 1,
                   Unit::TITLES[UNIT_1],
                   Unit::DESCRIPTIONS[UNIT_1])
    );

    // unit 2
    data1.emplace
    (
        UNIT_2,
        ObjectData(std::vector<int>{ 4, 5, 5, 4, 5, 4, 3, 3, 2, 6, 1, 4 },
                   std::vector<int>{ 200, 200, 0, 0 },
                   SpriteFileUnits, SPR_UNIT_02_F1,
                   OCU_SOLDIER, OCAT_UNIT, UNIT_2, 1, 1,
                   Unit::TITLES[UNIT_2],
                   Unit::DESCRIPTIONS[UNIT_2])
    );

    // unit 3
    data1.emplace
    (
        UNIT_3,
        ObjectData(std::vector<int>{ 6, 5, 2, 5, 3, 4, 4, 5, 5, 3, 3, 4 },
                   std::vector<int>{ 400, 400, 0, 0 },
                   SpriteFileUnits, SPR_UNIT_03_F1,
                   OCU_GENERIC, OCAT_UNIT, UNIT_3, 1, 1,
                   Unit::TITLES[UNIT_3],
                   Unit::DESCRIPTIONS[UNIT_3])

    );

    // unit 4
    data1.emplace
    (
        UNIT_4,
        ObjectData(std::vector<int>{ 6, 6, 3, 2, 3, 3, 4, 4, 4, 6, 1, 2 },
                   std::vector<int>{ 300, 300, 0, 0 },
                   SpriteFileUnits, SPR_UNIT_04_F1,
                   OCU_SCOUT, OCAT_UNIT, UNIT_4, 1, 1,
                   Unit::TITLES[UNIT_4],
                   Unit::DESCRIPTIONS[UNIT_4])

    );

    // -- FACTION 2 --
    std::unordered_map<UnitType, ObjectData> & data2 = mUnits[FACTION_2];

    // unit 1
    data2.emplace
    (
        UNIT_1,
        ObjectData(std::vector<int>{ 4, 4, 1, 1, 1, 2, 4, 2, 2, 5, 6, 6 },
                   std::vector<int>{ 150, 150, 0, 0 },
                   SpriteFileUnits, SPR_UNIT_01_F2,
                   OCU_WORKER, OCAT_UNIT, UNIT_1, 1, 1,
                   Unit::TITLES[UNIT_1],
                   Unit::DESCRIPTIONS[UNIT_1])
    );

    // unit 2
    data2.emplace
    (
        UNIT_2,
        ObjectData(std::vector<int>{ 4, 5, 5, 4, 5, 4, 3, 3, 2, 6, 1, 4 },
                   std::vector<int>{ 200, 200, 0, 0 },
                   SpriteFileUnits, SPR_UNIT_02_F2,
                   OCU_SOLDIER, OCAT_UNIT, UNIT_2, 1, 1,
                   Unit::TITLES[UNIT_2],
                   Unit::DESCRIPTIONS[UNIT_2])
    );

    // unit 3
    data2.emplace
    (
        UNIT_3,
        ObjectData(std::vector<int>{ 6, 5, 2, 5, 3, 4, 4, 5, 5, 3, 3, 4 },
                   std::vector<int>{ 400, 400, 0, 0 },
                   SpriteFileUnits, SPR_UNIT_03_F2,
                   OCU_GENERIC, OCAT_UNIT, UNIT_3, 1, 1,
                   Unit::TITLES[UNIT_3],
                   Unit::DESCRIPTIONS[UNIT_3])
    );

    // unit 4
    data2.emplace
    (
        UNIT_4,
        ObjectData(std::vector<int>{ 6, 6, 3, 2, 3, 3, 4, 4, 4, 6, 1, 2 },
                   std::vector<int>{ 300, 300, 0, 0 },
                   SpriteFileUnits, SPR_UNIT_04_F2,
                   OCU_SCOUT, OCAT_UNIT, UNIT_4, 1, 1,
                   Unit::TITLES[UNIT_4],
                   Unit::DESCRIPTIONS[UNIT_4])

    );

    // -- FACTION 3 --
    std::unordered_map<UnitType, ObjectData> & data3 = mUnits[FACTION_3];

    // unit 1
    data3.emplace
    (
        UNIT_1,
        ObjectData(std::vector<int>{ 4, 4, 1, 1, 1, 2, 4, 2, 2, 5, 6, 6 },
                   std::vector<int>{ 150, 150, 0, 0 },
                   SpriteFileUnits, SPR_UNIT_01_F3,
                   OCU_WORKER, OCAT_UNIT, UNIT_1, 1, 1,
                   Unit::TITLES[UNIT_1],
                   Unit::DESCRIPTIONS[UNIT_1])
    );

    // unit 2
    data3.emplace
    (
        UNIT_2,
        ObjectData(std::vector<int>{ 4, 5, 5, 4, 5, 4, 3, 3, 2, 6, 1, 4 },
                   std::vector<int>{ 200, 200, 0, 0 },
                   SpriteFileUnits, SPR_UNIT_02_F3,
                   OCU_SOLDIER, OCAT_UNIT, UNIT_2, 1, 1,
                   Unit::TITLES[UNIT_2],
                   Unit::DESCRIPTIONS[UNIT_2])
    );

    // unit 3
    data3.emplace
    (
        UNIT_3,
        ObjectData(std::vector<int>{ 6, 5, 2, 5, 3, 4, 4, 5, 5, 3, 3, 4 },
                   std::vector<int>{ 400, 400, 0, 0 },
                   SpriteFileUnits, SPR_UNIT_03_F3,
                   OCU_GENERIC, OCAT_UNIT, UNIT_3, 1, 1,
                   Unit::TITLES[UNIT_3],
                   Unit::DESCRIPTIONS[UNIT_3])
    );

    // unit 4
    data3.emplace
    (
        UNIT_4,
        ObjectData(std::vector<int>{ 6, 6, 3, 2, 3, 3, 4, 4, 4, 6, 1, 2 },
                   std::vector<int>{ 300, 300, 0, 0 },
                   SpriteFileUnits, SPR_UNIT_04_F3,
                   OCU_SCOUT, OCAT_UNIT, UNIT_4, 1, 1,
                   Unit::TITLES[UNIT_4],
                   Unit::DESCRIPTIONS[UNIT_4])

    );
}

} // namespace game
