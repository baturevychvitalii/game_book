#include "trade.h"
#include "../../game_handler/game_state_manager.h"
#include "../../game_handler/colors.h"

Trade::Trade(const xml::Tag & root, GameStateManager * manager)
    : Page(root, manager),
	trader_inventory(new Inventory(root.Child("trader").Child("inventory"))),
	player_inventory(&(gsm->player->GetInventory())),
	crossroads_menu(static_cast<graphics::menu_base *>(BotWindow())),
	current_menu(trader_inventory)
{
	AddWindow("trader inventory", *trader_inventory);
	trader_inventory->AppendText(root.Child("trader").Prop("name") + "'s inventory").Commit();
	trader_inventory->MoveTo(TopWindow()->LowestPoint(), 0);
	BotWindow()->MoveTo(trader_inventory->LowestPoint(), BotWindow()->LeftPoint());
	Commit();
}

bool Trade::Reacted(int input)
{
	switch (input)
	{
		case 'n':
		case 'N':
			current_menu->SetColor(page_trade_unselected_menu_bg_color);
			current_menu = current_menu == trader_inventory ? player_inventory : trader_inventory;
			current_menu->SetColor(page_trade_selected_menu_bg_color);
			return true;
		case 'i':
		case 'I':
			gsm->SwitchState(inventory_state, Notify::Trade);
			return true;
		case K_ENTER:
			if (current_menu == trader_inventory)
			{
				ProcessMenuSelection(current_menu);
				return true;
			}
		default:
			return Page::Reacted(input);
	}
}


