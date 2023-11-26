#include "GameObjects/DiamondsGenerator.h"

#include "GameConstants.h"
#include "GameMap.h"
#include "GameObjects/Diamonds.h"

#include <sgl/utilities/UniformDistribution.h>

namespace game
{

DiamondsGenerator::DiamondsGenerator(GameMap * gm)
    : CollectableGenerator(gm, 10, 40)
{
}

void DiamondsGenerator::OnGeneration()
{
    GameMap * gm = GetGameMap();

    const int r = GetRow();
    const int c = GetCol();

    GameObject * obj = gm->CreateObject(MapLayers::OBJECTS2, GameObject::TYPE_DIAMONDS,
                                        0, NO_FACTION, r, c);

    if(nullptr == obj)
        return ;

    auto diamonds = static_cast<Diamonds *>(obj);

    // set number of diamonds in cell
    sgl::utilities::UniformDistribution ran(Diamonds::MIN_UNITS, Diamonds::MAX_UNITS);
    const int num = ran.GetNextValue();
    diamonds->SetNum(num);

    diamonds->SetGenerator(this);

    // update visibility
    gm->ApplyLocalVisibilityToObject(obj);

    // make the cell walkable for collection
    gm->SetCellWalkable(r, c, true);
}

} // namespace game
