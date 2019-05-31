#include "pause_state.h"
#include "game_state_manager.h"
#include "colors.h"
#include "../utils/graphics/menu.h"

PauseState::PauseState(GameStateManager * manager)
    : IGameState(manager)
{
    auto & menu = AddWindow<graphics::Menu>(
        "pause",
        graphics::XPercent(50),
        graphics::YPercent(10),
        graphics::XPercent(25),
        pause_bg_color,
        pause_active_color,
        pause_inactive_color,
        1
    );

    menu.AppendText("Pause");
    menu.AddOption("Continue");
    menu.AddOption("Save");
    menu.AddOption("Controls");
    menu.AddOption("Quit to main menu (unsaved progress will be lost FOREVER!!)");

    SetTopAndBottom(menu, menu);
}

void PauseState::StandardManuHandlerProcess(graphics::Menu * to_test)
{
    size_t choice = to_test->GetChoice();

    switch (choice)
    {
        case 0:
            gsm->SwitchState(game_state, Notify::Continue);
            break;
        case 1:
            gsm->SwitchState(game_state, Notify::Save);
            break;
        case 2:
            gsm->PopUp("controls");
            break;
        case 3:
            gsm->SwitchState(menu_state);
            break;
        default:
            throw std::invalid_argument("unreal selection in pause");
    }
}

bool PauseState::Reacted(int input)
{
    graphics::Menu * menu = static_cast<graphics::Menu *>(BotWindow());

    if (StandardMenuHandlerReacted(menu, input))
        return true;

    return IGameState::Reacted(input);
}

void PauseState::GetNotification(Notify notification)
{
}

