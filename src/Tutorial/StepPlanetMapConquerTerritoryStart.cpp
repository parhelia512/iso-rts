#include "Tutorial/StepPlanetMapConquerTerritoryStart.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/PanelPlanetActionConquer.h"
#include "Widgets/Tutorial/FocusArea.h"
#include "Widgets/Tutorial/PanelClickFilter.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

#include <sgl/sgui/AbstractButton.h>

namespace game
{

StepPlanetMapConquerTerritoryStart::StepPlanetMapConquerTerritoryStart(PanelPlanetActionConquer * panel)
    : TutorialInfoStep(TutorialConstants::infoPlanetMapW, TutorialConstants::infoPlanetMapH)
    , mFocusArea(new FocusArea)
{
    // FOCUS
    auto btn = panel->GetButtonOk();

    const int padding = 10;
    const int fX = panel->GetX() + btn->GetX() - padding;
    const int fY = panel->GetY() + btn->GetY() - padding;
    const int fW = btn->GetWidth() + (padding * 2);
    const int fH = btn->GetHeight() + (padding * 2);

    mFocusArea->SetScreenArea(fX, fY, fW, fH);
    mFocusArea->SetCornersColor(TutorialConstants::colorFocusAction);
    mFocusArea->SetBlinking(true);
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(TutorialConstants::infoPlanetMapX, TutorialConstants::infoPlanetMapY);

    info->AddInfoEntry("Now click the button PROCEED to start your first mission.",
                       TutorialConstants::colorTextAction, 0.f, false, false);

    info->SetFunctionOnFinished([this, fX, fY, fW, fH]
    {
        // CLICK FILTER
        auto cf = GetClickFilter();
        cf->SetScreenClickableArea(fX, fY, fW, fH);
        cf->SetEnabled(true);

        // FOCUS
        mFocusArea->SetVisible(true);
    });

    // CONQUER BUTTON
    btn->AddOnClickFunction([this]
    {
        SetDone();
    });
}

StepPlanetMapConquerTerritoryStart::~StepPlanetMapConquerTerritoryStart()
{
    delete mFocusArea;
}

} // namespace game
