#include "Tutorial/StepPlanetMapIntro.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

namespace game
{

StepPlanetMapIntro::StepPlanetMapIntro()
    : TutorialInfoStep(infoPlanetMapW, infoPlanetMapH)
{
    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(infoPlanetMapX, infoPlanetMapY);

    info->AddInfoEntry("Welcome commander,",
                       colorTutorialText, 3.5f, true, true);
    info->AddInfoEntry("I am your assistant and I will guide you in your first planet conquest.",
                       colorTutorialText, 6.f, true, true);
    info->AddInfoEntry("This is the planet screen, where you can decide how to manage your expansion.",
                       colorTutorialText, 7.f, true, true);

    info->SetFunctionOnFinished([this]
    {
        SetDone();
    });
}

} // namespace game
