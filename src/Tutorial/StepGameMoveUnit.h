#pragma once

#include "Tutorial/TutorialInfoStep.h"

namespace game
{

class FocusArea;
class IsoMap;
class Player;
class Unit;

class StepGameMoveUnit : public TutorialInfoStep
{
public:
    StepGameMoveUnit(const Player * p, const IsoMap * isoMap);
    ~StepGameMoveUnit();

    void Update(float delta) override;

private:
    FocusArea * mFocusArea = nullptr;

    Unit * mUnit = nullptr;
};

} // namespace game
