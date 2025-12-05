#pragma once

#include <sgl/sgui/ImageButton.h>

namespace game
{

// ===== BUTTON LEFT ARROW =====
class ButtonDialogArrowLeft : public sgl::sgui::ImageButton
{
public:
    ButtonDialogArrowLeft(sgl::sgui::Widget * parent);

private:
    void HandleButtonDown() override;
    void HandleMouseOver() override;
};

// ===== BUTTON RIGHT ARROW =====
class ButtonDialogArrowRight : public sgl::sgui::ImageButton
{
public:
    ButtonDialogArrowRight(sgl::sgui::Widget * parent);

private:
    void HandleButtonDown() override;
    void HandleMouseOver() override;
};

} // namespace game
