#pragma once

#include "ObjectData.h"
#include "GameObjects/GameObjectTypes.h"
#include "GameObjectTools/WeaponData.h"

#include <unordered_map>

namespace game
{

class ObjectsDataRegistry
{
public:
    ObjectsDataRegistry();

    const ObjectData & GetObjectData(GameObjectTypeId type) const;

    const WeaponData & GetWeaponData(WeaponType type) const;

private:
    void InitObjectData();

    void InitWeaponData();

private:
    std::unordered_map<GameObjectTypeId, ObjectData> mDataObjects;

    std::unordered_map<WeaponType, WeaponData> mDataWeapons;
};

} // namespace game
