#include "Tutorial/StepGameSetSelectionDefaultAction.h"

#include "Player.h"
#include "GameObjects/GameObject.h"

namespace game
{

StepGameSetSelectionDefaultAction::StepGameSetSelectionDefaultAction(const Player * p,
                                                                     GameObjectActionType action)
    : mPlayer(p)
    , mAction(action)
{
}

void StepGameSetSelectionDefaultAction::OnStart()
{
    TutorialStep::OnStart();

    auto obj = mPlayer->GetSelectedObject();

    if(obj != nullptr)
        obj->SetDefaultAction(mAction);

    SetDone();
}

} // namespace game
