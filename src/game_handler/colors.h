#ifndef __GAME_COLORS__
#define __GAME_COLORS__

/**
colors which are initialized in InitColors()
*/
extern short    red_on_white,
                green_on_black,
                magneta_on_blue,
                white_on_red,
                red_on_black,
                magneta_on_black,
                cyan_on_black,
                black_on_white,
                white_on_black,
                white_on_magneta,
                magneta_on_white,
				yelow_on_black,
// cross states
                menu_bg_color,
                menu_active_color,
                menu_inactive_color,


/// pages
                page_header_color,

                page_story_body_color,

				page_trade_selected_menu_bg_color,
				page_trade_unselected_menu_bg_color,

/// creature
				status_health_active_color,
				status_health_inactive_color,
				status_theme_color,


                error_color,
				no_money_color,
                about_color,
				victory_color,
				death_color,
                controls_color;

/**
will initialize color pairs for ncurses
*/
void InitColors();


#endif
