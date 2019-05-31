#include "IGameState.h"
#include "game_exception.h"
#include "../utils/graphics/menu.h"

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
        case 'k':
            if (top->HighestPoint() < 0)
                Move(graphics::Direction::Down, 3);
            break;
        case 'j':
            if (bot->LowestPoint() > graphics::max_y)
                Move(graphics::Direction::Up, 3);
            break;
        default:
            return false;
    }

    return true;
}

bool IGameState::StandardMenuHandlerReacted(graphics::Menu * to_test, int input)
{
    // standard handler doesn't know what to do with this menu, may be
    // it'is normal, who knows better than derived class itself
    if (to_test->OptionsSize() == 0)
        throw GameException("can't work with empty menu");
    
    switch (input)
    {
        case KEY_UP:
            if (to_test->ChoicesAreVisible())
                (*to_test)--;
            break;
        case KEY_DOWN:
            if (to_test->ChoicesAreVisible())
                (*to_test)++;
            break;
        case 10: // Return pressed
            if (to_test->ChoicesAreVisible())
                StandardManuHandlerProcess(to_test);
            break;
        default:
            return false;
    }

    return true;
}

