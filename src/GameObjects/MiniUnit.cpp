#include "GameObjects/MiniUnit.h"

#include "GameConstants.h"
#include "GameData.h"
#include "IsoObject.h"

#include <sgl/graphic/Texture.h>
#include <sgl/graphic/TextureManager.h>

namespace
{
    const float maxSingleHealthValue = 50.f;
}

namespace game
{

MiniUnit::MiniUnit(const ObjectData & data, int elements)
    : GameObject(data)
    , mAttributes(data.GetAttributes())
    , mElements(elements)
{
    // SET CONCRETE ATTRIBUTES
    const float maxStatVal = 10.f;

    // set actual speed
    const float maxSpeed = 10.f;
    const float speed = maxSpeed * static_cast<float>(mAttributes[OBJ_ATT_SPEED]) / maxStatVal;
    SetSpeed(speed);

    // health
    const float maxHealthValue = maxSingleHealthValue * mElements;
    UpdateMaxHealth(maxHealthValue);

    // INIT GRAPHICS
    SetImage();
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

    // health
    const float maxHealthValue = maxSingleHealthValue * mElements;
    UpdateMaxHealth(maxHealthValue);

    UpdateGraphics();
}

void MiniUnit::UpdateGraphics()
{
    SetImage();
}

void MiniUnit::SetImage()
{
    const PlayerFaction faction = GetFaction();

    // avoid to set an image when there's no owner set
    if(NO_FACTION == faction)
        return ;

    const unsigned int texInd = SID_MUNIT_01_1X_F1 +
                                (NUM_MUNIT_SPRITES_PER_FACTION * faction) +
                                (NUM_MUNIT_SPRITES_PER_SQUAD * (mElements - 1)) +
                                static_cast<unsigned int>(IsSelected());

    auto * tm = sgl::graphic::TextureManager::Instance();
    sgl::graphic::Texture * tex =tm->GetSprite(SpriteFileMiniUnits, texInd);

    GetIsoObject()->SetTexture(tex);
}

} // namespace game
