#pragma once

#include "Tutorial/TutorialStep.h"

namespace game
{

class PanelClickFilter;
class PanelInfoTutorial;

class TutorialInfoStep : public TutorialStep
{
public:
    TutorialInfoStep(int infoW, int infoH);
    ~TutorialInfoStep();

    void OnStart() override;

protected:
    PanelClickFilter * GetClickFilter();
    PanelInfoTutorial * GetPanelInfo();

private:
    PanelClickFilter * mClickFilter = nullptr;
    PanelInfoTutorial * mInfo = nullptr;
};

inline PanelClickFilter * TutorialInfoStep::GetClickFilter() { return mClickFilter; }

inline PanelInfoTutorial * TutorialInfoStep::GetPanelInfo() { return mInfo; }

} // namespace game
