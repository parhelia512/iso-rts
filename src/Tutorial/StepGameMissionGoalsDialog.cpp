#include "Tutorial/StepGameMissionGoalsDialog.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/DialogMissionGoals.h"
#include "Widgets/GameHUD.h"
#include "Widgets/Tutorial/FocusArea.h"
#include "Widgets/Tutorial/PanelClickFilter.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

#include <sgl/sgui/AbstractButton.h>
#include <sgl/sgui/Stage.h>
#include <sgl/utilities/StringManager.h>

namespace game
{

StepGameMissionGoalsDialog::StepGameMissionGoalsDialog(GameHUD * HUD)
    : TutorialInfoStep(900, 140)
    , mFocusArea(new FocusArea)
    , mHUD(HUD)
{
    auto sm = sgl::utilities::StringManager::Instance();

    // FOCUS
    mFocusArea->SetCornersColor(TutorialConstants::colorFocusElement);
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(510, 60);

    info->AddInfoEntry(sm->GetCString("TUT_GAME_MISSION_GOALS_DIALOG_1"),
                       TutorialConstants::colorText, 13.f, true, true, [this]
                       {
                           mFocusArea->SetScreenArea(340, 290, 1240, 160);
                           mFocusArea->SetBlinking(true);
                           mFocusArea->SetVisible(true);
                       });

    info->AddInfoEntry(sm->GetCString("TUT_GAME_MISSION_GOALS_DIALOG_2"),
                       TutorialConstants::colorText, 9.f, true, true, [this]
                       {
                           mFocusArea->SetScreenArea(340, 460, 1240, 345);
                           mFocusArea->SetBlinking(true);
                           mFocusArea->SetVisible(true);
                       });

    info->AddInfoEntry(sm->GetCString("TUT_GAME_MISSION_GOALS_DIALOG_3"),
                       TutorialConstants::colorText, 12.f, true, true, [this]
                       {
                           mFocusArea->SetScreenArea(1300, 340, 280, 440);
                           mFocusArea->SetBlinking(true);
                           mFocusArea->SetVisible(true);
                       });

    info->AddInfoEntry(sm->GetCString("TUT_GAME_MISSION_GOALS_DIALOG_4"),
                       TutorialConstants::colorText, 12.f, true, true, [this]
                       {
                           const int padding = 10;
                           auto btn = mHUD->GetDialogMissionGoals()->GetButtonEnd();

                           const int x = btn->GetScreenX() - padding;
                           const int y = btn->GetScreenY() - padding;
                           const int w = btn->GetWidth() + (2 * padding);
                           const int h = btn->GetHeight() + (2 * padding);

                           mFocusArea->SetScreenArea(x, y, w, h);
                           mFocusArea->SetBlinking(true);
                           mFocusArea->SetVisible(true);
                       });

    info->AddInfoEntry(sm->GetCString("TUT_GAME_MISSION_GOALS_DIALOG_5"), TutorialConstants::colorText,
                       6.f, true, true, [this]
                        {
                            mFocusArea->SetVisible(false);
                        });

    info->AddInfoEntry(sm->GetCString("TUT_GAME_MISSION_GOALS_DIALOG_6"),
                       TutorialConstants::colorTextAction, 0.f, false, false, [this]
                       {
                           const int padding = 10;

                           auto dialog = mHUD->GetDialogMissionGoals();
                           auto btn = dialog->GetButtonClose();

                           // NOTE no need to remove the function later as the dialog is
                           // destroyed when the button is clicked
                           dialog->AddFunctionOnClose([this]
                                {
                                    SetDone();
                                });

                           const int x = btn->GetScreenX() - padding;
                           const int y = btn->GetScreenY() - padding;
                           const int w = btn->GetWidth() + (2 * padding);
                           const int h = btn->GetHeight() + (2 * padding);

                           GetClickFilter()->SetScreenClickableArea(x, y, w, h);

                           mFocusArea->SetScreenArea(x, y, w, h);
                           mFocusArea->SetCornersColor(TutorialConstants::colorFocusAction);
                           mFocusArea->SetBlinking(true);
                           mFocusArea->SetVisible(true);
                       });
}

StepGameMissionGoalsDialog::~StepGameMissionGoalsDialog()
{
    delete mFocusArea;
}

void StepGameMissionGoalsDialog::OnStart()
{
    TutorialInfoStep::OnStart();

    // move elements to front
    auto stage = sgl::sgui::Stage::Instance();
    stage->MoveChildToFront(mFocusArea);
    stage->MoveChildToFront(GetClickFilter());
    stage->MoveChildToFront(GetPanelInfo());
}

} // namespace game
