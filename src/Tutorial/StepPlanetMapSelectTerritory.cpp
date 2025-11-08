#include "Tutorial/StepPlanetMapSelectTerritory.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/PlanetMap.h"
#include "Widgets/Tutorial/FocusArea.h"
#include "Widgets/Tutorial/PanelClickFilter.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

#include <sgl/sgui/AbstractButton.h>

namespace game
{

StepPlanetMapSelectTerritory::StepPlanetMapSelectTerritory(PlanetMap * planet)
    : TutorialInfoStep(infoPlanetMapW, infoPlanetMapH)
    , mFocusArea(new FocusArea)
{
    // FOCUS
    mTerritory = planet->GetButton(0);

    const int padding = 10;
    const int fX = planet->GetX() + mTerritory->GetX() - padding;
    const int fY = planet->GetY() + mTerritory->GetY() - padding;
    const int fW = mTerritory->GetWidth() + (padding * 2);
    const int fH = mTerritory->GetHeight() + (padding * 2);

    mFocusArea->SetScreenArea(fX, fY, fW, fH);
    mFocusArea->SetCornersColor(colorTutorialFocusElement);
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(infoPlanetMapX, infoPlanetMapY);

    info->AddInfoEntry("Let's start to explore a territory of this planet.",
                       colorTutorialText, 5.f, true, true);
    info->AddInfoEntry("Select this one in the top with the LEFT MOUSE BUTTON", colorTutorialTextAction,
                       0.f, false, false);

    info->SetFunctionOnFinished([this, fX, fY, fW, fH]
    {
        mFocusArea->SetCornersColor(colorTutorialFocusAction);
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
