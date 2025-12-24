#pragma once

#include "Tutorial/TutorialStep.h"

namespace game
{

class Player;

enum GameObjectActionType : unsigned int;

class StepGameSetSelectionActiveAction : public TutorialStep
{
public:
    StepGameSetSelectionActiveAction(const Player * p, GameObjectActionType action);

    void OnStart() override;

private:
    const Player * mPlayer;

    GameObjectActionType mAction;
};

} // namespace game
