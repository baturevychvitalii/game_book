#ifndef __MAIN_MENU__
#define __MAIN_MENU__

#include "IGameState.h"

namespace graphics{class menu_base;}

/**
responsible for letting us quit, launch new game, load game or watch some info
*/
class MainMenu : public IGameState
{
    void ProcessMenuSelection(graphics::menu_base * to_test) override;
    void GetNotification(Notify notification) override;
    bool Reacted(int input) override;
    public:
        MainMenu() = delete;
        MainMenu(const MainMenu & other) = delete;
        MainMenu & operator=(const MainMenu & other) = delete;

        MainMenu(GameStateManager * manager);
};

#endif
