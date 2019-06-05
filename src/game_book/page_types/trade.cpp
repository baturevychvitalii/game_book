#include "trade.h"
#include "../../game_handler/game_state_manager.h"
#include "../../game_handler/colors.h"
#include "../creature.h"



game_states::Trade::Trade(const xml::Tag & root, GameStateManager * manager)
    : Page(root, manager),
	trader_inventory(new Inventory(root.Child("trader").Child("inventory"))),
	player_inventory(&(gsm->player->GetInventory())),
	crossroads_menu(static_cast<graphics::menu_base *>(BotWindow())),
	current_menu(trader_inventory)
{
	AddWindow("trader inventory", *trader_inventory).
	SetColor(page_trade_selected_menu_bg_color).
	MoveTo(TopWindow()->LowestPoint(), 0);
	trader_inventory->AppendText(root.Child("trader").Prop("name") + "'s inventory").
	Commit();

	BotWindow()->MoveTo(trader_inventory->LowestPoint(), BotWindow()->LeftPoint()).
	SetColor(page_trade_unselected_menu_bg_color).
	Commit();

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
			current_menu->SetColor(page_trade_unselected_menu_bg_color);
			current_menu = current_menu == trader_inventory ? crossroads_menu : trader_inventory;
			current_menu->SetColor(page_trade_selected_menu_bg_color);
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
		trader_inventory->AddOption(
			player_inventory->ReleaseOption(choice)
		);
		trader_inventory->Commit();
		BotWindow()->MoveTo(trader_inventory->LowestPoint(), BotWindow()->LeftPoint());
		gsm->player->ChangeBudget(price);
	}
	else
	{
		Page::GetNotification(notification);
	}
}

void game_states::Trade::ProcessMenuSelection(graphics::menu_base * menu)
{
	if (menu == trader_inventory)
	{
		size_t choice = menu->GetChoice();
		size_t price = (*trader_inventory)[choice].Price();
		if ( gsm->player->Budget() < price)
		{
			gsm->PopUp("no money");
		}
		else
		{
			player_inventory->AddOption(
				trader_inventory->ReleaseOption(choice)
			);

			gsm->player->ChangeBudget(-1 * static_cast<int>(price));
		}
	}
	else
	{
		Page::ProcessMenuSelection(menu);
	}
}
