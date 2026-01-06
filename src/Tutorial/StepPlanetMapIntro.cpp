#include "Tutorial/StepPlanetMapIntro.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

namespace game
{

StepPlanetMapIntro::StepPlanetMapIntro(bool won)
    : TutorialInfoStep(TutorialConstants::infoPlanetMapW, TutorialConstants::infoPlanetMapH)
{
    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(TutorialConstants::infoPlanetMapX, TutorialConstants::infoPlanetMapY);

    if(won)
        info->AddInfoEntry("Welcome back commander and well done on your first victory!",
                           TutorialConstants::colorText, 5.f, true, true);
    else
        info->AddInfoEntry("Welcome back commander,\n"
                           "your first mission didn't go well, but the war is not over!",
                           TutorialConstants::colorText, 7.f, true, true);

    info->AddInfoEntry("This is the planet screen, where you can plan your expansion.",
                       TutorialConstants::colorText, 8.f, true, true);

    info->SetFunctionOnFinished([this]
    {
        SetDone();
    });
}

} // namespace game
