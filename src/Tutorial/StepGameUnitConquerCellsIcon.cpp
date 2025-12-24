#include "Tutorial/StepGameUnitConquerCellsIcon.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/PanelObjectActions.h"
#include "Widgets/Tutorial/FocusArea.h"
#include "Widgets/Tutorial/PanelClickFilter.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

#include <sgl/sgui/AbstractButton.h>

namespace game
{

StepGameUnitConquerCellsIcon::StepGameUnitConquerCellsIcon(PanelObjectActions * panel)
    : TutorialInfoStep(450, 150)
    , mFocusArea(new FocusArea)
    , mPanelActions(panel)
{
    // FOCUS
    mFocusArea->SetCornersColor(TutorialConstants::colorFocusAction);
    mFocusArea->SetBlinking(true);
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(1100, 600);

    info->AddInfoEntry("Then click this button to set your unit's action to CELL CONQUEST.",
                       TutorialConstants::colorTextAction, 0.f, false, false, [this, panel]
                       {
                           // FOCUS
                           auto btn = panel->GetButton(PanelObjectActions::BTN_CONQUER_CELL);

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

    mClickId = panel->AddButtonFunction(PanelObjectActions::BTN_CONQUER_CELL, [this]
    {
        SetDone();
    });
}

StepGameUnitConquerCellsIcon::~StepGameUnitConquerCellsIcon()
{
    mPanelActions->RemoveButtonFunction(PanelObjectActions::BTN_CONQUER_CELL, mClickId);

    delete mFocusArea;
}

} // namespace game
