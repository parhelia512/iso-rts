#include "GameObjects/MiniUnit.h"

#include "GameConstants.h"
#include "GameData.h"
#include "IsoObject.h"

#include <sgl/graphic/Texture.h>
#include <sgl/graphic/TextureManager.h>

namespace game
{

MiniUnit::MiniUnit(const ObjectData & data)
    : GameObject(data.GetType(), GameObject::CAT_MINI_UNIT, data.GetRows(), data.GetCols())
    , mAttributes(data.GetAttributes())
{
}

void MiniUnit::SetNumElements(int num)
{
    const int MAX_ELEMENTS = 5;

    // cap elements
    if(num > MAX_ELEMENTS)
        num = MAX_ELEMENTS;

    // nothing has changed
    if(num == mElements)
        return ;

    mElements = num;

    UpdateGraphics();
}

void MiniUnit::UpdateGraphics()
{
    const PlayerFaction faction = GetFaction();

    // avoid to set an image when there's no owner set
    if(NO_FACTION == faction)
        return ;

    const unsigned int texInd = SID_MUNIT_01_1X_F1 +
                                (NUM_MUNIT_SPRITES_PER_FACTION * faction) +
                                (NUM_MUNIT_SPRITES_PER_SQUAD * mElements) +
                                static_cast<unsigned int>(IsSelected());

    auto * tm = sgl::graphic::TextureManager::Instance();
    sgl::graphic::Texture * tex =tm->GetSprite(SpriteFileMiniUnits, texInd);

    GetIsoObject()->SetTexture(tex);
}

} // namespace game
