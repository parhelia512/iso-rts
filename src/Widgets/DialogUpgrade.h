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
class ObjectsDataRegistry;

class DialogUpgrade : public sgl::sgui::Widget
{
public:
    DialogUpgrade(GameObject * obj, const ObjectsDataRegistry * odr);

    void SetFunctionOnClose(const std::function<void()> & f);

    void SetObject(GameObject * obj);

protected:
    void HandlePositionChanged() override;

private:
    void SetPositions();

private:
    sgl::graphic::Image * mBg = nullptr;
    ButtonDialogClose * mBtnClose = nullptr;

    sgl::sgui::Label * mLabelPoints = nullptr;

    GameObject * mObj = nullptr;

    int mPointsToAssign = 0;
};

class ValueUpgradeBar : public sgl::sgui::Widget
{
public:
    ValueUpgradeBar(int maxVal, sgl::sgui::Widget * parent);

    void SetValue(int numOn, int numNew);

private:
    std::vector<sgl::sgui::Image *> mImgs;
};

} // namespace game
