#pragma once

#include "Structure.h"

namespace game
{

class RadarStation : public Structure
{
public:
    RadarStation(const ObjectData & data);

protected:
    void UpdateGraphics() override;

private:
    void SetImage();
};

} // namespace game

