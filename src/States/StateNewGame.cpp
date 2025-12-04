#include "States/StateNewGame.h"

#include "Game.h"
#include "Screens/ScreenNewGame.h"
#include "States/StatesIds.h"

namespace game
{

StateNewGame::StateNewGame(Game * game)
    : BaseGameState(StateId::NEW_GAME, game)
{
}

void StateNewGame::OnActive()
{
    mGame->InitGameData();

    mScreen = new ScreenNewGame(mGame);
}

void StateNewGame::OnInactive()
{
    delete mScreen;
    mScreen = nullptr;
}

} // namespace game
