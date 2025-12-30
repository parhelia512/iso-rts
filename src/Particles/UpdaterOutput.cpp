#include "Particles/UpdaterOutput.h"

#include "Particles/DataParticleOutput.h"
#include "Particles/ParticleOutput.h"

namespace game
{

sgl::graphic::Particle * UpdaterOutput::CreateParticle(const sgl::graphic::ParticleData & initData)
{
    ParticleOutput * p = nullptr;

    if(mParticles.empty())
        p = new ParticleOutput;
    else
    {
        p = static_cast<ParticleOutput *>(mParticles.back());
        mParticles.pop_back();
    }

    // init data
    auto data = static_cast<const DataParticleOutput &>(initData);
    p->SetData(data);

    return p;
}

} // namespace game
