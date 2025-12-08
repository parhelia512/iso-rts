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
    // set attack range converting attribute
    const int attRanges[] = { 0, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12 };
    mAttackRange = attRanges[data.GetAttribute(OBJ_ATT_FIRE_RANGE)];

    SetImage();
}

void Bunker::Update(float delta)
{
    // do nothing if not linked
    if(!IsLinked())
    {
        mTarget = nullptr;
        return ;
    }

    // check if there's any target in range
    CheckForEnemies();

    // attacking other object
    if(mTarget)
    {
        mTimerAttack -= delta;

        // time to shoot!
        if(mTimerAttack < 0.f)
        {
            // target still alive -> shoot
            if(GetGameMap()->HasObject(mTarget))
                Shoot();
            // target destroyed -> clear pointer
            else
                mTarget = nullptr;

            mTimerAttack = mTimeAttack;
        }
    }
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

void Bunker::CheckForEnemies()
{
    const GameMap * gm = GetGameMap();

    const int row = GetRow0();
    const int col = GetCol0();

    const int mapRows = gm->GetNumRows();
    const int mapCols = gm->GetNumCols();

    const PlayerFaction faction = GetFaction();

    std::vector<GameObject *> objs;

    // find all enemies in range
    for(int i = 1; i <= mAttackRange; ++i)
    {
        const int rTL = (row - i) > 0 ? (row - i) : 0;
        const int rBR = (row + i) < mapRows ? (row + i) : (mapRows - 1);

        const int cTL = (col - i) > 0 ?  (col - i) : 0;
        const int cBR = (col + i) < mapCols ? (col + i) : (mapCols - 1);

        for(int r = rTL; r <= rBR; ++r)
        {
            for(int c = cTL; c <= cBR; ++c)
            {
                const GameMapCell & cell = gm->GetCell(r, c);

                GameObject * obj = cell.objTop;

                // only visible enemy objects
                if(obj && obj->GetFaction() != NO_FACTION && obj->GetFaction() != faction && obj->IsVisible())
                    objs.push_back(cell.objTop);
            }
        }
    }

    // no potential target -> clear current
    if(objs.empty())
    {
        mTarget = nullptr;
        return ;
    }

    // chose target
    // TODO more complex logic, for now just selecting 1st one
    mTarget = objs.front();
}

void Bunker::Shoot()
{
    IsoObject * isoObj = GetIsoObject();
    IsoObject * isoTarget = mTarget->GetIsoObject();

    const float isoX = isoObj->GetX();
    const float isoXC = isoObj->GetX() + isoObj->GetWidth() * 0.5f;
    const float isoY = isoObj->GetY();
    const float isoTargetX = isoTarget->GetX();
    const float isoTargetY = isoTarget->GetY();
    const float x0 = isoTargetX < isoX ? isoXC - 20.f : isoXC + 20.f;
    const float y0 = isoTargetY < isoY ? isoY + 4 : isoY + 30;

    mWeapon->Shoot(x0, y0, mTarget);
}

} // namespace game
