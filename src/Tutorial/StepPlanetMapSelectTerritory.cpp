#include "Tutorial/StepPlanetMapSelectTerritory.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/PlanetMap.h"
#include "Widgets/Tutorial/FocusArea.h"
#include "Widgets/Tutorial/PanelClickFilter.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

#include <sgl/sgui/AbstractButton.h>

namespace game
{

StepPlanetMapSelectTerritory::StepPlanetMapSelectTerritory(PlanetMap * planet, bool won)
    : TutorialInfoStep(TutorialConstants::infoPlanetMapW, TutorialConstants::infoPlanetMapH)
    , mFocusArea(new FocusArea)
{
    // FOCUS
    const unsigned int buttonId = won ? 2 : 1;
    mTerritory = planet->GetButton(buttonId);

    const int padding = 10;
    const int fX = planet->GetX() + mTerritory->GetX() - padding;
    const int fY = planet->GetY() + mTerritory->GetY() - padding;
    const int fW = mTerritory->GetWidth() + (padding * 2);
    const int fH = mTerritory->GetHeight() + (padding * 2);

    mFocusArea->SetScreenArea(fX, fY, fW, fH);
    mFocusArea->SetCornersColor(TutorialConstants::colorFocusElement);
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(TutorialConstants::infoPlanetMapX, TutorialConstants::infoPlanetMapY);

    info->AddInfoEntry("Let's start to explore a territory of this planet.",
                       TutorialConstants::colorText, 6.f, true, true);
    info->AddInfoEntry("Select this one with the LEFT MOUSE BUTTON",
                       TutorialConstants::colorTextAction, 0.f, false, false);

    info->SetFunctionOnFinished([this, fX, fY, fW, fH]
    {
        mFocusArea->SetCornersColor(TutorialConstants::colorFocusAction);
        mFocusArea->SetBlinking(true);

        GetClickFilter()->SetScreenClickableArea(fX, fY, fW, fH);

        mCheckTerritorySelected = true;
    });
}

StepPlanetMapSelectTerritory::~StepPlanetMapSelectTerritory()
{
    delete mFocusArea;
}

void StepPlanetMapSelectTerritory::OnStart()
{
    TutorialInfoStep::OnStart();

    // FOCUS
    mFocusArea->SetVisible(true);
}

void StepPlanetMapSelectTerritory::Update(float)
{
    if(mCheckTerritorySelected)
    {
        if(mTerritory->IsChecked())
            SetDone();
    }
}

} // namespace game
