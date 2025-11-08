#include "TutorialStep.h"

namespace game
{

void TutorialStep::SetPause(bool paused)
{
    mPaused = paused;
}

void TutorialStep::OnStart() { }

void TutorialStep::OnEnd() { }

void TutorialStep::Update(float) { }

} // namespace game
