#pragma once

#include "Tutorial/TutorialInfoStep.h"

namespace game
{

class FocusArea;
class PanelPlanetActions;

class StepPlanetMapExploreTerritory : public TutorialInfoStep
{
public:
    StepPlanetMapExploreTerritory(PanelPlanetActions * panelActions);
    ~StepPlanetMapExploreTerritory();

    void OnStart() override;

private:
    FocusArea * mFocusArea = nullptr;
};

} // namespace game
