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
                       colorTutorialText, 3.5f, true, false);
    info->AddInfoEntry("I am your field assistant and I am going to guide you during your first mission.",
                       colorTutorialText, 6.f, true, false);

    info->SetFunctionOnFinished([this]
    {
        SetDone();
    });
}

} // namespace game
