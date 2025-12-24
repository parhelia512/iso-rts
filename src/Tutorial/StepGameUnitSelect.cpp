#include "Tutorial/StepGameUnitSelect.h"

#include "IsoObject.h"
#include "Player.h"
#include "GameObjects/Unit.h"
#include "Tutorial/TutorialConstants.h"
#include "Widgets/Tutorial/FocusArea.h"
#include "Widgets/Tutorial/PanelClickFilter.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

namespace game
{

StepGameUnitSelect::StepGameUnitSelect(const Player * p)
    : TutorialInfoStep(500, 200)
    , mFocusArea(new FocusArea)
{
    // FOCUS
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(1300, 350);

    info->AddInfoEntry("Okay, let's do it!", TutorialConstants::colorText, 4.f, true, false);
    info->AddInfoEntry("Select your unit with the LEFT MOUSE BUTTON.",
                       TutorialConstants::colorTextAction, 0.f, false, false, [this, p]
                       {
                           // FOCUS
                           mUnit = p->GetUnit(0);
                           auto isoObj = mUnit->GetIsoObject();
                           const int objX = isoObj->GetX();
                           const int objY = isoObj->GetY();
                           const int objW = isoObj->GetWidth();
                           const int objH = isoObj->GetHeight();

                           mFocusArea->SetWorldArea(objX, objY, objW, objH);
                           mFocusArea->SetCornersColor(TutorialConstants::colorFocusAction);
                           mFocusArea->SetBlinking(true);
                           mFocusArea->SetVisible(true);

                           // CLICK FILTER
                           GetClickFilter()->SetWorldClickableArea(objX, objY, objW, objH);
                       });
}

StepGameUnitSelect::~StepGameUnitSelect()
{
    delete mFocusArea;
}
void StepGameUnitSelect::Update(float)
{
    if(mUnit != nullptr && mUnit->IsSelected())
            SetDone();
}

} // namespace game
