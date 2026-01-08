#include "Tutorial/StepGameConquerStruct.h"

#include "GameConstants.h"
#include "IsoMap.h"
#include "IsoObject.h"
#include "Player.h"
#include "GameObjects/Unit.h"
#include "Tutorial/TutorialConstants.h"
#include "Widgets/Tutorial/FocusArea.h"
#include "Widgets/Tutorial/PanelClickFilter.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

#include <sgl/core/event/MouseEvent.h>

namespace game
{

StepGameConquerStruct::StepGameConquerStruct(const Player * p, const GameObject * energyGen,
                                             const IsoMap * isoMap)
    : TutorialInfoStep(550, 300)
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
    mFocusArea->SetCornersColor(TutorialConstants::colorFocusElement);
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(1250, 200);

    info->AddInfoEntry("When your units move they can also conquer structures.",
                       TutorialConstants::colorText, 7.f, true, false);
    info->AddInfoEntry("For example we can conquer this ENERGY GENERATOR.", TutorialConstants::colorText, 7.f, true, false,
                       [this]
                       {
                           mFocusArea->SetVisible(true);
                       });
    info->AddInfoEntry("Click on this generator with the RIGHT MOUSE BUTTON to start the conquest.",
                       TutorialConstants::colorTextAction, 0.f, false, false,
                       [this, objX, objY, objW, objH, energyGen, isoMap, p]
                       {
                           // FOCUS
                           mFocusArea->SetCornersColor(TutorialConstants::colorFocusAction);
                           mFocusArea->SetBlinking(true);

                           // CLICK FILTER
                           auto cf = GetClickFilter();
                           cf->SetWorldClickableArea(objX, objY, objW, objH);
                           cf->SetButtonToExclude(sgl::core::MouseEvent::BUTTON_LEFT);
                           cf->SetClickableCells(isoMap, energyGen->GetRow1(), energyGen->GetCol1(),
                                                 energyGen->GetRow0(), energyGen->GetCol0());

                           // re-allow unit to move and conquer
                           auto unit = p->GetUnit(0);
                           unit->SetActiveAction(GameObjectActionType::MOVE);
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
