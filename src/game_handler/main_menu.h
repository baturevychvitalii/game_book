#ifndef __MAIN_MENU__
#define __MAIN_MENU__

#include "IGameState.h"

class MainMenu : public IGameState
{
    void ProcessMenuSelection(graphics::IMenu * to_test) override;
    void GetNotification(Notify notification) override;
    bool Reacted(int input) override;
    public:
        MainMenu() = delete;
        MainMenu(const MainMenu & other) = delete;
        MainMenu & operator=(const MainMenu & other) = delete;

        MainMenu(GameStateManager * manager);
};

#endif
