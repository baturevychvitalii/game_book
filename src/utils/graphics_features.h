#ifndef __GRAPHICS_COMMON_FEATURES__
#define __GRAPHICS_COMMON_FEATURES__

#include "graphics/window_manager.h"
#include "graphics/menu.h"

graphics::WindowManager wm;

size_t red_on_white = 1,
    green_on_black = 2,
    magneta_on_blue = 3,
    white_on_red = 4,
    red_on_black = 5,
    magneta_on_black = 6,
    cyan_on_black = 7,
    error_color = red_on_black,
    hacker = green_on_black;

void InitColors();

void RaiseErrorWindow(const std::exception & e);

size_t GetMenuSelection(graphics::Menu & m);


#endif
