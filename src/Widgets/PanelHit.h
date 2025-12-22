#pragma once

#include <sgl/sgui/Widget.h>

namespace sgl
{
    namespace graphic { class Image; }

    namespace sgui
    {
        class Image;
        class Label;
    }
}

namespace game
{

class GameObject;

class PanelHit : public sgl::sgui::Widget
{
public:
    PanelHit();

    void ShowAttackerData(const GameObject * attacker, const GameObject *target);

private:
    void HandlePositionChanged() override;

    void UpdatePositions();

private:
    sgl::graphic::Image * mBg = nullptr;

    sgl::sgui::Label * mLabelHit = nullptr;
    sgl::sgui::Label * mLabelFatal = nullptr;
    sgl::sgui::Label * mLabelCost = nullptr;
    sgl::sgui::Image * mIconCost = nullptr;
};

} // namespace sgl
