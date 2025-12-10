#include "Widgets/PanelSelfDestruction.h"

#include "Widgets/ButtonObjectActionOption.h"

#include <sgl/core/event/KeyboardEvent.h>
#include <sgl/graphic/Font.h>
#include <sgl/graphic/FontManager.h>
#include <sgl/graphic/TextureManager.h>

namespace game
{

// ===== DIALOG =====
PanelSelfDestruction::PanelSelfDestruction()
{
    using namespace sgl;

    SetResizePolicy(sgui::Widget::GROW_ONLY);

    auto fm = graphic::FontManager::Instance();
    auto tm = graphic::TextureManager::Instance();

    const int marginB = 10;

    // BUTTON DESTROY
    const int tooltipTime1 = 3000;
    auto btn = new ButtonObjectActionOption("DESTROY", "1", core::KeyboardEvent::KEY_1, this);
    btn->SetTooltipText("Quietly dismantle this object.", tooltipTime1);
    mBtnDestroy = btn;

    // BUTTON BLOW UP
    const int tooltipTime2 = 4000;
    btn = new ButtonObjectActionOption("BLOW UP", "2", core::KeyboardEvent::KEY_2, this);
    btn->SetTooltipText("Blow this object up damaging everything that surrounds it.", tooltipTime2);
    mBtnBlowup = btn;

    btn->SetY(mBtnDestroy->GetHeight() + marginB);
}

void PanelSelfDestruction::AddFunctionOnDestroy(const std::function<void()> & f)
{
    mBtnDestroy->AddOnClickFunction(f);
}

void PanelSelfDestruction::AddFunctionOnBlowup(const std::function<void()> & f)
{
    mBtnBlowup->AddOnClickFunction(f);
}

} // namespace game
