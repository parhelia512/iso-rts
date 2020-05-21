#pragma once

#include <unordered_map>

namespace lib
{
namespace utilities
{

class State;

class StateManager
{
public:
    StateManager();
    ~StateManager();

    bool AddState(State * state);
    State * RemoveState(int stateId);
    void RemoveAndDestroyState(int stateId);
    bool RequestNextActiveState(int stateId);
    void UpdateActive();

    bool SetActiveState(int stateId);
    State * GetActiveState() const;

private:
    std::unordered_map<int, State *> mStates;

    State * mActive = nullptr;
    State * mNext = nullptr;
};

inline State * StateManager::GetActiveState() const { return mActive; }

} // namespace utilities
} // namespace lib
