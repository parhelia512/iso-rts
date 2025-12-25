#include "Tutorial/StepGameStructConnected.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

namespace game
{

StepGameStructConnected::StepGameStructConnected()
    : TutorialInfoStep(750, 350)
{
    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(200, 100);

    info->AddInfoEntry("Well done commander!", TutorialConstants::colorText, 4.f, true, true);
    info->AddInfoEntry("Now the energy generator is connected to your base and from now on you "
                       "will receive energy from it every turn.", TutorialConstants::colorText, 10.f, true, false);
    info->AddInfoEntry("Connecting structures to your base will also grow your influence area, which is "
                       "delimited by the colored line surrounding all this area.", TutorialConstants::colorText,
                       12.f, true, false);
    info->AddInfoEntry("The bigger your influence area is the more money you will gain every turn, but it "
                       "will make it harder to defend your outpost, so plan your expansion carefully.",
                       TutorialConstants::colorText, 13.f, true, false);

    info->SetFunctionOnFinished([this]
    {
        SetDone();
    });
}

} // namespace game
