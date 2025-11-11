#include <sgl/sgui/Widget.h>

namespace sgl
{
    namespace graphic { class Image; }
}

namespace game
{

class ScreenOverlay : public sgl::sgui::Widget
{
public:
    ScreenOverlay();

    void HandleMouseButtonDown(sgl::core::MouseButtonEvent & event) override;
    void HandleMouseButtonUp(sgl::core::MouseButtonEvent & event) override;
    void HandleMouseMotion(sgl::core::MouseMotionEvent & event) override;

private:
    sgl::graphic::Image * mImg = nullptr;
};

} // namespace game
