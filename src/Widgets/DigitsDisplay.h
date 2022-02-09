#pragma once

#include <sgl/sgui/Widget.h>

#include <string>

namespace sgl  { namespace graphic  { class Renderable; } }

namespace game
{

class DigitsDisplay : public sgl::sgui::Widget
{
public:
    DigitsDisplay(int digits, sgl::sgui::Widget * parent);
    DigitsDisplay(int digits, int fontSize, const std::string & suffix, sgl::sgui::Widget * parent);

    void SetFontSize(int val);
    void SetSuffix(const std::string & suffix);
    void SetValue(int val);

private:
    void UpdateDigits(bool force = false);

    void HandlePositionChanged() override;

    void SetPositions();

private:
    std::string mSuffix;
    int mDigits = 0;
    int mValue = -1;

    int mNumZeros = -1;

    int mFontSize = 19;

    sgl::graphic::Renderable * mTxtZeros = nullptr;
    sgl::graphic::Renderable * mTxtDigits = nullptr;
};

} // namespace game
