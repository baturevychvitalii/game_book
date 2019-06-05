#include "inventory_state.h"
#include "game_state_manager.h"
#include "game_exception.h"
#include "../game_book/creature.h"
#include "colors.h"

InventoryState::InventoryState(GameStateManager * manager)
	: IGameState(manager)
{
}

void InventoryState::GetNotification(Notify notification)
{
	switch (notification)
	{
		case Notify::New:
			{
				Clear();
				auto & head = AddWindow<graphics::Textbox>(
					"header",
					graphics::max_x,
					0,
					0,
					menu_bg_color
				).AppendText("Lorries inventory");
				head.Commit();
				auto & status = AddWindow("bar", gsm->player->GetStatusBar());
				status.MoveTo(head.LowestPoint(), 0);
				auto & items = AddWindow("inventory", gsm->player->GetInventory());
				items.MoveTo(status.LowestPoint(), 0);
				items.ProlongueToBottom();
				SetTopAndBottom(head, items);
				break;
			}
		case Notify::Trade:
			in_trade = true;
			break;
		case Notify::Continue:
			in_trade = false;
			break;
		default:
			throw std::invalid_argument("wrong notification for inventory state");
	}
}

void InventoryState::ProcessMenuSelection(graphics::menu_base * to_test)
{
	if (to_test != &(gsm->player->GetInventory()))
		throw GameException("must be players inventory");


	if (in_trade)
	{
		gsm->SendNotification(game_state, Notify::Trade);
	}
	else
	{
		gsm->SwitchState(game_state, Notify::Continue);
	}	
}

bool InventoryState::Reacted(int input)
{
	graphics::menu_base * items = static_cast<graphics::menu_base *>(BotWindow());
	if (StandardMenuHandlerReacted(items, input))
		return true;

	switch (input)
	{
		case 'i':
		case 'I':
		case 'p':
		case 'P':
			gsm->SwitchState(game_state, Notify::Continue);
			return true;	
		default:
			return IGameState::Reacted(input);
	}	
}
