#include "Tutorial/StepGameMapNavigation.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

namespace game
{

StepGameMapNavigation::StepGameMapNavigation()
    : TutorialInfoStep(650, 400)
{
    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(1200, 450);

    info->AddInfoEntry("Now that you learned how to control your units I want to show you how to move around.",
                       TutorialConstants::colorText, 9.f, true, true);
    info->AddInfoEntry("You can navigate the map in 3 different ways:", TutorialConstants::colorText, 5.f, true, false);
    info->AddInfoEntry("- You can move your mouse to the border of the screen and the map will scroll in that "
                       "direction.", TutorialConstants::colorText, 12.f, true, false);
    info->AddInfoEntry("- You can use the keyboard keys W, A, S, D to move in the 4 directions.",
                       TutorialConstants::colorText, 10.f, true, false);
    info->AddInfoEntry("- You can click with your LEFT MOUSE button on it and drag to move in the opposite "
                       "direction.", TutorialConstants::colorText, 10.f, true, false);
    info->AddInfoEntry("Now I will let you to practice and to explore this map.",
                       TutorialConstants::colorText, 9.f, true, false);

    info->SetFunctionOnFinished([this]
    {
        SetDone();
    });
}

} // namespace game
