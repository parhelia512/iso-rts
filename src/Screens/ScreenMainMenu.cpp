#include "Screens/ScreenMainMenu.h"

#include "Game.h"
#include "States/StatesIds.h"

#include <graphic/Renderer.h>
#include <sgui/PushButton.h>
#include <sgui/Stage.h>

namespace game
{

ScreenMainMenu::ScreenMainMenu(Game * game)
    : Screen(game)
{
    using namespace lib::graphic;
    using namespace lib::sgui;

    game->SetClearColor(0x11, 0x11, 0x11, 0xFF);

    Widget * panel = new Widget(0);

    int buttonY = 0;
    const int VMARGIN = 100;

    // -- BUTTON NEW GAME --
    PushButton * button = new PushButton(panel);
    button->SetBackground("data/img/buttons/main_menu-bg-01.png");
    button->SetLabel("NEW GAME");
    button->SetLabelColor(0x183929FF);

    button->SetOnClickFunction([this]
    {
        Game * game = GetGame();

        game->AddPlayer("PLAYER 1", 1);

        game->RequestNextActiveState(StateId::GAME);
    });

    buttonY += button->GetHeight() + VMARGIN;

    // -- BUTTON EXIT --
    button = new PushButton(panel);
    button->SetBackground("data/img/buttons/main_menu-bg-01.png");
    button->SetLabel("EXIT");
    button->SetLabelColor(0x183929FF);

    button->SetOnClickFunction([this] { GetGame()->Exit(); });

    button->SetY(buttonY);

    // position buttons panel
    const int containerX = (Renderer::Instance()->GetWidth() - panel->GetWidth()) * 0.5f;
    const int containerY = 300;
    panel->SetPosition(containerX, containerY);
}

ScreenMainMenu::~ScreenMainMenu()
{
    lib::sgui::Stage::Instance()->ClearWidgets();
}

void ScreenMainMenu::Update()
{
}

void ScreenMainMenu::Render()
{
}

} // namespace game
