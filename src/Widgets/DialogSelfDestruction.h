#pragma once

#include <sgl/sgui/Widget.h>

#include <functional>

namespace sgl
{
    namespace sgui { class AbstractButton; }
}

namespace game
{

class DialogSelfDestruction : public sgl::sgui::Widget
{
public:
    DialogSelfDestruction();

    void AddFunctionOnDestroy(const std::function<void()> & f);
    void AddFunctionOnBlowup(const std::function<void()> & f);

private:
    sgl::sgui::AbstractButton * mBtnDestroy = nullptr;
    sgl::sgui::AbstractButton * mBtnBlowup = nullptr;
};

} // namespace game
