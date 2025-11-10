#pragma once

#include "Tutorial/Tutorial.h"

namespace game
{

class ScreenGame;

class TutorialGameIntro : public Tutorial
{
public:
    TutorialGameIntro(ScreenGame * screen);
    ~TutorialGameIntro();

private:
    ScreenGame * mScreen = nullptr;
};

} // namespace game
