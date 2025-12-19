#pragma once

#include "Structure.h"

namespace game
{

class ObjectData;

class DefensiveTower : public Structure
{
public:
    DefensiveTower(const ObjectData & data);

    void Update(float delta) override;

protected:
    void UpdateGraphics() override;

private:
    void SetImage();

    void CheckForEnemies();

    void PrepareShoot();

private:
    float mTimerAttack = 0.f;
};

} // namespace game
