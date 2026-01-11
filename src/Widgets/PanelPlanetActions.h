#pragma once

#include <sgl/sgui/Widget.h>
#include <sgl/utilities/StringsChangeListener.h>

#include <functional>

namespace sgl
{
    namespace graphic
    {
        class Image;
        class Text;
    }

    namespace sgui
    {
        class AbstractButton;
        class Label;
    }
}

namespace game
{

class ButtonPlanetMap;

enum TerritoryStatus : unsigned int;

class PanelPlanetActions : public sgl::sgui::Widget,
                           public sgl::utilities::StringsChangeListener
{
public:
    enum Button : unsigned int
    {
        EXPLORE,
        CONQUER,
        SEND_AI,

        NUM_BUTTONS
    };

public:
    PanelPlanetActions();

    void AddOnButtonClickFunction(Button btn, const std::function<void()> & f);

    void UpdateButtons(TerritoryStatus status, bool isPlayerOccupier);

    sgl::sgui::AbstractButton * GetButton(Button btn) const;

private:
    void HandlePositionChanged() override;

    void HandleStateEnabled() override;
    void HandleStateDisabled() override;

    void UpdatePositions();

    void OnStringsChanged() override;

private:
    sgl::graphic::Image * mBg = nullptr;

    sgl::sgui::Label * mTitle = nullptr;

    ButtonPlanetMap * mButtons[NUM_BUTTONS];
};

} // namespace game
