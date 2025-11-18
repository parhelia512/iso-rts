#pragma once

#include<functional>
#include <vector>

namespace game
{

class GameObject;

class GameObjectsGroup
{
public:
    // basic objects handling
    void AddObject(GameObject * o);
    void RemoveObject(GameObject * o);

    unsigned int GetNumObjects() const;
    bool IsEmpty() const;

    // actions on objects
    void DoForAll(const std::function<void(GameObject *)> & f) const;

    void SetSelected(bool selected) const;

private:
    std::vector<GameObject *> mObjects;
};

inline void GameObjectsGroup::AddObject(GameObject * o) { mObjects.emplace_back(o); }

inline unsigned int GameObjectsGroup::GetNumObjects() const { return mObjects.size(); }
inline bool GameObjectsGroup::IsEmpty() const { return mObjects.empty(); }

} // namespace game
