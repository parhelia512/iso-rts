#include "Tutorial/StepGameUnit.h"

#include "IsoObject.h"
#include "Player.h"
#include "GameObjects/Unit.h"
#include "Tutorial/TutorialConstants.h"
#include "Widgets/Tutorial/FocusArea.h"
#include "Widgets/Tutorial/PanelClickFilter.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

namespace game
{

StepGameUnit::StepGameUnit(const Player * p)
    : TutorialInfoStep(500, 200)
    , mFocusArea(new FocusArea)
{
    // FOCUS
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(1300, 450);

    info->AddInfoEntry("Well done commander, this is your first unit!", colorTutorialText, 5.f, true, false);
    info->AddInfoEntry("Now select it by clicking on its cell with the LEFT MOUSE BUTTON.",
                       colorTutorialTextAction, 0.f, false, false, [this, p]
                       {
                           // FOCUS
                           mUnit = p->GetUnit(0);
                           auto isoObj = mUnit->GetIsoObject();
                           const int objX = isoObj->GetX();
                           const int objY = isoObj->GetY();
                           const int objW = isoObj->GetWidth();
                           const int objH = isoObj->GetHeight();

                           mFocusArea->SetWorldArea(objX, objY, objW, objH);
                           mFocusArea->SetCornersColor(colorTutorialFocusAction);
                           mFocusArea->SetBlinking(true);
                           mFocusArea->SetVisible(true);

                           // CLICK FILTER
                           GetClickFilter()->SetWorldClickableArea(objX, objY, objW, objH);
                       });
}

StepGameUnit::~StepGameUnit()
{
    delete mFocusArea;
}

void StepGameUnit::Update(float)
{
    if(mUnit != nullptr && mUnit->IsSelected())
        SetDone();
}

} // namespace game
