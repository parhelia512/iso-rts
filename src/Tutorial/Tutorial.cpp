#include "Tutorial/Tutorial.h"

#include "Game.h"
#include "GameConstants.h"
#include "Tutorial/TutorialStep.h"

namespace game
{

Tutorial::Tutorial(TutorialId tutId, Game *game)
    : mGame(game)
    , mId(tutId)
{
}

Tutorial::~Tutorial()
{
    delete mCurrStep;

    for(const TutorialStep * s : mSteps)
        delete s;
}

void Tutorial::Start()
{
    // already started
    if(mStepsAtStart > 0)
        return ;

    mGame->SetTutorialState(mId, TS_IN_PROGRESS);

    OnStart();

    mStepsAtStart = mSteps.size();

    StartNextStep();
}

void Tutorial::SetPause(bool paused)
{
    mPaused = paused;

    if(mCurrStep != nullptr)
        mCurrStep->SetPause(paused);
}

void Tutorial::OnStart() { }
void Tutorial::OnEnd() { }

void Tutorial::Update(float delta)
{
    if(nullptr == mCurrStep || mPaused)
        return ;

    mCurrStep->Update(delta);

    if(mCurrStep->IsDone())
    {
        FinalizeStep();
        StartNextStep();
    }

    if(AreAllStepsDone())
    {
        mDone = true;

        mGame->SetTutorialState(mId, TS_DONE);

        OnEnd();
    }
}

void Tutorial::FinalizeStep()
{
    mCurrStep->OnEnd();

    delete mCurrStep;
    mCurrStep = nullptr;

    ++mStepsDone;
}

void Tutorial::StartNextStep()
{
    if(mSteps.empty())
        return ;

    mCurrStep = mSteps.front();
    mSteps.pop_front();

    mCurrStep->OnStart();
}

} // namespace game
