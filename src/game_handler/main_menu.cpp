#include "main_menu.h"
#include "colors.h"
#include "game_state_manager.h"

MainMenu::MainMenu(GameStateManager * manager)
  : MenuState(
      manager, 
      AddWindow<graphics::Menu>(
        "main menu",
        graphics::XPercent(50),
        4,
        graphics::XPercent(25),
        menu_bg_color, menu_active_color, menu_inactive_color, 1
      )
  )
{
    menu.AppendText("Story of Lory");
    menu.NewLine();
    menu.AppendText("<  or  > to select different options").
    AppendText("^  or  v to scroll");

    menu.AddOption("New");
    menu.AddOption("Load");
    menu.AddOption("Controls");
    menu.AddOption("About");
    menu.AddOption("Quit");
    menu.Commit();
    
    SetTopAndBottom(menu, menu);
}

void MainMenu::ProcessSelection(size_t selection)
{
  if (selection == 0)
    gsm->SwitchState(game_state, Notify::New);
  else if (selection == 1)
    gsm->SwitchState(game_state, Notify::Load);
  else if (selection == 2)
    gsm->PopUp("controls");
  else if (selection == 3)
    gsm->PopUp("about");
  else if (selection == 4)
    gsm->Stop();
  else
    throw std::invalid_argument("impossible selection from main menu");  
}
