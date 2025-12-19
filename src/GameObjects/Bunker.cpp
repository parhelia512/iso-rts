#include "GameObjects/Bunker.h"

#include "GameConstants.h"
#include "GameData.h"
#include "GameMap.h"
#include "IsoObject.h"
#include "GameObjects/ObjectData.h"
#include "GameObjectTools/Weapon.h"
#include "Screens/ScreenGame.h"

#include <sgl/graphic/Texture.h>
#include <sgl/graphic/TextureManager.h>

namespace game
{

Bunker::Bunker(const ObjectData & data)
    : Structure(data)
{
    SetImage();
}

void Bunker::Update(float delta)
{
    // do nothing if not linked
    if(!IsLinked())
        return ;

    mTimerAttack -= delta;

    // not ready to attack yet
    if(mTimerAttack > 0.f)
        return ;

    // nothing to do
    if(!mWeapon->HasTarget())
        return ;

    if(!mWeapon->Update(delta))
        return ;

    if(mWeapon->IsReadyToShoot())
        PrepareShoot();
}

void Bunker::UpdateGraphics()
{
    SetImage();
}

void Bunker::SetImage()
{
    auto * tm = sgl::graphic::TextureManager::Instance();

    IsoObject * isoObj = GetIsoObject();

    if(IsVisible())
        isoObj->SetColor(COLOR_VIS);
    else
        isoObj->SetColor(COLOR_FOW);

    const unsigned int faction = GetFaction();
    const unsigned int sel = static_cast<unsigned int>(IsSelected());

    unsigned int texInd = ID_STRUCT_BUNKER;

    if(NO_FACTION == faction)
        texInd += sel;
    else
        texInd = ID_STRUCT_BUNKER_F1 + (faction * NUM_BUNKER_SPRITES_PER_FAC) + sel;

    sgl::graphic::Texture * tex = tm->GetSprite(SpriteFileStructures, texInd);
    isoObj->SetTexture(tex);
}

void Bunker::PrepareShoot()
{
    const IsoObject * isoObj = GetIsoObject();
    const IsoObject * isoTarget = mWeapon->GetTarget()->GetIsoObject();

    const float isoX = isoObj->GetX();
    const float isoXC = isoObj->GetX() + isoObj->GetWidth() * 0.5f;
    const float isoY = isoObj->GetY();
    const float isoTargetX = isoTarget->GetX();
    const float isoTargetY = isoTarget->GetY();
    const float x0 = isoTargetX < isoX ? isoXC - 20.f : isoXC + 20.f;
    const float y0 = isoTargetY < isoY ? isoY + 4 : isoY + 30;

    mWeapon->Shoot(x0, y0);

    const float timeAttack = 0.5f;
    mTimerAttack = timeAttack;
}

} // namespace game
