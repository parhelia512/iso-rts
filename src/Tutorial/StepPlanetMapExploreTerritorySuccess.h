#pragma once

#include "Tutorial/TutorialInfoStep.h"

namespace sgl { namespace sgui { class AbstractButton; } }

namespace game
{

class FocusArea;
class PanelPlanetActionExplore;
class PanelPlanetInfo;
class PanelPlanetResources;

class StepPlanetMapExploreTerritorySuccess : public TutorialInfoStep
{
public:
    StepPlanetMapExploreTerritorySuccess(const PanelPlanetActionExplore * panelExplore,
                                         const PanelPlanetInfo * panelInfo,
                                         const PanelPlanetResources * panelResources);
    ~StepPlanetMapExploreTerritorySuccess();

    void OnStart() override;

private:
    FocusArea * mFocusArea = nullptr;
    FocusArea * mFocusInfo = nullptr;
    FocusArea * mFocusResources = nullptr;

    sgl::sgui::AbstractButton * mButton = nullptr;
    unsigned int mFuncId = 0;
};

} // namespace game
