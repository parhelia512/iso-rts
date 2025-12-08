#pragma once

namespace sgl
{
    namespace graphic { class ParticlesManager; }
}

namespace game
{

class GameMap;
class GameObject;

class Weapon
{
public:
    Weapon(GameObject * owner, GameMap * gm, const sgl::graphic::ParticlesManager * partMan);
    virtual ~Weapon() = default;

    virtual void Shoot(float x0, float y0, GameObject * target) = 0;

protected:
    GameObject * GetOwner() const;
    GameMap * GetGameMap() const;
    const sgl::graphic::ParticlesManager * GetParticlesManager() const;

private:
    GameObject * mOwner = nullptr;
    GameMap * mGameMap = nullptr;

    const sgl::graphic::ParticlesManager * mPartMan = nullptr;
};

inline GameObject * Weapon::GetOwner() const { return mOwner; }

inline GameMap * Weapon::GetGameMap() const { return mGameMap; }

inline const sgl::graphic::ParticlesManager * Weapon::GetParticlesManager() const { return mPartMan; }

} // namespace game
