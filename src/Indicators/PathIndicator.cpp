#include "Indicators/PathIndicator.h"

#include "GameConstants.h"
#include "GameData.h"

#include <sgl/graphic/DummyRenderable.h>
#include <sgl/graphic/Font.h>
#include <sgl/graphic/FontManager.h>
#include <sgl/graphic/Image.h>
#include <sgl/graphic/TextureManager.h>
#include <sgl/graphic/Text.h>

#include <cassert>
#include <sstream>

namespace game
{

PathIndicator::PathIndicator(PlayerFaction faction, bool final)
    : IsoObject(1,1)
    , mIconCost(new sgl::graphic::DummyRenderable)
    , mTextCost(new sgl::graphic::DummyRenderable)
    , mFaction(faction)
    , mFinal(final)
{
    assert(faction != NO_FACTION);

    UpdateTexture();
}

PathIndicator::~PathIndicator()
{
    delete mIconCost;
    delete mTextCost;
}

void PathIndicator::SetFaction(PlayerFaction faction)
{
    assert(faction != NO_FACTION);

    // nothing changed
    if(faction == mFaction)
        return ;

    mFaction = faction;

    UpdateTexture();
}

void PathIndicator::SetFinal(bool final)
{
    // nothing changed
    if(final == mFinal)
        return ;

    mFinal = final;

    UpdateTexture();
}

void PathIndicator::ClearCost()
{
    // cost already cleared
    if(mCost < 0)
        return;

    delete mIconCost;
    delete mTextCost;

    mIconCost = new sgl::graphic::DummyRenderable;
    mTextCost = new sgl::graphic::DummyRenderable;

    mCost = 0;
}

void PathIndicator::SetCost(int cost)
{
    using namespace sgl;

    // same value -> do nothing
    if(cost == mCost)
        return ;

    // negative cost -> clear
    if(cost < 0)
    {
        ClearCost();
        return ;
    }

    // OK -> delete old graphics and create new one
    mCost = cost;

    delete mIconCost;
    delete mTextCost;

    // create label
    const unsigned int color = 0xfcf1cfff;
    const int fontSize = 14;

    auto fm = graphic::FontManager::Instance();
    graphic::Font * font = fm->GetFont("Lato-Bold.ttf", fontSize, graphic::Font::NORMAL);

    std::ostringstream s;
    s << -cost;

    mTextCost = new graphic::Text(s.str().c_str(), font);
    mTextCost->SetColor(color);

    //create icon
    auto tm = graphic::TextureManager::Instance();
    graphic::Texture * tex = tm->GetSprite(SpriteFileMapIndicators, ID_MIND_ICON_ENERGY);

    mIconCost = new graphic::Image(tex);

    // now position graphics
    UpdatePositions();
}

void PathIndicator::Render()
{
    IsoObject::Render();

    mIconCost->Render();
    mTextCost->Render();
}

void PathIndicator::UpdateTexture()
{
    using namespace sgl;

    // update image of indicator and text color of cost
    auto tm = graphic::TextureManager::Instance();

    const unsigned int regularTexIDs[] =
    {
        ID_MIND_PATH_F1,
        ID_MIND_PATH_F2,
        ID_MIND_PATH_F3,
    };

    const unsigned int finalTexIDs[] =
    {
        ID_MIND_PATH_DEST_F1,
        ID_MIND_PATH_DEST_F2,
        ID_MIND_PATH_DEST_F3,
    };

    const unsigned int texID = mFinal ? finalTexIDs[mFaction] : regularTexIDs[mFaction];

    graphic::Texture * tex = tm->GetSprite(SpriteFileMapIndicators, texID);
    SetTexture(tex);
}

void PathIndicator::OnPositionChanged()
{
    UpdatePositions();
}

void PathIndicator::UpdatePositions()
{
    const int marginCont = 2;
    const int contW0 = mTextCost->GetWidth() + marginCont;
    const int contW = contW0 + mIconCost->GetWidth();

    const int paddingY = 24;
    const int x0 = GetX() + (GetWidth() - contW) / 2;
    const int y0 = GetY() + ((GetHeight() - mTextCost->GetHeight()) / 2) - paddingY;
    mTextCost->SetPosition(x0, y0);

    const int x1 = x0 + contW0;
    const int y1 = GetY() + ((GetHeight() - mIconCost->GetHeight()) / 2) - paddingY;
    mIconCost->SetPosition(x1, y1);
}

} // namespace game
