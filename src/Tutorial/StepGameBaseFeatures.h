#pragma once

#include "Tutorial/TutorialInfoStep.h"

namespace game
{

class FocusArea;
class PanelObjectActions;
class PanelSelectedObject;

class StepGameBaseFeatures : public TutorialInfoStep
{
public:
    StepGameBaseFeatures(const PanelSelectedObject * panelObj, PanelObjectActions * panelActions);
    ~StepGameBaseFeatures();

private:
    FocusArea * mFocusArea = nullptr;
};

} // namespace game
