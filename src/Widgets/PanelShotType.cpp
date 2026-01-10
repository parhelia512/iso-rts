#include "Widgets/PanelShotType.h"

#include "Widgets/ButtonObjectActionOption.h"

#include <sgl/core/event/KeyboardEvent.h>
#include <sgl/media/AudioManager.h>
#include <sgl/media/AudioPlayer.h>

namespace game
{

// ===== DIALOG =====
PanelShotType::PanelShotType()
    : sgl::sgui::ButtonsGroup(sgl::sgui::ButtonsGroup::VERTICAL)
{
    using namespace sgl;

    // spacing between buttons
    const int spacing = 10;
    SetSpacing(spacing);

    // BUTTON QUICK SHOT
    const int tooltipTime1 = 3000;
    auto btn = new ButtonObjectActionOption("QUICK SHOT", "1", core::KeyboardEvent::KEY_1, this);
    btn->CreateTooltip("Low energy cost, but lower accuracy", tooltipTime1);

    AddButton(btn);

    // BUTTON AIMED SHOT
    const int tooltipTime2 = 4000;
    btn = new ButtonObjectActionOption("AIMED SHOT", "2", core::KeyboardEvent::KEY_2, this);
    btn->CreateTooltip("High energy cost, but high accuracy and higher probability of fatal shot",
                        tooltipTime2);

    AddButton(btn);

    // BUTTON BURST SHOT
    btn = new ButtonObjectActionOption("BURST", "3", core::KeyboardEvent::KEY_3, this);
    btn->CreateTooltip("Multiple shots, but low accuracy",
                        tooltipTime1);
    AddButton(btn);

    SetButtonChecked(0, true);

    // play sound
    auto ap = media::AudioManager::Instance()->GetPlayer();
    ap->PlaySound("UI/panel-open-01.ogg");
}

PanelShotType::~PanelShotType()
{
    // play sound
    auto ap = sgl::media::AudioManager::Instance()->GetPlayer();
    ap->PlaySound("UI/panel-close-01.ogg");
}

} // namespace game
