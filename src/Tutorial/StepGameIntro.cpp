#include "Tutorial/StepGameIntro.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

namespace game
{

StepGameIntro::StepGameIntro()
    : TutorialInfoStep(550, 250)
{
    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(200, 100);

    info->AddInfoEntry("Welcome commander,",
                       TutorialConstants::colorText, 4.f, true, false);
    info->AddInfoEntry("I am your field assistant and I am going to guide you during your first mission.",
                       TutorialConstants::colorText, 7.f, true, false);

    info->SetFunctionOnFinished([this]
    {
        SetDone();
    });
}

} // namespace game
