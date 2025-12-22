#pragma once

#include "Structure.h"

namespace game
{

class PracticeTarget : public Structure
{
public:
    PracticeTarget(const ObjectData & data);

protected:
    void UpdateGraphics() override;

private:
    void SetImage();

    void SetObjColors();
};

} // namespace game
