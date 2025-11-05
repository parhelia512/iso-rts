#include "Tutorial/Tutorial.h"

#include "Game.h"
#include "GameConstants.h"
#include "Tutorial/TutorialManager.h"

namespace game
{

Tutorial::Tutorial(TutorialId tutId, Game *game)
    : mTutMan(new TutorialManager)
    , mGame(game)
    , mId(tutId)
{
}

Tutorial::~Tutorial()
{
    delete mTutMan;
    mTutMan = nullptr;
}

void Tutorial::AddStep(TutorialStep * step)
{
    mTutMan->AddStep(step);
}

void Tutorial::Start()
{
    mGame->SetTutorialState(mId, TS_IN_PROGRESS);

    OnStart();

    mTutMan->Start();
}

void Tutorial::OnStart() { }
void Tutorial::OnEnd() { }

void Tutorial::Update(float delta)
{
    mTutMan->Update(delta);

    if(mTutMan->AreAllStepsDone())
    {
        mDone = true;

        mGame->SetTutorialState(mId, TS_DONE);

        OnEnd();
    }
}

} // namespace game
