#include "Tutorial/StepGameBaseBuildUnit.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/DialogNewElement.h"
#include "Widgets/GameHUD.h"
#include "Widgets/Tutorial/FocusArea.h"
#include "Widgets/Tutorial/PanelClickFilter.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

#include <sgl/sgui/AbstractButton.h>
#include <sgl/sgui/Stage.h>

namespace game
{

StepGameBaseBuildUnit::StepGameBaseBuildUnit(GameHUD * HUD)
    : TutorialInfoStep(480, 250)
    , mFocusArea(new FocusArea)
    , mHUD(HUD)
{
    // FOCUS
    mFocusArea->SetCornersColor(TutorialConstants::colorFocusAction);
    mFocusArea->SetBlinking(true);
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(40, 810);

    info->AddInfoEntry("You can choose what unit you want to build using this dialog.",
                       TutorialConstants::colorText, 7.f, true, false);
    info->AddInfoEntry("You can only build worker units for now, so let's do that!",
                       TutorialConstants::colorText, 7.f, true, false);
    info->AddInfoEntry("Click the button BUILD to create one.",
                       TutorialConstants::colorTextAction, 0.f, false, false, [this, HUD]
                       {
                           auto dialog = HUD->GetDialogNewElement();
                           auto btn = dialog->GetButtonBuild();

                           mButtonActId = btn->AddOnClickFunction([this]
                                                                  {
                                                                      SetDone();
                                                                  });

                           // FOCUS
                           const int padding = 10;
                           const int fX = dialog->GetX() + btn->GetX() - padding;
                           const int fY = dialog->GetY() + btn->GetY() - padding;
                           const int fW = btn->GetWidth() + (padding * 2);
                           const int fH = btn->GetHeight() + (padding * 2);

                           mFocusArea->SetScreenArea(fX, fY, fW, fH);
                           mFocusArea->SetVisible(true);

                           // CLICK FILTER
                           GetClickFilter()->SetScreenClickableArea(fX, fY, fW, fH);
                       });
}

StepGameBaseBuildUnit::~StepGameBaseBuildUnit()
{
    delete mFocusArea;
}

void StepGameBaseBuildUnit::OnStart()
{
    TutorialInfoStep::OnStart();

    // move elements to front
    auto stage = sgl::sgui::Stage::Instance();
    stage->MoveChildToFront(mFocusArea);
    stage->MoveChildToFront(GetClickFilter());
    stage->MoveChildToFront(GetPanelInfo());
}

void StepGameBaseBuildUnit::OnEnd()
{
    auto dialog = mHUD->GetDialogNewElement();

    if(nullptr == dialog)
        return ;

    auto btn = dialog->GetButtonBuild();
    btn->RemoveClickFunction(mButtonActId);
}

} // namespace game
