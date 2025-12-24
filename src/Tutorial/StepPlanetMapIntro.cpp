#include "Tutorial/StepPlanetMapIntro.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

namespace game
{

StepPlanetMapIntro::StepPlanetMapIntro()
    : TutorialInfoStep(TutorialConstants::infoPlanetMapW, TutorialConstants::infoPlanetMapH)
{
    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(TutorialConstants::infoPlanetMapX, TutorialConstants::infoPlanetMapY);

    info->AddInfoEntry("Welcome commander,",
                       TutorialConstants::colorText, 4.f, true, true);
    info->AddInfoEntry("I am your assistant and I will guide you in your first planet conquest.",
                       TutorialConstants::colorText, 7.f, true, true);
    info->AddInfoEntry("This is the planet screen, where you can decide how to manage your expansion.",
                       TutorialConstants::colorText, 8.f, true, true);

    info->SetFunctionOnFinished([this]
    {
        SetDone();
    });
}

} // namespace game
