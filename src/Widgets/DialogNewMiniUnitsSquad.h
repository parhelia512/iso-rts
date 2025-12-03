#pragma once

#include <sgl/sgui/Widget.h>

#include <functional>

namespace sgl
{
    namespace graphic
    {
        class Image;
        class Text;
    }
    namespace sgui { class AbstractButton; }
}

namespace game
{

class DialogNewMiniUnitsSquad : public sgl::sgui::Widget
{
public:
    DialogNewMiniUnitsSquad();

    void AddFunctionOnClose(const std::function<void()> & f);

protected:
    void HandlePositionChanged() override;

private:
    void SetPositions();

private:
    sgl::graphic::Image * mBg = nullptr;
    sgl::graphic::Text * mTitle = nullptr;

    sgl::sgui::AbstractButton * mBtnClose = nullptr;
};

} // namespace game
