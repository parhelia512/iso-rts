#include "Tutorial/StepPlanetMapExploreTerritoryStart.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/PanelPlanetActionExplore.h"
#include "Widgets/Tutorial/FocusArea.h"
#include "Widgets/Tutorial/PanelClickFilter.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

#include <sgl/sgui/AbstractButton.h>

namespace game
{

StepPlanetMapExploreTerritoryStart::StepPlanetMapExploreTerritoryStart(PanelPlanetActionExplore * panelExplore)
    : TutorialInfoStep(infoPlanetMapW, infoPlanetMapH)
    , mFocusArea(new FocusArea)
{
    // FOCUS
    auto btnExplore = panelExplore->GetButtonOk();

    const int padding = 10;
    const int fX = panelExplore->GetX() + btnExplore->GetX() - padding;
    const int fY = panelExplore->GetY() + btnExplore->GetY() - padding;
    const int fW = btnExplore->GetWidth() + (padding * 2);
    const int fH = btnExplore->GetHeight() + (padding * 2);

    mFocusArea->SetScreenArea(fX, fY, fW, fH);
    mFocusArea->SetCornersColor(colorTutorialFocusAction);
    mFocusArea->SetBlinking(true);
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(infoPlanetMapX, infoPlanetMapY);

    info->AddInfoEntry("Now click the button PROCEED to start the exploration.",
                       colorTutorialTextAction, 0.f, false, false, [this, fX, fY, fW, fH]
                       {
                           GetClickFilter()->SetScreenClickableArea(fX, fY, fW, fH);
                       });

    // EXPLORE BUTTON
    btnExplore->AddOnClickFunction([this]
    {
        SetDone();
    });
}

StepPlanetMapExploreTerritoryStart::~StepPlanetMapExploreTerritoryStart()
{
    delete mFocusArea;
}

void StepPlanetMapExploreTerritoryStart::OnStart()
{
    TutorialInfoStep::OnStart();

    // FOCUS
    mFocusArea->SetVisible(true);
}

} // namespace game
