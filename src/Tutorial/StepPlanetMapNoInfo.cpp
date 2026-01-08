#include "Tutorial/StepPlanetMapNoInfo.h"

#include "Tutorial/TutorialConstants.h"
#include "Widgets/PanelPlanetInfo.h"
#include "Widgets/PanelPlanetResources.h"
#include "Widgets/Tutorial/FocusArea.h"
#include "Widgets/Tutorial/PanelInfoTutorial.h"

namespace game
{

StepPlanetMapNoInfo::StepPlanetMapNoInfo(const PanelPlanetInfo * panelInfo,
                                         const PanelPlanetResources * panelResources)
    : TutorialInfoStep(TutorialConstants::infoPlanetMapW, TutorialConstants::infoPlanetMapH)
    , mFocusInfo(new FocusArea)
    , mFocusResources(new FocusArea)
{
    // FOCUS
    const int padding = 10;

    const int fX1 = panelInfo->GetX() + padding;
    const int fY1 = panelInfo->GetY() + padding;
    const int fW1 = panelInfo->GetWidth() - (padding * 2);
    const int fH1 = panelInfo->GetHeight() - (padding * 2);

    mFocusInfo->SetScreenArea(fX1, fY1, fW1, fH1);
    mFocusInfo->SetCornersColor(TutorialConstants::colorFocusElement);
    mFocusInfo->SetVisible(false);
    mFocusInfo->SetBlinking(true);

    const int fX2 = panelResources->GetX() + padding;
    const int fY2 = panelResources->GetY() + padding;
    const int fW2 = panelResources->GetWidth() - (padding * 2);
    const int fH2 = panelResources->GetHeight() - (padding * 2);

    mFocusResources->SetScreenArea(fX2, fY2, fW2, fH2);
    mFocusResources->SetCornersColor(TutorialConstants::colorFocusElement);
    mFocusResources->SetVisible(false);
    mFocusResources->SetBlinking(true);

    // INFO
    auto info = GetPanelInfo();

    info->SetPosition(TutorialConstants::infoPlanetMapX, TutorialConstants::infoPlanetMapY);

    info->AddInfoEntry("The RESOURCES and INFO panels of this territory do not show any "
                       "data yet.", TutorialConstants::colorText, 8.f, true, true);
    info->AddInfoEntry("That's because this territory is still unexplored.",
                       TutorialConstants::colorText, 6.f, true, true, [this]
                       {
                           mFocusInfo->SetVisible(false);
                           mFocusResources->SetVisible(false);
                       });

    info->SetFunctionOnFinished([this]
    {
        SetDone();
    });
}

StepPlanetMapNoInfo::~StepPlanetMapNoInfo()
{
    delete mFocusInfo;
    delete mFocusResources;
}

void StepPlanetMapNoInfo::OnStart()
{
    TutorialInfoStep::OnStart();

    // FOCUS
    mFocusInfo->SetVisible(true);
    mFocusResources->SetVisible(true);
}

} // namespace game
