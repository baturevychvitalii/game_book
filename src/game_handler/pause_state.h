#ifndef __PAUSE_STATE__
#define __PAUSE_STATE__

#include "menu_state.h"

class PauseState : public MenuState
{
    void ProcessSelection(size_t selection) override;
    public:
        PauseState() = delete;
        PauseState(const PauseState & other) = delete;
        PauseState & operator=(const PauseState & other) = delete;

        PauseState(GameStateManager * manager);
};

#endif
