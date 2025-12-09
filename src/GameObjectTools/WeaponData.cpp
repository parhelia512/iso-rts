#include "WeaponData.h"

namespace game
{

using h = std::hash<std::string>;

// STRINGS ID
const std::string WeaponData::STR_LASER1("LASER1");
const std::string WeaponData::STR_LASER2("LASER2");
const std::string WeaponData::STR_LASER3("LASER3");
const std::string WeaponData::STR_LASER4("LASER4");
const std::string WeaponData::STR_LASER5("LASER5");

// TYPES
const WeaponType WeaponData::TYPE_LASER1 = h{}(STR_LASER1);
const WeaponType WeaponData::TYPE_LASER2 = h{}(STR_LASER2);
const WeaponType WeaponData::TYPE_LASER3 = h{}(STR_LASER3);
const WeaponType WeaponData::TYPE_LASER4 = h{}(STR_LASER4);
const WeaponType WeaponData::TYPE_LASER5 = h{}(STR_LASER5);

const WeaponType WeaponData::TYPE_NULL = 0;

// NULL OBJECT
const WeaponData WeaponData::NullObj(TYPE_NULL, {}, 0.f);

} // namespace game
