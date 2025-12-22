#pragma once

#include "Tutorial/Tutorial.h"

namespace game
{

class Screen;
class ScreenGame;

class TutorialGameIntro : public Tutorial
{
public:
    TutorialGameIntro(Screen * screen);
    ~TutorialGameIntro();

private:
    ScreenGame * mScreen = nullptr;
};

} // namespace game
