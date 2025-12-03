#pragma once

#include <sgl/sgui/ImageButton.h>

namespace game
{

// ===== BUTTON CLOSE DIALOG =====
class ButtonDialogClose : public sgl::sgui::ImageButton
{
public:
    ButtonDialogClose(sgl::sgui::Widget * parent);

private:
    void HandleButtonDown() override;
    void HandleMouseOver() override;
};

} // namespace game
