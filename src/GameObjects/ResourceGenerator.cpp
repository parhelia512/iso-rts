#include "GameObjects/ResourceGenerator.h"

#include "GameConstants.h"
#include "IsoObject.h"
#include "Player.h"

#include <graphic/TextureManager.h>

namespace game
{

ResourceGenerator::ResourceGenerator(ResourceType type, int rows, int cols)
    : Structure(OBJ_RES_GEN, rows, cols)
    , mResType(type)
{
    SetCanBeConquered(true);

    SetImage();

    UpdateOutput();
}

void ResourceGenerator::UpdateGraphics()
{
    SetImage();

    SetDefaultColors();
}

void ResourceGenerator::SetImage()
{
    auto * tm = lib::graphic::TextureManager::Instance();

    lib::graphic::Texture * tex = nullptr;

    IsoObject * isoObj = GetIsoObject();

    if(IsVisible())
        isoObj->SetColor(COLOR_VIS);
    else
        isoObj->SetColor(COLOR_FOW);

    const Player * owner = GetOwner();

    if(RES_ENERGY == mResType)
    {
        // not visible
        if(!IsVisible())
            tex = tm->GetTexture("data/img/energy_source.png");
        // visible
        else
        {
            if(nullptr == owner)
                tex = tm->GetTexture("data/img/energy_source.png");
            else
            {
                const unsigned int faction = owner->GetFaction();

                const char * filesFactions[] =
                {
                    "data/img/energy_source-f1.png",
                    "data/img/energy_source-f2.png",
                    "data/img/energy_source-f3.png"
                };

                tex = tm->GetTexture(filesFactions[faction]);
            }
        }
    }
    else if(RES_MATERIAL1 == mResType)
    {
        // not visible
        if(!IsVisible())
            tex = tm->GetTexture("data/img/material_source.png");
        // visible
        else
        {
            GetIsoObject()->SetColor(COLOR_VIS);

            if(nullptr == owner)
                tex = tm->GetTexture("data/img/material_source.png");
            else
            {
                const unsigned int faction = owner->GetFaction();

                const char * filesFactions[] =
                {
                    "data/img/material_source-f1.png",
                    "data/img/material_source-f2.png",
                    "data/img/material_source-f3.png"
                };

                tex = tm->GetTexture(filesFactions[faction]);
            }
        }
    }
    // unknown resource type
    else
        tex = tm->GetTexture("data/img/obj_null.png");

    isoObj->SetTexture(tex);
}

void ResourceGenerator::UpdateOutput()
{
    if(RES_ENERGY == mResType)
        mOutput = 30;
    else if(RES_MATERIAL1 == mResType)
        mOutput = 2;
    // default
    else
        mOutput = 1;
}

} // namespace game

