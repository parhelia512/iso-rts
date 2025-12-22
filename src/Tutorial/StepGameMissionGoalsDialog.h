#pragma once

#include "Tutorial/TutorialInfoStep.h"


namespace game
{

class FocusArea;
class GameHUD;

class StepGameMissionGoalsDialog : public TutorialInfoStep
{
public:
    StepGameMissionGoalsDialog(GameHUD * HUD);
    ~StepGameMissionGoalsDialog();

    void OnStart() override;

private:
    FocusArea * mFocusArea = nullptr;

    GameHUD * mHUD = nullptr;
};

} // namespace game
