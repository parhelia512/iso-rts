#pragma once

#include <sgl/sgui/ButtonsGroup.h>
#include <sgl/utilities/StringsChangeListener.h>

namespace game
{

class PanelShotType : public sgl::sgui::ButtonsGroup,
                      public sgl::utilities::StringsChangeListener
{
public:
    PanelShotType();
    ~PanelShotType();

private:
    void OnStringsChanged() override;
};

} // namespace game
