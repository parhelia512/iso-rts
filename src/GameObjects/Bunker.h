#pragma once

#include "Structure.h"

namespace game
{

class ObjectData;

class Bunker : public Structure
{
public:
    Bunker(const ObjectData & data);

    void Update(float delta) override;

protected:
    void UpdateGraphics() override;

private:
    void SetImage();

    void PrepareShoot();
};

} // namespace game
