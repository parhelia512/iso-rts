#include "Widgets/DialogSelfDestruction.h"

#include "Screens/Screen.h"
#include "Widgets/GameButton.h"
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

// ===== BUTTON CLOSE DIALOG =====
class ButtonClose : public sgl::sgui::ImageButton
{
public:
    ButtonClose(sgl::sgui::Widget * parent)
        : sgl::sgui::ImageButton({ ID_DLG_DESTR_BTN_CLOSE_NORMAL, ID_DLG_DESTR_BTN_CLOSE_DISABLED,
                                   ID_DLG_DESTR_BTN_CLOSE_OVER, ID_DLG_DESTR_BTN_CLOSE_PUSHED,
                                   ID_DLG_DESTR_BTN_CLOSE_PUSHED }, SpriteFileDialogDestruction, parent)
    {
        SetShortcutKey(sgl::core::KeyboardEvent::KEY_ESCAPE);
    }

private:
    void HandleMouseOver() override
    {
        sgl::sgui::AbstractButton::HandleMouseOver();

        auto player = sgl::media::AudioManager::Instance()->GetPlayer();
        player->PlaySound("UI/button_over-02.ogg");
    }

    void HandleButtonDown() override
    {
        sgl::sgui::AbstractButton::HandleButtonDown();

        auto player = sgl::media::AudioManager::Instance()->GetPlayer();
        player->PlaySound("UI/button_click-02.ogg");
    }
};

} // namespace

namespace game
{

// ===== DIALOG =====
DialogSelfDestruction::DialogSelfDestruction()
{
    using namespace sgl;

    auto fm = graphic::FontManager::Instance();
    auto tm = graphic::TextureManager::Instance();

    const int marginL = 40;
    const int marginT = 8;

    // BACKGROUND
    graphic::Texture * tex = tm->GetSprite(SpriteFileDialogDestruction, ID_DLG_DESTR_BG);
    mBg = new graphic::Image(tex);
    RegisterRenderable(mBg);

    const int w = mBg->GetWidth();
    const int h = mBg->GetHeight();
    SetSize(w, h);

    // BUTTON CLOSE
    mBtnClose = new ButtonClose(this);
    mBtnClose->SetX(GetWidth() - mBtnClose->GetWidth());

    // TITLE
    auto font = fm->GetFont(WidgetsConstants::FontFileDialogTitle, 28, graphic::Font::NORMAL);
    mTitle = new graphic::Text("SELF DESTRUCTION", font);
    mTitle->SetColor(WidgetsConstants::colorDialogTitle);
    RegisterRenderable(mTitle);

    // BUTTON DESTROY
    const int btnY0 = 80;
    const int marginBtnV = 60;
    int btnX = 0;
    int btnY = btnY0;

    auto btn = new ButtonDialog(this);
    mBtnDestroy = btn;

    btn->SetLabel("DESTROY");

    btnX = (w - btn->GetWidth()) / 2;
    btn->SetPosition(btnX, btnY);

    btnY += btn->GetHeight() + marginBtnV;

    // BUTTON BLOW UP
    btn = new ButtonDialog(this);
    mBtnBlowup = btn;

    btn->SetLabel("BLOW UP");

    btnX = (w - btn->GetWidth()) / 2;
    btn->SetPosition(btnX, btnY);
}

void DialogSelfDestruction::AddFunctionOnDestroy(const std::function<void()> & f)
{
    mBtnDestroy->AddOnClickFunction(f);
}

void DialogSelfDestruction::AddFunctionOnBlowup(const std::function<void()> & f)
{
    mBtnBlowup->AddOnClickFunction(f);
}

void DialogSelfDestruction::AddFunctionOnClose(const std::function<void()> & f)
{
    mBtnClose->AddOnClickFunction(f);
}

void DialogSelfDestruction::HandlePositionChanged()
{
    SetPositions();
}

void DialogSelfDestruction::SetPositions()
{
    const int x0 = GetScreenX();
    const int y0 = GetScreenY();

    mBg->SetPosition(x0, y0);

    const int marginL = 35;
    const int marginT = 5;
    int x = x0 + marginL;
    int y = y0 + marginT;
    mTitle->SetPosition(x, y);
}

} // namespace game
