#include "sgui/Image.h"

#include "graphic/DummyRenderable.h"
#include "graphic/Image.h"

#include <cassert>

namespace lib
{
namespace sgui
{

Image::Image(Widget * parent)
    : Widget(parent)
    , mImg(new graphic::DummyRenderable)
{
}

Image::Image(const char * file, Widget * parent)
    : Widget(parent)
{
    assert(file);

    LoadImage(file);
}

Image::~Image()
{
    delete mImg;
}

void Image::SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    mImg->SetColor(r, g, b, a);
}

void Image::SetColor(unsigned int color) { mImg->SetColor(color); }

void Image::LoadImage(const char * file)
{
    graphic::Renderable * oldImg = mImg;

    mImg = new graphic::Image(file);

    if(oldImg)
    {
        mImg->SetPosition(oldImg->GetX(), oldImg->GetY());
        mImg->SetColor(oldImg->GetColor());

        delete oldImg;
    }

    SetSize(mImg->GetWidth(), mImg->GetHeight());
}

void Image::HandlePositionChanged()
{
    mImg->SetPosition(GetScreenX(), GetScreenY());
}

void Image::OnRender()
{
    mImg->Render();
}

} // namespace sgui
} // namespace lib
