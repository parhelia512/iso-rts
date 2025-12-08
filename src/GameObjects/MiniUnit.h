#pragma once

#include "GameObject.h"
#include "ObjectData.h"

namespace game
{

class MiniUnit : public GameObject
{
public:
    MiniUnit(const ObjectData & data, int elements);

    int GetNumElements() const;
    void SetNumElements(int num);

    bool IsMoving() const;
    void SetMoving(bool moving);
    void setTargetReached();

    void Update(float delta) override;

private:
    void UpdateGraphics() override;

    void SetImage();

    void ExplodeNearEnemy();

private:
    int mElements;

    bool mMoving = false;
    bool mTargetReached = false;
};

inline int MiniUnit::GetNumElements() const { return mElements; }

inline bool MiniUnit::IsMoving() const { return mMoving; }
inline void MiniUnit::SetMoving(bool moving) { mMoving = moving; }

inline void MiniUnit::setTargetReached() { mTargetReached = true; }

} // namespace game
