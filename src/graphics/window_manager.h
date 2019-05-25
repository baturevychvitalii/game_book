#ifndef __GRAPHICS_WINDOW_MANAGER__
#define __GRAPHICS_WINDOW_MANAGER__

#include <unordered_map>

#include "screen.h"

enum Direction
{
    Up,
    Down,
    Left,
    Right
};

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
        void RemoveScreen(const std::string & name);

        void Draw();
        void Move(Direction direction, unsigned multiplier = 1);
};

#endif
