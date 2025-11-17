#pragma once

#include "GameObject.h"
#include "ObjectData.h"

#include <array>

namespace game
{

class MiniUnit : public GameObject
{
public:
    MiniUnit(const ObjectData & data);

    int GetNumElements() const;
    void SetNumElements(int num);

private:
    void UpdateGraphics() override;

private:
    // attributes
    std::array<int, NUM_OBJ_ATTRIBUTES> mAttributes;

    int mElements = 1;
};

int MiniUnit::GetNumElements() const { return mElements; }

} // namespace game
