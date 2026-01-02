#pragma once

#include <sgl/sgui/Widget.h>

namespace sgl
{
    namespace graphic
    {
        class Image;
        class Text;
    }
}

namespace game
{

class WarningMessage : public sgl::sgui::Widget
{
public:
    WarningMessage(const char * text, float time);

private:
    void HandlePositionChanged() override;

    void UpdatePositions();

    void OnUpdate(float delta) override;

private:
    sgl::graphic::Image * mIcon = nullptr;
    sgl::graphic::Text * mText = nullptr;

    float mTimer = 0.f;
};

} // namespace game
