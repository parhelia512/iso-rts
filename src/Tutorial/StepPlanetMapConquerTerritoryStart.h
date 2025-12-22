#pragma once

#include "Tutorial/TutorialInfoStep.h"

namespace game
{

class FocusArea;
class PanelPlanetActionConquer;

class StepPlanetMapConquerTerritoryStart : public TutorialInfoStep
{
public:
    StepPlanetMapConquerTerritoryStart(PanelPlanetActionConquer * panel);
    ~StepPlanetMapConquerTerritoryStart();

private:
    FocusArea * mFocusArea = nullptr;
};

} // namespace game
