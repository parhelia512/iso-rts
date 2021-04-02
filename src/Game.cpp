#include "Game.h"

#include "GameConstants.h"
#include "Player.h"
#include "States/StatesIds.h"
#include "States/StateGame.h"
#include "States/StateMainMenu.h"
#include "States/StateNewGame.h"
#include "States/StateTest.h"

#include <graphic/Font.h>
#include <graphic/FontManager.h>
#include <graphic/GraphicConstants.h>
#include <graphic/Image.h>
#include <graphic/Renderer.h>
#include <graphic/TextureManager.h>
#include <graphic/Window.h>
#include <sgui/Stage.h>
#include <utilities/StateManager.h>

#include <iostream>

namespace game
{

Game::Game(int argc, char * argv[])
    : lib::core::Application(argc, argv)
    , mMapFiles
    {
        "data/maps/10x10-01.map",
        "data/maps/11x11-01.map",
        "data/maps/12x12-01.map",
        "data/maps/15x15-01.map",
        "data/maps/20x20-01.map",
        "data/maps/40x40-01.map",
    }
{
    using namespace lib::graphic;

    mWin = Window::Create("Virtueror - v. 0.0.1", 1280, 720);
    mRenderer = Renderer::Create(mWin);
    mRenderer->SetLogicalSize(1920, 1080);

    TextureManager::Instance()->SetNewTextureQuality(TextureQuality::BEST);

    FontManager * fm = FontManager::Create();

    // -- State Manager --
    mStateMan = new lib::utilities::StateManager;

    mStateMan->AddState(new StateGame(this));
    mStateMan->AddState(new StateTest(this));
    mStateMan->AddState(new StateMainMenu(this));
    mStateMan->AddState(new StateNewGame(this));

    mStateMan->RequestNextActiveState(StateId::MAIN_MENU);

    // -- SGUI Stage --
    mStage = lib::sgui::Stage::Create();
    AddKeyboardListener(mStage);
    AddMouseListener(mStage);

    mFontGui = fm->GetFont("data/fonts/OpenSans.ttf", 32, Font::BOLD);
    mStage->SetDefaultFont(mFontGui);
}

Game::~Game()
{
    ClearPlayers();

    delete mStateMan;

    lib::sgui::Stage::Destroy();

    lib::graphic::FontManager::Destroy();

    lib::graphic::Renderer::Destroy();
    lib::graphic::Window::Destroy();
}

void Game::RequestNextActiveState(StateId sid) { mStateMan->RequestNextActiveState(sid); }

void Game::Update(float delta)
{
    mRenderer->Clear(mClearR, mClearG, mClearB, mClearA);

    mStateMan->UpdateActive();

    auto * state = static_cast<BaseGameState *>(mStateMan->GetActiveState());

    state->Update(delta);

    state->Render();
    mStage->Render();

    mRenderer->Finalize();
}

void Game::AddPlayer(const char * name, int pid)
{
    if(mPlayers.size() == MAX_NUM_PLAYERS)
        return;

    mPlayers.emplace_back(new Player(name, pid));
}

void Game::ClearPlayers()
{
    for(Player * p : mPlayers)
        delete p;

    mPlayers.clear();
}

} // namespace game
