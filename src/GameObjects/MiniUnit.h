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

private:
    void UpdateGraphics() override;

    void SetImage();

private:
    // attributes
    std::unordered_map<ObjAttId, int> mAttributes;

    int mElements = 1;
};

inline int MiniUnit::GetNumElements() const { return mElements; }

} // namespace game
