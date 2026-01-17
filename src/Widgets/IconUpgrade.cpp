#include "IconUpgrade.h"

#include "GameData.h"

#include <sgl/graphic/Camera.h>
#include <sgl/graphic/TextureManager.h>

namespace game
{

IconUpgrade::IconUpgrade()
{
    using namespace sgl;

    // IconUpgrade is part of the game scene
    SetCamera(graphic::Camera::GetDefaultCamera());

    // ICON
    const unsigned int colorIcon = 0xcffcfcff;

    auto tm = graphic::TextureManager::Instance();
    auto tex = tm->GetSprite(SpriteFileParticles, ID_PART_ICON_UPGRADE);
    SetTexture(tex);
    SetColor(colorIcon);
}

} // namespace game
