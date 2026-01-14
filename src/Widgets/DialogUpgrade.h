#pragma once

#include <sgl/sgui/Widget.h>

#include <functional>

namespace sgl
{
    namespace graphic { class Image; }
    namespace sgui
    {
        class AbstractButton;
        class Image;
        class Label;
    }
}

namespace game
{

class ButtonDialogClose;
class GameObject;

class DialogUpgrade : public sgl::sgui::Widget
{
public:
    DialogUpgrade(GameObject * obj);

    void SetFunctionOnClose(const std::function<void()> & f);

    void SetObject(GameObject * obj);

protected:
    void HandlePositionChanged() override;

private:
    void SetPositions();

private:
    sgl::graphic::Image * mBg = nullptr;
    ButtonDialogClose * mBtnClose = nullptr;
    sgl::sgui::Label * mTitle = nullptr;
    sgl::sgui::Image * mImg = nullptr;

    sgl::sgui::Widget * mStatRank = nullptr;
    sgl::sgui::Widget * mStatExperience = nullptr;
    sgl::sgui::Widget * mStatEnergy = nullptr;
    sgl::sgui::Widget * mStatHealth = nullptr;

    GameObject * mObj = nullptr;
};

} // namespace game
