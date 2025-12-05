#pragma once

#include "Widgets/GameButton.h"

namespace sgl
{
    namespace graphic { class Text; }
}

namespace game
{

class ButtonDialogAction : public GameButton
{
public:
    ButtonDialogAction(const char * text, const char * shortcut,
                       int shortcutKey, sgl::sgui::Widget * parent);

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
