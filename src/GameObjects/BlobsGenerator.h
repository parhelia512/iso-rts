#pragma once

#include "GameObjects/CollectableGenerator.h"

namespace game
{

class GameMap;

class BlobsGenerator : public CollectableGenerator
{
public:
    BlobsGenerator(const Game * g, GameMap * gm);

private:
    void OnGeneration() override;
};

} // namespace game
