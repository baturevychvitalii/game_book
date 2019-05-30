#ifndef __PAUSE_STATE__
#define __PAUSE_STATE__

#include "IGameState.h"
#include "../utils/graphics/menu.h"

class PauseState : public IGameState
{
    void Select(size_t arg) override;
    bool Reacted(int input) override;
    void ProcessSelection(size_t selection);
    graphics::Menu & menu;
    public:
        PauseState() = delete;
        PauseState(const PauseState & other) = delete;
        PauseState & operator=(const PauseState & other) = delete;

        PauseState(GameStateManager * gsm);
};

#endif
