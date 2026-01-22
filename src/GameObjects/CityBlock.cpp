#include "GameObjects/CityBlock.h"

#include "GameData.h"
#include "IsoObject.h"

#include <sgl/graphic/TextureManager.h>

namespace game
{

CityBlock::CityBlock(const ObjectData & data, const ObjectInitData & initData,
                         GameObjectVariantId part)
    : Structure(data, initData)
{
    SetCanBeConquered(true);

    mVariant = part;

    // set object health
    const float maxHealthValue = 2000.f;
    UpdateMaxHealth(maxHealthValue);

    SetImage();
}

void CityBlock::UpdateGraphics()
{
    SetImage();
}

void CityBlock::SetImage()
{
    IsoObject * isoObj = GetIsoObject();

    if(IsVisible())
        isoObj->SetColor(COLOR_VIS);
    else
        isoObj->SetColor(COLOR_FOW);

    // set texture
    auto tm = sgl::graphic::TextureManager::Instance();

    sgl::graphic::Texture * tex = nullptr;

    const int sel = static_cast<int>(IsSelected());
    const PlayerFaction f = GetFaction();

    const unsigned int factionSpriteIds[] =
    {
        ID_CITY_TL1_F1,
        ID_CITY_TL1_F2,
        ID_CITY_TL1_F3,
    };

    static_assert((sizeof(factionSpriteIds) / sizeof(unsigned int)) == NUM_FACTIONS);

    const unsigned int spriteId0 = f != NO_FACTION ? factionSpriteIds[f] : ID_CITY_TL1_NF;
    const unsigned int spriteId = spriteId0 + mVariant + (sel * NUM_CITY_SPRITES);
    tex = tm->GetSprite(SpriteFileSceneElements, spriteId);

    isoObj->SetTexture(tex);
}

} // namespace game
