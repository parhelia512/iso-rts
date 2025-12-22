#pragma once

#include "Tutorial/TutorialInfoStep.h"

namespace game
{

class FocusArea;
class PanelPlanetInfo;
class PanelPlanetResources;

class StepPlanetMapNoInfo : public TutorialInfoStep
{
public:
    StepPlanetMapNoInfo(const PanelPlanetInfo * panelInfo, const PanelPlanetResources * panelResources);
    ~StepPlanetMapNoInfo();

    void OnStart() override;

private:
    FocusArea * mFocusInfo = nullptr;
    FocusArea * mFocusResources = nullptr;
};

} // namespace game
