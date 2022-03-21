#include "AI/ObjectPath.h"

#include "GameMap.h"
#include "IsoLayer.h"
#include "IsoMap.h"
#include "IsoObject.h"
#include "Player.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Unit.h"
#include "Screens/ScreenGame.h"

#include <cmath>

namespace game
{

void ObjectPath::InitNextMoveStep()
{
    const IsoObject * isoObj = mObj->GetIsoObject();
    const IsoLayer * layerObj = isoObj->GetLayer();

    mObjX = isoObj->GetX();
    mObjY = isoObj->GetY();

    const unsigned int nextInd = mCells[mNextCell];
    const unsigned int nextRow = nextInd / mIsoMap->GetNumCols();
    const unsigned int nextCol = nextInd % mIsoMap->GetNumCols();
    const sgl::core::Pointd2D target = layerObj->GetObjectPosition(isoObj, nextRow, nextCol);
    mTargetX = target.x;
    mTargetY = target.y;

    mVelX = (mTargetX - mObjX) * mObj->GetSpeed();
    mVelY = (mTargetY - mObjY) * mObj->GetSpeed();

    ++mNextCell;
}

void ObjectPath::Start()
{
    // do nothing if already started
    if(mState != READY)
        return ;

    mNextCell = 1;

    const unsigned int nextInd = mCells[mNextCell];
    const unsigned int nextRow = nextInd / mIsoMap->GetNumCols();
    const unsigned int nextCol = nextInd % mIsoMap->GetNumCols();

    // check if next destination is walkable
    const GameMapCell & nextCell = mGameMap->GetCell(nextRow, nextCol);

    bool canMove = nextCell.walkable;

    // TODO remove check if mObj is changed into mUnit like for other paths
    if(mObj->GetObjectType() == OBJ_UNIT)
        canMove = canMove && static_cast<Unit *>(mObj)->HasEnergyForAction(MOVE);

    if(canMove)
    {
        mState = RUNNING;

        InitNextMoveStep();
    }
    else
    {
        mState = FAILED;

        // clear action data once the action is completed
        mScreen->SetObjectActionCompleted(mObj);
    }
}

void ObjectPath::Update(float delta)
{
    int todo = 2;

    // -- X --
    mObjX += mVelX * delta;

    if(mVelX < 0.f)
    {
        if(mObjX < mTargetX)
        {
            --todo;
            mObjX = mTargetX;
        }
    }
    else if(mVelX > 0.f)
    {
        if(mObjX > mTargetX)
        {
            --todo;
            mObjX = mTargetX;
        }
    }
    else
        --todo;

    // -- Y --
    mObjY += mVelY * delta;

    if(mVelY < 0.f)
    {
        if(mObjY < mTargetY)
        {
            --todo;
            mObjY = mTargetY;
        }
    }
    else if(mVelY > 0.f)
    {
        if(mObjY > mTargetY)
        {
            --todo;
            mObjY = mTargetY;
        }
    }
    else
        --todo;

    // position object
    IsoObject * isoObj = mObj->GetIsoObject();
    isoObj->SetX(static_cast<int>(std::roundf(mObjX)));
    isoObj->SetY(static_cast<int>(std::roundf(mObjY)));

    // handle reached target
    if(0 == todo)
    {
        Player * player = mObj->GetOwner();

        mGameMap->DelPlayerObjVisibility(mObj, player);

        const unsigned int targetInd = mCells[mNextCell - 1];
        const unsigned int targetRow = targetInd / mIsoMap->GetNumCols();
        const unsigned int targetCol = targetInd % mIsoMap->GetNumCols();

        const GameMapCell & targetCell = mGameMap->GetCell(targetRow, targetCol);

        // collect collectable object, if any
        if(targetCell.walkable && targetCell.objTop != nullptr)
        {
            player->HandleCollectable(targetCell.objTop);

            mGameMap->RemoveAndDestroyObject(targetCell.objTop);
        }

        // handle moving object
        mGameMap->MoveObjToCell(mObj, targetRow, targetCol);
        mGameMap->AddPlayerObjVisibility(mObj, player);
        mGameMap->ApplyVisibility(player);

        // TODO remove check if mObj is changed into mUnit like for other paths
        if(mObj->GetObjectType() == OBJ_UNIT)
            static_cast<Unit *>(mObj)->ConsumeEnergy(MOVE);

        // handle next step or termination
        if(ABORTING == mState)
        {
            mState = ABORTED;

            // clear action data once the action is completed
            mScreen->SetObjectActionCompleted(mObj);
        }
        else if(mNextCell < mCells.size())
        {
            const unsigned int nextInd = mCells[mNextCell];
            const unsigned int nextRow = nextInd / mIsoMap->GetNumCols();
            const unsigned int nextCol = nextInd % mIsoMap->GetNumCols();

            // check if next destination is walkable
            const GameMapCell & nextCell = mGameMap->GetCell(nextRow, nextCol);

            bool canMove = nextCell.walkable;

            // TODO remove check if mObj is changed into mUnit like for other paths
            if(mObj->GetObjectType() == OBJ_UNIT)
                canMove = canMove && static_cast<Unit *>(mObj)->HasEnergyForAction(MOVE);

            if(canMove)
                InitNextMoveStep();
            else
            {
                mState = FAILED;

                // clear action data once the action is completed
                mScreen->SetObjectActionCompleted(mObj);
            }
        }
        else
        {
            mState = COMPLETED;

            // clear action data once the action is completed
            mScreen->SetObjectActionCompleted(mObj);

            mOnCompleted();
        }
    }
}

void ObjectPath::UpdatePathCost()
{
    // TODO proper cost computation
    mCost = (mCells.size() - 1) * 0.5f;
}

} // namespace game
