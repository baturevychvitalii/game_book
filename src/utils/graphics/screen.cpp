#include "screen.h"

short graphics::Window::max_x = -1;
short graphics::Window::max_y = -1;


void graphics::Screen::Commit()
{
    for (auto & id_win : windows)
        id_win.second->Commit();
}

bool graphics::Screen::Empty() const
{
    return windows.empty();
}

bool graphics::Screen::HasWindow(const std::string & id)
{
    return windows.find(id) != windows.end();
}

void graphics::Screen::Move(short dy, short dx)
{
    Commit();
    for (auto & id_win : windows)
        id_win.second->Move(dy,dx);
}

void graphics::Screen::Draw()
{
    Commit();

    clear();
    for (auto & id_win : windows)
        id_win.second->Draw();

    refresh();
}

void graphics::Screen::Clear()
{
    windows.clear();
}

void graphics::Screen::RemoveWindow(const std::string & id)
{
    if (!HasWindow(id))
        throw std::invalid_argument("window with such id doesn't exist");

    windows.erase(id);
}

graphics::Window & graphics::Screen::GetWindow(const std::string & id)
{
    if (!HasWindow(id))
        throw std::invalid_argument("id");

    return *(windows[id]);
}
