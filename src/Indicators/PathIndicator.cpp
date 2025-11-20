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

    // OK -> delete old text and create new one
    mCost = cost;

    delete mTextCost;

    const unsigned int color[] =
    {
        0xfbd3d0ff,
        0xd0fbd3ff,
        0xd0f0fbff,
    };

    // create label
    auto fm = graphic::FontManager::Instance();
    graphic::Font * font = fm->GetFont("Lato-Bold.ttf", 12, graphic::Font::NORMAL);

    std::ostringstream s;
    s << cost;

    mTextCost = new graphic::Text(s.str().c_str(), font);
    mTextCost->SetColor(color[mFaction]);

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
    const int yPadding = 16;
    const int x = GetX() + (GetWidth() - mTextCost->GetWidth()) / 2;
    const int y = GetY() + ((GetHeight() - mTextCost->GetHeight()) / 2) - yPadding;
    mTextCost->SetPosition(x, y);
}

} // namespace game
