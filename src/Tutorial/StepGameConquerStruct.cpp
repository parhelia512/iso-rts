#include "Tutorial/StepGameConquerStruct.h"

#include "GameConstants.h"
#include "IsoMap.h"
#include "IsoObject.h"
#include "GameObjects/GameObject.h"
#include "Tutorial/TutorialConstants.h"
#include "Widgets/Tutorial/FocusArea.h"
#include "Widgets/Tutorial/PanelClickFilter.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

#include <sgl/core/event/MouseEvent.h>

namespace game
{

StepGameConquerStruct::StepGameConquerStruct(const GameObject * energyGen, const IsoMap * isoMap)
    : TutorialInfoStep(500, 300)
    , mFocusArea(new FocusArea)
    , mEnergyGen(energyGen)
{

    // FOCUS
    auto isoObj = mEnergyGen->GetIsoObject();
    const int objX = isoObj->GetX();
    const int objY = isoObj->GetY();
    const int objW = isoObj->GetWidth();
    const int objH = isoObj->GetHeight();

    mFocusArea->SetWorldArea(objX, objY, objW, objH);
    mFocusArea->SetCornersColor(colorTutorialFocusElement);
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(1300, 200);

    info->AddInfoEntry("When your unit action is set to MOVE you can also conquer structures.",
                       colorTutorialText, 7.f, true, false);
    info->AddInfoEntry("For example we can conquer this ENERGY GENERATOR.", colorTutorialText, 7.f, true, false,
                       [this]
                       {
                           mFocusArea->SetVisible(true);
                       });
    info->AddInfoEntry("Click on the generator with the RIGHT MOUSE BUTTON to start the conquest.",
                       colorTutorialTextAction, 0.f, false, false, [this, objX, objY, objW, objH, energyGen, isoMap]
                       {
                           // FOCUS
                           mFocusArea->SetCornersColor(colorTutorialFocusAction);
                           mFocusArea->SetBlinking(true);

                           // CLICK FILTER
                           auto cf = GetClickFilter();
                           cf->SetWorldClickableArea(objX, objY, objW, objH);
                           cf->SetButtonToExclude(sgl::core::MouseEvent::BUTTON_LEFT);
                           cf->SetClickableCells(isoMap, energyGen->GetRow1(), energyGen->GetCol1(),
                                                 energyGen->GetRow0(), energyGen->GetCol0());
                       });
}

StepGameConquerStruct::~StepGameConquerStruct()
{
    delete mFocusArea;
}

void StepGameConquerStruct::Update(float)
{
    if(mEnergyGen->GetFaction() != NO_FACTION)
        SetDone();
}

} // namespace game
