#include "pause_state.h"
#include "game_state_manager.h"
#include "colors.h"

PauseState::PauseState(GameStateManager * manager)
    : MenuState(
        manager,
        AddWindow<graphics::Menu>(
            "pause",
            graphics::XPercent(50),
            graphics::YPercent(10),
            graphics::XPercent(25),
            pause_bg_color,
            pause_active_color,
            pause_inactive_color,
            1
        )
    )
{
    menu.AppendText("Pause");
    menu.AddOption("Continue");
    menu.AddOption("Save");
    menu.AddOption("Controls");
    menu.AddOption("Quit to main menu (unsaved progress will be lost FOREVER!!)");
}

void PauseState::ProcessSelection(size_t selection)
{
    if (selection == 0)
        gsm->SwitchState(game_state, Notify::Continue);
    else if (selection == 1)
        gsm->SwitchState(game_state, Notify::Save);
    else if (selection == 2)
        gsm->PopUp("controls");
    else if (selection == 3)
        gsm->SwitchState(menu_state);
    else
        throw std::invalid_argument("unreal selection in pause");
}

