#include "colors.h"

short   red_on_white = 1,
        green_on_black = 2,
        magneta_on_blue = 3,
        white_on_red = 4,
        red_on_black = 5,
        magneta_on_black = 6,
        cyan_on_black = 7,
        white_on_yelow = 8,
        black_on_white = 9,
        white_on_black = 10,
        white_on_magneta = 11,
        magneta_on_white = 12,

        menu_bg_color = magneta_on_white,
        menu_active_color = white_on_magneta,
        menu_inactive_color = black_on_white,

        pause_bg_color = white_on_red,
        pause_active_color = white_on_yelow,
        pause_inactive_color = red_on_black,

        about_color = magneta_on_black,
        controls_color = green_on_black,

        page_header_color = magneta_on_white,
        page_crossroad_bg_color = magneta_on_white,
        page_crossroad_active_color = white_on_magneta,
        page_crossroad_inactive_color = magneta_on_white,

        page_story_body_color = black_on_white,


        error_color = red_on_black,
        hacker = green_on_black;

void InitColors()
{
    init_pair(red_on_white, COLOR_RED, COLOR_WHITE);
    init_pair(green_on_black, COLOR_GREEN, COLOR_BLACK);
    init_pair(magneta_on_blue, COLOR_MAGENTA, COLOR_BLUE);
    init_pair(white_on_red, COLOR_WHITE, COLOR_RED);
    init_pair(red_on_black, COLOR_RED, COLOR_BLACK);
    init_pair(magneta_on_black, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(cyan_on_black, COLOR_CYAN, COLOR_BLACK);
    init_pair(white_on_yelow, COLOR_WHITE, COLOR_YELLOW);
    init_pair(black_on_white, COLOR_BLACK, COLOR_WHITE);
    init_pair(white_on_black, COLOR_WHITE, COLOR_BLACK);
    init_pair(white_on_magneta, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(magneta_on_white, COLOR_MAGENTA, COLOR_WHITE);
}

