#pragma once

#include "Tutorial/TutorialInfoStep.h"

namespace game
{

class FocusArea;
class Player;
class Unit;

class StepGameUnitSelect : public TutorialInfoStep
{
public:
    StepGameUnitSelect(const Player * p);
    ~StepGameUnitSelect();

    void Update(float delta) override;

private:
    FocusArea * mFocusArea = nullptr;

    Unit * mUnit = nullptr;
};

} // namespace game
