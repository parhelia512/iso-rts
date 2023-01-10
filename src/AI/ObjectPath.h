#pragma once

#include <functional>
#include <vector>

namespace game
{

class GameMap;
class GameObject;
class IsoMap;
class ScreenGame;

class ObjectPath
{
public:
    enum PathState : unsigned int
    {
        READY,
        RUNNING,
        COMPLETED,
        FAILED,
        ABORTING,
        ABORTED,

        NUM_PATH_STATES
    };

public:
    ObjectPath(GameObject * obj, IsoMap * im, GameMap * gm, ScreenGame * sg);

    GameObject * GetObject() const;

    PathState GetState() const;

    float GetPathCost() const;

    void SetPathCells(const std::vector<unsigned int> & cells);

    void SetOnCompleted(const std::function<void()> & f);
    void SetOnFailed(const std::function<void()> & f);
    void SetOnAborted(const std::function<void()> & f);

    void Start();

    void Abort();
    void InstantAbort();

    void Update(float delta);

private:
    void InitNextMoveStep();

    void UpdatePathCost();

    void Fail();

private:
    std::vector<unsigned int> mCells;

    std::function<void()> mOnCompleted;
    std::function<void()> mOnFailed;
    std::function<void()> mOnAborted;

    GameObject * mObj = nullptr;

    IsoMap * mIsoMap = nullptr;
    GameMap * mGameMap = nullptr;

    ScreenGame * mScreen = nullptr;

    PathState mState = READY;

    unsigned int mNextCell = 0;

    float mObjX = 0.f;
    float mObjY = 0.f;

    float mVelX = 0.f;
    float mVelY = 0.f;

    float mTargetX = 0.f;
    float mTargetY = 0.f;

    float mCost = 0.f;
};

inline GameObject * ObjectPath::GetObject() const { return mObj; }

inline ObjectPath::PathState ObjectPath::GetState() const { return mState; }

inline float ObjectPath::GetPathCost() const { return mCost; }

inline void ObjectPath::SetPathCells(const std::vector<unsigned int> & cells)
{
    mCells = cells;
    UpdatePathCost();
}

inline void ObjectPath::SetOnCompleted(const std::function<void()> & f) { mOnCompleted = f; }
inline void ObjectPath::SetOnFailed(const std::function<void()> & f) { mOnFailed = f; }
inline void ObjectPath::SetOnAborted(const std::function<void()> & f) { mOnAborted = f; }

inline void ObjectPath::Abort()
{
    mState = ABORTING;
}

} // namespace game
