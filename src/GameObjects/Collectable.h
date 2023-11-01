#pragma once

#include "GameObject.h"

namespace game
{

class CollectableGenerator;

class Collectable : public GameObject
{
public:
    Collectable(GameObjectTypeId type, int rows, int cols);

    void SetGenerator(CollectableGenerator * gen);

    void Collected();

private:
    CollectableGenerator * mGen = nullptr;
};

inline Collectable::Collectable(GameObjectTypeId type, int rows, int cols) : GameObject(type, rows, cols)
{
    SetCanBeCollected(true);
}

inline void Collectable::SetGenerator(CollectableGenerator * gen) { mGen = gen; }

} // namespace game
