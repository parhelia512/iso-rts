#include "TutorialManager.h"

#include "TutorialStep.h"

namespace game
{

TutorialManager::~TutorialManager()
{
    for(const TutorialStep * s : mSteps)
        delete s;
}

void TutorialManager::Start()
{
    // already started
    if(mStepsAtStart > 0)
        return ;

    mStepsAtStart = mSteps.size();

    StartNextStep();
}

void TutorialManager::SetPause(bool paused)
{
    mPaused = paused;

    if(mCurrStep != nullptr)
        mCurrStep->SetPause(paused);
}

void TutorialManager::Update(float delta)
{
    if(nullptr == mCurrStep || mPaused)
        return ;

    mCurrStep->Update(delta);

    if(mCurrStep->IsDone())
    {
        FinalizeStep();

        StartNextStep();
    }
}

void TutorialManager::FinalizeStep()
{
    mCurrStep->OnEnd();

    delete mCurrStep;
    mCurrStep = nullptr;

    ++mStepsDone;
}

void TutorialManager::StartNextStep()
{
    if(mSteps.empty())
        return ;

    mCurrStep = mSteps.front();
    mSteps.pop_front();

    mCurrStep->OnStart();
}

} // namespace game
