#include "Tutorial/StepGameMoveUnit.h"

#include "IsoMap.h"
#include "Player.h"
#include "GameObjects/Unit.h"
#include "Tutorial/TutorialConstants.h"
#include "Widgets/Tutorial/FocusArea.h"
#include "Widgets/Tutorial/PanelClickFilter.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

namespace
{
const int destR = 57;
const int destC = 13;
}

namespace game
{

StepGameMoveUnit::StepGameMoveUnit(const Player * p, const IsoMap * isoMap)
    : TutorialInfoStep(600, 275)
    , mFocusArea(new FocusArea)
{
    // FOCUS
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(450, 125);

    info->AddInfoEntry("The default action of your units is MOVE, so let's do that.",
                       TutorialConstants::colorText, 7.f, true, false);
    info->AddInfoEntry("Click inside this cell with the RIGHT MOUSE BUTTON to move next "
                       "to that spiky structure.",
                       TutorialConstants::colorTextAction, 0.f, false, false, [this, p, isoMap]
                       {
                           const sgl::core::Pointd2D pos = isoMap->GetCellPosition(destR, destC);

                           // FOCUS
                           const int marginW = 5;
                           const int marginH = 10;
                           const int objX = pos.x - marginW;
                           const int objY = pos.y - marginH;
                           const int objW = isoMap->GetTileWidth() + (2 * marginW);
                           const int objH = isoMap->GetTileHeight() + (2 * marginH);

                           mFocusArea->SetWorldArea(objX, objY, objW, objH);
                           mFocusArea->SetCornersColor(TutorialConstants::colorFocusAction);
                           mFocusArea->SetBlinking(true);
                           mFocusArea->SetVisible(true);

                           // CLICK FILTER
                           auto cf = GetClickFilter();
                           cf->SetWorldClickableArea(objX, objY, objW, objH);
                           cf->SetClickableCell(isoMap, destR, destC);

                           // re-allow unit to move
                           mUnit = p->GetUnit(0);
                           mUnit->SetActiveAction(GameObjectActionType::MOVE);
                       });
}

StepGameMoveUnit::~StepGameMoveUnit()
{
    delete mFocusArea;
}

void StepGameMoveUnit::Update(float)
{
    if(mUnit != nullptr)
    {
        if(mUnit->GetRow0() == destR && mUnit->GetCol0() == destC)
            SetDone();
    }
}

} // namespace game
