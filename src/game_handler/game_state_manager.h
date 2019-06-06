#ifndef __GAME_STATE_MANAGER__
#define __GAME_STATE_MANAGER__

#include "../utils/graphics/window_manager.h"
#include "IGameState.h"

/**
Codes of game states, so one state can send notification or switch to other
*/
extern size_t menu_state,
              pause_state,
              game_state,
			  inventory_state;


class Creature;

/**
This class rules the game. Operates with diferent game states
sometimes called as GSM
*/
class GameStateManager final
{
    graphics::WindowManager wm;
    // five states: Menu, Pause, Current page, Temp page, Inventory
    std::array<std::unique_ptr<IGameState>, 5> states;
    size_t current_state;
    bool shall_run;
	std::string folder;


    public:
        std::unique_ptr<Creature> player;
        
        GameStateManager(char * folder_name);
        GameStateManager(const GameStateManager & other) = delete;
        GameStateManager & operator=(const GameStateManager & other) = delete;
        ~GameStateManager();

		/**
		Loads a page and puts it in state slot 2 or 3, depending on in which state game is now
		@param filename file, from which page will be parsed
		*/
        void TurnPage(const std::string & filename);

		/**
		Switch state to another one.
		Used when going from pause back to game, or from game to inventory and so on
		@param state_code code of a state, to which GSM will switch during next cycle
		@param notification notification to send to next state
		*/
        void SwitchState(size_t state_code, Notify notification = Notify::Empty);

		/**
		Sends notification to provided state
		*/
		void SendNotification(size_t state_code, Notify notification);
        
		/**
		main loop of a programm.
		Works on principles: Wait for input -> react -> if something changed -> draw
		*/
        void Launch();

		/**
		After call to this function Launch() loop will not continue
		*/
        void Stop();

		/**
		displays a pre-configured screen.
		screen will disappear after any keyboard activity
		*/
        void PopUp(const std::string & screen);

		/**
		Pops up an exception screen, which displayed exception message
		*/
        void DisplayException(const std::exception & e);
};

#endif
