#include "window.h"
#include "../utils/helpers.h"


graphics::Window::Window(IChangeable * parent, size_t width, short y, short x, short color)
    : IChangeable(parent),
      act_h(0),
      act_w(width),
      act_y(y),
      act_x(x),
      window_color(color)
{
    UpdateOnScreenWidth();
    UpdateOnScreenPositin();
}

void graphics::Window::Draw()
{
    if (!UpToDate())
        throw GraphicsException("trying to display uncommited changes");
    

    if (on_screen_h * on_screen_w == 0)
        return;
    
    
    attron(COLOR_PAIR(window_color));
    for (size_t i = 0; i < on_screen_h; i++)
    {
        for (size_t a = 0; a < on_screen_w; a++)
        {
            mvaddch( on_screen_y + i, on_screen_x + a, ' ');
        }
    }

    attroff(COLOR_PAIR(window_color));
}

void graphics::Window::SetHeight(size_t new_height)
{
    if (new_height < MinHeight())
        throw std::invalid_argument("height is smaller then minimal");

    act_h = new_height;
    UpdateOnScreenHeight();
}

void graphics::Window::Move(short dy, short dx)
{
    if (!UpToDate())
        throw GraphicsException("not up to date");

    act_x += dx;
    act_y += dy;
    UpdateOnScreenHeight();
    UpdateOnScreenWidth();
    UpdateOnScreenPositin();
}

void graphics::Window::MoveTo(short y, short x)
{
    Move(y - act_y, x - act_x);
}


void graphics::Window::UpdateOnScreenWidth() noexcept
{
    on_screen_w = Intersection(0, max_x, act_x, act_x + act_w);
}

void graphics::Window::UpdateOnScreenHeight() noexcept
{
    on_screen_h = Intersection(0, max_y, act_y, act_y + act_h);
}

void graphics::Window::UpdateOnScreenPositin() noexcept
{
    on_screen_x = act_x < 0 ? 0 : act_x;
    on_screen_y = act_y < 0 ? 0 : act_y;
}



short graphics::Window::MidXStart(short len) const
{
    return act_x + (act_w - len) / 2;
}

short graphics::Window::MidYStart(short len) const
{
    return act_y + (act_h - len) / 2;
}

short graphics::Window::HighestPoint() const
{
    if (!UpToDate())
        throw GraphicsException("not up to date");

    return act_y;
}

short graphics::Window::LowestPoint() const
{
    return act_y + Height();
}

short graphics::Window::RightPoint() const
{
    return act_x + Width();
}

short graphics::Window::LeftPoint() const
{
    if (!UpToDate())
        throw GraphicsException("not up to date");

    return act_x;
}

size_t graphics::Window::ActualSpace() const
{
    return Height() * Width();
}

size_t graphics::Window::Height() const
{
    if (!UpToDate())
        throw GraphicsException("not up to date");

    return act_h;
}

size_t graphics::Window::Width() const
{
    if (!UpToDate())
        throw GraphicsException("not up to date");

    return act_w;
}

size_t graphics::Window::WidthPercent(size_t percents) noexcept
{
    return (max_x * percents) / 100;
}

void graphics::Window::SetMaxes(short maxy, short maxx) noexcept
{
    max_y = maxy;
    max_x = maxx;
}
