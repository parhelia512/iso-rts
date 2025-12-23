#include "Indicators/MoveIndicator.h"

#include "GameData.h"

#include <sgl/graphic/Font.h>
#include <sgl/graphic/FontManager.h>
#include <sgl/graphic/TextureManager.h>
#include <sgl/graphic/Text.h>

#include <cmath>

namespace game
{

int const MoveIndicator::COST_UNKNOWN = -1;

MoveIndicator::MoveIndicator()
    : IsoObject(1, 1)
{
    // init type
    SetIndicatorType(NORMAL);

    // init cost label
    SetCost(0);
}

void MoveIndicator::SetIndicatorType(IndicatorType type)
{
    using namespace sgl::graphic;

    if(type == mType)
        return ;

    mType = type;

    // update image of indicator and text color of cost
    auto tm = TextureManager::Instance();
    Texture * tex = tm->GetSprite(SpriteFileMapIndicators, IND_MOVE);

    if(NO_VIS_CELL == mType)
    {
        SetColor(0x808080FF);
        mColorCost = 0xB2B2B2FF;
    }
    else
    {
        SetColor(0xE5E5E5FF);
        mColorCost = 0xE5E5E5FF;
    }

    SetTexture(tex);

    if(mTxtCost)
        mTxtCost->SetColor(mColorCost);
}

void MoveIndicator::SetCost(int val)
{
    using namespace sgl::graphic;

    // same cost as current -> do nothing
    if(val == mCost)
        return ;

    // update cost value
    mCost = val;

    // create label
    FontManager * fm = FontManager::Instance();
    Font * font = fm->GetFont("Lato-Bold.ttf", 14, Font::NORMAL);

    delete mTxtCost;

    const int minCost = 0;

    if(mCost < minCost)
        mTxtCost = new Text("?", font);
    else
        mTxtCost = new Text(std::to_string(mCost).c_str(), font);

    mTxtCost->SetColor(mColorCost);
}

void MoveIndicator::Render()
{
    IsoObject::Render();

    // position label
    const int x = GetX() + (GetWidth() - mTxtCost->GetWidth()) * 0.5f;
    const int y = GetY() + (GetHeight() - mTxtCost->GetHeight()) * 0.5f;
    mTxtCost->SetPosition(x, y);

    mTxtCost->Render();
}

} // namespace game
