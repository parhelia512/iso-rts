#pragma once

#include "Tutorial/TutorialInfoStep.h"

namespace game
{

class FocusArea;
class PanelTurnControl;

class StepGameEndTurn : public TutorialInfoStep
{
public:
    StepGameEndTurn(const game::PanelTurnControl * panel);
    ~StepGameEndTurn();

private:
    FocusArea * mFocusArea = nullptr;
};

} // namespace game
