#include "Widgets/ButtonDialogArrows.h"

#include "Widgets/GameUIData.h"

#include <sgl/core/event/KeyboardEvent.h>
#include <sgl/media/AudioManager.h>
#include <sgl/media/AudioPlayer.h>

namespace game
{

// ===== BUTTON LEFT ARROW =====
ButtonDialogArrowLeft::ButtonDialogArrowLeft(sgl::sgui::Widget * parent)
    : sgl::sgui::ImageButton({ IND_DLG_NEWE_LEFT_NORMAL, IND_DLG_NEWE_LEFT_DISABLED,
                               IND_DLG_NEWE_LEFT_OVER, IND_DLG_NEWE_LEFT_PUSHED,
                               IND_DLG_NEWE_LEFT_NORMAL }, SpriteFileDialogNewElement, parent)
{
    SetShortcutKey(sgl::core::KeyboardEvent::KEY_LEFT);
}

void ButtonDialogArrowLeft::HandleMouseOver()
{
    sgl::sgui::AbstractButton::HandleMouseOver();

    auto player = sgl::media::AudioManager::Instance()->GetPlayer();
    player->PlaySound("UI/button_over-03.ogg");
}

void ButtonDialogArrowLeft::HandleButtonDown()
{
    sgl::sgui::AbstractButton::HandleButtonDown();

    auto player = sgl::media::AudioManager::Instance()->GetPlayer();
    player->PlaySound("UI/button_click-03.ogg");
}

// ===== BUTTON RIGHT ARROW =====
ButtonDialogArrowRight::ButtonDialogArrowRight(sgl::sgui::Widget * parent)
    : sgl::sgui::ImageButton({ IND_DLG_NEWE_RIGHT_NORMAL, IND_DLG_NEWE_RIGHT_DISABLED,
                               IND_DLG_NEWE_RIGHT_OVER, IND_DLG_NEWE_RIGHT_PUSHED,
                               IND_DLG_NEWE_RIGHT_NORMAL }, SpriteFileDialogNewElement, parent)
{
    SetShortcutKey(sgl::core::KeyboardEvent::KEY_RIGHT);
}

void ButtonDialogArrowRight::HandleMouseOver()
{
    sgl::sgui::AbstractButton::HandleMouseOver();

    auto player = sgl::media::AudioManager::Instance()->GetPlayer();
    player->PlaySound("UI/button_over-03.ogg");
}

void ButtonDialogArrowRight::HandleButtonDown()
{
    sgl::sgui::AbstractButton::HandleButtonDown();

    auto player = sgl::media::AudioManager::Instance()->GetPlayer();
    player->PlaySound("UI/button_click-03.ogg");
}

} // namespace game
