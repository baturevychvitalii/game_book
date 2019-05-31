#include "window_manager.h"

graphics::WindowManager::WindowManager()
    : selected_screen(nullptr)
{
    
    initscr();
    if (!has_colors())
        throw GraphicsException("doesn't support colors");

    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    
    start_color();
    graphics::max_y = getmaxy(stdscr);
    graphics::max_x = getmaxx(stdscr);
    screens.reserve(5);
}

graphics::WindowManager::~WindowManager()
{
    endwin();
}

graphics::Screen & graphics::WindowManager::AddScreen(const std::string & name)
{
    if (screens.find(name) != screens.end())
        throw std::invalid_argument("screen with this name already exists");

    return *(screens[name] = std::make_unique<Screen>(name));
}

void graphics::WindowManager::RemoveScreen(const std::string & name)
{
    if (screens.find(name) == screens.end())
        throw std::invalid_argument("requested screen doesn't exist in database");

    if (selected_screen == screens[name].get())
        selected_screen = nullptr;

    screens.erase(name);
}

void graphics::WindowManager::RemoveScreen(graphics::Screen & scr)
{
    RemoveScreen(scr.Name);
}

graphics::Screen & graphics::WindowManager::SelectScreen(const std::string & name)
{

    if (screens.find(name) == screens.end())
        throw std::invalid_argument("requested screen doesn't exist in database");

    selected_screen = screens[name].get();
    return *selected_screen;
}

graphics::Screen & graphics::WindowManager::SelectScreen(graphics::Screen & scr)
{
    // check if screen belongs to this window manager
    if (screens.find(scr.Name) == screens.end())
        throw std::invalid_argument("requested screen doesn't exist in database");

    selected_screen = &scr;
    return *selected_screen;
}

void graphics::WindowManager::Draw()
{
    if (!selected_screen)
        throw GraphicsException("no screen is selected");

    selected_screen->Draw();
}

void graphics::WindowManager::Move(Direction direction, unsigned multiplier)
{
    if (!selected_screen)
        throw GraphicsException("no screen is selected");

    switch (direction)
    {
        case Direction::Down:
            selected_screen->Move(multiplier, 0);
            break;
        case Direction::Up:
            selected_screen->Move(-1 * multiplier, 0);
            break;
        case Direction::Left:
            selected_screen->Move(0, -1 * multiplier);
            break;
        case Direction::Right:
            selected_screen->Move(0, multiplier);
            break;
    }
}

