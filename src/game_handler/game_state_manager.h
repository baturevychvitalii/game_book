#ifndef __GAME_STATE_MANAGER__
#define __GAME_STATE_MANAGER__

#include "../utils/graphics/window_manager.h"
#include "IGameState.h"

extern size_t menu_state,
              pause_state,
              game_state;



class GameStateManager
{
    graphics::WindowManager wm;
    std::vector<std::unique_ptr<IGameState>> states;
    size_t current_state;
    bool shall_run;
    public:
        GameStateManager();
        GameStateManager(const GameStateManager & other) = delete;
        GameStateManager & operator=(const GameStateManager & other) = delete;
        ~GameStateManager() = default;

        void SwitchState(size_t state_code, Notify notification = Notify::Empty);
        void Launch();
        void Stop();
        void PopUp(const std::string & screen);
        void DisplayException(const std::exception & e);
        bool DefaultReactedToInput(int input, graphics::Window & bot, graphics::Window & top);
};

#endif
