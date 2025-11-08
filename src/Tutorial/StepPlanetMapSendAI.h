#pragma once

#include "Tutorial/TutorialInfoStep.h"

namespace game
{

class FocusArea;
class PanelPlanetActions;

class StepPlanetMapSendAI : public TutorialInfoStep
{
public:
    StepPlanetMapSendAI(PanelPlanetActions * panel);
    ~StepPlanetMapSendAI();

private:
    FocusArea * mFocusArea = nullptr;
};

} // namespace game
