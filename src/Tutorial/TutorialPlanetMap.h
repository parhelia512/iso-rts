#pragma once

#include "Tutorial/Tutorial.h"

namespace game
{

class Screen;
class ScreenPlanetMap;

class TutorialPlanetMap : public Tutorial
{
public:
    TutorialPlanetMap(Screen * screen);

private:
    ScreenPlanetMap * mScreen = nullptr;
};

} // namespace game
