#pragma once

#include <sgl/sgui/Widget.h>
#include <sgl/utilities/StringsChangeListener.h>

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

class PanelHit : public sgl::sgui::Widget, public sgl::utilities::StringsChangeListener
{
public:
    PanelHit();

    void ShowAttackerData(const GameObject * attacker, const GameObject *target);

private:
    void HandlePositionChanged() override;

    void UpdatePositions();

    void OnStringsChanged() override;

private:
    sgl::graphic::Image * mBg = nullptr;

    sgl::sgui::Label * mHeaderHit = nullptr;
    sgl::sgui::Label * mLabelHit = nullptr;
    sgl::sgui::Label * mHeaderFatal = nullptr;
    sgl::sgui::Label * mLabelFatal = nullptr;
    sgl::sgui::Label * mHeaderCost = nullptr;
    sgl::sgui::Label * mLabelCost = nullptr;
    sgl::sgui::Image * mIconCost = nullptr;
};

} // namespace game
