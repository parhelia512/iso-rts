#include "Tutorial/StepGameTurnEnergy.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/GameHUD.h"
#include "Widgets/PanelSelectedObject.h"
#include "Widgets/PanelTurnControl.h"
#include "Widgets/Tutorial/FocusArea.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

#include <sgl/sgui/AbstractButton.h>
#include <sgl/sgui/ButtonsGroup.h>

namespace game
{

StepGameTurnEnergy::StepGameTurnEnergy(const GameHUD * HUD)
    : TutorialInfoStep(650, 350)
    , mFocusArea(new FocusArea)
{
    // FOCUS
    mFocusArea->SetCornersColor(TutorialConstants::colorFocusElement);
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(1250, 550);

    info->AddInfoEntry("Now this energy generator is under your control.",
                       TutorialConstants::colorText, 9.f, true, true);
    info->AddInfoEntry("Always remember that your faction has a limited amount of energy to spend "
                       "each turn.", TutorialConstants::colorText, 10.f, true, false);
    info->AddInfoEntry("This big bar down below shows your remaining faction energy.",
                       TutorialConstants::colorText, 8.f, true, false, [this, HUD]
                       {
                           // FOCUS
                           const auto panel = HUD->GetPanelTurnControl();
                           const int padding = 10;
                           const int fX = panel->GetX() - padding;
                           const int fY = panel->GetY() - padding;
                           const int fW = panel->GetWidth() + (padding * 2);
                           const int fH = panel->GetHeight() + (padding * 2);

                           mFocusArea->SetScreenArea(fX, fY, fW, fH);
                           mFocusArea->SetVisible(true);
                           mFocusArea->SetBlinking(true);
                       });
    info->AddInfoEntry("You also need to consider the energy of your units or structures, "
                       "which you can find in the object panel.",
                       TutorialConstants::colorText, 10.f, true, false, [this, HUD]
                       {
                           // FOCUS
                           const auto panel = HUD->GetPanelSelectedObject();
                           const int padding = 10;
                           const int fX = panel->GetX();
                           const int fY = panel->GetY();
                           const int fW = panel->GetWidth() + padding;
                           const int fH = panel->GetHeight() + padding;

                           mFocusArea->SetScreenArea(fX, fY, fW, fH);
                           mFocusArea->SetVisible(true);
                           mFocusArea->SetBlinking(true);
                       });
    info->AddInfoEntry("Basic stats of your units are also available in their quick selection buttons",
                       TutorialConstants::colorText, 8.f, true, false,
                       [this, HUD]
                       {
                           // FOCUS
                           const auto group = HUD->GetQuickUnitButtonsGroup();
                           const auto btn = group->GetButton(0);
                           const int padding = 10;
                           const int fX = group->GetX() + btn->GetX() - padding;
                           const int fY = group->GetY() + btn->GetY() - padding;
                           const int fW = btn->GetWidth() + (2 * padding);
                           const int fH = btn->GetHeight() + padding;

                           mFocusArea->SetScreenArea(fX, fY, fW, fH);
                           mFocusArea->SetVisible(true);
                           mFocusArea->SetBlinking(true);
                       });

    info->SetFunctionOnFinished([this]
                                {
                                    SetDone();
                                });
}

StepGameTurnEnergy::~StepGameTurnEnergy()
{
    delete mFocusArea;
}

} // namespace game
