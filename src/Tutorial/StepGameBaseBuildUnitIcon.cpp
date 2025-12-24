#include "Tutorial/StepGameBaseBuildUnitIcon.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/PanelObjectActions.h"
#include "Widgets/Tutorial/FocusArea.h"
#include "Widgets/Tutorial/PanelClickFilter.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

#include <sgl/sgui/AbstractButton.h>

namespace game
{

StepGameBaseBuildUnitIcon::StepGameBaseBuildUnitIcon(PanelObjectActions * panel)
    : TutorialInfoStep(590, 200)
    , mFocusArea(new FocusArea)
    , mPanelActions(panel)
{
    // FOCUS
    mFocusArea->SetCornersColor(TutorialConstants::colorFocusAction);
    mFocusArea->SetBlinking(true);
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(300, 550);

    info->AddInfoEntry("You can also create worker units with your base.",
                       TutorialConstants::colorText, 5.f, true, false);
    info->AddInfoEntry("Let's create a new one now.",
                       TutorialConstants::colorText, 4.f, true, false);
    info->AddInfoEntry("Click this button to open the new units dialog.",
                       TutorialConstants::colorTextAction, 0.f, false, false, [this, panel]
                       {
                           // FOCUS
                           auto btn = panel->GetButton(PanelObjectActions::BTN_BUILD_UNIT_BASE);

                           const int padding = 10;
                           const int fX = panel->GetX() + btn->GetX() - padding;
                           const int fY = panel->GetY() + btn->GetY() - padding;
                           const int fW = btn->GetWidth() + (padding * 2);
                           const int fH = btn->GetHeight() + (padding * 2);

                           mFocusArea->SetScreenArea(fX, fY, fW, fH);
                           mFocusArea->SetVisible(true);

                           // CLICK FILTER
                           GetClickFilter()->SetScreenClickableArea(fX, fY, fW, fH);

                       });

    mClickId = panel->AddButtonFunction(PanelObjectActions::BTN_BUILD_UNIT_BASE, [this]
    {
        SetDone();
    });
}

StepGameBaseBuildUnitIcon::~StepGameBaseBuildUnitIcon()
{
    mPanelActions->RemoveButtonFunction(PanelObjectActions::BTN_BUILD_UNIT_BASE, mClickId);

    delete mFocusArea;
}

} // namespace game
