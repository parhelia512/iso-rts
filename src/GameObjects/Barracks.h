#pragma once

#include "Structure.h"

namespace game
{

class Barracks : public Structure
{
public:
    Barracks(const ObjectData & data);

protected:
    void UpdateGraphics() override;

private:
    void SetImage();
};

} // namespace game
