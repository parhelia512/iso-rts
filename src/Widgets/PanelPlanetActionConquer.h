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
        class TextArea;
    }
}

namespace game
{

class ButtonPlanetMap;
class SecondaryButtonPlanetMap;
class Player;

enum TerritoryStatus : unsigned int;

class PanelPlanetActionConquer : public sgl::sgui::Widget,
                                 public sgl::utilities::StringsChangeListener
{
public:
    PanelPlanetActionConquer();

    void AddOnButtonOkClickFunction(const std::function<void()> & f);
    void AddOnButtonCancelClickFunction(const std::function<void()> & f);

    sgl::sgui::AbstractButton * GetButtonOk() const;
    sgl::sgui::AbstractButton * GetButtonCancel() const;

private:
    void CreateContentStart();

    void HandlePositionChanged() override;

    void UpdatePositions();

    void OnStringsChanged() override;

private:
    sgl::graphic::Image * mBg = nullptr;

    sgl::sgui::Label * mTitle = nullptr;
    sgl::sgui::Widget * mContentStart = nullptr;
    sgl::sgui::TextArea * mDesc = nullptr;

    ButtonPlanetMap * mButtonOk = nullptr;
    SecondaryButtonPlanetMap * mButtonCancel = nullptr;
};

} // namespace game
