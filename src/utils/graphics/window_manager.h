#ifndef __GRAPHICS_WINDOW_MANAGER__
#define __GRAPHICS_WINDOW_MANAGER__

#include <unordered_map>

#include "screen.h"

namespace graphics
{
	/**
	manages screens
	*/
    class WindowManager
    {
        Screen * selected_screen;
        std::unordered_map<std::string,std::unique_ptr<Screen>> screens;
        public:
            WindowManager();
            WindowManager(const WindowManager & wm) = delete;
            WindowManager & operator=(const WindowManager & wm) = delete;
            ~WindowManager();
            Screen & AddScreen(const std::string & name);
            Screen & SelectScreen(const std::string & name);
            Screen & SelectScreen(Screen & scr);
            void RemoveScreen(const std::string & name);
            void RemoveScreen(Screen & scr);

			/**
			draws currently selected screen
			*/
            void Draw();

			/**
			moves currently selected screen
			*/
            void Move(Direction direction, unsigned multiplier = 1);
    };
}

#endif
