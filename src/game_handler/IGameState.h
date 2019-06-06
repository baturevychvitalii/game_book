#ifndef __INTERFACE_GAME_STATE__
#define __INTERFACE_GAME_STATE__

#include "../utils/graphics/screen.h"

#define K_ENTER 10

/**
Set of notifications, which can be transfered between game states
*/
enum Notify
{
    New,
    Save,
    Load,
    Continue,
    Quit,
	Trade,
	Fight,
    Empty,
	UseOnCurrent,
	UseOnOpponent
};

class GameStateManager;
namespace graphics{class menu_base;}

/**
abstract base of all game states
*/
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
		/**
		creates base of each game state.
		@param manager GSM to refer to, when sending notifications
		*/
        IGameState(GameStateManager * manager);

		/**
		Process notification
		*/
        virtual void GetNotification(Notify notification) = 0;

		/**
		Tells if this state somehow reacted to input
		@return true if input meant something to current state. in this case screen will be redrawn
				false otherwise. screen will not be redrawn
		*/
        virtual bool Reacted(int input);

		/**
		used for scrolling. so we don't scrol page away from the window
		*/
        graphics::Window * TopWindow();

		/**
		@see TopWindow()
		*/
        graphics::Window * BotWindow();

        virtual ~IGameState() = default;
};

#endif
