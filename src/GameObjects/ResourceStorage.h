#pragma once

#include "Structure.h"

namespace game
{

enum ResourceType : unsigned int;

class ResourceStorage : public Structure
{
public:
    ResourceStorage(const ObjectData & data, const ObjectInitData & initData);

    ResourceType GetResourceType() const;

private:
    void UpdateGraphics() override;

    void OnLinkedChanged() override;

    void UpdateCapacity();

    void SetImage();

private:
    ResourceType mResource;

    int mCapacity = 0;
};

inline ResourceType ResourceStorage::GetResourceType() const { return mResource; }

} // namespace game

