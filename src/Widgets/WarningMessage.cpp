#include "Widgets/WarningMessage.h"

#include "Widgets/GameUIData.h"
#include "Widgets/WidgetsConstants.h"

#include <sgl/graphic/Font.h>
#include <sgl/graphic/FontManager.h>
#include <sgl/graphic/Image.h>
#include <sgl/graphic/Text.h>
#include <sgl/graphic/TextureManager.h>

namespace
{
const int marginR = 5;
}

namespace game
{

WarningMessage::WarningMessage(const char * text, float time)
    : mTimer(time)
{
    using namespace sgl;

    auto tm = graphic::TextureManager::Instance();
    auto fm = graphic::FontManager::Instance();

    // ICON
    auto tex = tm->GetSprite(SpriteFileGameUIShared, ID_UIS_ICON_WARNING);
    mIcon = new graphic::Image(tex);
    RegisterRenderable(mIcon);

    // TEXT
    const int fontSize = 16;
    auto font = fm->GetFont(WidgetsConstants::FontFileText, fontSize, graphic::Font::NORMAL);

    mText = new graphic::Text(text, font);
    RegisterRenderable(mText);

    // SIZE
    const int w = mIcon->GetWidth() + marginR + mText->GetWidth();
    const int h = mIcon->GetHeight();

    SetSize(w, h);
}

void WarningMessage::HandlePositionChanged()
{
    UpdatePositions();
}

void WarningMessage::UpdatePositions()
{
    const int x0 = GetScreenX();
    const int y0 = GetScreenY();

    int x = x0;
    int y = y0;

    mIcon->SetPosition(x, y);

    x += mIcon->GetWidth() + marginR;
    y = y0 + (GetHeight() - mText->GetHeight()) / 2;
    mText->SetPosition(x, y);
}

void WarningMessage::OnUpdate(float delta)
{
    mTimer -= delta;

    if(mTimer < 0.f)
        DeleteLater();
}

} // namespace game
