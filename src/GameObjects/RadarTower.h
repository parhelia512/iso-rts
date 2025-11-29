#pragma once

#include "Structure.h"

namespace game
{

class RadarTower : public Structure
{
public:
    RadarTower(const ObjectData & data);

protected:
    void UpdateGraphics() override;

private:
    void SetImage();
};

} // namespace game

