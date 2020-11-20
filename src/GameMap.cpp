#include "GameMap.h"

#include "Cell2D.h"
#include "Game.h"
#include "GameConstants.h"
#include "IsoLayer.h"
#include "IsoMap.h"
#include "Player.h"
#include "Screens/ScreenGame.h"

#include <utilities/UniformDistribution.h>

#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

#include <iostream>

namespace game
{

enum CellTypes : int
{
    EMPTY = 0,
    FULL,

    // PLAYER 1
    P1L1,
    P1L2,
    P1L3,
    P1L4,

    // PLAYER 2
    P2L1,
    P2L2,
    P2L3,
    P2L4,

    // PLAYER 3
    P3L1,
    P3L2,
    P3L3,
    P3L4,

    // PLAYER 4
    P4L1,
    P4L2,
    P4L3,
    P4L4,

    NUM_CELL_TYPES
};

enum UnitType : int
{
    // PLAYER 1 - LEVEL 1
    P1_1UL1,
    P1_2UL1,
    P1_3UL1,
    P1_4UL1,

    // PLAYER 1 - LEVEL 2
    P1_1UL2,
    P1_2UL2,
    P1_3UL2,
    P1_4UL2,

    // PLAYER 1 - LEVEL 3
    P1_1UL3,
    P1_2UL3,
    P1_3UL3,
    P1_4UL3,

    // PLAYER 2 - LEVEL 1
    P2_1UL1,
    P2_2UL1,
    P2_3UL1,
    P2_4UL1,

    // PLAYER 2 - LEVEL 2
    P2_1UL2,
    P2_2UL2,
    P2_3UL2,
    P2_4UL2,

    // PLAYER 2 - LEVEL 3
    P2_1UL3,
    P2_2UL3,
    P2_3UL3,
    P2_4UL3,

    // PLAYER 3 - LEVEL 1
    P3_1UL1,
    P3_2UL1,
    P3_3UL1,
    P3_4UL1,

    // PLAYER 3 - LEVEL 2
    P3_1UL2,
    P3_2UL2,
    P3_3UL2,
    P3_4UL2,

    // PLAYER 3 - LEVEL 3
    P3_1UL3,
    P3_2UL3,
    P3_3UL3,
    P3_4UL3,

    // PLAYER 4 - LEVEL 1
    P4_1UL1,
    P4_2UL1,
    P4_3UL1,
    P4_4UL1,

    // PLAYER 4 - LEVEL 2
    P4_1UL2,
    P4_2UL2,
    P4_3UL2,
    P4_4UL2,

    // PLAYER 4 - LEVEL 3
    P4_1UL3,
    P4_2UL3,
    P4_3UL3,
    P4_4UL3,

    NUM_UNIT_TYPES,

    UNIT_NULL
};

// ==================== CONSTRUCTORS AND DESTRUCTOR ====================

GameMap::GameMap(Game * game, ScreenGame * sg, IsoMap * isoMap)
    : mCells(isoMap->GetNumRows() * isoMap->GetNumCols())
    , mGame(game)
    , mScreenGame(sg)
    , mIsoMap(isoMap)
    , mRows(isoMap->GetNumRows())
    , mCols(isoMap->GetNumCols())
{
    int index = 0;

    for(int r = 0; r < isoMap->GetNumRows(); ++r)
    {
        for(int c = 0; c < isoMap->GetNumCols(); ++c)
        {
            mCells[index].row = r;
            mCells[index].col = c;

            ++index;
        }
    }
}

// ==================== PUBLIC METHODS ====================

bool GameMap::Load(const char * file)
{
    std::fstream f(file);

    if(!f.is_open())
        return false;

    std::string line;

    for(unsigned int r = 0; r < mRows; ++r)
    {
        const unsigned int indb = r * mCols;

        std::getline(f, line);

        for(unsigned int c = 0; c < mCols; ++c)
        {
            const unsigned int ind = indb + c;

            const int type = line[c] - '0';

            mCells[ind].walkable = type != FULL;

            mIsoMap->SetCellType(r, c, type);
        }
    }

    return true;
}

void GameMap::SetHomeCell()
{
    const int limitRow = mIsoMap->GetNumRows() - 1;
    const int limitCol = mIsoMap->GetNumCols() - 1;

    const int NUM_CORNERS = 4;
    const Cell2D corners[NUM_CORNERS] =
    {
        { 0, 0 },
        { 0, limitCol },
        { limitRow, limitCol  },
        { limitRow, 0}
    };

    const int numPlayers = mGame->GetNumPlayers();

    int pick = rand() % NUM_CORNERS;

    for(int p = 0; p < numPlayers; ++p)
    {
        Player * player = mGame->GetPlayer(p);

        const int c = pick % NUM_CORNERS;
        const int ind = corners[c].row * mCols + corners[c].col;

        GameMapCell & cell = mCells[ind];
        cell.owner = player;

        const int cellType = DefineCellType(cell);
        mIsoMap->SetCellType(ind, cellType);

        player->SumCells(1);
        player->SumTotalCellsLevel(1);

        // inc by 2, 1, 2
        pick += 2 - (p % 2);
    }
}

void GameMap::AssignCell(const Cell2D & cell, Player * player)
{
    const int ind = cell.row * mCols + cell.col;
    GameMapCell & gcell = mCells[ind];

    gcell.owner = player;

    const int cellType = DefineCellType(gcell);
    mIsoMap->SetCellType(ind, cellType);

    player->SumCells(1);
    player->SumTotalCellsLevel(1);
}

bool GameMap::CanUpgradeCell(const Cell2D & cell, Player * player)
{
    const unsigned int r = static_cast<unsigned int>(cell.row);
    const unsigned int c = static_cast<unsigned int>(cell.col);

    // out of bounds
    if(!(r < mRows && c < mCols))
        return false;

    const int ind = r * mCols + c;
    GameMapCell & gcell = mCells[ind];

    // already changing, not own cell or already max level
    if(gcell.changing ||
       gcell.owner != player ||
       MAX_CELL_LEVEL == gcell.level)
        return false;

    // check if player has enough money
    const int cost = COST_CELL_UPGRADE[gcell.level];

    if(cost > player->GetMoney())
        return false;

    return true;
}

void GameMap::StartUpgradeCell(const Cell2D & cell, Player * player)
{
    const int ind = cell.row * mCols + cell.col;
    GameMapCell & gcell = mCells[ind];

    // take player's money
    const int cost = COST_CELL_UPGRADE[gcell.level];

    player->SumMoney(-cost);

    // mark cell as changing
    gcell.changing = true;
}

void GameMap::UpgradeCell(const Cell2D & cell, Player * player)
{
    const int ind = cell.row * mCols + cell.col;
    GameMapCell & gcell = mCells[ind];

    ++(gcell.level);

    // update player
    player->SumTotalCellsLevel(1);

    // update map
    const int cellType = DefineCellType(gcell);
    mIsoMap->SetCellType(ind, cellType);

    // reset cell's changing flag
    gcell.changing = false;
}

bool GameMap::CanFortifyCell(const Cell2D & cell, Player * player)
{
    const unsigned int r = static_cast<unsigned int>(cell.row);
    const unsigned int c = static_cast<unsigned int>(cell.col);

    // out of bounds
    if(!(r < mRows && c < mCols))
        return false;

    const int ind = r * mCols + c;
    GameMapCell & gcell = mCells[ind];

    // already changing, not own cell or max level cell -> exit
    if(gcell.changing ||
       gcell.owner != player ||
       MAX_CELL_FORT_LEVEL == gcell.fortLevel)
        return false;

    // check if player has enough money
    const int cost = COST_CELL_FORT[gcell.fortLevel];

    if(cost > player->GetMoney())
        return false;

    return true;
}

void GameMap::StartFortifyCell(const Cell2D & cell, Player * player)
{
    const int ind = cell.row * mCols + cell.col;
    GameMapCell & gcell = mCells[ind];

    // take player's money
    const int cost = COST_CELL_FORT[gcell.fortLevel];

    player->SumMoney(-cost);

    // mark cell as changing
    gcell.changing = true;
}

void GameMap::FortifyCell(const Cell2D & cell)
{
    const unsigned int r = static_cast<unsigned int>(cell.row);
    const unsigned int c = static_cast<unsigned int>(cell.col);
    const int ind = r * mCols + c;
    GameMapCell & gcell = mCells[ind];

    ++(gcell.fortLevel);

    // update map layer
    mIsoMap->GetLayer(FORTIFICATIONS)->ReplaceObject(r, c, gcell.fortLevel - 1, NO_ALIGNMENT);

    // reset cell's changing flag
    gcell.changing = false;
}

bool GameMap::CanCreateUnit(const Cell2D & cell, Player * player)
{
    const unsigned int r = static_cast<unsigned int>(cell.row);
    const unsigned int c = static_cast<unsigned int>(cell.col);

    // out of bounds
    if(!(r < mRows && c < mCols))
        return false;

    const int ind = r * mCols + c;
    GameMapCell & gcell = mCells[ind];

    // already changing, not own cell or max level cell -> exit
    if(gcell.changing ||
       gcell.owner != player ||
       MAX_CELL_UNITS == gcell.units)
        return false;

    // check if player has enough money
    const int cost = COST_NEW_UNIT[gcell.unitsLevel];

    if(cost > player->GetMoney())
        return false;

    return true;
}

void GameMap::StartCreateUnit(const Cell2D & cell, Player * player)
{
    const int ind = cell.row * mCols + cell.col;
    GameMapCell & gcell = mCells[ind];

    // make player pay
    const int cost = COST_NEW_UNIT[gcell.unitsLevel];
    player->SumMoney(-cost);

    // mark cell as changing
    gcell.changing = true;
}

void GameMap::CreateUnit(const Cell2D & cell, Player * player)
{
    const unsigned int r = static_cast<unsigned int>(cell.row);
    const unsigned int c = static_cast<unsigned int>(cell.col);

    const int ind = r * mCols + c;
    GameMapCell & gcell = mCells[ind];

    ++(gcell.units);

    // update player
    player->SumUnits(1);
    player->SumTotalUnitsLevel(gcell.unitsLevel + 1);

    // update map layer
    const int unitImg = DefineUnitType(gcell);

    if(unitImg != UNIT_NULL)
        mIsoMap->GetLayer(UNITS)->ReplaceObject(r, c, unitImg, NO_ALIGNMENT);

    // reset cell's changing flag
    gcell.changing = false;
}

bool GameMap::CanDestroyUnit(const Cell2D & cell, Player * player)
{
    const unsigned int r = static_cast<unsigned int>(cell.row);
    const unsigned int c = static_cast<unsigned int>(cell.col);

    // out of bounds
    if(!(r < mRows && c < mCols))
        return false;

    const int ind = r * mCols + c;
    GameMapCell & gcell = mCells[ind];

    // not own cell or no units -> exit
    if(gcell.owner != player || !gcell.units)
        return false;

    return true;
}

void GameMap::DestroyUnit(const Cell2D & cell, Player * player)
{
    const unsigned int r = static_cast<unsigned int>(cell.row);
    const unsigned int c = static_cast<unsigned int>(cell.col);
    const int ind = r * mCols + c;
    GameMapCell & gcell = mCells[ind];

    // update player
    player->SumUnits(-gcell.units);
    player->SumTotalUnitsLevel(-gcell.units * (gcell.unitsLevel + 1));

    // remove units from cell
    gcell.units = 0;
    gcell.unitsLevel = 0;

    // destroy object
    mIsoMap->GetLayer(UNITS)->ClearObject(r, c);
}

bool GameMap::CanUpgradeUnit(const Cell2D & cell, Player * player)
{
    const unsigned int r = static_cast<unsigned int>(cell.row);
    const unsigned int c = static_cast<unsigned int>(cell.col);

    // out of bounds
    if(!(r < mRows && c < mCols))
        return false;

    const int ind = r * mCols + c;
    GameMapCell & gcell = mCells[ind];

    // cell already changing, not own cell or max level units or no units -> exit
    if(gcell.changing ||
       gcell.owner != player ||
       MAX_UNITS_LEVEL == gcell.unitsLevel || !gcell.units)
        return false;

    // check if player has enough money
    const int cost = COST_UNIT_UPGRADE[gcell.unitsLevel] * gcell.units;

    if(cost > player->GetMoney())
        return false;

    return true;
}

void GameMap::StartUpgradeUnit(const Cell2D & cell, Player * player)
{
    const int ind = cell.row * mCols + cell.col;
    GameMapCell & gcell = mCells[ind];

    // make player pay
    const int cost = COST_UNIT_UPGRADE[gcell.unitsLevel];
    player->SumMoney(-cost);

    // mark cell as changing
    gcell.changing = true;
}

void GameMap::UpgradeUnit(const Cell2D & cell)
{
    const unsigned int r = static_cast<unsigned int>(cell.row);
    const unsigned int c = static_cast<unsigned int>(cell.col);
    const int ind = r * mCols + c;
    GameMapCell & gcell = mCells[ind];

    // all good -> upgrade
    ++(gcell.unitsLevel);

    // update player
    gcell.owner->SumTotalUnitsLevel(gcell.units);

    // update map layer
    const int unitImg = DefineUnitType(gcell);

    if(unitImg != UNIT_NULL)
        mIsoMap->GetLayer(UNITS)->ReplaceObject(r, c, unitImg, NO_ALIGNMENT);

    // reset cell's changing flag
    gcell.changing = false;
}

bool GameMap::MoveUnits(const Cell2D & start, const Cell2D & end, int numUnits, Player * player)
{
    const unsigned int r0 = static_cast<unsigned int>(start.row);
    const unsigned int c0 = static_cast<unsigned int>(start.col);

    // start out of bounds
    if(!(r0 < mRows && c0 < mCols))
        return false;

    const unsigned int r1 = static_cast<unsigned int>(end.row);
    const unsigned int c1 = static_cast<unsigned int>(end.col);

    // end out of bounds
    if(!(r1 < mRows && c1 < mCols))
        return false;

    const int diffR = abs(end.row - start.row);
    const int diffC = abs(end.col - start.col);

    // end too far - units can only move to next cell
    if(diffR > 1 || diffC > 1)
        return false;

    const int ind0 = r0 * mCols + c0;
    GameMapCell & gcell0 = mCells[ind0];

    // start cell is not own cell
    if(player != gcell0.owner)
        return false;

    // not enough units to move
    if(0 == numUnits || gcell0.units < numUnits)
        return false;

    const int ind1 = r1 * mCols + c1;
    GameMapCell & gcell1 = mCells[ind1];

    // not a walkable cell
    if(!gcell1.walkable)
        return false;

    Player * playerDest = gcell1.owner;

    const bool emptyDest = 0 ==gcell1.units;

    // move to empty cell
    if(nullptr == playerDest)
    {
        // move units between cells
        gcell0.units -= numUnits;
        gcell1.units += numUnits;

        // propagate unit level to end
        gcell1.unitsLevel = gcell0.unitsLevel;

        // update owner of end
        gcell1.owner = player;

        // update player stats after conquering a new cell
        player->SumCells(1);
        player->SumTotalCellsLevel(1);

        // update unit objects and cells
        UpdateCellsAfterMove(gcell0, gcell1, emptyDest);
    }
    // move to own cell
    else if(player == playerDest)
    {
        // end cell is empty
        if(emptyDest)
        {
            // move units between cells
            gcell0.units -= numUnits;
            gcell1.units += numUnits;

            // propagate unit level to end
            gcell1.unitsLevel = gcell0.unitsLevel;

            // update unit objects and cells
            UpdateCellsAfterMove(gcell0, gcell1, emptyDest);
        }
        // end cell has units
        else
        {
            // fail if destination is full or has different level units
            if(gcell1.units == MAX_CELL_UNITS || gcell0.unitsLevel != gcell1.unitsLevel)
                return false;

            // cap units moved to max allowed per cell
            if(gcell1.units + numUnits > MAX_CELL_UNITS)
                numUnits = MAX_CELL_UNITS - gcell1.units;

            // move units between cells
            gcell0.units -= numUnits;
            gcell1.units += numUnits;

            // update unit objects and cells
            UpdateCellsAfterMove(gcell0, gcell1, emptyDest);
        }
    }
    // move to enemy cell (attack)
    else
    {
        return false;
    }

    // TODO
    /*

    // enemy cell
    else
    {
        lib::utilities::UniformDistribution rgen(POINTS_CELL_MIN, POINTS_CELL_MAX);

        // points of cell
        const int cellPoints = rgen.GetNextValue() * (gcell1.fortLevel + POINTS_CELL_INC);

        // points of attacking units
        rgen.SetParameters(POINTS_UNIT_MIN, POINTS_UNIT_MAX);
        std::vector<int> pointsAtt(numUnits);

        for(int i = 0; i < numUnits; ++i)
            pointsAtt[i] = rgen.GetNextValue() * (gcell0.unitsLevel + POINTS_UNIT_INC);

        int lossesAtt = 0;

        Player * playerDef = mGame->GetPlayer(gcell1.ownerId);

        // cell with units
        if(gcell1.units)
        {
            // points of defending units
            rgen.SetParameters(POINTS_CELL_UNIT_MIN, POINTS_CELL_UNIT_MAX);
            std::vector<int> pointsDef(gcell1.units);

            for(int i = 0; i < gcell1.units; ++i)
                pointsDef[i] = rgen.GetNextValue() * (gcell1.unitsLevel + POINTS_CELL_UNIT_INC) + cellPoints;

            std::vector<bool> unitsDef(gcell1.units, false);
            std::vector<bool> unitsAtt(numUnits, false);

            int lossesDef = 0;

            for(int d = 0; d < gcell1.units; ++d)
            {
                for(int a = 0; a < numUnits; ++a)
                {
                    if(pointsDef[d] < pointsAtt[a])
                        unitsDef[d] = true;
                    else
                        unitsAtt[a] = true;
                }
            }

            lossesDef = std::count_if(unitsDef.begin(), unitsDef.end(), [](bool v) { return v; });
            lossesAtt = std::count_if(unitsAtt.begin(), unitsAtt.end(), [](bool v) { return v; });

            std::cout << "\nDEF: ";
            for(int d : pointsDef)
                std::cout << d << " ";

            std::cout << "\nATT: ";
            for(int a : pointsAtt)
                std::cout << a << " ";

            std::cout << "\nlosses DEF: " << lossesDef << " - losses ATT: "  << lossesAtt << std::endl;

            // update players
            player->SumUnits(-lossesAtt);
            player->SumTotalUnitsLevel(-lossesAtt * (gcell0.unitsLevel + 1));

            playerDef->SumUnits(-lossesDef);
            playerDef->SumTotalUnitsLevel(-lossesDef * (gcell1.unitsLevel + 1));

            // destroyed all defenders
            if(lossesDef == gcell1.units)
            {
                const int attackingLeft = numUnits - lossesAtt;

                // clear def fortification, if any
                mIsoMap->GetLayer(FORTIFICATIONS)->ClearObject(r1, c1);

                // update att cell
                gcell0.units -= numUnits;

                if(gcell0.units)
                {
                    const int unitImg0 = DefineUnitType(gcell0);
                    layerUnits->ReplaceObject(r0, c0, unitImg0, NO_ALIGNMENT);
                }
                else
                    layerUnits->ClearObject(r0, c0);

                // update conquered cell
                gcell1.ownerId = gcell0.ownerId;
                gcell1.fortLevel = 0;
                gcell1.unitsLevel = gcell0.unitsLevel;
                gcell1.units = attackingLeft;

                // clear any current activity in the cell
                if(gcell1.changing)
                {
                    mScreenGame->CancelProgressBar(end);
                    gcell1.changing = false;
                }

                // update conquered cell look
                const int cellType = DefineCellType(gcell1);
                mIsoMap->SetCellType(ind1, cellType);

                // replace units in conquered cell
                const int unitImg1 = DefineUnitType(gcell1);
                layerUnits->ReplaceObject(r1, c1, unitImg1, NO_ALIGNMENT);

                // update att player
                player->SumCells(1);
                player->SumTotalCellsLevel(1);

                // update def player
                playerDef->SumCells(-1);
                playerDef->SumTotalCellsLevel(-1);
            }
            // defenders won
            else
            {
                const int defLeft = gcell1.units - lossesDef;

                // update def cell
                gcell1.units = defLeft;

                const int unitImg1 = DefineUnitType(gcell1);
                layerUnits->ReplaceObject(r1, c1, unitImg1, NO_ALIGNMENT);

                // destroyed all unit in attacking cell
                if(lossesAtt == gcell0.units)
                {
                    // clear att fortification, if any
                    mIsoMap->GetLayer(FORTIFICATIONS)->ClearObject(r0, c0);

                    player->SumCells(-1);
                    player->SumTotalCellsLevel(-1);

                    // clear attacker cell
                    gcell0.Clear();

                    // delete units in attacker cell
                    layerUnits->ClearObject(r0, c0);
                }
                // some units left
                else
                {
                    // update units in attacking cell
                    gcell0.units -= lossesAtt;

                    const int unitImg0 = DefineUnitType(gcell0);
                    layerUnits->ReplaceObject(r0, c0, unitImg0, NO_ALIGNMENT);
                }

                // update cell
                const int cellType = DefineCellType(gcell0);
                mIsoMap->SetCellType(ind0, cellType);
            }
        }
        // cell with no units
        else
        {
            // fight
            for(int points : pointsAtt)
            {
                if(points <= cellPoints)
                {
                    --gcell0.units;
                    ++lossesAtt;
                }
            }

            std::cout << "\nDEF: "  << cellPoints;
            std::cout << "\nATT: ";
            for(int a : pointsAtt)
                std::cout << a << " ";

            std::cout << "\nlosses ATT: "  << lossesAtt << std::endl;

            // update player
            player->SumUnits(-lossesAtt);
            player->SumTotalUnitsLevel(-lossesAtt * (gcell0.unitsLevel + 1));

            // some attacking unit left
            if(gcell0.units)
            {
                // remove alive attacking units from cell0
                const int attackingLeft = numUnits - lossesAtt;
                gcell0.units -= attackingLeft;

                // update attacking units
                if(gcell0.units)
                {
                    const int unitType0 = DefineUnitType(gcell0);
                    layerUnits->ChangeObject(r0, c0, unitType0);
                }
                else
                    layerUnits->ClearObject(r0, c0);

                // some attacking unit left -> cell conquered
                if(attackingLeft)
                {
                    // clear fortification, if any
                    mIsoMap->GetLayer(FORTIFICATIONS)->ClearObject(r1, c1);

                    // update conquered cell
                    gcell1.ownerId = gcell0.ownerId;
                    gcell1.fortLevel = 0;
                    gcell1.unitsLevel = gcell0.unitsLevel;
                    gcell1.units = attackingLeft;

                    // clear any current activity in the cell
                    if(gcell1.changing)
                    {
                        mScreenGame->CancelProgressBar(end);
                        gcell1.changing = false;
                    }

                    // update source attacking cell
                    const int cellType = DefineCellType(gcell1);
                    mIsoMap->SetCellType(ind1, cellType);

                    // create new units in conquered cell
                    const int unitImg1 = DefineUnitType(gcell1);
                    layerUnits->AddObject(r1, c1, unitImg1, NO_ALIGNMENT);

                    // update att player
                    player->SumCells(1);
                    player->SumTotalCellsLevel(1);

                    // update def player
                    playerDef->SumCells(-1);
                    playerDef->SumTotalCellsLevel(-1);
                }
            }
            // no attacking units left -> defender won
            else
            {
                // clear fortification, if any
                mIsoMap->GetLayer(FORTIFICATIONS)->ClearObject(r0, c0);

                // clear attacker cell, but keep level
                gcell0.Clear();

                // update cell
                const int cellType = DefineCellType(gcell0);
                mIsoMap->SetCellType(ind0, cellType);

                // delete units in attacker cell
                layerUnits->ClearObject(r0, c0);
            }
        }
    }
    */

    // check for victory or game over
    const int players = mGame->GetNumPlayers();
    int defeated = 0;

    for(int i = 0; i < players; ++i)
    {
        Player * p = mGame->GetPlayer(i);

        if(p->GetNumCells() == 0)
        {
            if(p->IsLocal())
            {
                mScreenGame->GameOver();
                return true;
            }
            else
                ++defeated;
        }
    }

    // assuming players is always > 1
    if(defeated == (players - 1))
        mScreenGame->GameWon();

    return true;
}

// ==================== PRIVATE METHODS ====================

void GameMap::UpdateCellsAfterMove(GameMapCell & gcell0, GameMapCell & gcell1, bool emptyDest)
{
    IsoLayer * layerUnits = mIsoMap->GetLayer(UNITS);

    // moved all units
    if(0 == gcell0.units)
    {
        // reset unit level in start
        gcell0.unitsLevel = 0;

        // move unit object from start to end
        if(emptyDest)
            layerUnits->MoveObject(gcell0.row, gcell0.col, gcell1.row, gcell1.col, NO_ALIGNMENT);
        else
        {
            // delete unit object in start
            layerUnits->ClearObject(gcell0.row, gcell0.col);

            // update unit object in end
            const int unitType1 = DefineUnitType(gcell1);
            layerUnits->ChangeObject(gcell1.row, gcell1.col, unitType1);
        }
    }
    // moved part of units
    else
    {
        // update unit object in start
        const int unitType0 = DefineUnitType(gcell0);
        layerUnits->ChangeObject(gcell0.row, gcell0.col, unitType0);

        // add new unit object in end
        if(emptyDest)
        {
            const int unitType1 = DefineUnitType(gcell1);
            layerUnits->AddObject(gcell1.row, gcell1.col, unitType1, NO_ALIGNMENT);
        }
        // update existing object in end
        else
        {
            // update unit object in end
            const int unitType1 = DefineUnitType(gcell1);
            layerUnits->ChangeObject(gcell1.row, gcell1.col, unitType1);
        }
    }

    // update cell type of start
    const int cellType0 = DefineCellType(gcell0);
    mIsoMap->SetCellType(gcell0.row, gcell0.col, cellType0);

    // update cell type of end
    const int cellType1 = DefineCellType(gcell1);
    mIsoMap->SetCellType(gcell1.row, gcell1.col, cellType1);
}

int GameMap::DefineCellType(const GameMapCell & cell)
{
    // cell is not owned
    if(nullptr == cell.owner)
        return EMPTY;

    int type = EMPTY;

    switch(cell.owner->GetPlayerId())
    {
        case 0:
            type = P1L1 + cell.level;
        break;

        case 1:
            type = P2L1 + cell.level;
        break;

        case 2:
            type = P3L1 + cell.level;
        break;

        case 3:
            type = P4L1 + cell.level;
        break;

        default:
        break;
    }

    return type;
}

int GameMap::DefineUnitType(const GameMapCell & cell)
{
    // cell is not owned
    if(nullptr == cell.owner)
        return UNIT_NULL;

    int type = (cell.units - 1) + (cell.unitsLevel * MAX_CELL_UNITS);

    switch(cell.owner->GetPlayerId())
    {
        case 0:
            type += P1_1UL1;
        break;

        case 1:
            type += P2_1UL1;
        break;

        case 2:
            type += P3_1UL1;
        break;

        case 3:
            type += P4_1UL1;
        break;

        default:
            type = UNIT_NULL;
        break;
    }

    return type;
}

} // namespace game
