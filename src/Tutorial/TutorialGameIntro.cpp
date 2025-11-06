#include "Tutorial/TutorialGameIntro.h"

#include "Game.h"
#include "GameConstants.h"
#include "GameMap.h"
#include "Player.h"
#include "Screens/ScreenGame.h"
#include "Tutorial/StepDelay.h"
#include "Tutorial/StepGameBase.h"
#include "Tutorial/StepGameBaseBuildUnit.h"
#include "Tutorial/StepGameBaseBuildUnitIcon.h"
#include "Tutorial/StepGameBaseFeatures.h"
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
#include "Tutorial/StepGameStructConnected.h"
#include "Tutorial/StepGameStructDisconnected.h"
#include "Tutorial/StepGameTurnEnergy.h"
#include "Tutorial/StepGameUnit.h"
#include "Tutorial/StepGameUnitConquerCellsIcon.h"
#include "Tutorial/StepGameUnitSelect.h"
#include "Tutorial/StepGameWaitTurn.h"
#include "Widgets/GameHUD.h"

namespace game
{

TutorialGameIntro::TutorialGameIntro(ScreenGame * screen)
    : Tutorial(TUTORIAL_MISSION_INTRO, screen->GetGame())
{
    // TODO these will be replaced by dynamic values soon
    constexpr float TIME_NEW_UNIT = 2.f;

    const Game * game = screen->GetGame();
    const Player * local = game->GetLocalPlayer();

    auto panelActions = screen->mHUD->GetPanelObjectActions();
    auto panelObj = screen->mHUD->GetPanelSelectedObject();
    auto panelTurn = screen->mHUD->GetPanelTurnControl();

    AddStep(new StepGameDisableCamera(screen->mCamController));

    AddStep(new StepDelay(1.f));
    AddStep(new StepGameIntro);
    AddStep(new StepDelay(0.3f));
    AddStep(new StepGameBase(local->GetBase()));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepGameBaseFeatures(panelObj, panelActions));
    AddStep(new StepGameMissionGoalsIcon(panelActions));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepGameMissionGoalsDialog(screen->mHUD));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepGameBaseBuildUnitIcon(panelActions));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepGameBaseBuildUnit(screen->mHUD));
    // TODO replace constant with time from Base when implemented
    AddStep(new StepDelay(TIME_NEW_UNIT));
    AddStep(new StepGameUnit(local));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepGameMoveUnit(local, screen->mIsoMap));
    AddStep(new StepDelay(3.f));
    // TODO update based on tutorial map
    const int genR = 56;
    const int genC = 13;
    const GameMapCell gmc = screen->mGameMap->GetCell(genR, genC);
    AddStep(new StepGameMoveCamera(200, -100));
    AddStep(new StepGameConquerStruct(gmc.objTop, screen->mIsoMap));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepGameTurnEnergy(screen->mHUD));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepGameEndTurn(panelTurn));
    AddStep(new StepGameWaitTurn(screen));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepGameEnergyRegeneration);
    AddStep(new StepGameStructDisconnected);
    AddStep(new StepGameUnitSelect(local));
    AddStep(new StepGameUnitConquerCellsIcon(panelActions));
    AddStep(new StepGameConquerCells(local, screen->mIsoMap));
    AddStep(new StepDelay(0.5f));
    AddStep(new StepGameStructConnected);

    AddStep(new StepGameEnableCamera(screen->mCamController));

    AddStep(new StepGameMapNavigation);
}

} // namespace game
