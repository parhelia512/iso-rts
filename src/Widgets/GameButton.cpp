
#include "GameButton.h"

#include <graphic/Camera.h>
#include <graphic/Image.h>
#include <graphic/TextureManager.h>

namespace game
{

GameButton::GameButton(lib::sgui::Widget * parent)
    : lib::sgui::PushButton(parent)
    , mBody(new lib::graphic::Image)
{
    RegisterRenderable(mBody);
}

GameButton::GameButton(const std::array<const char *, NUM_VISUAL_STATES> & bgFiles,
                       const std::array<unsigned int, NUM_VISUAL_STATES> & labelsColor,
                       lib::sgui::Widget * parent)
    : GameButton(parent)
{
    SetData(bgFiles, labelsColor);
}

GameButton::GameButton(const char * spriteFile,
                       const std::array<unsigned int, NUM_VISUAL_STATES> & spriteIds,
                       const std::array<unsigned int, NUM_VISUAL_STATES> & labelsColor,
                       lib::sgui::Widget * parent)
    : GameButton(parent)
{
    SetData(spriteFile, spriteIds, labelsColor);
}

GameButton::~GameButton()
{
    delete mBody;
}

void GameButton::SetData(const std::array<const char *, NUM_VISUAL_STATES> & bgFiles,
                         const std::array<unsigned int, NUM_VISUAL_STATES> & labelsColor)
{
    auto tm = lib::graphic::TextureManager::Instance();

    // init background data
    for(unsigned int i = 0; i < NUM_VISUAL_STATES; ++i)
        mBackgrounds[i] = tm->GetTexture(bgFiles[i]);

    // init label data
    mLabelsColor = labelsColor;

    SetState(NORMAL);
}

void GameButton::SetData(const char * spriteFile,
                         const std::array<unsigned int, NUM_VISUAL_STATES> & spriteIds,
                         const std::array<unsigned int, NUM_VISUAL_STATES> & labelsColor)
{
    auto tm = lib::graphic::TextureManager::Instance();

    // init background data
    for(unsigned int i = 0; i < NUM_VISUAL_STATES; ++i)
        mBackgrounds[i] = tm->GetSprite(spriteFile, spriteIds[i]);

    // init label data
    mLabelsColor = labelsColor;

    // default state after setting data
    SetState(NORMAL);
}

void GameButton::OnStateChanged(lib::sgui::PushButton::VisualState state)
{
    // refresh body
    mBody->SetTexture(mBackgrounds[state]);
    SetCurrBg(mBody);

    // update label color
    SetLabelColor(mLabelsColor[state]);
}

} // namespace game

