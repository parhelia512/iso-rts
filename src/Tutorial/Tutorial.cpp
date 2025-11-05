#include "Tutorial/Tutorial.h"

#include "Tutorial/TutorialManager.h"

namespace game
{

Tutorial::Tutorial()
    : mTutMan(new TutorialManager)
{
}

Tutorial::~Tutorial()
{
    delete mTutMan;
    mTutMan = nullptr;
}

void Tutorial::Start()
{
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

        OnEnd();
    }
}

} // namespace game
