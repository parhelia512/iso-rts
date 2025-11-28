#pragma once

#include "GameObject.h"

namespace game
{

class CollectableGenerator;
class Player;

class Collectable : public GameObject
{
public:
    Collectable(const ObjectData & data);

    virtual void Collected(Player * collector);
};

inline Collectable::Collectable(const ObjectData & data) :
    GameObject(data)
{
}

} // namespace game
