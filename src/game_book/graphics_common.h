#ifndef __GAMEBOOK_GRAPHICS_COMMON_TOOLS__
#define __GAMEBOOK_GRAPHICS_COMMON_TOOLS__

#include "../utils/graphics/window_manager.h"
#include "../utils/graphics/menu.h"
#include "../utils/xml_parser/xml_parser.h"

extern graphics::WindowManager wm;
extern xml::Parser xmp;
extern const std::string save_path;
extern const std::string first_page;

extern size_t red_on_white,
              green_on_black,
              magneta_on_blue,
              white_on_red,
              red_on_black,
              magneta_on_black,
              cyan_on_black,
              error_color,
              hacker;

void InitColors();

void RaiseErrorWindow(const std::exception & e);

void CreateMainMenu();
void CreatePauseMenu();
void CreateControlsWindow();
void CreateAuthorWindow();

size_t GetMenuSelection(graphics::Menu & m);


#endif
