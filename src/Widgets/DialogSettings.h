#pragma once

#include <sgl/sgui/Widget.h>
#include <sgl/utilities/StringsChangeListener.h>

#include <functional>

namespace sgl
{
    namespace graphic { class Image; }
    namespace sgui
    {
        class AbstractButtonsGroup;
        class ComboBox;
        class ImageButton;
    }
}

namespace game
{

class Game;

class DialogSettings : public sgl::sgui::Widget, public sgl::utilities::StringsChangeListener
{
public:
    DialogSettings(Game * game);
    ~DialogSettings();

    void AddOnCloseClickedFunction(const std::function<void()> & f);

private:
    void HandlePositionChanged() override;

    void SetPositions();

    void CreatePanelGame(sgl::sgui::Widget * parent);
    void CreatePanelAudio(sgl::sgui::Widget * parent);
    void CreatePanelVideo(sgl::sgui::Widget * parent);
    void CreatePanelControls(sgl::sgui::Widget * parent);

    void UpdateCurrentResolution();

    void OnStringsChanged() override;

private:
    enum Panel : unsigned int
    {
        GAME,
        AUDIO,
        VIDEO,
        CONTROLS,

        NUM_PANELS
    };

private:
    Game * mGame = nullptr;

    sgl::sgui::AbstractButtonsGroup * mGroupButtons = nullptr;

    sgl::sgui::Widget * mPanels[NUM_PANELS];

    sgl::graphic::Image * mBg = nullptr;

    sgl::sgui::ImageButton * mButtonBack = nullptr;

    sgl::sgui::ComboBox * mComboRes = nullptr;
};

} // namespace game
