#include "Widgets/DialogNewMiniUnitsSquad.h"

#include "Widgets/ButtonDialogClose.h"
#include "Widgets/GameButton.h"
#include "Widgets/GameSimpleTooltip.h"
#include "Widgets/GameUIData.h"
#include "Widgets/WidgetsConstants.h"

#include <sgl/graphic/Font.h>
#include <sgl/graphic/FontManager.h>
#include <sgl/graphic/Image.h>
#include <sgl/graphic/Text.h>
#include <sgl/graphic/TextureManager.h>

namespace game
{

// ===== DIALOG =====
DialogNewMiniUnitsSquad::DialogNewMiniUnitsSquad()
{
    using namespace sgl;

    auto fm = graphic::FontManager::Instance();
    auto tm = graphic::TextureManager::Instance();

    const int marginL = 40;
    const int marginT = 8;

    // BACKGROUND
    graphic::Texture * tex = tm->GetTexture(SpriteFileDialogNewMiniUnits);
    mBg = new graphic::Image(tex);
    RegisterRenderable(mBg);

    const int w = mBg->GetWidth();
    const int h = mBg->GetHeight();
    SetSize(w, h);

    // BUTTON CLOSE
    mBtnClose = new ButtonDialogClose(this);
    mBtnClose->SetX(GetWidth() - mBtnClose->GetWidth());

    // TITLE
    auto font = fm->GetFont(WidgetsConstants::FontFileDialogTitle, 28, graphic::Font::NORMAL);
    mTitle = new graphic::Text("CREATE MINI UNITS SQUADS", font);
    mTitle->SetColor(WidgetsConstants::colorDialogTitle);
    RegisterRenderable(mTitle);

}

void DialogNewMiniUnitsSquad::AddFunctionOnClose(const std::function<void()> & f)
{
    mBtnClose->AddOnClickFunction(f);
}

void DialogNewMiniUnitsSquad::HandlePositionChanged()
{
    SetPositions();
}

void DialogNewMiniUnitsSquad::SetPositions()
{
    const int x0 = GetScreenX();
    const int y0 = GetScreenY();

    mBg->SetPosition(x0, y0);

    const int marginL = 40;
    const int marginT = 7;
    int x = x0 + marginL;
    int y = y0 + marginT;
    mTitle->SetPosition(x, y);
}

} // namespace game
