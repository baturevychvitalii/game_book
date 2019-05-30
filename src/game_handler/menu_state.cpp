#include "menu_state.h"
#include "game_state_manager.h"
#include "colors.h"

MenuState::MenuState(GameStateManager * gsm, graphics::Menu & m)
    : IGameState(gsm, "main menu screen"),
      menu(
        screen.AddWindow<graphics::Menu>(
            "main menu",
            graphics::Window::XPercent(50),
            4,
            graphics::Window::XPercent(25),
            menu_bg_color, menu_active_color, menu_inactive_color, 1
        )
      )
{
    menu.AppendText("Story of Lory");
    menu.NewLine();
    menu.AppendText("<  or  > to select different options");
    menu.AppendText("^  or  v to scroll");
    main_new = menu.AddOption("New");
    main_load = menu.AddOption("Load");
    main_controls = menu.AddOption("Controls");
    main_about = menu.AddOption("About");
    main_quit = menu.AddOption("Quit");
}

void MainMenuState::Select(size_t arg)
{
    // has to do nothing upon selection
}

bool MainMenuState::Reacted(int input)
{
    if (gsm->DefaultReactedToInput(input, menu, menu))
        return true;

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
            return false; 
    }

    return true;
}


