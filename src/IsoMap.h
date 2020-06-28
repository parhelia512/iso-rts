#pragma once

#include <core/Point.h>

#include <string>
#include <vector>

namespace lib { namespace graphic { class Image; } }

namespace game
{

struct Cell2D;

class IsoMap
{
public:
    IsoMap(unsigned int rows, unsigned int cols, int tileW);
    ~IsoMap();

    void SetTiles(const std::vector<std::string> & files);

    void SetCellType(unsigned int r, unsigned int c, unsigned int type);
    void SetCellType(unsigned int index, unsigned int type);
    int GetCellType(unsigned int r, unsigned int c) const;
    int GetCellType(unsigned int index) const;

    int GetTileWidth() const;
    int GetTileHeight() const;

    int GetWidth() const;
    int GetHeight() const;

    void SetOrigin(int x, int y);

    void Render();

    Cell2D CellFromScreenPoint(int x, int y) const;

    bool IsCellInside(const Cell2D & cell) const;

private:
    void UpdateTilePositions();

private:
    unsigned int mRows = 0;
    unsigned int mCols = 0;

    int mX0 = 0;
    int mRenderX0 = 0;
    int mY0 = 0;

    int mTileW = 0;
    int mTileH = 0;
    int mTileHalfH = 0;
    int mOrthoTileSize = 0;

    std::vector<unsigned int> mMap;
    std::vector<lib::graphic::Image *> mTiles;
    std::vector<lib::core::Point2D> mTilePositions;
};

inline void IsoMap::SetCellType(unsigned int r, unsigned int c, unsigned int type)
{
    if(r < mRows && c < mCols)
        SetCellType(r * mCols + c, type);
}

inline void IsoMap::SetCellType(unsigned int index, unsigned int type)
{
    if(index < mMap.size() && type < mTiles.size())
        mMap[index] = type;
}

inline int IsoMap::GetCellType(unsigned int r, unsigned int c) const
{
    if(r < mRows && c < mCols)
        return GetCellType(r * mCols + c);
    else
        return -1;
}

inline int IsoMap::GetCellType(unsigned int index) const
{
    if(index < mMap.size())
        return mMap[index];
    else
        return -1;
}

inline int IsoMap::GetTileWidth() const { return mTileW; }
inline int IsoMap::GetTileHeight() const { return mTileH; }

inline int IsoMap::GetWidth() const { return mTileW * mCols; }
inline int IsoMap::GetHeight() const { return mTileH * mRows; }

inline void IsoMap::SetOrigin(int x, int y)
{
    mX0 = x;
    mY0 = y;

    // rendering x is shifted of -w/2 because image origin is TL corner
    mRenderX0 = x - mTileH;

    UpdateTilePositions();
}

} // namespace game

