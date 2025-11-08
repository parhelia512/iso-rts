#pragma once

#include "Tutorial/TutorialInfoStep.h"

namespace game
{

class FocusArea;
class PanelPlanetActionExplore;

class StepPlanetMapExploreTerritoryStart : public TutorialInfoStep
{
public:
    StepPlanetMapExploreTerritoryStart(PanelPlanetActionExplore * panelExplore);
    ~StepPlanetMapExploreTerritoryStart();

    void OnStart() override;

private:
    FocusArea * mFocusArea = nullptr;
};

} // namespace game
