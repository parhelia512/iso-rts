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

enum AttackMode : unsigned int;
enum ObjAttId : unsigned int;

class Weapon
{
public:
    Weapon(const WeaponData & data, GameObject * owner, GameMap * gm,
           const sgl::graphic::ParticlesManager * partMan);
    virtual ~Weapon() = default;

    AttackMode GetAttackMode() const;
    void SetAttackMode(AttackMode am);

    void ClearTarget();
    bool SetTarget(GameObject * obj);
    bool IsTargetInRange(const GameObject * obj) const;

    unsigned int GetBurstShots() const;
    unsigned int GetBurstToShoot() const;
    float GetBurstDelay() const;
    void DecreaseBurstShots();

    int GetRange() const;

    const std::unordered_map<ObjAttId, int> & GetAttributes() const;

    void Shoot(float x0, float y0);

    bool Update(float delta);

protected:
    GameObject * GetOwner() const;
    GameObject * GetTarget() const;
    GameMap * GetGameMap() const;
    const sgl::graphic::ParticlesManager * GetParticlesManager() const;

private:
    void InitBurstShoot();

    virtual void OnShoot(float x0, float y0) = 0;

private:
    std::unordered_map<ObjAttId, int> mAttributes;

    GameObject * mOwner = nullptr;
    GameMap * mGameMap = nullptr;

    const sgl::graphic::ParticlesManager * mPartMan = nullptr;

    // attack
    AttackMode mAttackMode;
    GameObject * mTarget = nullptr;
    float mTimerBurst = 0.f;

    int mRange = 0;
    int mBurstShots = 0;
    int mBurstToShoot = 0;
    float mBurstDelay = 0.f;
};

inline AttackMode Weapon::GetAttackMode() const { return mAttackMode; }
inline void Weapon::SetAttackMode(AttackMode am) { mAttackMode = am; }

inline void Weapon::ClearTarget() { mTarget = nullptr; }

inline unsigned int Weapon::GetBurstShots() const { return mBurstShots; }
inline unsigned int Weapon::GetBurstToShoot() const { return mBurstToShoot; }
inline float Weapon::GetBurstDelay() const { return mBurstDelay; }
inline void Weapon::DecreaseBurstShots()
{
    if(mBurstToShoot > 0)
        --mBurstToShoot;
}

inline int Weapon::GetRange() const { return mRange; }

inline const std::unordered_map<ObjAttId, int> & Weapon::GetAttributes() const { return mAttributes; }

inline GameObject * Weapon::GetOwner() const { return mOwner; }

inline GameObject * Weapon::GetTarget() const { return mTarget; }

inline GameMap * Weapon::GetGameMap() const { return mGameMap; }

inline const sgl::graphic::ParticlesManager * Weapon::GetParticlesManager() const { return mPartMan; }

inline void Weapon::InitBurstShoot()
{
    mBurstToShoot = mBurstShots;
    mTimerBurst = 0.f;
}

} // namespace game
