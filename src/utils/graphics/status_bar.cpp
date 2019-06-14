#include "status_bar.h"

graphics::StatusBar::StatusBar(
    IChangeable * parent,
    size_t width,
    short y,
    short x,
    short active_color,
    short inactive_color,
    size_t actual,
    size_t maximum
)
    : Textbox(parent, width, y, x, inactive_color),
	active_color(active_color),
	act_value(actual),
	max_value(maximum)
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

void graphics::StatusBar::DrawSpecific()
{
	DrawBackground();

	size_t to_draw = act_value * act_w / max_value;
	to_draw = std::min(to_draw, on_screen_w);

	attron(COLOR_PAIR(active_color));
	for (size_t r = 0; r < on_screen_h; r ++)
	{
		for (size_t c = 0; c < to_draw; c++)
		{
			mvaddch(on_screen_y + r, on_screen_x + c, ' ');
		}
	}
	attroff(COLOR_PAIR(active_color));

	DrawLines();
}

graphics::StatusBar & graphics::StatusBar::SetMax(size_t maximum)
{
	if (maximum < act_value)
		throw std::invalid_argument("maximum must be greater than actual");
	max_value = maximum;
	return *this;
}

graphics::StatusBar & graphics::StatusBar::SetAct(size_t actual)
{
	if (actual > max_value)
		throw std::invalid_argument("maximum must be greater than actual");
	act_value = actual;
	return *this;
}
