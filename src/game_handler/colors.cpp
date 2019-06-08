#include "colors.h"
#include <ncurses.h>

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
		white_on_green = 13,
		magneta_on_yelow = 14,
		yelow_on_black = 15,

		default_theme_color = magneta_on_white,
		anti_color = white_on_magneta,

        menu_bg_color = default_theme_color,
        menu_active_color = white_on_magneta,
        menu_inactive_color = black_on_white,

        page_header_color = default_theme_color,

        page_story_body_color = black_on_white,

		page_trade_selected_menu_bg_color = default_theme_color,
		page_trade_unselected_menu_bg_color = anti_color,

		status_theme_color = anti_color,
		status_health_active_color = white_on_green,
		status_health_inactive_color = white_on_red,

        about_color = anti_color,
        controls_color = magneta_on_yelow,
		no_money_color = white_on_green,
		victory_color = red_on_white,
		death_color = white_on_red,
        error_color = red_on_black;

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
	init_pair(white_on_green, COLOR_WHITE, COLOR_GREEN);
	init_pair(magneta_on_yelow, COLOR_MAGENTA, COLOR_YELLOW);
	init_pair(yelow_on_black, COLOR_YELLOW, COLOR_BLACK);
}

