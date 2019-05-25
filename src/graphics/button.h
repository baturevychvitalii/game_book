#ifndef __GRAPHICS_BUTTON__
#define __GRAPHICS_BUTTON__

#include "textbox.h"

// final class
class Button : public Textbox
{
    short active_color, inactive_color;         
    bool is_active;   
    public:
        Button(IChangeable * parent,
               size_t width,
               short y,
               short x,
               short active_color,
               short inactive_color);
        Button(const Button & butt) = delete;
        Button & operator=(const Button& other) = delete;

        void Select();
        void Unselect();
        bool IsSelected() const;
};

#endif
