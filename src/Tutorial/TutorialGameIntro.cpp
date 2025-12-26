#include "Tutorial/TutorialGameIntro.h"

#include "CameraMapController.h"
#include "Game.h"
#include "GameConstants.h"
#include "GameMap.h"
#include "Player.h"
#include "GameObjects/Base.h"
#include "Screens/ScreenGame.h"
#include "Tutorial/StepDelay.h"
#include "Tutorial/StepGameBase.h"
#include "Tutorial/StepGameBaseBuildUnit.h"
#include "Tutorial/StepGameBaseBuildUnitIcon.h"
#include "Tutorial/StepGameBaseFeatures.h"
#include "Tutorial/StepGameClearSelection.h"
#include "Tutorial/StepGameConquerCells.h"
#include "Tutorial/StepGameConquerStruct.h"
#include "Tutorial/StepGameDisableCamera.h"
#include "Tutorial/StepGameEnableCamera.h"
#include "Tutorial/StepGameEndTurn.h"
#include "Tutorial/StepGameEnergyRegeneration.h"
#include "Tutorial/StepGameIntro.h"
#include "Tutorial/StepGameMapNavigation.h"
#include "Tutorial/StepGameMissionGoalsIcon.h"
#include "Tutorial/StepGameMissionGoalsDialog.h"
#include "Tutorial/StepGameMoveCamera.h"
#include "Tutorial/StepGameMoveUnit.h"
#include "Tutorial/StepGameSetSelectionActiveAction.h"
#include "Tutorial/StepGameSetSelectionDefaultAction.h"
#include "Tutorial/StepGameStructConnected.h"
#include "Tutorial/StepGameStructDisconnected.h"
#include "Tutorial/StepGameTurnEnergy.h"
#include "Tutorial/StepGameUnit.h"
#include "Tutorial/StepGameUnitConquerCellsIcon.h"
#include "Tutorial/StepGameWaitTurn.h"
#include "Widgets/GameHUD.h"

#include <cassert>

namespace game
{

TutorialGameIntro::TutorialGameIntro(Screen * screen)
    : Tutorial(TUTORIAL_MISSION_INTRO)
    , mScreen(dynamic_cast<ScreenGame *>(screen))
{
    assert(mScreen);

    const Player * local = mScreen->GetGame()->GetLocalPlayer();

    auto panelActions = mScreen->mHUD->GetPanelObjectActions();
    auto panelObj = mScreen->mHUD->GetPanelSelectedObject();
    auto panelTurn = mScreen->mHUD->GetPanelTurnControl();

    auto localBase = local->GetBase();

    AddStep(new StepGameDisableCamera(mScreen->mCamController));

    AddStep(new StepDelay(1.f));
    AddStep(new StepGameIntro);
    AddStep(new StepDelay(0.3f));
    AddStep(new StepGameBase(localBase));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepGameBaseFeatures(panelObj, panelActions));
    AddStep(new StepGameMissionGoalsIcon(panelActions));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepGameMissionGoalsDialog(mScreen->mHUD));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepGameBaseBuildUnitIcon(panelActions));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepGameBaseBuildUnit(mScreen->mHUD));
    AddStep(new StepDelay(localBase->GetTimeBuildUnit()));
    AddStep(new StepGameUnit(local));
    AddStep(new StepGameSetSelectionActiveAction(local, GameObjectActionType::IDLE));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepGameMoveUnit(local, mScreen->mIsoMap));
    AddStep(new StepGameSetSelectionActiveAction(local, GameObjectActionType::IDLE));
    // TODO update based on tutorial map
    const int genR = 56;
    const int genC = 13;
    const GameMapCell gmc = mScreen->mGameMap->GetCell(genR, genC);
    AddStep(new StepGameMoveCamera(200, -100));
    AddStep(new StepGameConquerStruct(local, gmc.objTop, mScreen->mIsoMap));
    AddStep(new StepGameSetSelectionDefaultAction(local, GameObjectActionType::IDLE));
    AddStep(new StepGameSetSelectionActiveAction(local, GameObjectActionType::IDLE));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepGameTurnEnergy(mScreen->mHUD));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepGameEndTurn(panelTurn));
    AddStep(new StepGameWaitTurn(mScreen));
    AddStep(new StepGameSetSelectionActiveAction(local, GameObjectActionType::IDLE));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepGameEnergyRegeneration);
    AddStep(new StepGameStructDisconnected);
    AddStep(new StepGameUnitConquerCellsIcon(panelActions));
    AddStep(new StepGameConquerCells(local, mScreen->mIsoMap));
    AddStep(new StepGameSetSelectionDefaultAction(local, GameObjectActionType::MOVE));
    AddStep(new StepGameClearSelection(mScreen));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepGameStructConnected);

    AddStep(new StepGameEnableCamera(mScreen->mCamController));

    AddStep(new StepGameMapNavigation);
}

TutorialGameIntro::~TutorialGameIntro()
{
    // re-enable camera in game in case tutorial is quit
    mScreen->mCamController->SetEnabled(true);
}

} // namespace game
