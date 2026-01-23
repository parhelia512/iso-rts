#include "GameObjects/CityGroup.h"

#include "Player.h"
#include "GameObjects/CityBlock.h"

namespace game
{

void CityGroup::UpdateCityConquered(Player * conqueror)
{
    const std::vector<GameObject *> & objs = GetObjects();

    const PlayerFaction f = conqueror->GetFaction();

    for(auto o : objs)
    {
        auto cb = static_cast<CityBlock *>(o);

        if(cb->IsBorder() && cb->GetFaction() != f)
        {
            mConquered = false;
            return;
        }
    }

    // all border blocks are conquered -> city is conquered
    mConquered = true;

    for(auto o : objs)
        o->SetOwner(conqueror);
}

} // namespace game
