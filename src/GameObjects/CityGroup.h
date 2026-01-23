#pragma once

#include "GameObjects/GameObjectsGroup.h"

namespace game
{

class GameObject;
class Player;

class CityGroup : public GameObjectsGroup
{
public:
    bool IsCityConquered() const;

    void UpdateCityConquered(Player * conqueror);

private:
    bool mConquered = false;

};

inline bool CityGroup::IsCityConquered() const { return mConquered; }

} // namespace game
