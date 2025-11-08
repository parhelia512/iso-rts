#pragma once

#include "Tutorial/TutorialInfoStep.h"

namespace game
{

class FocusArea;
class IsoMap;
class Player;
class Unit;

class StepGameConquerCells : public TutorialInfoStep
{
public:
    StepGameConquerCells(const Player * p, const IsoMap * isoMap);
    ~StepGameConquerCells();

    void Update(float delta) override;

private:
    FocusArea * mFocusArea = nullptr;

    Unit * mUnit = nullptr;
};

} // namespace game
