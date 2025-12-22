#pragma once

#include "Tutorial/TutorialInfoStep.h"

namespace game
{

class FocusArea;
class Player;
class Unit;

class StepGameUnit : public TutorialInfoStep
{
public:
    StepGameUnit(const Player * p);
    ~StepGameUnit();

    void Update(float delta) override;

private:
    FocusArea * mFocusArea = nullptr;

    Unit * mUnit = nullptr;
};

} // namespace game
