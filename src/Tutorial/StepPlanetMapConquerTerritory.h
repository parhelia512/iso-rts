#pragma once

#include "Tutorial/TutorialInfoStep.h"

namespace game
{

class FocusArea;
class PanelPlanetActions;

class StepPlanetMapConquerTerritory : public TutorialInfoStep
{
public:
    StepPlanetMapConquerTerritory(PanelPlanetActions * panelActions);
    ~StepPlanetMapConquerTerritory();

private:
    FocusArea * mFocusArea = nullptr;
};

} // namespace game
