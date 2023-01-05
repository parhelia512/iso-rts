#pragma once

#include "Cell2D.h"
#include "Screen.h"
#include "GameObjects/GameObjectAction.h"

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace sgl
{
    namespace ai { class Pathfinder; }
    namespace graphic
    {
        class ParticlesManager;
        class ParticlesUpdater;
    }
    namespace sgui
    {
        class ButtonsGroup;
        class Widget;
    }
}

namespace game
{

class AttackRangeIndicator;
class ButtonMinimap;
class CameraMapController;
class CellProgressBar;
class ConquestIndicator;
class DialogExit;
class DialogNewElement;
class GameMap;
class GameObject;
class IsoLayer;
class IsoMap;
class MiniMap;
class MoveIndicator;
class PanelObjectActions;
class PanelResources;
class Player;
class PlayerAI;
class StructureIndicator;
class Unit;
class WallIndicator;

enum GameObjectType : unsigned int;
enum PlayerFaction : unsigned int;
enum StructureType : unsigned int;
enum UnitType : unsigned int;

enum ParticlesUpdaterId : unsigned int
{
    PU_DAMAGE,
    PU_SINGLE_LASER
};

class ScreenGame : public Screen
{
public:
    ScreenGame(Game * game);
    ~ScreenGame();

    void Update(float delta) override;
    void Render() override;

    void OnKeyDown(sgl::core::KeyboardEvent & event) override;
    void OnKeyUp(sgl::core::KeyboardEvent & event) override;
    void OnMouseButtonUp(sgl::core::MouseButtonEvent & event) override;
    void OnMouseMotion(sgl::core::MouseMotionEvent & event) override;

    void GameOver();
    void GameWon();

    void CancelProgressBar(const Cell2D & cell);
    void CreateProgressBar(const Cell2D & cell, float time, Player * player,
                           const std::function<void()> & onCompleted);

    void SetObjectActionCompleted(GameObject * obj);

    sgl::graphic::ParticlesUpdater * GetParticleUpdater(ParticlesUpdaterId updaterId);

    void ClearSelection(Player * player);
    void SelectObject(GameObject * obj, Player * player);

    void CenterCameraOverCell(int row, int col);
    void CenterCameraOverObject(GameObject * obj);

    MiniMap * GetMiniMap() const;

private:
    void OnApplicationQuit(sgl::core::ApplicationEvent & event) override;

    void InitParticlesSystem();

    void CreateIsoMap();
    void CreateLayers();

    void CreateUI();
    void CreateDialogExit();
    void HidePanelObjActions();
    void ClearNewElemDialog();

    CellProgressBar * CreateProgressBar(const Cell2D & cell, float time, PlayerFaction playerFaction);
    void UpdateProgressBars(float delta);

    void UpdateAI(float delta);
    void ExecuteAIAction(PlayerAI * ai);

    int CellToIndex(const Cell2D & cell) const;

    bool SetupNewUnit(UnitType type, GameObject * gen, Player * player, const std::function<void()> & OnDone = []{});
    bool SetupStructureConquest(Unit * unit, const Cell2D & start, const Cell2D & end, Player * player,
                                const std::function<void()> & OnDone = []{});
    bool SetupStructureBuilding(Unit * unit, const Cell2D & cellTarget, Player * player,
                                const std::function<void()> & OnDone = []{});
    bool SetupUnitUpgrade(GameObject * obj, Player * player, const std::function<void()> & OnDone = []{});
    bool SetupUnitMove(Unit * unit, const Cell2D & start, const Cell2D & end,
                       const std::function<void()> & OnDone = []{});
    bool SetupConnectCells(Unit * unit, const std::function<void()> & OnDone = []{});

    void HandleUnitOnMouseMove(Unit * unit, const Cell2D & cell);
    void HandleUnitMoveOnMouseMove(Unit * unit, const Cell2D & currCell);
    void HandleUnitConquestOnMouseMove(Unit * unit, const Cell2D & currCell);
    void HandleUnitBuildWallOnMouseMove(Unit * unit, const Cell2D & currCell);
    void HandleUnitBuildStructureOnMouseMove(Unit * unit, const Cell2D & currCell);

    void HandleUnitMoveOnMouseUp(Unit * unit, const Cell2D & clickCell);
    void HandleUnitBuildStructureOnMouseUp(Unit * unit, const Cell2D & clickCell);

    void HandleSelectionClick(sgl::core::MouseButtonEvent & event);
    void HandleActionClick(sgl::core::MouseButtonEvent & event);

    void ShowAttackIndicators(const GameObject * obj, int range);
    void ClearCellOverlays();

    void CenterCameraOverPlayerBase();

private:
    std::vector<Player *> mAiPlayers;

    std::unordered_map<int, CellProgressBar *> mProgressBars;
    std::vector<int> mProgressBarsToDelete;

    std::vector<ConquestIndicator *> mConquestIndicators;
    std::unordered_map<StructureType, StructureIndicator *> mStructIndicators;
    std::vector<WallIndicator *> mWallIndicators;
    std::vector<AttackRangeIndicator *> mAttIndicators;
    StructureIndicator * mTempStructIndicator = nullptr;

    std::vector<unsigned int> mConquestPath;
    std::vector<unsigned int> mWallPath;

    std::vector<GameObjectAction> mActiveObjActions;

    CameraMapController * mCamController = nullptr;

    sgl::graphic::ParticlesManager * mPartMan = nullptr;

    // -- UI --
    std::vector<sgl::sgui::Widget *> mWidgetsToDelete;
    PanelResources * mPanelResBar = nullptr;
    PanelObjectActions * mPanelObjActions = nullptr;
    DialogExit * mDialogExit = nullptr;
    DialogNewElement * mDialogNewElement = nullptr;
    sgl::sgui::ButtonsGroup  * mGroupQuickUnitSel = nullptr;
    ButtonMinimap * mButtonMinimap = nullptr;
    MiniMap * mMiniMap = nullptr;

    GameMap * mGameMap = nullptr;
    IsoMap * mIsoMap = nullptr;

    sgl::ai::Pathfinder * mPathfinder = nullptr;

    MoveIndicator * mMoveInd = nullptr;

    struct Cell2D mPrevCell;

    float mTimerEnergy;
    float mTimerAI;

    unsigned int mCurrPlayerAI = 0;

    bool mPaused = false;
};

inline MiniMap * ScreenGame::GetMiniMap() const { return mMiniMap; }

} // namespace game
