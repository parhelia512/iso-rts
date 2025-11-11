#include "States/StatePlanetMap.h"

#include "Game.h"
#include "Screens/ScreenPlanetMap.h"
#include "States/StatesIds.h"

namespace game
{

StatePlanetMap::StatePlanetMap(Game * game)
    : BaseGameState(StateId::PLANET_MAP, game)
{
}

void StatePlanetMap::OnActive()
{
    mScreen = new ScreenPlanetMap(mGame);

    mGame->AddKeyboardListener(mScreen);
}

void StatePlanetMap::OnInactive()
{
    delete mScreen;
    mScreen = nullptr;
}

} // namespace game
