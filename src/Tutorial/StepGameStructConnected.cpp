#include "Tutorial/StepGameStructConnected.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

namespace game
{

StepGameStructConnected::StepGameStructConnected()
    : TutorialInfoStep(750, 330)
{
    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(200, 100);

    info->AddInfoEntry("Now the energy generator is connected to your base and it will give "
                       "you energy every turn.", TutorialConstants::colorText, 10.f, true, false);
    info->AddInfoEntry("Connecting structures to your base also grows your influence area, "
                       "which is delimited by the colored line surrounding all this area.",
                       TutorialConstants::colorText, 12.f, true, false);
    info->AddInfoEntry("A bigger influence area will gain you more money every turn, but it "
                       "will make it harder to defend your outpost, so plan your expansion "
                       "carefully.", TutorialConstants::colorText, 13.f, true, false);

    info->SetFunctionOnFinished([this]
    {
        SetDone();
    });
}

} // namespace game
