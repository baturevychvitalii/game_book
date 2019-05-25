#include "screen.h"

short Window::max_x = -1;
short Window::max_y = -1;

Screen::Screen()
{
    windows.reserve(15);
}

void Screen::Commit()
{
    for (auto & winptr : windows)
        winptr->Commit();
}

void Screen::Move(short dy, short dx)
{
    Commit();
    for (auto & w : windows)
        w->Move(dy,dx);
}

void Screen::Draw()
{
    Commit();

    clear();
    for (auto & w : windows)
        w->Draw();

    refresh();
}

void Screen::Clear()
{
    windows.clear();
}

void Screen::RemoveWindow(Window & win)
{
    for (size_t i = 0; i < windows.size(); i++)
    {
        if (windows[i].get() == &win)
        {
            windows.erase(windows.begin() + i);
            return;
        }
    }
    
    throw std::invalid_argument("window doesn't exist");
}


Textbox & Screen::AddTextbox(size_t width, short y, short x, short color)
{
    Textbox * tb = new Textbox(nullptr, width, y, x, color);
    windows.emplace_back(tb);
    return *tb;
}

Menu & Screen::AddMenu(size_t width, short y, short x,
                       short bg_color,
                       short active_color,
                       short inactive_color,
                       size_t colomns)
{
    Menu * mn = new Menu(nullptr, width, y, x, bg_color, active_color, inactive_color, colomns);
    windows.emplace_back(mn);
    return *mn;
}
