#pragma once

#include "Tutorial/TutorialInfoStep.h"

namespace game
{

class FocusArea;
class PanelObjectActions;

class StepGameUnitConquerCellsIcon : public TutorialInfoStep
{
public:
    StepGameUnitConquerCellsIcon(PanelObjectActions * panel);
    ~StepGameUnitConquerCellsIcon();

private:
    FocusArea * mFocusArea = nullptr;
    PanelObjectActions * mPanelActions = nullptr;

    unsigned int mClickId = 0;
};

} // namespace game
