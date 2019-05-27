#include "screen.h"

short graphics::Window::max_x = -1;
short graphics::Window::max_y = -1;

graphics::Screen::Screen()
{
    windows.reserve(15);
}

void graphics::Screen::Commit()
{
    for (auto & winptr : windows)
        winptr->Commit();
}

void graphics::Screen::Move(short dy, short dx)
{
    Commit();
    for (auto & w : windows)
        w->Move(dy,dx);
}

void graphics::Screen::Draw()
{
    Commit();

    clear();
    for (auto & w : windows)
        w->Draw();

    refresh();
}

void graphics::Screen::Clear()
{
    windows.clear();
}

const graphics::Window & graphics::Screen::LastAdded() const
{
    if (windows.empty())
        throw GraphicsException("screen is empty");
    
    return *(windows[windows.size() - 1]);
}

void graphics::Screen::RemoveWindow(Window & win)
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
