#include "screen.h"

graphics::Screen::Screen(std::string name)
    : Name(std::move(name))
{
}

graphics::Screen & graphics::Screen::Commit()
{
    for (auto & id_win : windows)
        id_win.second->Commit();
    
    return *this;
}

bool graphics::Screen::Empty() const
{
    return windows.empty();
}

bool graphics::Screen::HasWindow(const std::string & id)
{
    return windows.find(id) != windows.end();
}

graphics::Screen & graphics::Screen::Move(short dy, short dx)
{
    Commit();
    for (auto & id_win : windows)
        id_win.second->Move(dy,dx);
    
    return *this;
}

graphics::Screen & graphics::Screen::Move(graphics::Direction direction, unsigned multiplier)
{
    short dy, dx;
    graphics::CastDirection(direction, multiplier, dy, dx);
    return Move(dy, dx);
}

void graphics::Screen::Draw()
{
    Commit();

    clear();
    for (auto & id_win : windows)
        id_win.second->Draw();

    refresh();
}

graphics::Screen & graphics::Screen::Clear()
{
    windows.clear();
    return *this;
}

graphics::Window & graphics::Screen::AddWindow(const std::string & id, graphics::Window & new_win)
{
	if (new_win.HasParent())
		throw GraphicsException("trying to add window, which has a parent");

	if (HasWindow(id))
		throw GraphicsException("window already exists");

	windows.emplace(id, &new_win);
	return *(windows[id]);
}

graphics::Screen & graphics::Screen::RemoveWindow(const std::string & id)
{
    if (!HasWindow(id))
        throw std::invalid_argument("window with such id doesn't exist");

    windows.erase(id);
    return *this;
}

graphics::Window & graphics::Screen::ReleaseWindow(const std::string & id)
{
	if (!HasWindow(id))
        throw std::invalid_argument("window with such id doesn't exist");

	Window * released = windows[id].release();
	windows.erase(id);
	return *released;
}

graphics::Window & graphics::Screen::GetWindow(const std::string & id)
{
    if (!HasWindow(id))
        throw std::invalid_argument("id");

    return *(windows[id]);
}
