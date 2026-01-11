#pragma once

#include "GameButton.h"
#include <sgl/utilities/StringsChangeListener.h>

namespace game
{

class GameSimpleTooltip;

class ButtonPlanetMap : public GameButton
{
public:
    ButtonPlanetMap(sgl::sgui::Widget * parent);

    void SetTooltipText(const char * text);

private:
    void HandleMouseOver() override;
    void HandleButtonDown() override;

    void CreateTooltip(const char * text);

private:
    GameSimpleTooltip * mTooltip = nullptr;
};

class SecondaryButtonPlanetMap : public GameButton
{
public:
    SecondaryButtonPlanetMap(sgl::sgui::Widget * parent);

private:
    void HandleMouseOver() override;
    void HandleButtonDown() override;
};

class ButtonLeavePlanet : public GameButton, public sgl::utilities::StringsChangeListener
{
public:
    ButtonLeavePlanet(sgl::sgui::Widget * parent);

private:
    void OnStringsChanged() override;

private:
    void HandleMouseOver() override;
    void HandleButtonDown() override;
};

} // namespace game
