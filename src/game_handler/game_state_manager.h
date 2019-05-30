#ifndef __GAME_STATE_MANAGER__
#define __GAME_STATE_MANAGER__

#include "IGameState.h"

extern size_t menu_state,
              pause_state,
              game_state;

// args for states
extern size_t empty_arg,
              main_quit,
              main_load,
              main_new,
              main_controls,
              main_about,
              pause_continue,
              pause_controls,
              pause_save,
              pause_quit;

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

        void SwitchState(size_t state_code, size_t arg = empty_arg);
        void Launch();
        void Stop();
        void PopUp(const std::string & screen);
        void DisplayException(const std::exception & e);
        graphics::WindowManager & GetWindowManager();
        bool DefaultReactedToInput(int input, graphics::Window & bot, graphics::Window & top);
};

#endif
