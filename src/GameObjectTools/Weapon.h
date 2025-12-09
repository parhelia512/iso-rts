#pragma once

#include <unordered_map>

namespace sgl
{
    namespace graphic { class ParticlesManager; }
}

namespace game
{

class GameMap;
class GameObject;
class WeaponData;

enum ObjAttId : unsigned int;

class Weapon
{
public:
    Weapon(const WeaponData & data, GameObject * owner, GameMap * gm,
           const sgl::graphic::ParticlesManager * partMan);
    virtual ~Weapon() = default;

    int GetRange() const;

    const std::unordered_map<ObjAttId, int> & GetAttributes() const;

    virtual void Shoot(float x0, float y0, GameObject * target) = 0;

protected:
    GameObject * GetOwner() const;
    GameMap * GetGameMap() const;
    const sgl::graphic::ParticlesManager * GetParticlesManager() const;

private:
    std::unordered_map<ObjAttId, int> mAttributes;

    GameObject * mOwner = nullptr;
    GameMap * mGameMap = nullptr;

    const sgl::graphic::ParticlesManager * mPartMan = nullptr;

    int mRange = 0;
};

inline int Weapon::GetRange() const { return mRange; }

inline const std::unordered_map<ObjAttId, int> & Weapon::GetAttributes() const { return mAttributes; }

inline GameObject * Weapon::GetOwner() const { return mOwner; }

inline GameMap * Weapon::GetGameMap() const { return mGameMap; }

inline const sgl::graphic::ParticlesManager * Weapon::GetParticlesManager() const { return mPartMan; }

} // namespace game
