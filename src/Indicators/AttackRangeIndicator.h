#pragma once

#include "IsoObject.h"

namespace game
{

enum PlayerFaction : unsigned int;

class AttackRangeIndicator : public IsoObject
{
public:
    AttackRangeIndicator();

    void SetDistance(unsigned int d, unsigned int range);
};

} // namespace game
