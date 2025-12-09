#pragma once

#include "Widgets/GameButton.h"

namespace sgl
{
    namespace graphic { class Text; }
}

namespace game
{

class ButtonObjectActionOption : public GameButton
{
public:
    ButtonObjectActionOption(const char * text, const char * shortcut,
                             int shortcutKey, sgl::sgui::Widget * parent);

    void SetTooltipText(const char * text, int timeShowing);

private:
    void HandleButtonDown() override;
    void HandleMouseOver() override;

    void HandlePositionChanged() override;
    void SetPositions();

    void OnStateChanged(sgl::sgui::AbstractButton::VisualState state) override;

private:
    sgl::graphic::Text * mShortcut = nullptr;
};

} // namespace game
