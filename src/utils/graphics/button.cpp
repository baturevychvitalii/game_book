#include "button.h"

graphics::Button::Button(IChangeable * parent,
               size_t width,
               short y,
               short x,
               short active_color, 
               short inactive_color)
    : Textbox(parent, width, y, x, inactive_color),
      active_color(active_color),
      inactive_color(inactive_color),
      is_active(false)
{
}

graphics::Button & graphics::Button::Select()
{
    is_active = true;
    window_color = active_color;
    
	SwitchLinesColor(inactive_color, active_color);
	return *this;
}

graphics::Button & graphics::Button::Unselect()
{
    is_active = false;
    window_color = inactive_color;

	SwitchLinesColor(active_color, inactive_color);
	return *this;
}

bool graphics::Button::IsSelected() const
{
    return is_active;
}
