
#pragma once

#include <sgl/core/event/ApplicationEventListener.h>
#include <sgl/core/event/KeyboardEventListener.h>
#include <sgl/core/event/MouseEventListener.h>

namespace game
{

class Game;
class SharedScreenListener;

class Screen : public sgl::core::ApplicationEventListener, public sgl::core::KeyboardEventListener,
               public sgl::core::MouseEventListener
{
public:
    Screen(Game * game);
    ~Screen();

    Game * GetGame() const;

    virtual void Update(float delta) = 0;

    virtual void Render() = 0;

private:
    Game * mGame = nullptr;

    SharedScreenListener * mSharedListener = nullptr;
};

inline Game * Screen::GetGame() const { return mGame; }

} // namespace game
