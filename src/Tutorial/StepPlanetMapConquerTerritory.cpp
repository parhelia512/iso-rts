#include "Tutorial/StepPlanetMapConquerTerritory.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/PanelPlanetActions.h"
#include "Widgets/Tutorial/FocusArea.h"
#include "Widgets/Tutorial/PanelClickFilter.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

#include <sgl/sgui/AbstractButton.h>

namespace game
{

StepPlanetMapConquerTerritory::StepPlanetMapConquerTerritory(PanelPlanetActions * panelActions)
    : TutorialInfoStep(TutorialConstants::infoPlanetMapW, TutorialConstants::infoPlanetMapH)
    , mFocusArea(new FocusArea)
{
    // FOCUS
    auto btn = panelActions->GetButton(PanelPlanetActions::CONQUER);

    const int padding = 10;
    const int fX = panelActions->GetX() + btn->GetX() - padding;
    const int fY = panelActions->GetY() + btn->GetY() - padding;
    const int fW = btn->GetWidth() + (padding * 2);
    const int fH = btn->GetHeight() + (padding * 2);

    mFocusArea->SetScreenArea(fX, fY, fW, fH);
    mFocusArea->SetCornersColor(TutorialConstants::colorFocusAction);
    mFocusArea->SetBlinking(true);
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(TutorialConstants::infoPlanetMapX, TutorialConstants::infoPlanetMapY);

    info->AddInfoEntry("I would suggest you to conquer the territory yourself.",
                       TutorialConstants::colorText, 6.f, true, true);
    info->AddInfoEntry("To do that click the button CONQUER.",
                       TutorialConstants::colorTextAction, 0.f, false, false, [this, fX, fY, fW, fH]
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

StepPlanetMapConquerTerritory::~StepPlanetMapConquerTerritory()
{
    delete mFocusArea;
}

} // namespace game
