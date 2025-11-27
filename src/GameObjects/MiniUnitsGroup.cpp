#include "GameObjects/MiniUnitsGroup.h"

#include "GameConstants.h"

namespace game
{

MiniUnitsGroup::MiniUnitsGroup(PlayerFaction faction)
    : mFaction(faction)
{
}

// this reduces the current path of 1 step and changes the tarteg to the new end
bool MiniUnitsGroup::PopPathTargetBack(int mapCols)
{
    if(mPath.empty())
        return false;

    mPath.pop_back();

    if(mPath.empty())
        return false;

    const unsigned int targetInd = mPath.back();

    mTarget.row = targetInd / mapCols;
    mTarget.col = targetInd % mapCols;

    return true;
}

} // namespace game
