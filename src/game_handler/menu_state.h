#ifndef __MENU_STATE__
#define __MENU_STATE__

#include "IGameState.h"
#include "../utils/graphics/menu.h"

class MenuState : public IGameState
{
    bool Reacted(int input) override;
    virtual void ProcessSelection(size_t selection) = 0;
    protected:
        graphics::Menu & menu;
    public:
        MenuState() = delete;
        MenuState(const MenuState & other) = delete;
        MenuState & operator=(const MenuState & other) = delete;

        MenuState(GameStateManager * manager, graphics::Menu & m);
};

#endif
