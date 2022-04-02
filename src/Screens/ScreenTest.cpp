#include "Screens/ScreenTest.h"

#include "Game.h"
#include "GameConstants.h"
#include "Widgets/ButtonMainMenu.h"
#include "Widgets/ButtonUnitsSelector.h"
#include "Widgets/CellProgressBar.h"
#include "Widgets/Test/TestComboBox.h"
#include "Widgets/Test/TestSliderH.h"

#include <sgl/core/event/MouseButtonEvent.h>
#include <sgl/graphic/Font.h>
#include <sgl/graphic/FontManager.h>
#include <sgl/graphic/Image.h>
#include <sgl/graphic/Text.h>
#include <sgl/graphic/Texture.h>
#include <sgl/graphic/TextureManager.h>
#include <sgl/sgui/ButtonsGroup.h>
#include <sgl/sgui/Image.h>
#include <sgl/sgui/Label.h>
#include <sgl/sgui/Stage.h>
#include <sgl/sgui/TextArea.h>

#include <iostream>

namespace game
{

const float TIME_PB = 4.f;

ScreenTest::ScreenTest(Game * game)
    : Screen(game)
{
    using namespace sgl::graphic;

    game->SetClearColor(0x22, 0x22, 0x22, 0xFF);

    // -- Image testing --
    Image * img = nullptr;

    img = new Image("data/img/obj_null.png");
    img->SetPosition(64, 32);
    mRenderables.emplace_back(img);

    img = new Image("data/img/obj_null.png");
    img->SetPosition(128, 64);
    img->SetAlpha(128);
    mRenderables.emplace_back(img);

    img = new Image("data/img/obj_null.png");
    img->SetPosition(300, 32);
    img->ScaleH(2.f);
    img->SetRotation(45.f);
    img->SetColor(0x3366F0FF);
    mRenderables.emplace_back(img);

    img = new Image("data/img/obj_null.png");
    img->SetPosition(32, 64);
    img->SetWidth(64);
    img->SetHeight(32);
    mRenderables.emplace_back(img);

    // -- Text testing --
    FontManager * fm = FontManager::Instance();

    const int TXT_X0 = 20;
    Font * font = fm->GetFont("data/fonts/OpenSans.ttf", 24, Font::NORMAL);
    Text * txt = nullptr;

    txt = new Text("Text 1", font);
    txt->SetPosition(TXT_X0, 250);
    mRenderables.emplace_back(txt);

    font = fm->GetFont("data/fonts/OpenSans.ttf", 24, Font::BOLD | Font::ITALIC);
    txt = new Text("Text 2 (bold & italic)", font);
    txt->SetPosition(TXT_X0, 300);
    mRenderables.emplace_back(txt);

    font = fm->GetFont("data/fonts/OpenSans.ttf", 24, Font::BOLD);
    txt = new Text("Text 3 (bold - A=128)", font);
    txt->SetPosition(TXT_X0, 350);
    txt->SetAlpha(128);
    mRenderables.emplace_back(txt);

    font = fm->GetFont("data/fonts/OpenSans.ttf", 24, Font::NORMAL);
    txt = new Text("Text 4 (50, 150, 250, 255)", font);
    txt->SetPosition(TXT_X0, 400);
    txt->SetColor(50, 150, 250, 255);
    mRenderables.emplace_back(txt);

    txt = new Text("Text 5 (50, 150, 250, 128)", font);
    txt->SetPosition(TXT_X0, 450);
    txt->SetColor(50, 150, 250, 128);
    mRenderables.emplace_back(txt);

    TestSprite();

    TestRotation();

    TestSGui();
}

ScreenTest::~ScreenTest()
{
    for(sgl::graphic::TexturedRenderable * r : mRenderables)
        delete r;

    sgl::sgui::Stage::Instance()->ClearWidgets();
}

void ScreenTest::Update(float delta)
{
    if(mTimerPb < TIME_PB)
    {
        mTimerPb += delta;

        const float perc = mTimerPb * 100.f / TIME_PB;

        mPb0->SetValuePerc(perc);
        mPb1->SetValuePerc(perc);
        mPb2->SetValuePerc(perc);
    }
}

void ScreenTest::Render()
{
    for(sgl::graphic::TexturedRenderable * r : mRenderables)
        r->Render();
}

void ScreenTest::OnMouseButtonUp(sgl::core::MouseButtonEvent & event)
{
    std::cout << "Mouse clicked - button: " << event.GetButton()
              << " - pos: " << event.GetX() << " , " << event.GetY() << std::endl;
}

void ScreenTest::TestSGui()
{
    using namespace sgl::graphic;
    using namespace sgl::sgui;

    const int marginV = 50;

    Widget * container = new Widget;
    container->SetPosition(600, 20);

    FontManager * fm = FontManager::Instance();

    // -- PUSHBUTTON --
    Font * font = fm->GetFont("data/fonts/OpenSans.ttf", 24, Font::BOLD);
    Label * label = new Label("PUSH BUTTON", font, container);

    ButtonMainMenu * button = new ButtonMainMenu("BUTTON 1", container);
    button->SetY(label->GetHeight() + 20);

    font = fm->GetFont("data/fonts/OpenSans.ttf", 24, Font::NORMAL);
    label = new Label(font, container);
    label->SetY(button->GetY() + button->GetHeight() + 10);

    button->AddOnClickFunction([label]
    {
        label->SetText("button 1 clicked");
        std::cout << "button 1 clicked" << std::endl;
    });

    button = new ButtonMainMenu("BUTTON 2", container);
    button->SetY(label->GetY() + marginV);

    button->AddOnClickFunction([label]
    {
        label->SetText("button 2 clicked");
        std::cout << "button 2 clicked" << std::endl;
    });

    int buttonY = button->GetY() + button->GetHeight() + marginV;

    button = new ButtonMainMenu("BUTTON 3", container);
    button->SetEnabled(false);
    button->SetY(buttonY);

    buttonY += button->GetHeight() + marginV;

    button = new ButtonMainMenu("SELECTED", container);
    button->SetCheckable(true);
    button->SetY(buttonY);

    buttonY += button->GetHeight() + marginV;

    // -- TEXT AREA --
    font = fm->GetFont("data/fonts/OpenSans.ttf", 24, Font::BOLD);
    label = new Label("TEXT AREA", font, container);
    label->SetY(buttonY);

    buttonY += label->GetHeight() * 1.5f;

    button = new ButtonMainMenu("CHANGE TEXT", container);
    button->SetY(label->GetY() + marginV);

    buttonY += button->GetHeight() * 1.5f;

    auto tm = TextureManager::Instance();
    auto borders = new sgl::sgui::Image(tm->GetTexture("data/img/test/text_area.png"), container);
    borders->SetPosition(0, buttonY);

    const int taW = 400;
    const int taH = 300;
    const char * text = "This is a pretty long text.(NN)\n\nOver multiple lines, well, at least 4 and I bet that "
                        "this line will wrap at some point before the newline.(N)\nHere it is the end!";
    font = fm->GetFont("data/fonts/OpenSans.ttf", 22, Font::NORMAL);
    auto ta = new TextArea(taW, taH, text, font, container);
    ta->SetY(buttonY);
    ta->SetColor(0x99FFAAFF);

    button->AddOnClickFunction([ta]
    {
        ta->SetText("Text changed after pushing a button. All good so far. Also NO newline in this case!");
    });

    ButtonsGroup * bgAlignH = new ButtonsGroup(ButtonsGroup::HORIZONTAL, container);
    bgAlignH->AddButton(new ButtonUnitsSelector("L"));
    bgAlignH->AddButton(new ButtonUnitsSelector("C"));
    bgAlignH->AddButton(new ButtonUnitsSelector("R"));
    bgAlignH->SetButtonChecked(0, true);
    bgAlignH->SetPosition(ta->GetX(), ta->GetY() + ta->GetHeight());

    bgAlignH->SetFunctionOnToggle([ta](unsigned int ind, bool checked)
    {
       if(checked)
           ta->setTextAlignmentHorizontal(static_cast<TextArea::Alignment>(ind));
    });

    ButtonsGroup * bgAlignV = new ButtonsGroup(ButtonsGroup::HORIZONTAL, container);
    bgAlignV->AddButton(new ButtonUnitsSelector("T"));
    bgAlignV->AddButton(new ButtonUnitsSelector("C"));
    bgAlignV->AddButton(new ButtonUnitsSelector("B"));
    bgAlignV->SetButtonChecked(0, true);
    bgAlignV->SetPosition(ta->GetX() + ta->GetWidth() - bgAlignV->GetWidth(),
                          ta->GetY() + ta->GetHeight());

    bgAlignV->SetFunctionOnToggle([ta](unsigned int ind, bool checked)
    {
       if(checked)
           ta->setTextAlignmentVertical(static_cast<TextArea::Alignment>(ind + TextArea::ALIGN_V_TOP));
    });

    // -- BUTTONS GROUP --
    font = fm->GetFont("data/fonts/OpenSans.ttf", 24, Font::BOLD);

    label = new Label("BUTTONS GROUP", font, container);
    label->SetX(400);

    ButtonsGroup * bg = new ButtonsGroup(ButtonsGroup::HORIZONTAL, container);
    bg->SetPosition(label->GetX(), label->GetHeight() + 50);

    bg->AddButton(new ButtonUnitsSelector("1"));
    bg->AddButton(new ButtonUnitsSelector("2"));
    bg->AddButton(new ButtonUnitsSelector("3"));
    bg->AddButton(new ButtonUnitsSelector("4"));

    // set initial checked
    bg->SetButtonChecked(0, true);

    // test set checked on disabled
    bg->SetButtonEnabled(3, false);
    bg->SetButtonChecked(3, true);

    label = new Label("1", font, container);
    label->SetPosition(bg->GetX() + bg->GetWidth() * 1.1f,
                       bg->GetY() + (bg->GetHeight() - label->GetHeight()) * 0.5f);

    for(unsigned int n = 0; n < bg->GetNumButtons(); ++n)
    {
        auto btn = static_cast<ButtonUnitsSelector *>(bg->GetButton(n));
        btn->AddOnToggleFunction([label, n](bool checked)
        {
            if(checked)
                label->SetText(std::to_string(n + 1).c_str());
        });
    }

    // -- PROGRESS BAR --
    font = fm->GetFont("data/fonts/OpenSans.ttf", 24, Font::BOLD);

    label = new Label("PROGRESS BAR", font, container);
    label->SetX(700);

    const int pbX = label->GetX();
    const int pbY = label->GetY() + label->GetHeight() + 50;
    const int marginbBars = 25;

    mPb0 = new CellProgressBar(FACTION_1, container);
    mPb0->SetPosition(pbX, pbY);
    mPb0->SetValue(0);
    mPb0->SetFunctionOnCompleted([]{ std::cout << "TEST PROGRESS 0 100%" << std::endl; });

    mPb1 = new CellProgressBar(FACTION_2, container);
    mPb1->SetPosition(pbX, pbY + mPb0->GetHeight() + marginbBars);
    mPb1->SetValue(0);
    mPb1->SetFunctionOnCompleted([]{ std::cout << "TEST PROGRESS 1 100%" << std::endl; });

    mPb2 = new CellProgressBar(FACTION_3, container);
    mPb2->SetPosition(pbX, mPb1->GetY() + mPb1->GetHeight() + marginbBars);
    mPb2->SetValue(0);
    mPb2->SetFunctionOnCompleted([]{ std::cout << "TEST PROGRESS 2 100%" << std::endl; });

    button = new ButtonMainMenu("RESET", container);
    button->SetPosition(mPb0->GetX() + mPb0->GetWidth() + marginbBars * 2, mPb0->GetY());
    button->AddOnClickFunction([this]
    {
        mTimerPb = 0;
        mPb0->Reset();
        mPb1->Reset();
        mPb2->Reset();
    });

    // -- SET ALPHA --
    int wX = 1300;
    int wY = button->GetY() + button->GetHeight() * 2;

    auto container2 = new Widget;
    container2->SetPosition(wX, wY);

    label = new Label("SET ALPHA", font, container2);
    wY = label->GetHeight() * 2;

    button = new ButtonMainMenu("ALPHA 50%", container2);
    button->SetY(wY);
    button->AddOnClickFunction([container2]{ container2->SetAlpha(128); });

    button = new ButtonMainMenu("ALPHA 100%", container2);
    wY += button->GetHeight() * 2;
    button->SetY(wY);
    button->AddOnClickFunction([container2]{ container2->SetAlpha(255); });

    // -- COMBO BOX --
    wY = 550;

    auto container3 = new Widget;
    container3->SetPosition(wX, wY);

    label = new Label("COMBO BOX", font, container3);
    wY = label->GetHeight() * 2;

    auto cb = new TestComboBox(container3);
    cb->AddItem(new TestComboBoxItem("OPTION 1"));
    cb->AddItem(new TestComboBoxItem("OPTION 2"));
    cb->AddItem(new TestComboBoxItem("OPTION 3"));

    cb->SetY(wY);

    font = fm->GetFont("data/fonts/OpenSans.ttf", 22, Font::NORMAL);
    label = new Label(cb->GetActiveItem()->GetText().c_str(), font, container3);
    label->SetPosition(cb->GetX() + cb->GetWidth() + 50, cb->GetY());

    cb->SetOnActiveChanged([label, cb](int index)
    {
        label->SetText(cb->GetActiveItem()->GetText().c_str());
    });

    // SLIDER
    wY = 725;
    auto container4 = new Widget;
    container4->SetPosition(wX, wY);

    font = fm->GetFont("data/fonts/OpenSans.ttf", 24, Font::BOLD);
    label = new Label("SLIDER", font, container4);
    wY = label->GetHeight() * 2;

    auto slider = new TestSliderH(container4);
    slider->SetY(wY);

    font = fm->GetFont("data/fonts/OpenSans.ttf", 22, Font::NORMAL);
    label = new Label(std::to_string(slider->GetValue()).c_str(), font, container4);
    label->SetPosition(slider->GetX() + slider->GetWidth() + 50, slider->GetY());

    slider->SetOnValueChanged([label](int val)
    {
        label->SetText(std::to_string(val).c_str());
    });

}

void ScreenTest::TestSprite()
{
    using namespace sgl::graphic;

    auto tm = TextureManager::Instance();

    const std::vector<sgl::core::Rectd> rects
    {
        { 0, 0, 40, 40 },
        { 40, 0, 40, 40 },
        { 0, 40, 40, 40 },
        { 40, 40, 40, 40 }
    };

    const unsigned int numRects = rects.size();

    const char file[] = "data/img/test/test_sprite.png";

    tm->RegisterSprite(file, rects);

    const int x0 = 20;
    const int y0 = 550;
    const int marginH = 20;
    const int marginV = 20;

    Image * img = nullptr;

    img = new Image(tm->GetTexture(file));
    mRenderables.emplace_back(img);

    img->SetPosition(x0, y0);

    const int x1 = x0 + img->GetWidth() + marginH;

    // row 1
    int x = x1;

    for(unsigned int i = 0; i < numRects; ++i)
    {
        img = new Image(tm->GetSprite(file, i));
        img->SetPosition(x, y0);
        mRenderables.emplace_back(img);

        x += img->GetWidth() + marginH;
    }

    // row 2
    x = x1;
    const int y1 = y0 + img->GetHeight() + marginV;

    for(unsigned int i = 0; i < numRects; ++i)
    {
        img = new Image(tm->GetSprite(file, numRects - i - 1));
        img->SetPosition(x, y1);
        mRenderables.emplace_back(img);

        x += img->GetWidth() + marginH;
    }
}

void ScreenTest::TestRotation()
{
    using namespace sgl::graphic;

    Image * img = nullptr;

    // no bg bar
    img = new Image("data/img/test/square100.png");
    img->SetPosition(50, 800);
    mRenderables.emplace_back(img);

    img = new Image("data/img/test/test-bar-nobg.png");
    img->SetPosition(50, 800);
    img->SetRotation(45.f);
    mRenderables.emplace_back(img);

    img = new Image("data/img/test/red_dot4.png");
    img->SetPosition(50, 800);
    mRenderables.emplace_back(img);

    // bar in square
    img = new Image("data/img/test/square100.png");
    img->SetPosition(200, 800);
    mRenderables.emplace_back(img);

    img = new Image("data/img/test/test-bar-bg.png");
    img->SetPosition(200, 800);
    img->SetRotation(45.f);
    mRenderables.emplace_back(img);

    img = new Image("data/img/test/red_dot4.png");
    img->SetPosition(200, 800);
    mRenderables.emplace_back(img);

    // no bg bar - centered in origin
    img = new Image("data/img/test/square100.png");
    img->SetPosition(50, 950);
    mRenderables.emplace_back(img);

    img = new Image("data/img/test/test-bar-nobg.png");
    img->SetPosition(50 - img->GetWidth() * 0.5f, 950- img->GetHeight() * 0.5f);
    img->SetRotation(45.f);
    mRenderables.emplace_back(img);

    img = new Image("data/img/test/red_dot4.png");
    img->SetPosition(50, 950);
    mRenderables.emplace_back(img);

    // bar in square - centered in origin
    img = new Image("data/img/test/square100.png");
    img->SetPosition(200, 950);
    mRenderables.emplace_back(img);

    img = new Image("data/img/test/test-bar-bg.png");
    img->SetPosition(200 - img->GetWidth() * 0.5f, 950- img->GetHeight() * 0.5f);
    img->SetRotation(45.f);
    mRenderables.emplace_back(img);

    img = new Image("data/img/test/red_dot4.png");
    img->SetPosition(200, 950);
    mRenderables.emplace_back(img);
}

} // namespace game
