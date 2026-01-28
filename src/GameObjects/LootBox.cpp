#include "GameObjects/LootBox.h"

#include "Game.h"
#include "GameConstants.h"
#include "GameData.h"
#include "IsoObject.h"
#include "Player.h"
#include "Particles/DataParticleOutput.h"
#include "Particles/UpdaterOutput.h"

#include <sgl/graphic/ParticlesManager.h>
#include <sgl/graphic/TextureManager.h>
#include <sgl/media/AudioManager.h>
#include <sgl/media/AudioPlayer.h>
#include <sgl/utilities/LoadedDie.h>
#include <sgl/utilities/UniformDistribution.h>

#include <cmath>

namespace game
{

LootBox::LootBox(const ObjectData & data, const ObjectInitData & initData)
    : Collectable(data, initData)
{
    SetImage();

    SetObjColors();

    // define TYPE of prize
    sgl::utilities::LoadedDie die({ 15.f, 15.f, 20.f, 20.f, 30.f });
    mPrizeType = static_cast<LootBox::Prize>(die.GetNextValue());

    // define QUANTITY of prize
    int min;
    int max;

    if(LB_MONEY == mPrizeType)
    {
        min = 100;
        max = 500;
    }
    else if(LB_BLOBS == mPrizeType || LB_DIAMONDS == mPrizeType)
    {
        min = 5;
        max = 25;
    }
    // energy and material
    else
    {
        min = 50;
        max = 250;
    }

    sgl::utilities::UniformDistribution d(min, max, GetGame()->GetRandSeed());

    // round quantity to 5
    const int r = 5;
    mPrizeQuantity = std::roundf(d.GetNextValue() / static_cast<float>(r)) * r;
}

void LootBox::Collected(Player * collector)
{
    Collectable::Collected(collector);

    // do not show anyting for AI players
    if(collector->IsAI())
        return ;

    // emit notification
    auto partMan = GetParticlesManager();
    auto pu = static_cast<UpdaterOutput *>(partMan->GetUpdater(PU_OUTPUT));

    IsoObject * isoObj = GetIsoObject();

    const float x0 = isoObj->GetX() + isoObj->GetWidth() * 0.5f;
    const float y0 = isoObj->GetY() - isoObj->GetHeight() * 0.25f;

    const float speed = 50.f;
    const float decaySpeed = 150.f;

    OutputType ot[NUM_OUTPUT_TYPES] =
    {
        OT_BLOBS,
        OT_DIAMONDS,
        OT_ENERGY,
        OT_MATERIAL,
        OT_MONEY,
    };

    static_assert(static_cast<unsigned int>(NUM_OUTPUT_TYPES) ==
                  static_cast<unsigned int>(NUM_LB_PRIZES));

    DataParticleOutput pd(mPrizeQuantity, ot[mPrizeType], x0, y0, speed, decaySpeed);

    pu->AddParticle(pd);

    // play SFX
    auto ap = sgl::media::AudioManager::Instance()->GetPlayer();
    ap->PlaySound("game/collect-01.ogg");
}

void LootBox::UpdateGraphics()
{
    SetImage();

    SetObjColors();
}

void LootBox::SetImage()
{
    auto * tm = sgl::graphic::TextureManager::Instance();

    IsoObject * isoObj = GetIsoObject();

    if(IsVisible())
        isoObj->SetColor(COLOR_VIS);
    else
        isoObj->SetColor(COLOR_FOW);

    const unsigned int sel = static_cast<unsigned int>(IsSelected());
    const unsigned int texInd = IND_LOOTBOX + sel;

    sgl::graphic::Texture * tex = tm->GetSprite(SpriteCollectiblesFile, texInd);
    isoObj->SetTexture(tex);
}

void LootBox::SetObjColors()
{
    mObjColors.clear();

    mObjColors.push_back(0xdba457ff);
    mObjColors.push_back(0xd28d2dff);
    mObjColors.push_back(0xe0b06cff);
    mObjColors.push_back(0x805519ff);
    mObjColors.push_back(0x6b4715ff);
    mObjColors.push_back(0x95631dff);
}

} // namespace game
