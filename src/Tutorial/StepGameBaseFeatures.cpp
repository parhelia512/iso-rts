#include "Tutorial/StepGameBaseFeatures.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/PanelObjectActions.h"
#include "Widgets/PanelSelectedObject.h"
#include "Widgets/Tutorial/FocusArea.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

namespace game
{

StepGameBaseFeatures::StepGameBaseFeatures(const PanelSelectedObject * panelObj,
                                           PanelObjectActions * panelActions)
    : TutorialInfoStep(660, 250)
    , mFocusArea(new FocusArea)
{
    // FOCUS
    const int padding = 10;
    const int fX = panelObj->GetX();
    const int fY = panelObj->GetY();
    const int fW = panelObj->GetWidth() + padding;
    const int fH = panelObj->GetHeight() + padding;

    mFocusArea->SetScreenArea(fX, fY, fW, fH);
    mFocusArea->SetCornersColor(TutorialConstants::colorFocusElement);
    mFocusArea->SetVisible(false);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(150, 400);

    info->AddInfoEntry("Well done commander, you selected your base!",
                       TutorialConstants::colorText, 5.f, true, true);
    info->AddInfoEntry("When you select something this panel will appear in the top-left corner showing "
                       "several stats and giving you access to the full info panel for that object.",
                       TutorialConstants::colorText, 13.f, true, false, [this]
                       {
                           mFocusArea->SetBlinking(true);
                           mFocusArea->SetVisible(true);
                       });
    info->AddInfoEntry("At the bottom of the screen you will see all the actions of the object you selected.",
                       TutorialConstants::colorText, 9.f, true, false, [this, panelActions, padding]
                       {
                           const int fX = panelActions->GetX() - padding;
                           const int fY = panelActions->GetY() - padding;
                           const int fW = panelActions->GetWidth() + (2 * padding);
                           const int fH = panelActions->GetHeight() + (2 * padding);

                           mFocusArea->SetBlinking(true);
                           mFocusArea->SetScreenArea(fX, fY, fW, fH);
                       });

    info->SetFunctionOnFinished([this]
    {
        SetDone();
    });
}

StepGameBaseFeatures::~StepGameBaseFeatures()
{
    delete mFocusArea;
}

} // namespace game
