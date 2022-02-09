#pragma once

#include "Widgets/ShortcutButton.h"

namespace sgl
{
    namespace graphic
    {
        class Image;
        class Text;
    }
}

namespace game
{

class ObjectActionButton : public ShortcutButton
{
public:
    enum ActionIcon : unsigned int
    {
        UNITS,
        MOVE,
        ATTACK,
        CONQUER_CELL,
        BUILD_WALL,
        BUILD_STRUCT,
        UPGRADE,
        CANCEL,

        NUM_ACTION_ICONS
    };

public:
    ObjectActionButton(ActionIcon icon, const char * shortcut,
                       int shortcutKey, sgl::sgui::Widget * parent);

private:
    void OnStateChanged(sgl::sgui::PushButton::VisualState state) override;

    void HandlePositionChanged() override;

private:
    sgl::graphic::Image * mBody = nullptr;
    sgl::graphic::Image * mIcon = nullptr;
    sgl::graphic::Text * mShortcut = nullptr;
};

} // namespace game
