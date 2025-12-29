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
    : TutorialInfoStep(TutorialConstants::infoPlanetMapW, TutorialConstants::infoPlanetMapH)
    , mFocusArea(new FocusArea)
{
    // FOCUS
    mButton = panelActions->GetButton(PanelPlanetActions::EXPLORE);

    const int padding = 10;
    const int fX = panelActions->GetX() + mButton->GetX() - padding;
    const int fY = panelActions->GetY() + mButton->GetY() - padding;
    const int fW = mButton->GetWidth() + (padding * 2);
    const int fH = mButton->GetHeight() + (padding * 2);

    mFocusArea->SetScreenArea(fX, fY, fW, fH);
    mFocusArea->SetCornersColor(TutorialConstants::colorFocusAction);
    mFocusArea->SetBlinking(true);
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(TutorialConstants::infoPlanetMapX, TutorialConstants::infoPlanetMapY);

    info->AddInfoEntry("Click the button EXPLORE to try to explore it.",
                       TutorialConstants::colorTextAction, 0.f, false, false, [this, fX, fY, fW, fH]
                       {
                           GetClickFilter()->SetScreenClickableArea(fX, fY, fW, fH);
                       });

    // EXPLORE BUTTON
    mFuncId = mButton->AddOnClickFunction([this]
    {
        SetDone();
    });
}

StepPlanetMapExploreTerritory::~StepPlanetMapExploreTerritory()
{
    delete mFocusArea;

    // clear callback
    mButton->RemoveClickFunction(mFuncId);
}

void StepPlanetMapExploreTerritory::OnStart()
{
    TutorialInfoStep::OnStart();

    // FOCUS
    mFocusArea->SetVisible(true);
}

} // namespace game
