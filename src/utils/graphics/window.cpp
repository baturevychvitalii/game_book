#include "window.h"
#include "../helpers.h"


size_t graphics::max_x = 0;
size_t graphics::max_y = 0;

graphics::Window::Window(IChangeable * parent, size_t width, short y, short x, short color)
    : IChangeable(parent),
      sticky(false),								
      act_h(0),
      act_w(width),
      act_y(y),
      act_x(x),
      window_color(color)
{	
	UpdateOnScreenWidth();
	UpdateOnScreenPositin();
}

void graphics::Window::DrawBackground() const
{
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

void graphics::Window::Draw() const
{
	if (!UpToDate())
		throw GraphicsException("trying to display uncommited changes");

	if (OnScreenSpace() > 0)	
		DrawSpecific();
}

graphics::Window & graphics::Window::SetHeight(size_t new_height)
{
	if (new_height < MinHeight())
		throw std::invalid_argument("height is smaller then minimal");

	act_h = new_height;
	UpdateOnScreenHeight();
	NotifyParent();
	return *this;
}

graphics::Window & graphics::Window::ProlongueToBottom()
{
	if (LowestPoint() < static_cast<short>(max_y))
		SetHeight(max_y - HighestPoint());

	return *this;
}

graphics::Window & graphics::Window::SetColor(short new_color)
{
	window_color = new_color;
	return *this;
}

graphics::Window & graphics::Window::SetSticky(bool value)
{
	sticky = value;
	return *this;
}

graphics::Window & graphics::Window::Move(short dy, short dx)
{
	if (!UpToDate())
		throw GraphicsException("not up to date");

	if (!sticky)
	{
		act_x += dx;
		act_y += dy;
		UpdateOnScreenHeight();
		UpdateOnScreenWidth();
		UpdateOnScreenPositin();
		MoveChildren(dy, dx);
	}

	return *this;
}

graphics::Window & graphics::Window::MoveTo(short y, short x)
{
	return Move(y - act_y, x - act_x);
}

graphics::Window & graphics::Window::Move(graphics::Direction direction, unsigned multiplier)
{
	if (!sticky)
	{
		short dy, dx;
		graphics::CastDirection(direction, multiplier, dy, dx);
		Move(dy, dx);
	}

	return *this;
}

graphics::Window & graphics::Window::MoveToTouch(graphics::Direction direction)
{
	switch (direction)
	{
		case Direction::Up:
			MoveTo(0, LeftPoint());
			break;
		case Direction::Down:
			MoveTo(max_y - Height(), LeftPoint());
			break;
		case Direction::Left:
			MoveTo(HighestPoint(), 0);
			break;
		case Direction::Right:
			MoveTo(HighestPoint(), max_x - Width());
			break;
		default:
			throw GraphicsException("unknown direction");
	}

	return *this;
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

size_t graphics::Window::OnScreenSpace() const
{
	return on_screen_h * on_screen_w;
}

size_t graphics::Window::VisiblePercent() const
{
	return OnScreenSpace() * 100 / ActualSpace();
}

size_t graphics::Window::visible_consiederation = 100;

bool graphics::Window::Visible() const
{
	return VisiblePercent() >= visible_consiederation;
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

size_t graphics::XPercent(size_t percents) noexcept
{
	return max_x * percents / 100;
}

size_t graphics::YPercent(size_t percents) noexcept
{
	return max_y * percents / 100;
}

void graphics::CastDirection(graphics::Direction direction, unsigned multiplier, short & dy, short & dx)
{
	dy = 0, dx = 0;
	switch (direction)
	{
		case Direction::Down:
			dy = multiplier;
			break;
		case Direction::Up:
			dy = -1 * multiplier;
			break;
		case Direction::Left:
			dx = -1 * multiplier;
			break;
		case Direction::Right:
			dx = multiplier;
			break;
		default:
			throw GraphicsException("unsupported direction");
	}
}
