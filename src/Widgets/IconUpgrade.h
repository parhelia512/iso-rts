#pragma once

#include <sgl/sgui/Image.h>

namespace game
{

enum PlayerFaction : unsigned int;

class IconUpgrade : public sgl::sgui::Image
{
public:
    IconUpgrade(PlayerFaction f);
};

} // namespace game
