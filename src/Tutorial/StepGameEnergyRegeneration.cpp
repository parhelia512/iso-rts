#include "Tutorial/StepGameEnergyRegeneration.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

namespace game
{

StepGameEnergyRegeneration::StepGameEnergyRegeneration()
    : TutorialInfoStep(600, 325)
{
    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(1250, 600);

    info->AddInfoEntry("Now all your faction energy is restored.",
                       TutorialConstants::colorText, 6.f, true, false);
    info->AddInfoEntry("Your unit's energy is fully restored too, but it's not always like that.",
                       TutorialConstants::colorText, 7.f, true, false);
    info->AddInfoEntry("The amount restored depends on its REGENERATION attribute and by how much "
                       "energy was left when you ended your turn.", TutorialConstants::colorText,
                       11.f, true, false);

    info->SetFunctionOnFinished([this]
    {
        SetDone();
    });
}

} // namespace game
