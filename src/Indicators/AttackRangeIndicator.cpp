#include "Indicators/AttackRangeIndicator.h"

#include "GameData.h"

#include <sgl/graphic/TextureManager.h>

namespace game
{

AttackRangeIndicator::AttackRangeIndicator()
    : IsoObject(1, 1)
{
    using namespace sgl::graphic;

    // upate object body
    const unsigned int indSprite = IND_ATTACK_RANGE;

    auto tm = TextureManager::Instance();
    Texture * tex = tm->GetSprite(SpriteFileMapIndicators, indSprite);

    SetTexture(tex);
}

void AttackRangeIndicator::SetDistance(unsigned int d, unsigned int range)
{
    const unsigned int maxAlpha = 255;
    const unsigned int step = maxAlpha / range;
    const unsigned int alpha =  maxAlpha - ((d - 1) * step);

    SetAlpha(alpha);
}

} // namespace game
