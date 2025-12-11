#pragma once

#include "GameObjects/GameObjectTypes.h"

#include <string>
#include <unordered_map>

namespace game
{

enum WeaponClass : unsigned int
{
    WEAPONC_LASER,

    NUM_WEAPON_CLASSES,

    WEAPONC_NULL
};

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
    WeaponData(WeaponType wt, WeaponClass wc, unsigned int bs, float bd,
               const std::unordered_map<ObjAttId, int> & atts);

    WeaponType GetType() const;
    WeaponClass GetClass() const;

    const std::unordered_map<ObjAttId, int> & GetAttributes() const;

    unsigned int GetBurstShots() const;
    float GetBurstDelay() const;

private:
    static const std::string STR_LASER1;
    static const std::string STR_LASER2;
    static const std::string STR_LASER3;
    static const std::string STR_LASER4;
    static const std::string STR_LASER5;

private:
    std::unordered_map<ObjAttId, int> mAttributes;

    WeaponType mType;
    WeaponClass mClass;

    int mBurstShots;
    float mBurstDelay;
};

inline WeaponData::WeaponData(WeaponType wt, WeaponClass wc, unsigned int bs, float bd,
                              const std::unordered_map<ObjAttId, int> & atts)
    : mAttributes(atts)
    , mType(wt)
    , mClass(wc)
    , mBurstShots(bs)
    , mBurstDelay(bd)
{
}

inline WeaponType WeaponData::GetType() const { return mType; }
inline WeaponClass WeaponData::GetClass() const { return mClass; }

inline const std::unordered_map<ObjAttId, int> & WeaponData::GetAttributes() const
{
    return mAttributes;
}

inline unsigned int WeaponData::GetBurstShots() const { return mBurstShots; }
inline float WeaponData::GetBurstDelay() const { return mBurstDelay; }

} // namespace game
