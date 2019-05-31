#include "IGameState.h"
#include "game_exception.h"

IGameState::IGameState(GameStateManager * manager)
    : Screen("detetched"), gsm(manager), top(nullptr), bot(nullptr)
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

graphics::Window & IGameState::TopWindow()
{
    return top ? *top : throw GameException("top window not set");
}

graphics::Window & IGameState::BotWindow()
{
    return bot ? *bot : throw GameException("bot window not set");
}

bool IGameState::Reacted(int input)
{
    switch (input)
    {
        case 'k':
            if (bot->LowestPoint() > graphics::max_y)
                Move(graphics::Direction::Down, 3);
            break;
        case 'j':
            if (top->HighestPoint() < 0)
                Move(graphics::Direction::Up, 3);
            break;
        default:
            return false;
    }

    return true;
}

