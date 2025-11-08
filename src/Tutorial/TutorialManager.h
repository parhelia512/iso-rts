#pragma once

#include <deque>

namespace game
{

class TutorialStep;

class TutorialManager
{
public:
    ~TutorialManager();

    void AddStep(TutorialStep * step);

    void Start();

    void SetPause(bool paused);
    bool IsPaused() const;

    void Update(float delta);

    unsigned int GetNumStepsAtStart() const;
    unsigned int GetNumStepsTodo() const;
    unsigned int GetNumStepsDone() const;
    bool AreAllStepsDone() const;

private:
    void FinalizeStep();
    void StartNextStep();

private:
    std::deque<TutorialStep *> mSteps;

    TutorialStep * mCurrStep = nullptr;

    unsigned int mStepsAtStart = 0;
    unsigned int mStepsDone = 0;

    bool mPaused = false;
};

inline void TutorialManager::AddStep(TutorialStep * step) { mSteps.push_back(step); }

inline bool TutorialManager::IsPaused() const { return mPaused; }

inline unsigned int TutorialManager::GetNumStepsAtStart() const { return mStepsAtStart; }
inline unsigned int TutorialManager::GetNumStepsTodo() const { return mSteps.size(); }
inline unsigned int TutorialManager::GetNumStepsDone() const { return mStepsDone; }
inline bool TutorialManager::AreAllStepsDone() const { return mStepsDone == mStepsAtStart; }

} // namespace game
