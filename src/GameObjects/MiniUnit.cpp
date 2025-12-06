#include "GameObjects/MiniUnit.h"

#include "GameConstants.h"
#include "GameData.h"
#include "GameMap.h"
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

void MiniUnit::Update(float delta)
{
    // nothing to do until a target is reached
    if(!mTargetReached)
        return ;

    const GameObjectTypeId type = GetObjectType();

    if(type == TYPE_MINI_UNIT1)
        ExplodeNearEnemy();

    // reset flag
    mTargetReached = false;
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

void MiniUnit::ExplodeNearEnemy()
{
    auto gm = GetGameMap();

    const int mapRows = gm->GetNumRows();
    const int mapCols = gm->GetNumCols();

    const std::vector<GameMapCell> & cells = gm->GetCells();

    const int cr = GetRow0();
    const int cc = GetCol0();

    const int rad = 1;
    const int r0 = cr >= rad ? cr - rad : 0;
    const int r1 = cr + rad < mapRows ? cr + rad + 1 : mapRows;
    const int c0 = cc >= rad ? cc - rad : 0;
    const int c1 = cc + rad < mapCols ? cc + rad + 1 : mapCols;

    const PlayerFaction ownFaction = GetFaction();

    for(int r = r0; r < r1; ++r)
    {
        const int ind0 = r * mapCols;

        for(int c = c0; c < c1; ++c)
        {
            const int ind = ind0 + c;
            const GameMapCell & cell = cells[ind];

            // enemy found -> boom!
            if((cell.objTop != nullptr && cell.objTop->GetFaction() != ownFaction &&
                 cell.objTop->GetFaction() != NO_FACTION) ||
                (cell.objBottom != nullptr && cell.objBottom->GetFaction() != ownFaction &&
                 cell.objBottom->GetFaction() != NO_FACTION))
            {
                SelfDestroy();
                return ;
            }
        }
    }
}

} // namespace game
