#include "Widgets/DialogUpgrade.h"

#include "Game.h"
#include "GameData.h"
#include "GameObjects/MiniUnit.h"
#include "GameObjects/ObjectsDataRegistry.h"
#include "Widgets/ButtonDialogClose.h"
#include "Widgets/GameUIData.h"
#include "Widgets/ObjectVisualAttribute.h"
#include "Widgets/ProgressBarObjectVisualStat.h"
#include "Widgets/WidgetsConstants.h"

#include <sgl/core/event/KeyboardEvent.h>
#include <sgl/graphic/Font.h>
#include <sgl/graphic/FontManager.h>
#include <sgl/graphic/Image.h>
#include <sgl/graphic/Text.h>
#include <sgl/graphic/TextureManager.h>
#include <sgl/media/AudioManager.h>
#include <sgl/media/AudioPlayer.h>
#include <sgl/sgui/Image.h>
#include <sgl/sgui/ImageButton.h>
#include <sgl/sgui/Label.h>
#include <sgl/utilities/StringManager.h>
#include <sgl/utilities/System.h>

// anonymous namespace for local "private" classes
namespace
{

}

namespace game
{

// ===== DIALOG =====
DialogUpgrade::DialogUpgrade(GameObject * obj, const ObjectsDataRegistry * odr)
    : mObj(obj)
{
    using namespace sgl;

    auto fm = graphic::FontManager::Instance();
    auto tm = graphic::TextureManager::Instance();
    auto sm = utilities::StringManager::Instance();

    // BACKGROUND
    graphic::Texture * tex = tm->GetSprite(SpriteFileDialogUpgrade, ID_DLG_OBJ_BG);
    mBg = new graphic::Image(tex);
    RegisterRenderable(mBg);

    const int w = mBg->GetWidth();
    const int h = mBg->GetHeight();
    SetSize(w, h);

    // BUTTON CLOSE
    mBtnClose = new ButtonDialogClose(this);

    const int buttonX = w - mBtnClose->GetWidth();
    const int buttonY = 0;
    mBtnClose->SetPosition(buttonX, buttonY);

    // -- CONTENT --
    const int marginL = 35;

    // TITLE
    const int marginTitleT = 10;

    auto font = fm->GetFont(WidgetsConstants::FontFileDialogTitle, 28, sgl::graphic::Font::NORMAL);
    mTitle = new sgui::Label(sm->GetCString("UPGRADE"), font, this);
    mTitle->SetColor(WidgetsConstants::colorDialogTitle);
    mTitle->SetPosition(marginL, marginTitleT);

    // IMAGE
    const ObjectData & data = odr->GetObjectData(obj->GetObjectType());
    const unsigned int texInd = data.GetIconTexId(obj->GetFaction(), obj);
    tex = tm->GetSprite(data.GetIconTexFile(), texInd);

    const int panelImgX = 35;
    const int panelImgY = 70;
    const int panelImgW = 300;
    const int panelImgH = 220;

    mImg = new sgui::Image(tex, this);
    mImg->SetPosition(panelImgX + (panelImgW - mImg->GetWidth()) / 2,
                      panelImgY + (panelImgH - mImg->GetHeight()) / 2);
}

void DialogUpgrade::SetFunctionOnClose(const std::function<void()> & f)
{
    mBtnClose->AddOnClickFunction(f);
}


void DialogUpgrade::HandlePositionChanged()
{
    SetPositions();
}

void DialogUpgrade::SetPositions()
{
    const int x0 = GetScreenX();
    const int y0 = GetScreenY();

    // BACKGROUND
    mBg->SetPosition(x0, y0);
}

} // namespace game
