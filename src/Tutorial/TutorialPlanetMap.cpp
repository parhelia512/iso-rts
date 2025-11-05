#include "Tutorial/TutorialPlanetMap.h"

#include "GameConstants.h"
#include "Screens/ScreenPlanetMap.h"
#include "Tutorial/StepDelay.h"
#include "Tutorial/StepPlanetMapConquerTerritory.h"
#include "Tutorial/StepPlanetMapConquerTerritoryStart.h"
#include "Tutorial/StepPlanetMapIntro.h"
#include "Tutorial/StepPlanetMapExploreTerritory.h"
#include "Tutorial/StepPlanetMapExploreTerritoryInfo.h"
#include "Tutorial/StepPlanetMapExploreTerritoryStart.h"
#include "Tutorial/StepPlanetMapExploreTerritorySuccess.h"
#include "Tutorial/StepPlanetMapNoInfo.h"
#include "Tutorial/StepPlanetMapSelectTerritory.h"
#include "Tutorial/StepPlanetMapSendAI.h"

namespace game
{

TutorialPlanetMap::TutorialPlanetMap(ScreenPlanetMap * screen)
    : Tutorial(TUTORIAL_PLANET_MAP, screen->GetGame())
    , mScreen(screen)
{
    AddStep(new StepDelay(1.f));
    AddStep(new StepPlanetMapIntro);
    AddStep(new StepPlanetMapSelectTerritory(mScreen->mPlanet));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepPlanetMapNoInfo(mScreen->mPanelInfo, mScreen->mPanelResources));
    AddStep(new StepPlanetMapExploreTerritory(mScreen->mPanelActions));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepPlanetMapExploreTerritoryInfo);
    AddStep(new StepPlanetMapExploreTerritoryStart(mScreen->mPanelExplore));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepPlanetMapExploreTerritorySuccess(mScreen->mPanelExplore, mScreen->mPanelInfo,
                                                     mScreen->mPanelResources));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepPlanetMapSendAI(mScreen->mPanelActions));
    AddStep(new StepPlanetMapConquerTerritory(mScreen->mPanelActions));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepPlanetMapConquerTerritoryStart(mScreen->mPanelConquer));
}

} // namespace game
