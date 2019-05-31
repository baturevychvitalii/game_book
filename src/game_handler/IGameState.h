#ifndef __INTERFACE_GAME_STATE__
#define __INTERFACE_GAME_STATE__

#include "../utils/graphics/screen.h"


enum Notify
{
    New,
    Save,
    Load,
    Continue,
    Quit,
    Empty
};

class GameStateManager;

class IGameState : public graphics::Screen
{
    graphics::Window * top;
    graphics::Window * bot;
    protected:
        GameStateManager * gsm;
        void SetTopAndBottom(graphics::Window & t, graphics::Window & b);
    public:
        IGameState(GameStateManager * manager);
        virtual void GetNotification(Notify notification) = 0;
        virtual bool Reacted(int input);

        graphics::Window & TopWindow();
        graphics::Window & BotWindow();

        virtual ~IGameState() = default;
};

#endif
