#pragma once

#include <vector>

namespace game
{

class IsoLayer;
class PathIndicator;

enum PlayerFaction : unsigned int;

class PathOverlay
{
public:
    PathOverlay(IsoLayer * layer, int mapRows, int mapCols);
    ~PathOverlay();

    void ClearPath();
    void SetPath(const std::vector<unsigned int> & path, PlayerFaction faction, int cost = -1);

private:
    PathIndicator * GetNewIndicator(PlayerFaction faction, bool final);

private:
    std::vector<PathIndicator * > mActiveIndicators;
    std::vector<PathIndicator * > mIndicators;

    IsoLayer * mLayer = nullptr;

    unsigned int mNextIndicator = 0;

    int mMapRows = 0;
    int mMapCols = 0;
};

} // namespace game
