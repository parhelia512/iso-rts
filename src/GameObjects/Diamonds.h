#pragma once

#include "Collectable.h"

namespace game
{

class DiamondsGenerator;

class Diamonds : public Collectable
{
public:
    Diamonds(const ObjectData & data, const ObjectInitData & initData);

    int GetNum() const;
    void MaximizeUnits();
    void MinimizeUnits();

    void Collected(Player * collector) override;

protected:
    void UpdateGraphics() override;

private:
    void SetImage();

    void SetObjColors();

private:
    int mNum = 0;
};

inline int Diamonds::GetNum() const { return mNum; }

} // namespace game
