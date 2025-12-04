#include "Widgets/DialogNewMiniUnitsSquad.h"

#include "Player.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/ObjectsDataRegistry.h"
#include "Widgets/ButtonDialogClose.h"
#include "Widgets/GameButton.h"
#include "Widgets/GameSliderH.h"
#include "Widgets/GameUIData.h"
#include "Widgets/ObjectVisualAttribute.h"
#include "Widgets/WidgetsConstants.h"

#include <sgl/graphic/Font.h>
#include <sgl/graphic/FontManager.h>
#include <sgl/graphic/Image.h>
#include <sgl/graphic/TextureManager.h>
#include <sgl/sgui/Image.h>
#include <sgl/sgui/Label.h>
#include <sgl/sgui/TextArea.h>

namespace
{
constexpr int topPanelY0 = 67;
}

namespace game
{

// ===== DIALOG =====
DialogNewMiniUnitsSquad::DialogNewMiniUnitsSquad(Player * player, const ObjectsDataRegistry * dataReg)
    : mPlayer(player)
    , mDataReg(dataReg)
    , mTypeToBuild(GameObject::TYPE_MINI_UNIT1)
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
    CreatePanelPreview();
    CreatePanelDescription();
    CreatePanelAttributes();
    CreatePanelConfig();

    UpdateData();
}

void DialogNewMiniUnitsSquad::AddFunctionOnClose(const std::function<void()> & f)
{
    mBtnClose->AddOnClickFunction(f);
}

void DialogNewMiniUnitsSquad::CreatePanelPreview()
{
    using namespace sgl;

    const int panelX0 = 40;

}

void DialogNewMiniUnitsSquad::CreatePanelDescription()
{
    using namespace sgl;

    const int panelX0 = 280;
    const int marginL = 20;
    const int marginT = 20;
    const int marginHeaderB = 5;
    const int x0 = panelX0 + marginL;

    auto fm = graphic::FontManager::Instance();
    auto tm = graphic::TextureManager::Instance();

    auto fontHeader = fm->GetFont(WidgetsConstants::FontFilePanelHeader, 20, graphic::Font::NORMAL);
    auto fontText = fm->GetFont(WidgetsConstants::FontFileText, 18, graphic::Font::NORMAL);

    int x = x0;
    int y = topPanelY0 + marginT;

    // -- DESCRIPTION --
    // HEADER DESCRIPTION
    auto header = new sgui::Label("DESCRIPTION", fontHeader, this);
    header->SetColor(WidgetsConstants::colorPanelHeader);
    header->SetPosition(x, y);

    y += header->GetHeight() + marginHeaderB;

    // TEXT DESCRIPTION
    const int textW = 480;
    const int textH = 70;
    const int marginTextB = 10;

    mDescription = new sgui::TextArea(textW, textH, fontText, false, this);
    mDescription->SetColor(WidgetsConstants::colorPanelText);
    mDescription->SetPosition(x, y);

    y +=  textH + marginTextB;

    // -- COST --
    const int marginHeaderCostB = 10;
    const int marginIconR = 10;
    const int marginIconToNextR = 140;

    // HEADER COST
    header = new sgui::Label("UNITARY COST", fontHeader, this);
    header->SetColor(WidgetsConstants::colorPanelHeader);
    header->SetPosition(x, y);

    y += header->GetHeight() + marginHeaderCostB;

    // ENERGY
    auto tex = tm->GetSprite(SpriteFileGameUIShared, ID_UIS_ICON_W_RES_ENERGY);
    auto icon = new sgui::Image(tex, this);
    icon->SetColor(WidgetsConstants::colorDialogIcon);
    icon->SetPosition(x, y);

    x += icon->GetWidth() + marginIconR;

    mLabelCostEnergy = new sgui::Label(fontText, this);
    mLabelCostEnergy->SetColor(WidgetsConstants::colorDialogText);
    mLabelCostEnergy->SetPosition(x, y);

    x = icon->GetX() + marginIconToNextR;

    // MATERIAL
    tex = tm->GetSprite(SpriteFileGameUIShared, ID_UIS_ICON_W_RES_MATERIAL);
    icon = new sgui::Image(tex, this);
    icon->SetColor(WidgetsConstants::colorDialogIcon);
    icon->SetPosition(x, y);

    x += icon->GetWidth() + marginIconR;

    mLabelCostMaterial = new sgui::Label(fontText, this);
    mLabelCostMaterial->SetColor(WidgetsConstants::colorDialogText);
    mLabelCostMaterial->SetPosition(x, y);

    x = icon->GetX() + marginIconToNextR;

    // DIAMONDS
    tex = tm->GetSprite(SpriteFileGameUIShared, ID_UIS_ICON_W_RES_DIAMONDS);
    icon = new sgui::Image(tex, this);
    icon->SetColor(WidgetsConstants::colorDialogIcon);
    icon->SetPosition(x, y);

    x += icon->GetWidth() + marginIconR;

    mLabelCostDiamonds = new sgui::Label(fontText, this);
    mLabelCostDiamonds->SetColor(WidgetsConstants::colorDialogText);
    mLabelCostDiamonds->SetPosition(x, y);

    x = icon->GetX() + marginIconToNextR;

    // BLOBS
    tex = tm->GetSprite(SpriteFileGameUIShared, ID_UIS_ICON_W_RES_BLOBS);
    icon = new sgui::Image(tex, this);
    icon->SetColor(WidgetsConstants::colorDialogIcon);
    icon->SetPosition(x, y);

    x += icon->GetWidth() + marginIconR;

    mLabelCostBlobs = new sgui::Label(fontText, this);
    mLabelCostBlobs->SetColor(WidgetsConstants::colorDialogText);
    mLabelCostBlobs->SetPosition(x, y);
}

void DialogNewMiniUnitsSquad::CreatePanelAttributes()
{
    using namespace sgl;

    const int panelX0 = 40;
    const int panelY0 = topPanelY0 + 200;

    const int rows = 6;
    const int cols = 2;

    int x = panelX0;
    int y = panelY0;

    for(int r = 0; r < rows; ++r)
    {
        for(int c = 0; c < cols; ++c)
        {
            auto panel = new ObjectVisualAttribute(this);
            panel->SetPosition(x, y);

            mAttributes.emplace_back(panel);

            x += panel->GetWidth();
        }

        x = panelX0;
        y += mAttributes[0]->GetHeight();
    }
}

void DialogNewMiniUnitsSquad::CreatePanelConfig()
{
    using namespace sgl;

    const int panelX0 = 840;
    const int marginL = 20;
    const int marginT = 20;
    const int x0 = panelX0 + marginL;
    const int marginHeaderB = 20;
    const int marginBlockB = 60;

    auto fm = graphic::FontManager::Instance();
    auto tm = graphic::TextureManager::Instance();

    auto fontHeader = fm->GetFont(WidgetsConstants::FontFilePanelHeader, 20, graphic::Font::NORMAL);
    auto fontText = fm->GetFont(WidgetsConstants::FontFileText, 18, graphic::Font::NORMAL);

    auto texSliderBg = tm->GetSprite(SpriteFileDialogExploreTemple, ID_DLG_EXTM_SLIDER_BG);
    auto texSliderBar = tm->GetSprite(SpriteFileDialogExploreTemple, ID_DLG_EXTM_SLIDER_BAR);
    auto texSliderBtn = tm->GetSprite(SpriteFileDialogExploreTemple, ID_DLG_EXTM_SLIDER_BTN);

    int x = x0;
    int y = topPanelY0 + marginT;

    // -- ELEMENTS --
    // HEADER ELEMENTS
    auto header = new sgui::Label("ELEMENTS", fontHeader, this);
    header->SetColor(WidgetsConstants::colorPanelHeader);
    header->SetPosition(x, y);

    y += header->GetHeight() + marginHeaderB;

    // SLIDER ELEMENTS
    const int minElements = 1;
    const int maxElements = 5;
    const int defElements = 2;

    const int marginSliderR = 20;
    const int marginSliderB = 60;

    mSliderElements = new GameSliderH(texSliderBg, texSliderBar, texSliderBtn, this);
    mSliderElements->SetMinMax(minElements, maxElements);
    mSliderElements->SetValue(defElements);
    mSliderElements->SetPosition(x, y);

    x += mSliderElements->GetWidth() + marginSliderR;

    auto label = new sgui::Label(std::to_string(defElements).c_str(), fontText, this);
    label->SetColor(WidgetsConstants::colorDialogText);
    label->SetPosition(x, y);

    mSliderElements->SetOnValueChanged([this, label](int val)
    {
        label->SetText(std::to_string(val).c_str());

        UpdateTotalCosts();
    });

    x = x0;
    y += mSliderElements->GetHeight() + marginBlockB;

    // -- SQUADS --
    // HEADER SQUADS
    header = new sgui::Label("SQUADS", fontHeader, this);
    header->SetColor(WidgetsConstants::colorPanelHeader);
    header->SetPosition(x, y);

    y += header->GetHeight() + marginHeaderB;

    // SLIDER SQUADS
    const int minSquads = 1;
    const int maxSquads = 12;
    const int defSquads = 4;

    mSliderSquads = new GameSliderH(texSliderBg, texSliderBar, texSliderBtn, this);
    mSliderSquads->SetMinMax(minSquads, maxSquads);
    mSliderSquads->SetValue(defSquads);
    mSliderSquads->SetPosition(x, y);

    x += mSliderSquads->GetWidth() + marginSliderR;

    label = new sgui::Label(std::to_string(defSquads).c_str(), fontText, this);
    label->SetColor(WidgetsConstants::colorDialogText);
    label->SetPosition(x, y);

    mSliderSquads->SetOnValueChanged([this, label](int val)
    {
        label->SetText(std::to_string(val).c_str());

        UpdateTotalCosts();
    });

    x = x0;
    y += mSliderSquads->GetHeight() + marginBlockB;

    // -- TOTAL COST --
    const int marginIconR = 10;
    const int marginIconB = 50;
    const int marginIconToNextR = 150;

    // HEADER TOTAL COST
    header = new sgui::Label("TOTAL COST", fontHeader, this);
    header->SetColor(WidgetsConstants::colorPanelHeader);
    header->SetPosition(x, y);

    y += header->GetHeight() + marginHeaderB;

    // ENERGY
    auto tex = tm->GetSprite(SpriteFileGameUIShared, ID_UIS_ICON_W_RES_ENERGY);
    auto icon = new sgui::Image(tex, this);
    icon->SetColor(WidgetsConstants::colorDialogIcon);
    icon->SetPosition(x, y);

    x += icon->GetWidth() + marginIconR;

    mLabelTotCostEnergy = new sgui::Label(fontText, this);
    mLabelTotCostEnergy->SetPosition(x, y);

    x = icon->GetX() + marginIconToNextR;

    // MATERIAL
    tex = tm->GetSprite(SpriteFileGameUIShared, ID_UIS_ICON_W_RES_MATERIAL);
    icon = new sgui::Image(tex, this);
    icon->SetColor(WidgetsConstants::colorDialogIcon);
    icon->SetPosition(x, y);

    x += icon->GetWidth() + marginIconR;

    mLabelTotCostMaterial = new sgui::Label(fontText, this);
    mLabelTotCostMaterial->SetPosition(x, y);

    x = x0;
    y += marginIconB;

    // DIAMONDS
    tex = tm->GetSprite(SpriteFileGameUIShared, ID_UIS_ICON_W_RES_DIAMONDS);
    icon = new sgui::Image(tex, this);
    icon->SetColor(WidgetsConstants::colorDialogIcon);
    icon->SetPosition(x, y);

    x += icon->GetWidth() + marginIconR;

    mLabelTotCostDiamonds = new sgui::Label(fontText, this);
    mLabelTotCostDiamonds->SetPosition(x, y);

    x = icon->GetX() + marginIconToNextR;

    // BLOBS
    tex = tm->GetSprite(SpriteFileGameUIShared, ID_UIS_ICON_W_RES_BLOBS);
    icon = new sgui::Image(tex, this);
    icon->SetColor(WidgetsConstants::colorDialogIcon);
    icon->SetPosition(x, y);

    x += icon->GetWidth() + marginIconR;

    mLabelTotCostBlobs = new sgui::Label(fontText, this);
    mLabelTotCostBlobs->SetPosition(x, y);
}

void DialogNewMiniUnitsSquad::UpdateTotalCosts()
{
    const ObjectData & data = mDataReg->GetObjectData(mTypeToBuild);
    const std::array<int, NUM_OBJ_COSTS> & costs = data.GetCosts();

    const int totElements = mSliderElements->GetValue() * mSliderSquads->GetValue();

    const int totCost[NUM_OBJ_COSTS] =
    {
        costs[OBJ_COST_ENERGY] * totElements,
        costs[OBJ_COST_MATERIAL] * totElements,
        costs[OBJ_COST_DIAMONDS] * totElements,
        costs[OBJ_COST_BLOBS] * totElements
    };

    const bool canSpend[NUM_OBJ_COSTS] =
    {
        mPlayer->HasEnough(Player::ENERGY,  totCost[OBJ_COST_ENERGY]),
        mPlayer->HasEnough(Player::MATERIAL, totCost[OBJ_COST_MATERIAL]),
        mPlayer->HasEnough(Player::DIAMONDS, totCost[OBJ_COST_DIAMONDS]),
        mPlayer->HasEnough(Player::BLOBS, totCost[OBJ_COST_BLOBS])
    };

    const unsigned int colors[] =
    {
        WidgetsConstants::colorDialogBad,
        WidgetsConstants::colorDialogGood
    };

    // ENERGY
    mLabelTotCostEnergy->SetText(std::to_string(totCost[OBJ_COST_ENERGY]).c_str());
    mLabelTotCostEnergy->SetColor(colors[canSpend[OBJ_COST_ENERGY]]);

    // MATERIAL
    mLabelTotCostMaterial->SetText(std::to_string(totCost[OBJ_COST_MATERIAL]).c_str());
    mLabelTotCostMaterial->SetColor(colors[canSpend[OBJ_COST_MATERIAL]]);

    // DIAMONDS
    mLabelTotCostDiamonds->SetText(std::to_string(totCost[OBJ_COST_DIAMONDS]).c_str());
    mLabelTotCostDiamonds->SetColor(colors[canSpend[OBJ_COST_DIAMONDS]]);

    // BLOBS
    mLabelTotCostBlobs->SetText(std::to_string(totCost[OBJ_COST_BLOBS]).c_str());
    mLabelTotCostBlobs->SetColor(colors[canSpend[OBJ_COST_BLOBS]]);
}

void DialogNewMiniUnitsSquad::UpdateData()
{
    // DESCRIPTION
    mDescription->SetText(GameObject::DESCRIPTIONS.at(mTypeToBuild).c_str());

    const ObjectData & data = mDataReg->GetObjectData(mTypeToBuild);
    const std::array<int, NUM_OBJ_COSTS> & costs = data.GetCosts();

    // COSTS
    mLabelCostEnergy->SetText(std::to_string(costs[OBJ_COST_ENERGY]).c_str());
    mLabelCostMaterial->SetText(std::to_string(costs[OBJ_COST_MATERIAL]).c_str());
    mLabelCostDiamonds->SetText(std::to_string(costs[OBJ_COST_DIAMONDS]).c_str());
    mLabelCostBlobs->SetText(std::to_string(costs[OBJ_COST_BLOBS]).c_str());

    // ATTRIBUTES
    const unsigned int numPanelAttributes = mAttributes.size();

    unsigned int attAdded = 0;

    for(unsigned int i = 0; i < NUM_OBJ_ATTRIBUTES; ++i)
    {
        const int val = data.GetAttribute(static_cast<ObjAttId>(i));

        if(val > 0)
            mAttributes[attAdded++]->SetData(ObjectData::STR_ATTRIBUTES[i], val);

        // it shouldn't happen, but just in case
        if(numPanelAttributes == attAdded)
            break;
    }

    for(unsigned int i = attAdded; i < numPanelAttributes; ++i)
        mAttributes[i]->ClearData();

    // TOTAL COSTS
    UpdateTotalCosts();
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
