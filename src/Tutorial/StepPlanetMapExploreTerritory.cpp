#include "Tutorial/StepPlanetMapExploreTerritory.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/PanelPlanetActions.h"
#include "Widgets/Tutorial/FocusArea.h"
#include "Widgets/Tutorial/PanelClickFilter.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

#include <sgl/sgui/AbstractButton.h>

namespace game
{

StepPlanetMapExploreTerritory::StepPlanetMapExploreTerritory(PanelPlanetActions * panelActions)
    : TutorialInfoStep(infoPlanetMapW, infoPlanetMapH)
    , mFocusArea(new FocusArea)
{
    // FOCUS
    auto btnExplore = panelActions->GetButton(PanelPlanetActions::EXPLORE);

    const int padding = 10;
    const int fX = panelActions->GetX() + btnExplore->GetX() - padding;
    const int fY = panelActions->GetY() + btnExplore->GetY() - padding;
    const int fW = btnExplore->GetWidth() + (padding * 2);
    const int fH = btnExplore->GetHeight() + (padding * 2);

    mFocusArea->SetScreenArea(fX, fY, fW, fH);
    mFocusArea->SetCornersColor(colorTutorialFocusAction);
    mFocusArea->SetBlinking(true);
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(infoPlanetMapX, infoPlanetMapY);

    info->AddInfoEntry("Click the button EXPLORE to try to explore it.",
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

StepPlanetMapExploreTerritory::~StepPlanetMapExploreTerritory()
{
    delete mFocusArea;
}

void StepPlanetMapExploreTerritory::OnStart()
{
    TutorialInfoStep::OnStart();

    // FOCUS
    mFocusArea->SetVisible(true);
}

} // namespace game
