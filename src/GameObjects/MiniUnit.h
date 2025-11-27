#pragma once

#include "GameObject.h"
#include "ObjectData.h"

#include <unordered_map>

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

private:
    void UpdateGraphics() override;

    void SetImage();

private:
    // attributes
    std::unordered_map<ObjAttId, int> mAttributes;

    int mElements;

    bool mMoving = false;
};

inline int MiniUnit::GetNumElements() const { return mElements; }

inline bool MiniUnit::IsMoving() const { return mMoving; }
inline void MiniUnit::SetMoving(bool moving) { mMoving = moving; }


} // namespace game
