#include "IGameState.h"
#include "game_exception.h"
#include "../utils/graphics/menu_base.h"

static const unsigned scroll_speed = 1; 

IGameState::IGameState(GameStateManager * manager)
    : Screen("detetched"), top(nullptr), bot(nullptr), gsm(manager)
{
}

void IGameState::GetNotification(Notify notification)
{
}

void IGameState::SetTopAndBottom(graphics::Window & t, graphics::Window & b)
{
    top = &t;
    bot = &b;
}

graphics::Window * IGameState::TopWindow()
{
    return top ? top : throw GameException("top window not set");
}

graphics::Window * IGameState::BotWindow()
{
    return bot ? bot : throw GameException("bot window not set");
}

bool IGameState::Reacted(int input)
{
    switch (input)
    {
        case 'K':
        case 'k':
            if (top->HighestPoint() < 0)
                Move(graphics::Direction::Down, scroll_speed);
            break;
        case 'J':
        case 'j':
            if (bot->LowestPoint() > static_cast<short>(graphics::max_y))
                Move(graphics::Direction::Up, scroll_speed);
            break;
        default:
            return false;
    }

    return true;
}

bool IGameState::StandardMenuHandlerReacted(graphics::menu_base * to_test, int input)
{
    // standard handler doesn't know what to do with this menu, may be
    // it'is normal, who knows better than derived class itself
    if (to_test->Size() == 0)
        return false;
    
    switch (input)
    {
        case KEY_UP:
            if (to_test->PrevIsVisible())
                to_test->Prev();
            break;
        case KEY_DOWN:
            if (to_test->NextIsVisible())
                to_test->Next();
            break;
        case K_ENTER: // Return pressed
            if (to_test->CurrIsVisible())
                ProcessMenuSelection(to_test);
            break;
        default:
            return false;
    }

    return true;
}

