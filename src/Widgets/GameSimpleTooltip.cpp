#include "GameSimpleTooltip.h"

#include "Widgets/GameUIData.h"
#include "Widgets/WidgetsConstants.h"

#include <sgl/graphic/GraphicConstants.h>
#include <sgl/graphic/Font.h>
#include <sgl/graphic/FontManager.h>
#include <sgl/graphic/Image.h>
#include <sgl/graphic/TextureManager.h>
#include <sgl/graphic/Text.h>
#include <sgl/graphic/Texture.h>

namespace
{
    constexpr int marginCont = 10;
}

namespace game
{

GameSimpleTooltip::GameSimpleTooltip(const char * text)
{
    using namespace sgl;

    auto tm = graphic::TextureManager::Instance();

    const int marginL = 40;
    const int marginT = 8;

    // BACKGROUND
    graphic::Texture * tex = tm->GetSprite(SpriteFileTooltipsExp, IND_TOOLTIP_SIMPLE_LEFT);
    tex->SetScaleMode(graphic::TSCALE_NEAREST);

    mBgLeft = new graphic::Image(tex);
    RegisterRenderable(mBgLeft);

    tex = tm->GetSprite(SpriteFileTooltipsExp, IND_TOOLTIP_SIMPLE_CONT);
    mBgCont = new graphic::Image(tex);
    RegisterRenderable(mBgCont);

    tex = tm->GetSprite(SpriteFileTooltipsExp, IND_TOOLTIP_SIMPLE_RIGHT);
    mBgRight = new graphic::Image(tex);
    RegisterRenderable(mBgRight);

    // LABEL
    SetText(text);
}

void GameSimpleTooltip::SetText(const char * text)
{
    using namespace sgl;

    if(mLabel != nullptr)
    {
        UnregisterRenderable(mLabel);
        delete mLabel;
    }

    const unsigned int color = 0x98bbd9ff;
    auto fm = graphic::FontManager::Instance();
    auto font = fm->GetFont(WidgetsConstants::FontFileText, 16, graphic::Font::NORMAL);

    mLabel = new graphic::Text(text, font);
    mLabel->SetColor(color);
    RegisterRenderable(mLabel);

    // SET SIZES
    const int contentW = mLabel->GetWidth() + (marginCont * 2);
    const int w = mBgLeft->GetWidth() + contentW + mBgRight->GetWidth();
    const int h = mBgCont->GetHeight();

    mBgCont->SetWidth(contentW);

    SetSize(w, h);

    // reposition
    SetPositions();
}

void GameSimpleTooltip::HandlePositionChanged()
{
    SetPositions();
}

void GameSimpleTooltip::SetPositions()
{
    const int x0 = GetScreenX();
    const int y0 = GetScreenY();

    // BACKGROUND
    int x = x0;
    int y = y0;

    mBgLeft->SetPosition(x, y);

    x += mBgLeft->GetWidth();

    mBgCont->SetPosition(x, y);

    x += mBgCont->GetWidth();

    mBgRight->SetPosition(x, y);

    // LABEL
    const int labelX = mBgCont->GetX() +
                       (mBgCont->GetWidth() - mLabel->GetWidth()) / 2;
    const int labelY = y0 + (mBgCont->GetHeight() - mLabel->GetHeight()) / 2;

    mLabel->SetPosition(labelX, labelY);
}

} // namespace game
