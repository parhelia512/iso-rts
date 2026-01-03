#pragma once

#include "Structure.h"

namespace game
{

class ResearchCenter : public Structure
{
public:
    ResearchCenter(const ObjectData & data, const ObjectInitData & initData);

protected:
    void UpdateGraphics() override;

private:
    void SetImage();
};

} // namespace game
