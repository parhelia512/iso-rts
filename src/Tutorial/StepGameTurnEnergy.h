#pragma once

#include "Tutorial/TutorialInfoStep.h"

namespace game
{

class FocusArea;
class GameHUD;

class StepGameTurnEnergy : public TutorialInfoStep
{
public:
    StepGameTurnEnergy(const GameHUD * HUD);
    ~StepGameTurnEnergy();

private:
    FocusArea * mFocusArea = nullptr;
};

} // namespace game
