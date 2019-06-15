#include "pause_state.h"
#include "game_state_manager.h"
#include "colors.h"
#include "../utils/graphics/menu.h"

PauseState::PauseState(GameStateManager * manager)
    : IGameState(manager, "PauseState")
{
    auto & menu = AddWindow<graphics::Menu<>>(
        "pause",
        graphics::XPercent(50),
        graphics::YPercent(10),
        graphics::XPercent(25),
        menu_bg_color,
        menu_active_color,
        menu_inactive_color,
        1
    );

	menu.AddOption().AppendText("Continue");
	menu.AddOption().AppendText("Save");
    menu.AddOption().AppendText("Controls");
    menu.AddOption().AppendText("Quit to main menu (unsaved progress will be lost FOREVER!!)");

    SetTopAndBottom(menu, menu);
}

void PauseState::ProcessMenuSelection(graphics::menu_base * to_test)
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
	graphics::menu_base * menu = static_cast<graphics::menu_base *>(BotWindow());

	if (StandardMenuHandlerReacted(menu, input))
		return true;

	switch (input)
	{
		case 'p':
		case 'P':
			gsm->SwitchState(game_state, Notify::Continue);
			break;
		case 'q':
		case 'Q':
			gsm->SwitchState(menu_state);
			break;
		default:
			return IGameState::Reacted(input);
	}

	return true;
}

void PauseState::GetNotification(Notify notification)
{
}

