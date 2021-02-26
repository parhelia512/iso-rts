﻿#pragma once

#include <unordered_map>

namespace game
{

class GameObject;
class Player;
class ResourceGenerator;
class Unit;

enum CellTypes : int
{
    EMPTY = 0,
    SCENE,
    DIAMONDS_SOURCE,

    // FACTION 1
    F1,
    F1_CONNECTED,
    F1_INFLUENCED,

    // FACTION 2
    F2,
    F2_CONNECTED,
    F2_INFLUENCED,

    // FACTION 3
    F3,
    F3_CONNECTED,
    F3_INFLUENCED,

    // SPECIAL
    FOG_OF_WAR,

    NUM_CELL_TYPES
};

struct GameMapCell
{
    GameMapCell();

    Unit * GetUnit() const;
    bool HasUnit() const;

    ResourceGenerator * GetResourceGenerator() const;
    bool HasResourceGenerator() const;

    std::unordered_map<int, bool> influencers;
    int influencer = -1;

    Player * owner = nullptr;
    GameObject * obj = nullptr;

    CellTypes basicType = EMPTY;

    int row = 0;
    int col = 0;
    bool walkable = true;
    bool changing = false;
    bool linked = false;
};

} // namespace game
