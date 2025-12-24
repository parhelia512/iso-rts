#pragma once

#include "Tutorial/TutorialStep.h"

namespace game
{

class ScreenGame;

class StepGameClearSelection : public TutorialStep
{
public:
    StepGameClearSelection(ScreenGame * screen);

    void OnStart() override;

private:
    ScreenGame * mScreen = nullptr;
};

} // namespace game
