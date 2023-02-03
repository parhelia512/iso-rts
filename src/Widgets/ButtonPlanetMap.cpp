#include "ButtonPlanetMap.h"

#include "Widgets/GameSimpleTooltip.h"
#include "Widgets/GameUIData.h"

#include <sgl/graphic/Font.h>
#include <sgl/graphic/FontManager.h>
#include <sgl/media/AudioManager.h>
#include <sgl/media/AudioPlayer.h>

namespace game
{

// PRIMARY BUTTON
ButtonPlanetMap::ButtonPlanetMap(sgl::sgui::Widget * parent) :
    GameButton(SpriteFilePlanetMap,
        { IND_PM_BTN_NORMAL, IND_PM_BTN_DISABLED, IND_PM_BTN_OVER,
          IND_PM_BTN_PRESSED, IND_PM_BTN_NORMAL },
        { 0xd7eaf4ff, 0x335f73b2, 0xebf4f9ff, 0xc3dfeeff, 0xd7eaf4ff },
        parent)
{
    const char * fileFont = "Lato-Regular.ttf";
    const int size = 20;

    auto fm = sgl::graphic::FontManager::Instance();
    sgl::graphic::Font * fnt = fm->GetFont(fileFont, size, sgl::graphic::Font::NORMAL);
    SetLabelFont(fnt);
}

void ButtonPlanetMap::SetTooltipText(const char * tooltip)
{
    // TOOLTIP
    auto tt = new GameSimpleTooltip(tooltip);
    SetTooltip(tt);
    SetTooltipDelay(500);
    SetTooltipShowingTime(2500);
}

void ButtonPlanetMap::HandleMouseOver()
{
    sgl::sgui::AbstractButton::HandleMouseOver();

    auto player = sgl::media::AudioManager::Instance()->GetPlayer();
    player->PlaySound("UI/button_over-01.ogg");
}

void ButtonPlanetMap::HandleButtonDown()
{
    sgl::sgui::AbstractButton::HandleButtonDown();

    auto player = sgl::media::AudioManager::Instance()->GetPlayer();
    player->PlaySound("UI/button_click-01.ogg");
}

// SECONDARY BUTTON
SecondaryButtonPlanetMap::SecondaryButtonPlanetMap(sgl::sgui::Widget * parent) :
    GameButton(SpriteFilePlanetMap,
        { IND_PM_BTN2_NORMAL, IND_PM_BTN2_DISABLED, IND_PM_BTN2_OVER,
          IND_PM_BTN2_PRESSED, IND_PM_BTN2_NORMAL },
        { 0xf4e5d7ff, 0x735333b2, 0xf9f2ebff, 0xeed9c3ff, 0xf4e5d7ff },
        parent)
{
    const char * fileFont = "Lato-Regular.ttf";
    const int size = 20;

    auto fm = sgl::graphic::FontManager::Instance();
    sgl::graphic::Font * fnt = fm->GetFont(fileFont, size, sgl::graphic::Font::NORMAL);
    SetLabelFont(fnt);
}

void SecondaryButtonPlanetMap::HandleMouseOver()
{
    sgl::sgui::AbstractButton::HandleMouseOver();

    auto player = sgl::media::AudioManager::Instance()->GetPlayer();
    player->PlaySound("UI/button_over-01.ogg");
}

void SecondaryButtonPlanetMap::HandleButtonDown()
{
    sgl::sgui::AbstractButton::HandleButtonDown();

    auto player = sgl::media::AudioManager::Instance()->GetPlayer();
    player->PlaySound("UI/button_click_cancel-01.ogg");
}

} // namespace game
