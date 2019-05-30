#ifndef __INTERFACE_GAME_STATE__
#define __INTERFACE_GAME_STATE__

#include "../utils/graphics/window_manager.h"

class GameStateManager;

class IGameState
{
    protected:
        GameStateManager * gsm;
        graphics::WindowManager & wm;
        graphics::Screen & screen;
    public:
        IGameState(GameStateManager * game_state_manager, const std::string & screen_id);
        virtual void Select(size_t arg) = 0;
        virtual bool Reacted(int input) = 0;
        void Draw();

        virtual ~IGameState();
};

#endif
