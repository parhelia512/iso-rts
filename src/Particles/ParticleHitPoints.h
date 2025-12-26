#pragma once

#include <sgl/graphic/Particle.h>

namespace sgl
{
    namespace graphic { class TexturedRenderable; }
}

namespace game
{

class GameObject;

struct DataParticleHitPoints;

class ParticleHitPoints : public sgl::graphic::Particle
{
public:
    ~ParticleHitPoints();

    void SetData(const DataParticleHitPoints & data);

    float GetSpeed() const;

    void Update(float delta) override;

    void Render() override;

private:
    void SetStart(int x0, int y0);

private:
    sgl::graphic::TexturedRenderable * mTxt = nullptr;

    float mPosXf = 0.f;
    float mPosYf = 0.f;
    float mPosY0f = 0.f;

    float mSpeed = 0.f;
    float mAlpha = 255.f;
    float mDecaySpeed = 1.f;
    float mMaxDistance = 10.f;
};

inline float ParticleHitPoints::GetSpeed() const { return mSpeed; }


} // namespace game
