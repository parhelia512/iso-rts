#include "Widgets/ScreenOverlay.h"

#include "Widgets/GameUIData.h"

#include <sgl/core/event/MouseButtonEvent.h>
#include <sgl/core/event/MouseMotionEvent.h>
#include <sgl/graphic/GraphicConstants.h>
#include <sgl/graphic/Image.h>
#include <sgl/graphic/Renderer.h>
#include <sgl/graphic/Texture.h>
#include <sgl/graphic/TextureManager.h>

namespace game
{

ScreenOverlay::ScreenOverlay()
{
    using namespace sgl;

    auto renderer = sgl::graphic::Renderer::Instance();
    const int rendW = renderer->GetWidth();
    const int rendH = renderer->GetHeight();

    SetSize(rendW, rendH);

    auto tm = graphic::TextureManager::Instance();
    auto tex = tm->GetSprite(SpriteFileGameUIExp, ID_SCREEN_OVERLAY_BG);
    tex->SetScaleMode(graphic::TSCALE_NEAREST);

    mImg = new graphic::Image(tex);
    mImg->SetWidth(rendW);
    mImg->SetHeight(rendH);

    RegisterRenderable(mImg);
}

void ScreenOverlay::HandleMouseButtonDown(sgl::core::MouseButtonEvent & event)
{
    event.SetConsumed();
}

void ScreenOverlay::HandleMouseButtonUp(sgl::core::MouseButtonEvent & event)
{
    event.SetConsumed();
}

void ScreenOverlay::HandleMouseMotion(sgl::core::MouseMotionEvent & event)
{
    event.SetConsumed();
}

} // namespace game
