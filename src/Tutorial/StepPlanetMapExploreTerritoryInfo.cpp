#include "Tutorial/StepPlanetMapExploreTerritoryInfo.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

#include <sgl/sgui/AbstractButton.h>

namespace game
{

StepPlanetMapExploreTerritoryInfo::StepPlanetMapExploreTerritoryInfo()
    : TutorialInfoStep(infoPlanetMapW, infoPlanetMapH)
{
    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(infoPlanetMapX, infoPlanetMapY);

    info->AddInfoEntry("As you can see exploring a territory requires to spend some resources.",
                       colorTutorialText, 7.f, true, true);
    info->AddInfoEntry("But it's well worth it as it reveals all the important details.",
                       colorTutorialText, 7.f, true, true);

    info->SetFunctionOnFinished([this]
    {
        SetDone();
    });
}

} // namespace game
