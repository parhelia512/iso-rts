#include "Widgets/DialogNewMiniUnitsSquad.h"

#include "Widgets/ButtonDialogClose.h"
#include "Widgets/GameButton.h"
#include "Widgets/GameSimpleTooltip.h"
#include "Widgets/GameSliderH.h"
#include "Widgets/GameUIData.h"
#include "Widgets/WidgetsConstants.h"

#include <sgl/graphic/Font.h>
#include <sgl/graphic/FontManager.h>
#include <sgl/graphic/Image.h>
#include <sgl/graphic/Text.h>
#include <sgl/graphic/TextureManager.h>
#include <sgl/sgui/Label.h>

namespace game
{

// ===== DIALOG =====
DialogNewMiniUnitsSquad::DialogNewMiniUnitsSquad()
{
    using namespace sgl;

    auto fm = graphic::FontManager::Instance();
    auto tm = graphic::TextureManager::Instance();

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
    const int marginL = 40;
    const int marginT = 7;

    auto font = fm->GetFont(WidgetsConstants::FontFileDialogTitle, 28, graphic::Font::NORMAL);

    auto title = new sgui::Label("CREATE MINI UNITS SQUADS", font, this);
    title->SetColor(WidgetsConstants::colorDialogTitle);
    title->SetPosition(marginL, marginT);

    // PANELS
    CreatePanelConfig();
}

void DialogNewMiniUnitsSquad::AddFunctionOnClose(const std::function<void()> & f)
{
    mBtnClose->AddOnClickFunction(f);
}

void DialogNewMiniUnitsSquad::CreatePanelConfig()
{
    using namespace sgl;

    const int panelX0 = 840;
    const int panelY0 = 67;
    const int marginL = 20;
    const int marginT = 20;
    const int x0 = panelX0 + marginL;
    const int marginTitleB = 20;
    const int marginBlockB = 60;

    auto fm = graphic::FontManager::Instance();
    auto tm = graphic::TextureManager::Instance();

    auto fontHeader = fm->GetFont(WidgetsConstants::FontFilePanelHeader, 20, graphic::Font::NORMAL);
    auto fontText = fm->GetFont(WidgetsConstants::FontFileText, 18, graphic::Font::NORMAL);

    auto texSliderBg = tm->GetSprite(SpriteFileDialogExploreTemple, ID_DLG_EXTM_SLIDER_BG);
    auto texSliderBar = tm->GetSprite(SpriteFileDialogExploreTemple, ID_DLG_EXTM_SLIDER_BAR);
    auto texSliderBtn = tm->GetSprite(SpriteFileDialogExploreTemple, ID_DLG_EXTM_SLIDER_BTN);

    int x = x0;
    int y = panelY0 + marginT;

    // -- ELEMENTS --
    // HEADER ELEMENTS
    auto header = new sgui::Label("ELEMENTS", fontHeader, this);
    header->SetColor(WidgetsConstants::colorPanelHeader);
    header->SetPosition(x, y);

    y += header->GetHeight() + marginTitleB;

    // SLIDER ELEMENTS
    const int minElements = 1;
    const int maxElements = 5;
    const int defElements = 2;

    const int marginSliderR = 20;
    const int marginSliderB = 60;

    auto slider = new GameSliderH(texSliderBg, texSliderBar, texSliderBtn, this);
    slider->SetMinMax(minElements, maxElements);
    slider->SetValue(defElements);
    slider->SetPosition(x, y);

    x += slider->GetWidth() + marginSliderR;

    auto label = new sgui::Label(std::to_string(defElements).c_str(), fontText, this);
    label->SetColor(WidgetsConstants::colorDialogText);
    label->SetPosition(x, y);

    slider->SetOnValueChanged([this, label](int val)
    {
        label->SetText(std::to_string(val).c_str());

        OnNumElementsChanged(val);
    });

    x = x0;
    y += slider->GetHeight() + marginBlockB;

    // -- SQUADS --
    // HEADER SQUADS
    header = new sgui::Label("SQUADS", fontHeader, this);
    header->SetColor(WidgetsConstants::colorPanelHeader);
    header->SetPosition(x, y);

    y += header->GetHeight() + marginTitleB;

    // SLIDER ELEMENTS
    const int minSquads = 1;
    const int maxSquads = 12;
    const int defSquads = 4;

    slider = new GameSliderH(texSliderBg, texSliderBar, texSliderBtn, this);
    slider->SetMinMax(minSquads, maxSquads);
    slider->SetValue(defSquads);
    slider->SetPosition(x, y);

    x += slider->GetWidth() + marginSliderR;

    label = new sgui::Label(std::to_string(defSquads).c_str(), fontText, this);
    label->SetColor(WidgetsConstants::colorDialogText);
    label->SetPosition(x, y);

    slider->SetOnValueChanged([this, label](int val)
    {
        label->SetText(std::to_string(val).c_str());

        OnNumSquadsChanged(val);
    });

    x = x0;
    y += slider->GetHeight() + marginBlockB;

    // -- TOTAL COST --
    // HEADER TOTAL COST
    header = new sgui::Label("TOTAL COST", fontHeader, this);
    header->SetColor(WidgetsConstants::colorPanelHeader);
    header->SetPosition(x, y);

    y += header->GetHeight() + marginTitleB;
}

void DialogNewMiniUnitsSquad::OnNumElementsChanged(int num)
{

}

void DialogNewMiniUnitsSquad::OnNumSquadsChanged(int num)
{

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
}

} // namespace game
