#ifndef __GAME_COLORS__
#define __GAME_COLORS__

#include <ncurses.h>

// raw colors
extern size_t red_on_white,
              green_on_black,
              magneta_on_blue,
              white_on_red,
              red_on_black,
              magneta_on_black,
              cyan_on_black,
// cross states
              menu_bg_color,
              menu_active_color,
              menu_inactive_color,

              pause_bg_color,
              pause_active_color,
              pause_inactive_color,

              about_color,
              controls_color,
/// pages
              page_header_color,
              page_crossroad_bg_color,
              page_crossroad_active_color,
              page_crossroad_inactive_color,

              error_color,
              hacker;


void InitColors();


#endif
