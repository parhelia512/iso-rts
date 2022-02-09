#include "GameObjects/Diamonds.h"

#include "GameData.h"
#include "IsoObject.h"

#include <sgl/graphic/TextureManager.h>

namespace game
{

void Diamonds::SetNum(int num)
{
    if(num < MIN_UNITS)
        mNum = MIN_UNITS;
    else if(num > MAX_UNITS)
        mNum = MAX_UNITS;
    else
        mNum = num;

    SetImage();
}

void Diamonds::UpdateGraphics()
{
    SetImage();
}

void Diamonds::SetImage()
{
    // set color
    IsoObject * isoObj = GetIsoObject();

    if(IsVisible())
        isoObj->SetColor(COLOR_VIS);
    else
        isoObj->SetColor(COLOR_FOW);

    // assign texture
    const int spriteId = SpriteCollectiblesId::DIAMONDS_1 + (mNum - 1);

    auto * tm = sgl::graphic::TextureManager::Instance();
    sgl::graphic::Texture * tex = tm->GetSprite(SpriteCollectiblesFile, spriteId);

    isoObj->SetTexture(tex);
}

void Diamonds::SetObjColors()
{
    mObjColors.clear();

    mObjColors.push_back(0xf9f4b8ff);
    mObjColors.push_back(0xf5ed89ff);
    mObjColors.push_back(0xe1d66bff);
    mObjColors.push_back(0xdbd057ff);
    mObjColors.push_back(0xd7ca42ff);
    mObjColors.push_back(0xbdb128ff);
}

} // namespace game
