#pragma once

#include "Structure.h"

namespace game
{

class ObjectData;

class SpawningTower : public Structure
{
public:
    SpawningTower(const ObjectData & data, const ObjectInitData & initData);

    float GetTimeSpawnMiniUnit() const;

private:
    void UpdateGraphics() override;

    void SetImage();
};

} // namespace game
