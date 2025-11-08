#pragma once

#include "Tutorial/TutorialInfoStep.h"

namespace game
{

class FocusArea;
class PanelObjectActions;

class StepGameBaseBuildUnitIcon : public TutorialInfoStep
{
public:
    StepGameBaseBuildUnitIcon(PanelObjectActions * panel);
    ~StepGameBaseBuildUnitIcon();

private:
    FocusArea * mFocusArea = nullptr;
    PanelObjectActions * mPanelActions = nullptr;

    unsigned int mClickId = 0;
};

} // namespace game
