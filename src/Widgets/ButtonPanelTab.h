#pragma once

#include <sgl/sgui/AbstractButton.h>


namespace sgl
{
    namespace sgui
    {
        class Image;
        class Label;
    }
}

namespace game
{

class ButtonPanelTab : public sgl::sgui::AbstractButton
{
public:
    ButtonPanelTab(const char * text, sgl::sgui::Widget * parent);

    void SetLabel(const char * text);

private:
    void HandleMouseOver() override;

    void HandleButtonDown() override;

    void OnStateChanged(sgl::sgui::AbstractButton::VisualState state) override;

    void UpdateGraphics(sgl::sgui::AbstractButton::VisualState state);

    void UpdatePositions();

private:
    sgl::sgui::Label * mLabel = nullptr;

    sgl::sgui::Image * mBar = nullptr;
};

} // namespace game
