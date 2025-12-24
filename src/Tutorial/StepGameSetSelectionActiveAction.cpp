#include "Tutorial/StepGameSetSelectionActiveAction.h"

#include "Player.h"
#include "GameObjects/GameObject.h"

namespace game
{

StepGameSetSelectionActiveAction::StepGameSetSelectionActiveAction(const Player * p,
                                                                   GameObjectActionType action)
    : mPlayer(p)
    , mAction(action)
{
}

void StepGameSetSelectionActiveAction::OnStart()
{
    TutorialStep::OnStart();

    auto obj = mPlayer->GetSelectedObject();

    if(obj != nullptr)
        obj->SetActiveAction(mAction);

    SetDone();
}

} // namespace game
