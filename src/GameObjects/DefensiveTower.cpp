#include "GameObjects/DefensiveTower.h"

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

const int maxAttVal = 11;
const int attRanges[maxAttVal] = { 0, 2, 3, 4, 5, 6, 7, 9, 10, 12, 14 };

DefensiveTower::DefensiveTower(const ObjectData & data)
    : Structure(data)
{
    SetImage();
}

void DefensiveTower::FindEnemyTarget()
{
    // not working if not linked
    if(!IsLinked())
        return ;

    const GameMap * gm = GetGameMap();

    const int r0 = GetRow0();
    const int c0 = GetCol0();

    const int mapRows = gm->GetNumRows();
    const int mapCols = gm->GetNumCols();

    const PlayerFaction faction = GetFaction();

    GameObject * target = nullptr;
    int minDist = mapRows + mapCols;

    // find all enemies in range
    const int range = GetWeapon()->GetRange();

    for(int i = 1; i <= range; ++i)
    {
        const int rTL = (r0 - i) > 0 ? (r0 - i) : 0;
        const int rBR = (r0 + i) < mapRows ? (r0 + i) : (mapRows - 1);

        const int cTL = (c0 - i) > 0 ?  (c0 - i) : 0;
        const int cBR = (c0 + i) < mapCols ? (c0 + i) : (mapCols - 1);

        for(int r = rTL; r <= rBR; ++r)
        {
            for(int c = cTL; c <= cBR; ++c)
            {
                const GameMapCell & cell = gm->GetCell(r, c);

                GameObject * obj = cell.objTop;

                // only visible enemy objects
                if(obj && obj->GetFaction() != NO_FACTION && obj->GetFaction() != faction && obj->IsVisible())
                {
                    const int dist = std::abs(r0 - r) + std::abs(c0 - c);

                    if(dist < minDist)
                    {
                        target = obj;
                        minDist = dist;
                    }
                }
            }
        }
    }

    if(target != nullptr)
        mWeapon->SetTarget(target);
    else
        mWeapon->ClearTarget();
}


void DefensiveTower::Update(float delta)
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

void DefensiveTower::UpdateGraphics()
{
    SetImage();
}

void DefensiveTower::SetImage()
{
    auto * tm = sgl::graphic::TextureManager::Instance();

    IsoObject * isoObj = GetIsoObject();

    if(IsVisible())
        isoObj->SetColor(COLOR_VIS);
    else
        isoObj->SetColor(COLOR_FOW);

    const unsigned int faction = GetFaction();
    const unsigned int sel = static_cast<unsigned int>(IsSelected());

    unsigned int texInd = ID_STRUCT_DTOWER_L1;

    if(NO_FACTION == faction)
        texInd += sel;
    else
        texInd = ID_STRUCT_DTOWER_L1_F1 + (faction * NUM_DTOWER_SPRITES_PER_FAC) + sel;

    sgl::graphic::Texture * tex = tm->GetSprite(SpriteFileStructures, texInd);
    isoObj->SetTexture(tex);
}

void DefensiveTower::PrepareShoot()
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
