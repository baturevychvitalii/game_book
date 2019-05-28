#include "graphics_features.h"

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
    auto & err = wm.SelectScreen("error");
    auto & win = err.AddWindow<graphics::Textbox>(graphics::Window::XPercent(50),
                                    graphics::Window::YPercent(10), 
                                    graphics::Window::XPercent(25),
                                    error_color);
    win.AppendText("Exception was thrown!");
    win.NewLine();
    win.AppendText(e.what());
    wm.Draw();
    getch();
    wm.RemoveScreen("error");
}

size_t GetMenuSelection(graphics::Menu & m)
{
    m.Draw();
    int input;
    while((input = getch()) != 10)
    {
        switch (input)
        {
            case KEY_UP:
                if (m.HighestPoint() > 0)
                    wm.Move(graphics::Direction::Up, 3);
                break;
            case KEY_DOWN:
                if (m.LowestPoint() < graphics::Window::max_y)
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
