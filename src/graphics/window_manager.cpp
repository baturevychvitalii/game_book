#include "window_manager.h"

WindowManager::WindowManager()
    : selected_screen(nullptr)
{
    
    initscr();
    if (!has_colors())
        throw GraphicsException("doesn't support colors");

    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    
    start_color();
    Window::SetMaxes(getmaxy(stdscr), getmaxx(stdscr));
    screens.reserve(5);
}

WindowManager::~WindowManager()
{
    endwin();
}

Screen & WindowManager::AddScreen(const std::string & name)
{
    if (screens.find(name) != screens.end())
        throw std::invalid_argument("screen with this name already exists");

    return *(screens[name] = std::make_unique<Screen>());
}

void WindowManager::RemoveScreen(const std::string & name)
{
    screens.erase(name);
}

Screen & WindowManager::SelectScreen(const std::string & name)
{
    selected_screen = screens.find(name) == screens.end() ?
        (screens[name] = std::make_unique<Screen>()).get() :
        screens[name].get();

    return *selected_screen;
}

void WindowManager::Draw()
{
    if (!selected_screen)
        throw GraphicsException("no screen is selected");

    selected_screen->Draw();
}

void WindowManager::Move(Direction direction, unsigned multiplier)
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

