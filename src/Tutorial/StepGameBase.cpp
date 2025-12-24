#include "Tutorial/StepGameBase.h"

#include "IsoObject.h"
#include "GameObjects/Base.h"
#include "Tutorial/TutorialConstants.h"
#include "Widgets/Tutorial/FocusArea.h"
#include "Widgets/Tutorial/PanelClickFilter.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

namespace game
{

StepGameBase::StepGameBase(const Base * b)
    : TutorialInfoStep(500, 250)
    , mFocusArea(new FocusArea)
    , mBase(b)
{
    // FOCUS
    auto isoObj = mBase->GetIsoObject();
    const int objX = isoObj->GetX();
    const int objY = isoObj->GetY();
    const int objW = isoObj->GetWidth();
    const int objH = isoObj->GetHeight();

    mFocusArea->SetWorldArea(objX, objY, objW, objH);
    mFocusArea->SetCornersColor(TutorialConstants::colorFocusElement);
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(1150, 400);

    info->AddInfoEntry("This is your base.", TutorialConstants::colorText, 4.f, true, false);
    info->AddInfoEntry("You must protect it at all costs because if "
                       "destroyed you are defeated.", TutorialConstants::colorText, 7.f, true, false);
    info->AddInfoEntry("Select it with the LEFT MOUSE BUTTON", TutorialConstants::colorTextAction, 0.f, false, false);

    info->SetFunctionOnFinished([this, objX, objY, objW, objH]
    {
        mFocusArea->SetCornersColor(TutorialConstants::colorFocusAction);
        mFocusArea->SetBlinking(true);

        GetClickFilter()->SetWorldClickableArea(objX, objY, objW, objH);

        mCheckBaseSelected = true;
    });
}

StepGameBase::~StepGameBase()
{
    delete mFocusArea;
}

void StepGameBase::OnStart()
{
    TutorialInfoStep::OnStart();

    // FOCUS
    mFocusArea->SetVisible(true);
}

void StepGameBase::Update(float)
{
    if(mCheckBaseSelected)
    {
        if(mBase->IsSelected())
            SetDone();
    }
}

} // namespace game
