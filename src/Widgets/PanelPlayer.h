#pragma once

#include <sgui/Widget.h>

#include <functional>
#include <string>

namespace lib
{
    namespace sgui { class Label; }
}

namespace game
{

class ButtonPanelPlayer;
class ButtonsPanel;
class Player;

struct GameMapCell;

class PanelPlayer : public lib::sgui::Widget
{
public:
    PanelPlayer(Player * player, lib::sgui::Widget * parent = nullptr);

    void SetPanelCellVisible(bool val);
    void SetPanelUnitsVisible(bool val);

    void UpdateCells(int cells);
    void UpdateCoins(int coins);
    void UpdateUnits(int units);

    void ClearSelectedCell();
    void SetSelectedCell(const GameMapCell & cell);

    void UpdateButtonCellFortify(int fortLevel);
    void UpdateButtonCellUpgrade(int cellLevel);
    void UpdateButtonNewUnit(int num, int level);
    void UpdateButtonUnitUpgrade(int num, int level);

    void SetFunctionCellFortify(const std::function<void()> & f);
    void SetFunctionCellUpgrade(const std::function<void()> & f);
    void SetFunctionNewUnit(const std::function<void()> & f);

    void SetFunctionUnitsMove(const std::function<void()> & f);
    void SetFunctionUnitsUpgrade(const std::function<void()> & f);

    int GetNumUnitsToMove() const;
    void ClearNumUnitsToMove();

private:
    std::string MakeStrCells(int cells);
    std::string MakeStrCoins(int coins);
    std::string MakeStrUnits(int units);

    void CreatePanelCell();

    void CreatePanelUnits();

private:
    ButtonsPanel * mPanelCell = nullptr;
    ButtonsPanel * mPanelUnits = nullptr;

    lib::sgui::Label * mLabelCells = nullptr;
    lib::sgui::Label * mLabelCoins = nullptr;
    lib::sgui::Label * mLabelUnits = nullptr;

    ButtonPanelPlayer * mButtonCellFortify = nullptr;
    ButtonPanelPlayer * mButtonCellUpgrade = nullptr;
    ButtonPanelPlayer * mButtonNewUnit = nullptr;

    ButtonPanelPlayer * mButtonUnitsMove = nullptr;
    ButtonPanelPlayer * mButtonUnitsUpgrade = nullptr;

    int mNumUnitsToMove = 0;
};

inline int PanelPlayer::GetNumUnitsToMove() const { return mNumUnitsToMove; }
inline void PanelPlayer::ClearNumUnitsToMove() { mNumUnitsToMove = 0; }

} // namespace game
