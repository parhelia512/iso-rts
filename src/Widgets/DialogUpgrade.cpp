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

#include <sstream>

// anonymous namespace for local "private" classes
namespace
{
}

namespace game
{

// ===== ValueUpgradeBar =====
ValueUpgradeBar::ValueUpgradeBar(int maxVal, sgl::sgui::Widget * parent)
    : sgl::sgui::Widget(parent)
{
    using namespace sgl;

    auto tm = graphic::TextureManager::Instance();
    auto tex = tm->GetSprite(SpriteFileDialogUpgrade, ID_DLG_UP_VAL_BAR_PIP_OFF);

    int x = 0;

    for(int i = 0; i < maxVal; ++i)
    {
        auto img = new sgui::Image(tex, this);
        mImgs.emplace_back(img);
        img->SetX(x);

        x += img->GetWidth();
    }
}

void ValueUpgradeBar::SetValue(int numOn, int numNew)
{
    using namespace sgl;

    auto tm = graphic::TextureManager::Instance();

    // ON
    auto tex = tm->GetSprite(SpriteFileDialogUpgrade, ID_DLG_UP_VAL_BAR_PIP_ON);

    for(int i = 0; i < numOn; ++i)
        mImgs[i]->SetTexture(tex);

    // NEW
    const unsigned int lastNew = numOn + numNew;

    tex = tm->GetSprite(SpriteFileDialogUpgrade, ID_DLG_UP_VAL_BAR_PIP_NEW);

    for(int i = numOn; i < lastNew; ++i)
        mImgs[i]->SetTexture(tex);

    // OFF
    const unsigned int tot = mImgs.size();

    tex = tm->GetSprite(SpriteFileDialogUpgrade, ID_DLG_UP_VAL_BAR_PIP_OFF);

    for(int i = lastNew; i < tot; ++i)
        mImgs[i]->SetTexture(tex);
}

// ===== DIALOG =====
DialogUpgrade::DialogUpgrade(GameObject * obj, const ObjectsDataRegistry * odr)
    : mObj(obj)
{
    using namespace sgl;

    auto fm = graphic::FontManager::Instance();
    auto tm = graphic::TextureManager::Instance();
    auto sm = utilities::StringManager::Instance();

    // BACKGROUND
    graphic::Texture * tex = tm->GetSprite(SpriteFileDialogUpgrade, ID_DLG_UP_BG);
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
    const int sizeTitle = 28;
    const int marginTitleT = 10;

    auto font = fm->GetFont(WidgetsConstants::FontFileDialogTitle, sizeTitle,
                            graphic::Font::NORMAL);
    auto title = new sgui::Label(sm->GetCString("UPGRADE"), font, this);
    title->SetColor(WidgetsConstants::colorDialogTitle);
    title->SetPosition(marginL, marginTitleT);

    // IMAGE
    const ObjectData & data = odr->GetObjectData(obj->GetObjectType());
    const unsigned int texInd = data.GetIconTexId(obj->GetFaction(), obj);
    tex = tm->GetSprite(data.GetIconTexFile(), texInd);

    const int panelImgX = marginL;
    const int panelImgY = 70;
    const int panelImgW = 300;
    const int panelImgH = 220;

    auto img = new sgui::Image(tex, this);
    img->SetPosition(panelImgX + (panelImgW - img->GetWidth()) / 2,
                     panelImgY + (panelImgH - img->GetHeight()) / 2);

    // -- DATA --
    const int panelDataX = marginL;
    const int panelDataY = 290;
    const int panelDataW = 300;
    const int panelDataH = 260;
    const int paddingDataL = 20;
    const int paddingDataT = 20;
    const int marginHeaderV = 10;
    const int marginHeaderV2 = 5;
    const int blockDataH = 85;

    const int sizeHeader = 18;
    auto fontHeader = fm->GetFont(WidgetsConstants::FontFileHeader,
                                  sizeHeader, graphic::Font::NORMAL);

    const int sizeText = 18;
    auto fontText = fm->GetFont(WidgetsConstants::FontFileText,
                                sizeText, graphic::Font::NORMAL);

    // LEVEL
    const int dataX = panelDataX + paddingDataL;
    int dataY = panelDataY + paddingDataT;

    auto header = new sgui::Label(sm->GetCString("LEVEL"), fontHeader, this);
    header->SetColor(WidgetsConstants::colorDialogHeader2);
    header->SetPosition(dataX, dataY);

    dataY += header->GetHeight() + marginHeaderV;

    const int level = obj->GetExperienceLevel();
    const unsigned int barLvlTexId = ID_DLG_OBJ_SBAR_0 + level;
    tex = tm->GetSprite(SpriteFileDialogObject, barLvlTexId);
    auto levelBar = new sgui::Image(tex, this);
    levelBar->SetPosition(dataX, dataY);

    // NEXT LEVEL
    dataY = header->GetY() + blockDataH;

    header = new sgui::Label(sm->GetCString("NEXT_LEVEL"), fontHeader, this);
    header->SetColor(WidgetsConstants::colorDialogHeader2);
    header->SetPosition(dataX, dataY);

    dataY += header->GetHeight() + marginHeaderV2;

    std::ostringstream ss;
    ss << obj->GetExperience() << " / " << obj->GetExperienceToNextLevel();

    auto label = new sgui::Label(ss.str().c_str(), fontText, this);
    label->SetColor(WidgetsConstants::colorDialogText);
    label->SetPosition(dataX, dataY);

    // UPGRADE POINTS
    dataY = header->GetY() + blockDataH;

    header = new sgui::Label(sm->GetCString("UP_POINTS"), fontHeader, this);
    header->SetColor(WidgetsConstants::colorDialogHeader2);
    header->SetPosition(dataX, dataY);

    dataY += header->GetHeight() + marginHeaderV2;

    const int points[] = { 2, 2, 2, 3, 3, 3, 4, 4, 4, 5 };

    mPointsToAssign = points[level];

    mLabelPoints = new sgui::Label(std::to_string(mPointsToAssign).c_str(), fontText, this);
    mLabelPoints->SetColor(WidgetsConstants::colorDialogText);
    mLabelPoints->SetPosition(dataX, dataY);

    // -- ATTRIBUTES --
    const int areaAttX = 335;
    const int areaAttY = 70;
    const int paddingAttL = 10;

    const unsigned int maxAtt = 12;

    unsigned int attUsed = 0;

    int attY = areaAttY;

    // ASSIGNED ATTRIBUTES
    tex = tm->GetSprite(SpriteFileDialogUpgrade, ID_DLG_UP_ATT_BG);

    for(unsigned int i = 0; i < NUM_BASIC_ATTRIBUTES; ++i)
    {
        const int val = obj->GetAttribute(static_cast<ObjAttId>(i));

        if(val <= 0)
            continue;

        // attribute bg
        auto bg = new sgui::Image(tex, this);
        bg->SetPosition(areaAttX, attY);

        // attribute header
        header = new sgui::Label(sm->GetCString(ObjectData::STR_ATTRIBUTES[i]),
                                 fontHeader, bg);
        header->SetColor(WidgetsConstants::colorDialogHeader2);
        header->SetPosition(paddingAttL, (bg->GetHeight() - header->GetHeight()) / 2);

        // attribute bar
        auto bar = new ValueUpgradeBar(static_cast<int>(MAX_STAV_VAL), bg);
        bar->SetValue(val, 0);
        bar->SetPosition(380, (bg->GetHeight() - bar->GetHeight()) / 2);

        // move to next
        attY += bg->GetHeight();

        ++attUsed;

        if(attUsed == maxAtt)
            break;
    }

    // OTHER SLOTS
    tex = tm->GetSprite(SpriteFileDialogUpgrade, ID_DLG_UP_ATT_DISABLED_BG);

    for(unsigned int i = attUsed; i < maxAtt; ++i)
    {
        auto bg = new sgui::Image(tex, this);
        bg->SetPosition(areaAttX, attY);

        attY += bg->GetHeight();
    }
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
