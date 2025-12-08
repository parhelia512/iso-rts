#pragma once

#include "Structure.h"

namespace game
{

class ObjectData;
class Weapon;

class Bunker : public Structure
{
public:
    Bunker(const ObjectData & data);

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
    float mTimeAttack = 0.25f;
    float mTimerAttack = 0.f;
    int mAttackRange = 1;

    Weapon * mWeapon = nullptr;
};

inline void Bunker::SetWeapon(Weapon * w) { mWeapon = w; }

inline int Bunker::GetAttackRange() const { return mAttackRange; }

} // namespace game
