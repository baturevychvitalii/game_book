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

	/*
	 * Called when user chosen something in current menu and commited
	 * his(her) choice (for example pressed K_ENTER.
	 * @param to_test currently selected menu. Use to_test->GetChoice()
	 * to get currently selected button.
	 */
	virtual void ProcessMenuSelection(graphics::menu_base * to_test) = 0;

	protected:
		GameStateManager * gsm;

		/*
		 * top and bottom windows are used to prevent scrolling whole page
		 * when you don't really want to scroll it
		 */
		void SetTopAndBottom(graphics::Window & t, graphics::Window & b);

		/*
		 * Checks basic interactions with current menu.
		 * If selection was changed or choice was commited.
		 * @param to_test menu to apply interactions to, and if commited
		 * to call a reaction
		 * @param input keyboard input from user
		 * @return true if provided key presses relate to menu navigation.
		 * false otherwise
		 */
		bool StandardMenuHandlerReacted(graphics::menu_base * to_test, int input);
	public:
		/*
		 * creates base of each game state.
		 * @param manager GSM to refer to, when sending notifications
		 */
		IGameState(GameStateManager * manager, const std::string & scr_name);

		/*
		 * Process notification
		 */
		virtual void GetNotification(Notify notification) = 0;

		/*
		 * Tells if this state somehow reacted to input
		 * @return true if input meant something to current state. in this case screen will be redrawn
		 * false otherwise. screen will not be redrawn
		 */
		virtual bool Reacted(int input);

		/*
		 * used for scrolling. so we don't scrol page away from the window
		 */
		graphics::Window * TopWindow();

		/*
		 * @see TopWindow()
		 */
		graphics::Window * BotWindow();

		virtual ~IGameState() = default;
};

#endif
