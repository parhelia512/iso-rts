#include "Tutorial/StepGameConquerCells.h"

#include "IsoMap.h"
#include "Player.h"
#include "GameObjects/Unit.h"
#include "Tutorial/TutorialConstants.h"
#include "Widgets/Tutorial/FocusArea.h"
#include "Widgets/Tutorial/PanelClickFilter.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

namespace
{
const int destR = 62;
const int destC = 13;
}

namespace game
{

StepGameConquerCells::StepGameConquerCells(const Player * p, const IsoMap * isoMap)
    : TutorialInfoStep(600, 350)
    , mFocusArea(new FocusArea)
{
    // FOCUS
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(1250, 350);

    info->AddInfoEntry("Moving your mouse around will design a path for your unit to conquer.",
                       TutorialConstants::colorText, 8.f, true, false);
    info->AddInfoEntry("You can set anchor points clicking the RIGHT MOUSE BUTTON and finalize "
                       "the path with a DOUBLE RIGHT CLICK.", TutorialConstants::colorText, 14.f,
                       true, false);
    info->AddInfoEntry("Now move your mouse inside this cell and double click the RIGHT MOUSE BUTTON "
                       "to start the conquest.", TutorialConstants::colorTextAction,
                       0.f, false, false, [this, p, isoMap]
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

                           mUnit = p->GetUnit(0);
                       });
}

StepGameConquerCells::~StepGameConquerCells()
{
    delete mFocusArea;
}

void StepGameConquerCells::Update(float)
{
    if(mUnit != nullptr)
    {
        if(mUnit->GetRow0() == destR && mUnit->GetCol0() == destC &&
           mUnit->GetCurrentAction() == IDLE)
            SetDone();
    }
}

} // namespace game
