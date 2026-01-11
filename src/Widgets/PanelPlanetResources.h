#pragma once

#include <sgl/sgui/Widget.h>
#include <sgl/utilities/StringsChangeListener.h>

#include <vector>

namespace sgl
{
    namespace graphic { class Image; }
    namespace sgui { class Label; }
}

namespace game
{

class PanelPlanetResources : public sgl::sgui::Widget,
                             public sgl::utilities::StringsChangeListener
{
public:
    PanelPlanetResources();

    void SetResourceValue(unsigned int res, unsigned int value);

private:
    void HandlePositionChanged() override;

    void HandleStateEnabled() override;
    void HandleStateDisabled() override;

    void UpdatePositions();

    void OnStringsChanged() override;

private:
    std::vector<sgl::graphic::Image *> mIcons;
    std::vector<sgl::graphic::Image *> mBars;
    std::vector<int> mBarsValue;

    sgl::graphic::Image * mBg = nullptr;

    sgl::sgui::Label * mTitle = nullptr;
};

} // namespace game
