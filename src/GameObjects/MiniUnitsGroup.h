#pragma once

#include "GameObjects/GameObjectsGroup.h"

#include <vector>

namespace game
{

class GameObject;

class MiniUnitsGroup : public GameObjectsGroup
{
public:
    // PATH
    void ClearPath();
    const std::vector<unsigned int> & GetPath() const;
    void SetPath(const std::vector<unsigned int> && path);

    bool HasPathSet() const;

private:
    std::vector<unsigned int> mPath;
};

inline void MiniUnitsGroup::ClearPath() { mPath.clear(); }

inline const std::vector<unsigned int> & MiniUnitsGroup::GetPath() const
{
    return mPath;
}

inline void MiniUnitsGroup::SetPath(const std::vector<unsigned int> && path)
{
    mPath = path;
}

inline bool MiniUnitsGroup::HasPathSet() const { return !mPath.empty(); }

} // namespace game
