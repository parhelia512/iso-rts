#pragma once

#include "Screen.h"

#include <vector>

namespace sgl
{
    namespace graphic { class TexturedRenderable; }
}

namespace game
{

class CellProgressBar;

class ScreenTest : public Screen
{
public:
    ScreenTest(Game * game);
    ~ScreenTest();

    void Update(float delta) override;
    void Render() override;

    void OnMouseButtonUp(sgl::core::MouseButtonEvent & event) override;

private:
    void TestSGui();
    void TestSprite();
    void TestRotation();

private:
    std::vector<sgl::graphic::TexturedRenderable *> mRenderables;

    CellProgressBar * mPb0 = nullptr;
    CellProgressBar * mPb1 = nullptr;
    CellProgressBar * mPb2 = nullptr;
    float mTimerPb = 0.f;
};

} // namespace game
