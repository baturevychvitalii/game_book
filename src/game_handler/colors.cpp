#include "colors.h"

size_t red_on_white = 1,
       green_on_black = 2,
       magneta_on_blue = 3,
       white_on_red = 4,
       red_on_black = 5,
       magneta_on_black = 6,
       cyan_on_black = 7,

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
}

