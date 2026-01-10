#pragma once

#include <sgl/sgui/Widget.h>
#include <sgl/utilities/StringsChangeListener.h>

#include <functional>

namespace game
{

class ButtonObjectActionOption;

class PanelSelfDestruction : public sgl::sgui::Widget,
                             public sgl::utilities::StringsChangeListener
{
public:
    PanelSelfDestruction();
    ~PanelSelfDestruction();

    void AddFunctionOnDestroy(const std::function<void()> & f);
    void AddFunctionOnBlowup(const std::function<void()> & f);

private:
    void OnStringsChanged() override;

private:
    ButtonObjectActionOption * mBtnDestroy = nullptr;
    ButtonObjectActionOption * mBtnBlowup = nullptr;
};

} // namespace game
