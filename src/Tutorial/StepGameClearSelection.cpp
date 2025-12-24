#include "Tutorial/StepGameClearSelection.h"

#include "Screens/ScreenGame.h"

namespace game
{

StepGameClearSelection::StepGameClearSelection(ScreenGame * screen)
    : mScreen(screen)
{
}

void StepGameClearSelection::OnStart()
{
    TutorialStep::OnStart();

    auto p = mScreen->GetActivePlayer();
    mScreen->ClearSelection(p);

    SetDone();
}

} // namespace game
