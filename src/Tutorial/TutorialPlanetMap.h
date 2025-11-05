#pragma once

#include "Tutorial/Tutorial.h"

namespace game
{

class ScreenPlanetMap;

class TutorialPlanetMap : public Tutorial
{
public:
    TutorialPlanetMap(ScreenPlanetMap * screen);

private:
    ScreenPlanetMap * mScreen = nullptr;
};

} // namespace game
