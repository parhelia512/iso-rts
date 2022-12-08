#include "Screens/SharedScreenListener.h"

#include "Game.h"
#include "Player.h"
#include "Screens/Screen.h"
#include "States/StatesIds.h"

#include <sgl/core/event/ApplicationEvent.h>
#include <sgl/core/event/KeyboardEvent.h>
#include <sgl/graphic/Window.h>

namespace game
{
void SharedScreenListener::OnApplicationQuit(sgl::core::ApplicationEvent & event)
{
    mScreen->GetGame()->Exit();

    event.SetConsumed();
}

void SharedScreenListener::OnKeyUp(sgl::core::KeyboardEvent & event)
{
    using namespace sgl::core;
    using namespace sgl::graphic;

    const int key = event.GetKey();

    // EXIT
    if(key == KeyboardEvent::KEY_ESC)
        mScreen->GetGame()->Exit();

    // -- SCREENS NAVIGATION --
    else if(key == KeyboardEvent::KEY_M)
        mScreen->GetGame()->RequestNextActiveState(StateId::MAIN_MENU);
    else if(key == KeyboardEvent::KEY_T)
        mScreen->GetGame()->RequestNextActiveState(StateId::TEST);

    // -- WINDOW --
    else if(key == KeyboardEvent::KEY_F)
        Window::Instance()->SwitchFullscreen();
    else if(key == KeyboardEvent::KEY_F1)
        Window::Instance()->SetSize(1280, 720);
    else if(key == KeyboardEvent::KEY_F2)
        Window::Instance()->SetSize(1600, 900);
    else if(key == KeyboardEvent::KEY_F3)
        Window::Instance()->SetSize(1920, 1080);
    else if(key == KeyboardEvent::KEY_F4)
        Window::Instance()->SetSize(2560, 1440);

    // -- GAME --
    // DEBUG: SHIFT/CTRL + R -> add/remove resources
    else if(key == KeyboardEvent::KEY_R)
    {
        Player * p = mGame->GetLocalPlayer();

        if(event.IsModShiftDown())
        {
            p->SumResource(Player::Stat::MONEY, 500);
            p->SumResource(Player::Stat::ENERGY, 100);
            p->SumResource(Player::Stat::MATERIAL, 100);
            p->SumResource(Player::Stat::BLOBS, 10);
            p->SumResource(Player::Stat::DIAMONDS, 10);
        }
        else if(event.IsModCtrlDown())
        {
            p->SumResource(Player::Stat::MONEY, -500);
            p->SumResource(Player::Stat::ENERGY, -100);
            p->SumResource(Player::Stat::MATERIAL, -100);
            p->SumResource(Player::Stat::BLOBS, -10);
            p->SumResource(Player::Stat::DIAMONDS, -10);
        }
    }
}

} // namespace game
