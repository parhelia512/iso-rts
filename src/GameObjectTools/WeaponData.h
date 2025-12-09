#pragma once

#include "GameObjects/GameObjectTypes.h"

#include <string>
#include <unordered_map>

namespace game
{

enum ObjAttId : unsigned int;

class WeaponData
{
public:
    static const WeaponType TYPE_LASER1;
    static const WeaponType TYPE_LASER2;
    static const WeaponType TYPE_LASER3;
    static const WeaponType TYPE_LASER4;
    static const WeaponType TYPE_LASER5;

    static const WeaponType TYPE_NULL;
    static const WeaponData NullObj;

public:
    WeaponData(WeaponType t, const std::unordered_map<ObjAttId, int> & atts);

    WeaponType GetType() const;

    const std::unordered_map<ObjAttId, int> & GetAttributes() const;

    float GetTimeAttack() const;

private:
    static const std::string STR_LASER1;
    static const std::string STR_LASER2;
    static const std::string STR_LASER3;
    static const std::string STR_LASER4;
    static const std::string STR_LASER5;

private:
    std::unordered_map<ObjAttId, int> mAttributes;

    WeaponType mType;
};

inline WeaponData::WeaponData(WeaponType t, const std::unordered_map<ObjAttId, int> & atts)
    : mAttributes(atts)
    , mType(t)
{
}

inline WeaponType WeaponData::GetType() const { return mType; }

inline const std::unordered_map<ObjAttId, int> & WeaponData::GetAttributes() const
{
    return mAttributes;
}

} // namespace game
