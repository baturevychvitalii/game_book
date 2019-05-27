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

const Window & Screen::LastAdded() const
{
    if (windows.empty())
        throw GraphicsException("screen is empty");
    
    return *(windows[windows.size() - 1]);
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
