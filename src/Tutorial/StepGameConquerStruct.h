#pragma once

#include "Tutorial/TutorialInfoStep.h"

namespace game
{

class FocusArea;
class GameObject;
class IsoMap;
class PanelClickFilter;
class PanelInfoTutorial;

class StepGameConquerStruct : public TutorialInfoStep
{
public:
    StepGameConquerStruct(const GameObject * energyGen, const IsoMap * isoMap);
    ~StepGameConquerStruct();

    void Update(float delta) override;

private:
    FocusArea * mFocusArea = nullptr;

    const GameObject * mEnergyGen = nullptr;
};

} // namespace game
