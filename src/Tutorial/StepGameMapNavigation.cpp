#include "Tutorial/StepGameMapNavigation.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

namespace game
{

StepGameMapNavigation::StepGameMapNavigation()
    : TutorialInfoStep(750, 400)
{
    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(1100, 450);

    info->AddInfoEntry("Now I want to show you how to move around.",
                       TutorialConstants::colorText, 9.f, true, true);
    info->AddInfoEntry("You can navigate a map in 3 different ways:",
                       TutorialConstants::colorText, 5.f, true, false);
    info->AddInfoEntry("- You can move your mouse to the border of the screen to move in "
                       "that direction.", TutorialConstants::colorText, 12.f, true, false);
    info->AddInfoEntry("- You can use the keyboard keys W, A, S, D to move in the 4 directions.",
                       TutorialConstants::colorText, 10.f, true, false);
    info->AddInfoEntry("- You can hold your LEFT MOUSE button and drag to move in the opposite "
                       "direction.", TutorialConstants::colorText, 10.f, true, false);
    info->AddInfoEntry("Now you can practice and explore this map.",
                       TutorialConstants::colorText, 9.f, true, false);

    info->SetFunctionOnFinished([this]
    {
        SetDone();
    });
}

} // namespace game
