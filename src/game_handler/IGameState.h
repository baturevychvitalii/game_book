#ifndef __INTERFACE_GAME_STATE__
#define __INTERFACE_GAME_STATE__

#include "../utils/graphics/screen.h"

#define K_ENTER 10


enum Notify
{
    New,
    Save,
    Load,
    Continue,
    Quit,
	Trade,
    Empty
};

class GameStateManager;
namespace graphics{class menu_base;}

class IGameState : public graphics::Screen
{
    graphics::Window * top;
    graphics::Window * bot;

    virtual void ProcessMenuSelection(graphics::menu_base * to_test) {};
    protected:
        GameStateManager * gsm;
        void SetTopAndBottom(graphics::Window & t, graphics::Window & b);
        bool StandardMenuHandlerReacted(graphics::menu_base * to_test, int input);
    public:
        IGameState(GameStateManager * manager);
        virtual void GetNotification(Notify notification) = 0;
        virtual bool Reacted(int input);

        graphics::Window * TopWindow();
        graphics::Window * BotWindow();

        virtual ~IGameState() = default;
};

#endif
