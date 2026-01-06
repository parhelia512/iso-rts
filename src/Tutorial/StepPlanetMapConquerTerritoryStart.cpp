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
    mButton = panel->GetButtonOk();

    const int padding = 10;
    const int fX = panel->GetX() + mButton->GetX() - padding;
    const int fY = panel->GetY() + mButton->GetY() - padding;
    const int fW = mButton->GetWidth() + (padding * 2);
    const int fH = mButton->GetHeight() + (padding * 2);

    mFocusArea->SetScreenArea(fX, fY, fW, fH);
    mFocusArea->SetCornersColor(TutorialConstants::colorFocusAction);
    mFocusArea->SetBlinking(true);
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(TutorialConstants::infoPlanetMapX, TutorialConstants::infoPlanetMapY);

    info->AddInfoEntry("Now click the button PROCEED to start your mission.",
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
    mFuncId = mButton->AddOnClickFunction([this]
    {
        SetDone();
    });
}

StepPlanetMapConquerTerritoryStart::~StepPlanetMapConquerTerritoryStart()
{
    delete mFocusArea;

    // clear callback
    mButton->RemoveClickFunction(mFuncId);
}

} // namespace game
