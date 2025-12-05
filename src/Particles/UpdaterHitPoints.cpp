#include "Particles/UpdaterHitPoints.h"

#include "Particles/DataParticleHitPoints.h"
#include "Particles/ParticleHitPoints.h"

namespace game
{

sgl::graphic::Particle * UpdaterHitPoints::CreateParticle(const sgl::graphic::ParticleData & initData)
{
    ParticleHitPoints * p = nullptr;

    if(mParticles.empty())
        p = new ParticleHitPoints;
    else
    {
        p = static_cast<ParticleHitPoints *>(mParticles.back());
        mParticles.pop_back();
    }

    // init data
    auto data = static_cast<const DataParticleHitPoints &>(initData);
    p->SetData(data);

    return p;
}

} // namespace game
