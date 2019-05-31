#ifndef __MAIN_MENU__
#define __MAIN_MENU__

#include "menu_state.h"

class MainMenu : public MenuState
{
    void ProcessSelection(size_t selection) override;
    public:
        MainMenu() = delete;
        MainMenu(const MainMenu & other) = delete;
        MainMenu & operator=(const MainMenu & other) = delete;

        MainMenu(GameStateManager * manager);
};

#endif
