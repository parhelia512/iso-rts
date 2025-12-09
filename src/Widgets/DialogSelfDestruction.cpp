#include "Widgets/DialogSelfDestruction.h"

#include "Widgets/ButtonObjectActionOption.h"
#include "Widgets/ButtonDialogClose.h"
#include "Widgets/GameButton.h"
#include "Widgets/GameSimpleTooltip.h"
#include "Widgets/GameUIData.h"
#include "Widgets/WidgetsConstants.h"

#include <sgl/core/event/KeyboardEvent.h>
#include <sgl/graphic/Font.h>
#include <sgl/graphic/FontManager.h>
#include <sgl/graphic/Image.h>
#include <sgl/graphic/Text.h>
#include <sgl/graphic/TextureManager.h>
#include <sgl/media/AudioManager.h>
#include <sgl/media/AudioPlayer.h>
#include <sgl/sgui/ImageButton.h>
#include <sgl/utilities/System.h>

/*
// anonymous namespace for local "private" classes
namespace
{

using namespace game;

// ===== BUTTON CONFIRMATION =====
class ButtonDialog : public GameButton
{
public:
    ButtonDialog(sgl::sgui::Widget * parent)
        : GameButton(SpriteFileDialogDestruction,
                     { ID_DLG_DESTR_BTN1_NORMAL, ID_DLG_DESTR_BTN1_DISABLED,
                       ID_DLG_DESTR_BTN1_OVER, ID_DLG_DESTR_BTN1_PUSHED, ID_DLG_DESTR_BTN1_PUSHED },
                     { 0xc6dde9ff, 0x5c6970ff, 0xdae9f1ff, 0xb3d4e5ff, 0xb3d4e5ff },
                     parent)
    {
        using namespace sgl;

        const int size = 24;

        auto fm = graphic::FontManager::Instance();
        auto fnt = fm->GetFont(WidgetsConstants::FontFileButton, size, graphic::Font::NORMAL);
        SetLabelFont(fnt);
    }

    void SetTooltipText(const char * text)
    {
        const int timeShowing = 4000;

        auto tt = new GameSimpleTooltip(text);
        SetTooltip(tt);
        SetTooltipDelay(WidgetsConstants::timeTooltipButtonDelay);
        SetTooltipShowingTime(timeShowing);
    }

    void HandleMouseOver() override
    {
        sgl::sgui::AbstractButton::HandleMouseOver();

        auto player = sgl::media::AudioManager::Instance()->GetPlayer();
        player->PlaySound("UI/button_over-01.ogg");
    }

    void HandleButtonDown() override
    {
        sgl::sgui::AbstractButton::HandleButtonDown();

        auto player = sgl::media::AudioManager::Instance()->GetPlayer();
        player->PlaySound("UI/button_click-01.ogg");
    }
};

} // namespace
*/

namespace game
{

// ===== DIALOG =====
DialogSelfDestruction::DialogSelfDestruction()
{
    using namespace sgl;

    SetResizePolicy(sgui::Widget::GROW_ONLY);

    auto fm = graphic::FontManager::Instance();
    auto tm = graphic::TextureManager::Instance();

    const int tooltipTime = 4000;
    const int marginB = 10;

    // BUTTON DESTROY
    auto btn = new ButtonObjectActionOption("DESTROY", "1", core::KeyboardEvent::KEY_1, this);
    btn->SetTooltipText("Dismantle this object without damaging anything around it.", tooltipTime);
    mBtnDestroy = btn;

    // BUTTON BLOW UP
    btn = new ButtonObjectActionOption("BLOW UP", "2", core::KeyboardEvent::KEY_2, this);
    btn->SetTooltipText("Blow this object up damaging everything that surrounds it.", tooltipTime);
    mBtnBlowup = btn;

    btn->SetY(mBtnDestroy->GetHeight() + marginB);

}

void DialogSelfDestruction::AddFunctionOnDestroy(const std::function<void()> & f)
{
    mBtnDestroy->AddOnClickFunction(f);
}

void DialogSelfDestruction::AddFunctionOnBlowup(const std::function<void()> & f)
{
    mBtnBlowup->AddOnClickFunction(f);
}

} // namespace game
