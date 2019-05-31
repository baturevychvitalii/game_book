#include "menu_state.h"
#include "game_state_manager.h"

MenuState::MenuState(GameStateManager * gsm, graphics::Menu & m)
    : IGameState(gsm), menu(m)
{
}

bool MenuState::Reacted(int input)
{
    switch (input)
    {
        case 10: // Return pressed
            ProcessSelection(menu.GetChoice());
            break;
        case KEY_DOWN:
            menu++;
            break;
        case KEY_UP:
            menu--;
            break;
        default:
            return IGameState::Reacted(input);
    }

    return true;
}


