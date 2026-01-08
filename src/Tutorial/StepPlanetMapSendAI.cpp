#include "Tutorial/StepPlanetMapSendAI.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/PanelPlanetActions.h"
#include "Widgets/Tutorial/FocusArea.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

#include <sgl/sgui/AbstractButton.h>

namespace game
{

StepPlanetMapSendAI::StepPlanetMapSendAI(PanelPlanetActions * panel)
    : TutorialInfoStep(TutorialConstants::infoPlanetMapW, TutorialConstants::infoPlanetMapH)
    , mFocusArea(new FocusArea)
{
    // FOCUS
    auto btn = panel->GetButton(PanelPlanetActions::SEND_AI);

    const int padding = 10;
    const int fX = panel->GetX() + btn->GetX() - padding;
    const int fY = panel->GetY() + btn->GetY() - padding;
    const int fW = btn->GetWidth() + (padding * 2);
    const int fH = btn->GetHeight() + (padding * 2);

    mFocusArea->SetScreenArea(fX, fY, fW, fH);
    mFocusArea->SetCornersColor(TutorialConstants::colorFocusElement);
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(TutorialConstants::infoPlanetMapX, TutorialConstants::infoPlanetMapY);

    info->AddInfoEntry("Now that this territory is explored you can decide if you want to conquer it "
                       "or not.", TutorialConstants::colorText, 7.f, true, true);
    info->AddInfoEntry("You can send an AI general to do the job for you, but it will cost you "
                       "a lot of resources.",
                       TutorialConstants::colorText, 8.f, true, true, [this]
                       {
                           mFocusArea->SetBlinking(true);
                           mFocusArea->SetVisible(true);
                       });

    info->SetFunctionOnFinished([this]
    {
        SetDone();
    });
}

StepPlanetMapSendAI::~StepPlanetMapSendAI()
{
    delete mFocusArea;
}

} // namespace game
