#pragma once

#include "Tutorial/TutorialInfoStep.h"

namespace sgl { namespace sgui { class AbstractButton; } }

namespace game
{

class FocusArea;
class PanelTurnControl;

class StepGameEndTurn : public TutorialInfoStep
{
public:
    StepGameEndTurn(const PanelTurnControl * panel);
    ~StepGameEndTurn();

private:
    FocusArea * mFocusArea = nullptr;

    sgl::sgui::AbstractButton * mButton = nullptr;
    unsigned int mFuncId = 0;
};

} // namespace game
