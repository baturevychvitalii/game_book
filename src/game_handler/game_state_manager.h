#ifndef __GAME_STATE_MANAGER__
#define __GAME_STATE_MANAGER__

#include "../utils/graphics/window_manager.h"
#include "IGameState.h"

extern size_t menu_state,
              pause_state,
              game_state;


class Creature;

class GameStateManager final
{
    graphics::WindowManager wm;
    // four states: Menu, Pause, Current page, Temp page
    std::array<std::unique_ptr<IGameState>, 4> states;
    size_t current_state;
    bool shall_run;


    public:
        std::unique_ptr<Creature> player;
        
        GameStateManager();
        GameStateManager(const GameStateManager & other) = delete;
        GameStateManager & operator=(const GameStateManager & other) = delete;
        ~GameStateManager();

        void TurnPage(const std::string & filename);
        void SwitchState(size_t state_code, Notify notification = Notify::Empty);
        
        void Launch();
        void Stop();

        void PopUp(const std::string & screen);
        void DisplayException(const std::exception & e);
};

#endif
