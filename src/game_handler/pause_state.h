#ifndef __PAUSE_STATE__
#define __PAUSE_STATE__

#include "IGameState.h"

/**
responsible for pause menu.
let's user save the game, read controlls or quit
*/
class PauseState : public IGameState
{
    void GetNotification(Notify notification) override;
    bool Reacted(int input) override;
    void ProcessMenuSelection(graphics::menu_base * to_test) override;
    public:
        PauseState() = delete;
        PauseState(const PauseState & other) = delete;
        PauseState & operator=(const PauseState & other) = delete;

        PauseState(GameStateManager * manager);
};

#endif
