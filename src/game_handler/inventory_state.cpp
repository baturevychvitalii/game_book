#include "inventory_state.h"
#include "game_state_manager.h"
#include "game_exception.h"
#include "../game_book/creature.h"
#include "colors.h"

InventoryState::InventoryState(GameStateManager * manager)
	: IGameState(manager, "InventoryState"),
	current_state(Notify::Empty)
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
				auto & status = AddWindow("status", gsm->player->GetStatusBar());
				status.MoveTo(head.LowestPoint(), 0);
				auto & items = AddWindow("inventory", gsm->player->GetInventory());
				items.MoveTo(status.LowestPoint(), 0);
				items.ProlongueToBottom();
				SetTopAndBottom(head, items);
				break;
			}
		case Notify::Trade:
			current_state = notification;
			break;
		case Notify::Fight:
			current_state = notification;
			break;
		case Notify::Continue:
			current_state = notification;
			break;
		default:
			throw std::invalid_argument("wrong notification for inventory state");
	}
}

void InventoryState::ProcessMenuSelection(graphics::menu_base * to_test)
{
	if (to_test != BotWindow())
		throw GameException("must be inventory menu");

	switch (current_state)
	{
		case Notify::Continue:
			static_cast<Inventory *>(to_test)->ChosenButton().Use();
			break;
		case Notify::Trade:
		case Notify::Fight:
			gsm->SwitchState(game_state, current_state);
			break;
		default:
			throw GameException("invalid inventory state");
	}
}

bool InventoryState::Reacted(int input)
{
	graphics::menu_base * menu = static_cast<graphics::menu_base *>(BotWindow());
	if (StandardMenuHandlerReacted(menu, input))
		return true;

	switch (input)
	{
		case 'i':
		case 'I':
		case 'p':
		case 'P':
			if (current_state != Notify::Fight)
			{
				gsm->SwitchState(game_state, Notify::Continue);
				return true;
			}
			return false;
		default:
			return IGameState::Reacted(input);
	}	
}

