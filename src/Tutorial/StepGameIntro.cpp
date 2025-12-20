#include "Tutorial/StepGameIntro.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

namespace game
{

StepGameIntro::StepGameIntro()
    : TutorialInfoStep(500, 250)
{
    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(200, 100);

    info->AddInfoEntry("Welcome commander,",
                       colorTutorialText, 4.f, true, false);
    info->AddInfoEntry("I am your field assistant and I am going to guide you during your first mission.",
                       colorTutorialText, 7.f, true, false);

    info->SetFunctionOnFinished([this]
    {
        SetDone();
    });
}

} // namespace game
