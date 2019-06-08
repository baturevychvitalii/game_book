#include "trade.h"
#include "../../game_handler/game_state_manager.h"
#include "../../game_handler/colors.h"
#include "../../game_handler/game_exception.h"
#include "../creature.h"

game_states::Trade::Trade(const xml::Tag & root, GameStateManager * manager)
    : Page(root, manager),
	trader_inventory(new Inventory(root.Child("trader").Child("inventory"))),
	player_inventory(&(gsm->player->GetInventory())),
	crossroads_menu(static_cast<graphics::menu_base *>(BotWindow())),
	current_menu(trader_inventory)
{
	AddWindow("trader inventory", *trader_inventory).
	MoveTo(TopWindow()->LowestPoint(), 0);
	trader_inventory->AppendText(root.Child("trader").Prop("name") + "'s inventory").
	Commit();

	BotWindow()->MoveTo(trader_inventory->LowestPoint(), BotWindow()->LeftPoint()).
	Commit();

	if (!crossroads_menu->Empty())
		(*crossroads_menu)[crossroads_menu->GetChoice()].Unselect();

	BotWindow()->ProlongueToBottom();

	// z_instruction because screen uses sorted map, and if i want to draw something on top - just alter the key
	auto & instruct = AddWindow<graphics::Textbox>(
		"z_instruction",
		8,
		0,
		0,
		controls_color
	).AppendText("press 'N' to switch menu");
	instruct.Commit();
	instruct.MoveToTouch(graphics::Direction::Down).SetSticky();
}

void game_states::Trade::ChangeFocusedMenu()
{
	if (!current_menu->Empty())
		(*current_menu)[current_menu->GetChoice()].Unselect();

	current_menu = current_menu == trader_inventory ? crossroads_menu : trader_inventory;

	if (!current_menu->Empty())
		(*current_menu)[current_menu->GetChoice()].Select();
}

bool game_states::Trade::Reacted(int input)
{
	if (StandardMenuHandlerReacted(current_menu, input))
		return true;

	switch (input)
	{
		case 'n':
		case 'N':
			if (HasWindow("z_instruction"))
				RemoveWindow("z_instruction");
			ChangeFocusedMenu();
			return true;
		case 'i':
		case 'I':
			gsm->SwitchState(inventory_state, Notify::Trade);
			return true;
		default:
			return Page::Reacted(input);
	}
}

void game_states::Trade::GetNotification(Notify notification)
{
	if (notification == Notify::Trade)// from inventory_state, it means that player wants to sell something
	{
		size_t choice = player_inventory->GetChoice();
		size_t price = (*player_inventory)[choice].Price();
		if (gsm->player->ChangeBudget(static_cast<int>(price)))
			trader_inventory->StealItemFrom(*player_inventory, choice);

		trader_inventory->Commit();
		BotWindow()->MoveTo(trader_inventory->LowestPoint(), BotWindow()->LeftPoint());
	}
	else
		Page::GetNotification(notification);
}

void game_states::Trade::ProcessMenuSelection(graphics::menu_base * menu)
{
	if (menu == trader_inventory)
	{
		size_t choice = menu->GetChoice();
		size_t price = (*trader_inventory)[choice].Price();
		if ( gsm->player->ChangeBudget(-1 * static_cast<int>(price)))
			player_inventory->StealItemFrom(*trader_inventory, choice);
		else
			gsm->PopUp("no money");
	}
	else
	{
		Page::ProcessMenuSelection(menu);
	}
}
