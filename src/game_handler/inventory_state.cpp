#include "inventory_state.h"
#include "game_state_manager.h"
#include "game_exception.h"
#include "../game_book/creature.h"
#include "colors.h"

InventoryState::InventoryState(GameStateManager * manager)
	: IGameState(manager),
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

bool InventoryState::CustomMenuHandlerReacted(int input)
{
	graphics::menu_base & menu = GetWindow<graphics::menu_base>("inventory");

	if (menu.Empty())
		return false;

	// menu navigation is common for all states of inventory
	switch (input)
    {
        case KEY_UP:
           	menu.PrevSelect(); 
		return true;
        case KEY_DOWN:
		menu.NextSelect();
            return true;
	}

	switch (current_state)
	{
		case Notify::Continue:
		case Notify::Trade:
			if (input == K_ENTER)
			{
				gsm->SwitchState(game_state, current_state);
				return true;
			}
			break;
		case Notify::Fight:
			if (input == KEY_LEFT)
			{
				gsm->SwitchState(game_state, Notify::UseOnCurrent);
				return true;
			}
			else if (input == KEY_RIGHT)
			{
				gsm->SwitchState(game_state, Notify::UseOnOpponent);
				return true;
			}
			break;
		default:
			throw GameException("invalid inventory state");
	}

	return false;
}

bool InventoryState::Reacted(int input)
{
	if (CustomMenuHandlerReacted(input))
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
