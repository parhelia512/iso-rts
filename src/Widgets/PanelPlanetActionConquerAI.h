#pragma once

#include <sgl/sgui/Widget.h>
#include <sgl/utilities/StringsChangeListener.h>

#include <functional>

namespace sgl
{
    namespace graphic { class Image; }

    namespace sgui
    {
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

class PanelPlanetActionConquerAI : public sgl::sgui::Widget,
                                   public sgl::utilities::StringsChangeListener
{
public:
    PanelPlanetActionConquerAI(Player * player, int money, int energy, int material, int diamonds);

    void ShowAction();
    void ShowResult(bool success);

    void AddOnButtonOkClickFunction(const std::function<void()> & f);
    void AddOnButtonCancelClickFunction(const std::function<void()> & f);

private:
    void CreateContentStart(int money, int energy, int material, int diamonds);
    void CreateContentFailure();
    void CreateContentSuccess();

    void HandlePositionChanged() override;

    void UpdatePositions();

    void OnStringsChanged() override;

private:
    sgl::graphic::Image * mBg = nullptr;
    sgl::sgui::Label * mTitle = nullptr;

    sgl::sgui::Widget * mContentStart = nullptr;
    sgl::sgui::Widget * mContentFailure = nullptr;
    sgl::sgui::Widget * mContentSuccess = nullptr;

    sgl::sgui::Label * mLabelMoney = nullptr;
    sgl::sgui::Label * mLabelEnergy = nullptr;
    sgl::sgui::Label * mLabelMaterial = nullptr;
    sgl::sgui::Label * mLabelDiamonds = nullptr;

    sgl::sgui::TextArea * mTextDesc = nullptr;
    sgl::sgui::TextArea * mTextResFail = nullptr;
    sgl::sgui::TextArea * mTextResSuccess = nullptr;

    ButtonPlanetMap * mButtonOk = nullptr;
    SecondaryButtonPlanetMap * mButtonCancel = nullptr;

    Player * mPlayer = nullptr;

    int mCostMoney = 0;
    int mCostenergy = 0;
    int mCostmaterial = 0;
    int mCostDiamonds = 0;
};

} // namespace game
