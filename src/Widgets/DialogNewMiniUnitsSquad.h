#pragma once

#include <sgl/sgui/Widget.h>

#include <functional>

namespace sgl
{
    namespace graphic { class Image; }
    namespace sgui { class AbstractButton; }
}

namespace game
{

class DialogNewMiniUnitsSquad : public sgl::sgui::Widget
{
public:
    DialogNewMiniUnitsSquad();

    void AddFunctionOnClose(const std::function<void()> & f);

private:
    void CreatePanelConfig();

    void OnNumElementsChanged(int num);
    void OnNumSquadsChanged(int num);

    void HandlePositionChanged() override;

    void SetPositions();

private:
    sgl::graphic::Image * mBg = nullptr;

    sgl::sgui::AbstractButton * mBtnClose = nullptr;
};

} // namespace game
