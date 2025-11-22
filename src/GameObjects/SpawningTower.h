#pragma once

#include "Structure.h"

namespace game
{

class ObjectData;

class SpawningTower : public Structure
{
public:
    SpawningTower(const ObjectData & data);

private:
    void UpdateGraphics() override;

    void SetImage();
};

} // namespace game
