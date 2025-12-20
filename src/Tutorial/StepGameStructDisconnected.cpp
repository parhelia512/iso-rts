#include "Tutorial/StepGameStructDisconnected.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

namespace game
{

StepGameStructDisconnected::StepGameStructDisconnected()
    : TutorialInfoStep(550, 350)
{
    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(1300, 250);

    info->AddInfoEntry("Okay, enough of that for now. Let's go back to your conquest!",
                       colorTutorialText, 6.f, true, true);
    info->AddInfoEntry("You might have noticed the blinking icon on top of the energy generator.",
                       colorTutorialText, 7.f, true, false);
    info->AddInfoEntry("That means that this structire is not connected to your base yet, hence "
                       "it's not active.", colorTutorialText, 7.f, true, false);
    info->AddInfoEntry("To connect it to your base you need to create a path of conquered cells "
                       "with your unit.", colorTutorialText, 11.f, true, false);

    info->SetFunctionOnFinished([this]
    {
        SetDone();
    });
}

} // namespace game
