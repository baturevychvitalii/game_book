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

void graphics::Button::Select()
{
    is_active = true;
    window_color = active_color;
    
    for (size_t i = 0; i < SizeLines(); i++)
        AlterColor(i, active_color);
}

void graphics::Button::Unselect()
{
    is_active = false;
    window_color = inactive_color;

    for (size_t i = 0; i < SizeLines(); i++)
        AlterColor(i, inactive_color);
}

bool graphics::Button::IsSelected() const
{
    return is_active;
}
