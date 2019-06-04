#ifndef __PAUSE_STATE__
#define __PAUSE_STATE__

#include "IGameState.h"

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
