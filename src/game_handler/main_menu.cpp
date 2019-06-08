#include "main_menu.h"
#include "colors.h"
#include "game_state_manager.h"
#include "../utils/graphics/menu.h"

MainMenu::MainMenu(GameStateManager * manager)
	: IGameState(manager)
{
	auto & menu = AddWindow<graphics::Menu<>>(
		"main menu",
		graphics::max_x,
		0,
		0,
		menu_bg_color,
		menu_active_color,
		menu_inactive_color,
		1
	);


	menu.AppendText("Story of Lory");
	menu.NewLine();
	menu.AppendText("^ or v to select different options").
	AppendText("pgup or pgdn to scroll");

	menu.AddOption().AppendText("New");
	menu.AddOption().AppendText("Load");
	menu.AddOption().AppendText("Controls");
	menu.AddOption().AppendText("About");
	menu.AddOption().AppendText("Quit");
	menu.Commit();

	if (menu.Height() < graphics::max_y)
		menu.SetHeight(graphics::max_y);

	SetTopAndBottom(menu, menu);
}

void MainMenu::ProcessMenuSelection(graphics::menu_base * to_test)
{
	size_t selection = to_test->GetChoice();
	switch (selection)
	{
		case 0:
			gsm->SwitchState(game_state, Notify::New);
			break;
		case 1:
			gsm->SwitchState(game_state, Notify::Load);
			break;
		case 2:
			gsm->PopUp("controls");
			break;
		case 3:
			gsm->PopUp("about");
			break;
		case 4:
			gsm->Stop();
			break;
		default:
			throw std::invalid_argument("impossible selection from main menu");
	}
}

bool MainMenu::Reacted(int input)
{
	graphics::menu_base * menu = static_cast<graphics::menu_base *>(BotWindow());

	if (StandardMenuHandlerReacted(menu, input))
		return true;

	return IGameState::Reacted(input);
}

void MainMenu::GetNotification(Notify notification)
{
}
