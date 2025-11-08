#include "Tutorial/StepGameEndTurn.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/PanelTurnControl.h"
#include "Widgets/Tutorial/FocusArea.h"
#include "Widgets/Tutorial/PanelClickFilter.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

#include <sgl/sgui/AbstractButton.h>
#include <sgl/sgui/ButtonsGroup.h>

namespace game
{

StepGameEndTurn::StepGameEndTurn(const PanelTurnControl * panel)
    : TutorialInfoStep(550, 200)
    , mFocusArea(new FocusArea)
{

    // FOCUS
    mFocusArea->SetCornersColor(colorTutorialFocusElement);
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(1300, 650);

    info->AddInfoEntry("You can restore your energy by ending a turn and waiting for your "
                       "opponents to finish theirs.", colorTutorialText, 9.f, true, false);

    info->AddInfoEntry("Click this button to END THIS TURN, then wait your enemy's moves.",
                       colorTutorialTextAction, 0.f, false, false, [this, panel]
                       {
                           // FOCUS
                           auto btn = panel->GetButtonEndTurn();
                           const int padding = 10;
                           const int fX = panel->GetX() + btn->GetX() - padding;
                           const int fY = panel->GetY() + btn->GetY() - padding;
                           const int fW = btn->GetWidth() + (padding * 2);
                           const int fH = btn->GetHeight() + (padding * 2);

                           mFocusArea->SetCornersColor(colorTutorialFocusAction);
                           mFocusArea->SetBlinking(true);
                           mFocusArea->SetScreenArea(fX, fY, fW, fH);
                           mFocusArea->SetVisible(true);

                           // CLICK FILTER
                           GetClickFilter()->SetScreenClickableArea(fX, fY, fW, fH);
                       });

    auto btn = panel->GetButtonEndTurn();

    btn->AddOnClickFunction([this]
    {
        SetDone();
    });
}

StepGameEndTurn::~StepGameEndTurn()
{
    delete mFocusArea;
}

} // namespace game
