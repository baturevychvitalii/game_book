#ifndef __GAME_COLORS__
#define __GAME_COLORS__

#include <ncurses.h>

extern size_t red_on_white,
              green_on_black,
              magneta_on_blue,
              white_on_red,
              red_on_black,
              magneta_on_black,
              cyan_on_black,

              menu_bg_color,
              menu_active_color,
              menu_inactive_color,

              about_color,
              controls_color,

              page_header_color,

              error_color,
              hacker;


void InitColors();


#endif
