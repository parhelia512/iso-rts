#pragma once

#include "Structure.h"

namespace game
{

class Barracks : public Structure
{
public:
    Barracks(const ObjectData & data, const ObjectInitData & initData);

protected:
    void UpdateGraphics() override;

private:
    void SetImage();
};

} // namespace game
