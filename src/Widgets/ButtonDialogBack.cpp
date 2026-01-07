#include "ButtonDialogBack.h"

#include "Widgets/GameUIData.h"
#include "Widgets/WidgetsConstants.h"

#include <sgl/graphic/Font.h>
#include <sgl/graphic/FontManager.h>
#include <sgl/media/AudioManager.h>
#include <sgl/media/AudioPlayer.h>
#include <sgl/utilities/StringManager.h>

namespace game
{

ButtonDialogBack::ButtonDialogBack(sgl::sgui::Widget * parent)
    : GameButton(SpriteFileFactionSelection,
                {
                    IND_FSEL_BACK_NORMAL,
                    IND_FSEL_BACK_NORMAL,
                    IND_FSEL_BACK_OVER,
                    IND_FSEL_BACK_PUSHED,
                    IND_FSEL_BACK_NORMAL
                 },
                 {
                    0xd6ebf5ff,
                    0xFFFFFFFF,
                    0xecf5f9ff,
                    0xd7eaf4ff,
                    0xFFFFFFFF
                 },
                 parent)
{
    using namespace sgl;

    // set label font
    auto fm = graphic::FontManager::Instance();
    auto font = fm->GetFont(WidgetsConstants::FontFileButton, 28, graphic::Font::NORMAL);

    SetLabelFont(font);

    // init label
    auto sm = utilities::StringManager::Instance();
    SetLabel(sm->GetCString("BACK"));
}

void ButtonDialogBack::HandleMouseOver()
{
    sgl::sgui::AbstractButton::HandleMouseOver();

    auto player = sgl::media::AudioManager::Instance()->GetPlayer();
    player->PlaySound("UI/button_over-02.ogg");
}

void ButtonDialogBack::HandleButtonDown()
{
    sgl::sgui::AbstractButton::HandleButtonDown();

    auto player = sgl::media::AudioManager::Instance()->GetPlayer();
    player->PlaySound("UI/button_click-02.ogg");
}

} // namespace game
