#ifndef __INTERFACE_GAME_STATE__
#define __INTERFACE_GAME_STATE__

#include "../utils/graphics/screen.h"

class GameStateManager;

enum Notify
{
    New,
    Save,
    Load,
    Continue,
    Quit,
    Empty
};

class IGameState : public graphics::Screen
{
    protected:
        GameStateManager * gsm;
    public:
        IGameState(GameStateManager * manager)
            : Screen("detetched"), gsm(manager)
        {
        }

        virtual void GetNotification(Notify notification)
        {
        }

        virtual bool Reacted(int input) = 0;

        virtual ~IGameState() = default;
};

#endif
