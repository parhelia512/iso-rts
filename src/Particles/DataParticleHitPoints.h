#pragma once

#include <sgl/graphic/ParticleData.h>

namespace game
{

struct DataParticleHitPoints : public sgl::graphic::ParticleData
{
    DataParticleHitPoints(int v, float x, float y, float sp, float ds, bool f)
        : sgl::graphic::ParticleData(x, y, sp)
        , value(v)
        , decaySpeed(ds)
        , fatal(f)
    {
    }

    int value = 0;
    float decaySpeed = 1.f;
    bool fatal = false;
};

} // namespace game
