#include "Tutorial/StepPlanetMapExploreTerritoryInfo.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

#include <sgl/sgui/AbstractButton.h>

namespace game
{

StepPlanetMapExploreTerritoryInfo::StepPlanetMapExploreTerritoryInfo()
    : TutorialInfoStep(TutorialConstants::infoPlanetMapW, TutorialConstants::infoPlanetMapH)
{
    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(TutorialConstants::infoPlanetMapX, TutorialConstants::infoPlanetMapY);

    info->AddInfoEntry("As you can see, exploring a territory requires some resources.",
                       TutorialConstants::colorText, 7.f, true, true);
    info->AddInfoEntry("But it's well worth it as it reveals some important data.",
                       TutorialConstants::colorText, 7.f, true, true);

    info->SetFunctionOnFinished([this]
    {
        SetDone();
    });
}

} // namespace game
