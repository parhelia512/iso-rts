#include "Widgets/ButtonDialogAction.h"

#include "Widgets/GameUIData.h"
#include "Widgets/WidgetsConstants.h"

#include <sgl/graphic/Font.h>
#include <sgl/graphic/FontManager.h>
#include <sgl/graphic/Text.h>
#include <sgl/media/AudioManager.h>
#include <sgl/media/AudioPlayer.h>

namespace game
{

ButtonDialogAction::ButtonDialogAction(const char * text, const char * shortcut,
                                       int shortcutKey, sgl::sgui::Widget * parent)
    : GameButton(SpriteFileDialogNewElement,
                 { IND_DLG_NEWE_BUILD_NORMAL, IND_DLG_NEWE_BUILD_DISABLED,
                   IND_DLG_NEWE_BUILD_OVER, IND_DLG_NEWE_BUILD_PUSHED,
                   IND_DLG_NEWE_BUILD_PUSHED },
                 { 0xe3e6e8ff, 0x454f54ff, 0xf1f2f4ff, 0xabb4baff, 0xc2c2a3ff}, parent)
{
    using namespace sgl;

    auto fm = graphic::FontManager::Instance();

    // LABEL
    auto font = fm->GetFont(WidgetsConstants::FontFileButton, 18, graphic::Font::NORMAL);
    SetLabelFont(font);
    SetLabel(text);

    // SHORTCUT
    font = fm->GetFont(WidgetsConstants::FontFileShortcut, 11, graphic::Font::NORMAL);
    mShortcut = new graphic::Text(shortcut, font, true);
    mShortcut->SetColor(WidgetsConstants::colorShortcut);

    RegisterRenderable(mShortcut);

    SetShortcutKey(shortcutKey);

    SetPositions();
}

void ButtonDialogAction::HandleMouseOver()
{
    GameButton::HandleMouseOver();

    auto player = sgl::media::AudioManager::Instance()->GetPlayer();
    player->PlaySound("UI/button_over-01.ogg");
}

void ButtonDialogAction::HandleButtonDown()
{
    GameButton::HandleButtonDown();

    auto player = sgl::media::AudioManager::Instance()->GetPlayer();
    player->PlaySound("UI/button_click_long-02.ogg");
}

void ButtonDialogAction::HandlePositionChanged()
{
    GameButton::HandlePositionChanged();

    SetPositions();
}

void ButtonDialogAction::SetPositions()
{
    const int x0 = GetScreenX();
    const int y0 = GetScreenY();

    // SHORTCUT
    const int shortBgX0 = 182;
    const int shortBgY0 = 22;
    const int shortBgSize = 14;

    const int shortcutX = x0 + shortBgX0 + (shortBgSize - mShortcut->GetWidth()) / 2;
    const int shortcutY = y0 + shortBgY0 + (shortBgSize - mShortcut->GetHeight()) / 2;

    mShortcut->SetPosition(shortcutX, shortcutY);
}

void ButtonDialogAction::OnStateChanged(sgl::sgui::AbstractButton::VisualState state)
{
    GameButton::OnStateChanged(state);

    // update shortcut label
    if(DISABLED == state)
        mShortcut->SetColor(WidgetsConstants::colorShortcutDisabled);
    else
        mShortcut->SetColor(WidgetsConstants::colorShortcut);
}

} // namespace game
