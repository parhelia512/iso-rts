#pragma once

#include "Structure.h"

namespace game
{

class ObjectData;
class Weapon;

class DefensiveTower : public Structure
{
public:
    DefensiveTower(const ObjectData & data);

    // weapon
    void SetWeapon(Weapon * w);

    int GetAttackRange() const;

    void Update(float delta) override;

protected:
    void UpdateGraphics() override;

private:
    void SetImage();

    void CheckForEnemies();

    void Shoot();

private:
    GameObject * mTarget = nullptr;

    // weapon
    Weapon * mWeapon = nullptr;

    float mTimeAttack = 0.25f;
    float mTimerAttack = 0.f;
    int mAttackRange = 1;
};

inline void DefensiveTower::SetWeapon(Weapon * w) { mWeapon = w; }

inline int DefensiveTower::GetAttackRange() const { return mAttackRange; }

} // namespace game
