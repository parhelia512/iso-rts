#pragma once

#include "GameObjects/GameObjectsGroup.h"

namespace game
{

class GameObject;

class CityGroup : public GameObjectsGroup
{
public:
    bool IsCityConquered() const;

private:
    bool mConquered = false;

};

inline bool CityGroup::IsCityConquered() const { return mConquered; }

} // namespace game
