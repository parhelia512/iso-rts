#include "AI/ConquerPath.h"

#include "GameConstants.h"
#include "GameMap.h"
#include "IsoLayer.h"
#include "IsoMap.h"
#include "IsoObject.h"
#include "Player.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Unit.h"
#include "Indicators/ConquestIndicator.h"
#include "Screens/ScreenGame.h"

#include <cmath>
#include <unordered_set>

namespace game
{

ConquerPath::ConquerPath(Unit * unit, IsoMap * im, GameMap * gm, ScreenGame * sg)
    : mOnCompleted([]{}), mOnFailed([]{}), mUnit(unit), mIsoMap(im), mGameMap(gm), mScreen(sg)
{
    mLocalPlayer = unit->GetOwner()->IsLocal();
}

ConquerPath::~ConquerPath()
{
    // delete the ConquestIndicators
    for(auto ind : mIndicators)
        delete ind;
}

void ConquerPath::Start()
{
    // do nothing if already started
    if(mState != READY)
        return ;

    if(mLocalPlayer)
        CreateIndicators();

    // stat conquering first cell
    InitNextConquest();
}

void ConquerPath::Abort()
{
    if(CONQUERING_CELL == mState)
        FinishAbortion();
    else
        mState = ABORTED;
}

void ConquerPath::Update(float delta)
{
    if(CONQUER_NEXT == mState)
        InitNextConquest();
}

void ConquerPath::CreateIndicators()
{
    IsoLayer * layer = mIsoMap->GetLayer(MapLayers::CELL_OVERLAYS1);
    Player * player = mUnit->GetOwner();

    const PlayerFaction faction = player->GetFaction();

    // do not create indicator for cell 0 as it's current under conquest
    for(unsigned int i = 1; i < mCells.size(); ++i)
    {
        ConquestIndicator * ind = new ConquestIndicator;
            mIndicators.emplace_back(ind);

        // add indicator to layer
        const unsigned int pathInd = mCells[i];
        const unsigned int indRow = pathInd / mIsoMap->GetNumCols();
        const unsigned int indCol = pathInd % mIsoMap->GetNumCols();

        layer->AddObject(ind, indRow, indCol);

        ind->SetFaction(faction);
    }
}

void ConquerPath::InitNextConquest()
{
    mState = CONQUERING_CELL;

    IsoLayer * layerOverlay = mIsoMap->GetLayer(MapLayers::CELL_OVERLAYS1);

    // check if unit has enough energy to continue
    if(!mUnit->HasEnergyForAction(CONQUER_CELL))
    {
        Fail();

        // clear indicators
        layerOverlay->ClearObjects();

        return ;
    }

    Player * player = mUnit->GetOwner();

    while(mNextCell < mCells.size())
    {
        const unsigned int nextInd = mCells[mNextCell];
        const unsigned int nextRow = nextInd / mIsoMap->GetNumCols();
        const unsigned int nextCol = nextInd % mIsoMap->GetNumCols();
        const Cell2D nextCell(nextRow, nextCol);

        // check if conquest is possible
        if(!mGameMap->CanConquerCell(nextCell, player))
        {
            ++mNextCell;

            // remove current indicator if not finished yet
            if(mLocalPlayer && mNextCell < mCells.size())
                layerOverlay->ClearObject(mIndicators[mNextCell - 1]);

            continue;
        }

        // start conquest
        mGameMap->StartConquerCell(nextCell, player);

        // TODO get conquer time from unit
        constexpr float TIME_CONQ_CELL = 0.5f;

        mScreen->CreateProgressBar(nextCell, TIME_CONQ_CELL, player,
                                   [this, nextCell, player, layerOverlay]
        {
            mGameMap->ConquerCell(nextCell, player);

            mUnit->ConsumeEnergy(CONQUER_CELL);

            ++mNextCell;

            if(mNextCell < mCells.size())
            {
                mState = CONQUER_NEXT;

                // remove current indicator
                if(mLocalPlayer)
                    layerOverlay->ClearObject(mIndicators[mNextCell - 1]);
            }
            else
            {
                mState = COMPLETED;

                // clear action data once the action is completed
                mScreen->SetObjectActionCompleted(mUnit);

                mOnCompleted();
            }
        });

        return ;
    }

    Fail();
}

void ConquerPath::UpdatePathCost()
{
    // TODO proper cost computation
    // use set to ignore repeated cells
    std::unordered_set<unsigned int> cells(mCells.begin(), mCells.end());
    mCost = (cells.size() - 1) * 0.5f;
}

void ConquerPath::FinishAbortion()
{
    // clear progress bar
    const unsigned int nextInd = mCells[mNextCell];
    const unsigned int nextRow = nextInd / mIsoMap->GetNumCols();
    const unsigned int nextCol = nextInd % mIsoMap->GetNumCols();
    const Cell2D cell(nextRow, nextCol);

    mScreen->CancelProgressBar(cell);

    mGameMap->SetCellChanging(nextRow, nextCol, false);

    // clear indicators
    IsoLayer * layerOverlay = mIsoMap->GetLayer(MapLayers::CELL_OVERLAYS1);
    layerOverlay->ClearObjects();

    // set new state
    mState = ABORTED;
}

void ConquerPath::Fail()
{
    mState = FAILED;

    // clear action data once the action is completed
    mScreen->SetObjectActionCompleted(mUnit);

    mOnFailed();
}

} // namespace game
