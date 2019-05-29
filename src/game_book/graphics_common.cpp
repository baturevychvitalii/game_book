#include "graphics_common.h"

graphics::WindowManager wm;
xml::Parser xmp;
const std::string first_page = "book/begin.xml";
const std::string save_path = "save.xml";

size_t red_on_white = 1,
       green_on_black = 2,
       magneta_on_blue = 3,
       white_on_red = 4,
       red_on_black = 5,
       magneta_on_black = 6,
       cyan_on_black = 7,
       error_color = red_on_black,
       hacker = green_on_black;

void InitColors()
{
    init_pair(red_on_white, COLOR_RED, COLOR_WHITE);
    init_pair(green_on_black, COLOR_GREEN, COLOR_BLACK);
    init_pair(magneta_on_blue, COLOR_MAGENTA, COLOR_BLUE);
    init_pair(white_on_red, COLOR_WHITE, COLOR_RED);
    init_pair(red_on_black, COLOR_RED, COLOR_BLACK);
    init_pair(magneta_on_black, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(cyan_on_black, COLOR_CYAN, COLOR_BLACK);
}

void RaiseErrorWindow(const std::exception & e)
{
    auto & screen = wm.SelectScreen("error");
    screen.Clear();
    auto & win = screen.AddWindow<graphics::Textbox>(
        "error",
        graphics::Window::XPercent(50),
        graphics::Window::YPercent(10), 
        graphics::Window::XPercent(25),
        error_color
    );
    win.AppendText("Exception was thrown!");
    win.NewLine();
    win.AppendText(e.what());
    win.NewLine();
    win.AppendText("press any key to continue", hacker);
    wm.Draw();
    getch();
}

size_t GetMenuSelection(graphics::Menu & m)
{
    wm.Draw();
    int input;
    while((input = getch()) != 10)
    {
        switch (input)
        {
            case KEY_UP:
                if (m.LowestPoint() > graphics::Window::max_y)
                    wm.Move(graphics::Direction::Up, 3);
                break;
            case KEY_DOWN:
                if (m.HighestPoint() < 0)
                    wm.Move(graphics::Direction::Down, 3);
                break;
            case KEY_LEFT:
                m--;
                break;
            case KEY_RIGHT:
                m++;
                break;
            default:
                continue;
        }
        wm.Draw();
    }

    return m.GetChoice();
}

void CreateAuthorWindow()
{
    auto & author = wm.AddScreen("author");
    auto & text = author.AddWindow<graphics::Textbox>(
        "author info",
        graphics::Window::XPercent(77),
        3,
        graphics::Window::XPercent(33) / 2,
        hacker
    );

    text.AppendText("By Vitalii Baturevych");
}

void CreateControlsWindow()
{
    auto & controls = wm.AddScreen("controls");

    auto & text = controls.AddWindow<graphics::Textbox>(
        "controls info",
        graphics::Window::max_x,
        0,
        0,
        hacker
    );

    text.AppendText("Controls");
    text.AppendText("press any key to continue");
    text.NewLine();
    text.NewLine("<- -> navigate in menu");
    text.NewLine("^   v scroll window");
    text.NewLine("Enter select");
    text.NewLine("  p   pause (in game)");
    text.NewLine("  i   inventory (in game)");
}

void CreateMainMenu()
{
    auto & main = wm.AddScreen("main");
    
    auto & menu = main.AddWindow<graphics::Menu>(
        "main menu",
        graphics::Window::XPercent(50),
        4,
        graphics::Window::XPercent(25),
        white_on_red, red_on_white, white_on_red, 1
    );

    menu.AppendText("Story of Lory");
    menu.NewLine();
    menu.AppendText("<  or  > to select different options");
    menu.AppendText("^  or  v to scroll");
    menu.AddOption("New");
    menu.AddOption("Load");
    menu.AddOption("Controls");
    menu.AddOption("About");
    menu.AddOption("Quit");
}

void CreatePauseMenu()
{
    auto & pause = wm.AddScreen("pause");

    auto & menu = pause.AddWindow<graphics::Menu>(
        "pause menu",
        graphics::Window::XPercent(50),
        4,
        graphics::Window::XPercent(25),
        white_on_red, red_on_white, white_on_red, 1
    );

    menu.AppendText("Pause");
    menu.AddOption("Continue");
    menu.AddOption("Save");
    menu.AddOption("Controls");
    menu.AddOption("Quit to main menu (unsaved progress will be lost FOREVER!!)");
}
