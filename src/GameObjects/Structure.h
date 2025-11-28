#pragma once

#include "GameObject.h"

namespace game
{

class BlinkingIconEnergy;

class Structure : public GameObject
{
public:
    Structure(const ObjectData & data);

    void OnPositionChanged() override;

protected:
    void OnFactionChanged() override;
    void OnLinkedChanged() override;

private:
    void HideIconEnergy();
    void ShowIconEnergy();
    void PositionIconEnergy();

private:
    BlinkingIconEnergy * mIconEnergy = nullptr;
};


} // namespace game
