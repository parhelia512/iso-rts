#pragma once

#include "GameObjects/GameObjectTypes.h"

#include <sgl/sgui/Widget.h>

namespace sgl
{
    namespace graphic { class Image; }

    namespace sgui
    {
        class AbstractButton;
        class Label;
        class Slider;
    }
}

namespace game
{

class ObjectsDataRegistry;
class Player;

class DialogNewMiniUnitsSquad : public sgl::sgui::Widget
{
public:
    DialogNewMiniUnitsSquad(Player * player, const ObjectsDataRegistry * dataReg);

    void AddFunctionOnClose(const std::function<void()> & f);

private:
    void CreatePanelConfig();

    void UpdateCosts();

    void HandlePositionChanged() override;

    void SetPositions();

private:
    sgl::graphic::Image * mBg = nullptr;

    sgl::sgui::AbstractButton * mBtnClose = nullptr;
    sgl::sgui::Slider * mSliderElements = nullptr;
    sgl::sgui::Slider * mSliderSquads = nullptr;
    sgl::sgui::Label * mLabelCostEnergy = nullptr;
    sgl::sgui::Label * mLabelCostMaterial = nullptr;
    sgl::sgui::Label * mLabelCostDiamonds = nullptr;
    sgl::sgui::Label * mLabelCostBlobs= nullptr;

    Player * mPlayer = nullptr;

    const ObjectsDataRegistry * mDataReg = nullptr;

    GameObjectTypeId mTypeToBuild;
};

} // namespace game
