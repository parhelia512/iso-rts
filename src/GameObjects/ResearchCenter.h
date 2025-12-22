#pragma once

#include "Structure.h"

namespace game
{

class ResearchCenter : public Structure
{
public:
    ResearchCenter(const ObjectData & data);

protected:
    void UpdateGraphics() override;

private:
    void SetImage();
};

} // namespace game
