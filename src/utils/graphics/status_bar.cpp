#include "status_bar.h"

graphics::StatusBar::StatusBar(
    IChangeable * parent,
    size_t width,
    short y,
    short x,
    short empty_color,
    short filled_color,
    size_t actual,
    size_t maximum
)
    : Window(parent, width, y, x, empty_color), filled_color(filled_color), act_value(actual), max_value(maximum)
{
}

void graphics::StatusBar::ApplyChange()
{
	if (act_h < MinHeight())
		SetHeight(MinHeight());
}

size_t graphics::StatusBar::MinHeight() const
{
    return 1;
}

void graphics::StatusBar::DrawSpecific() const
{
	DrawBackground();

	size_t to_draw = act_value * act_w / max_value;
	to_draw = std::min(to_draw, on_screen_w);

	attron(filled_color);
	for (size_t r = 0; r < on_screen_h; r ++)
	{
		for (size_t c = 0; c < to_draw; c++)
		{
			mvaddch(on_screen_y + r, on_screen_x + c, ' ');
		}
	}
	attroff(filled_color);
}

graphics::StatusBar & graphics::StatusBar::SetMax(size_t maximum)
{
	max_value = maximum;
	return *this;
}

graphics::StatusBar & graphics::StatusBar::SetAct(size_t actual)
{
	act_value = actual;
	return *this;
}
