#include "combat.h"
#include "../../utils/graphics/mirror.h"
#include "../../game_handler/colors.h"
#include "../../game_handler/game_exception.h"
#include "../../game_handler/game_state_manager.h"


// to delete file with saved progress in case player died
#include <cstdio>

game_states::Combat::Combat(const xml::Tag & root, GameStateManager * manager)
	: Page(root, manager),
	enemy(root.Child("enemy")),
	rng(),
	current_attacker(rng(0, 100) > 20 ? &enemy : gsm->player.get()),
	death_figured_out(false),
	shal_change_player(false)
{
	auto & status = AddWindow<graphics::Group<graphics::Window>>(
		"fight process",
		graphics::max_x,
		TopWindow()->LowestPoint(),
		0,
		menu_inactive_color,
		1,
		2, 0
	);

	status.EmplaceBack<graphics::Mirror<>>(gsm->player->GetStatusBar());
	status.EmplaceBack(enemy.GetStatusBar());
	status.SetDrawBackground().Commit();

	BotWindow()->MoveTo(status.LowestPoint(), BotWindow()->LeftPoint());
	BotWindow()->ProlongueToBottom();


	// tip at bottom left which says whose turn is now
	auto & tip = AddWindow<graphics::Textbox>(
		"z_tip",
		11,
		0,
		0,
		controls_color
	);
	tip.NewLine(current_attacker == &enemy ? "AI turn" : "your turn");
	tip.Commit();
	tip.MoveToTouch(graphics::Direction::Down);
	tip.SetSticky();
	Commit();
}

game_states::Combat::~Combat()
{
	delete &(enemy.GetInventory());
}

bool game_states::Combat::PlayerUsedItem(int input)
{
	if (current_attacker != gsm->player.get()) // player makes turn
		throw GameException("wrong usage of function");

	if (input == 'I' || input == 'i')
	{
		if (!(gsm->player->GetInventory().Empty()))
			gsm->SwitchState(inventory_state, Notify::Fight);
		else
			GetOpponent()->ChangeHealth(-1 * current_attacker->DefaultDamage());

		return true;
	}

	return false;
}

void game_states::Combat::ArtificialInteligence()
{
	if (current_attacker != &enemy)
		throw GameException("wrong usage of function");

	Inventory & inve = enemy.GetInventory();
	// select random item
	if (!inve.Empty())
	{
		inve.Choose(rng(0, inve.Size()));
		inve.ChosenButton().Use(rng(1, 3), GetOpponent());
	}
	else
		GetOpponent()->ChangeHealth(-1 * current_attacker->DefaultDamage());
}

bool game_states::Combat::Reacted(int input)
{
	if (shal_change_player)
	{
		current_attacker = GetOpponent();
		shal_change_player = false;
	}

	// fight continues
	if (gsm->player->IsAlive() && enemy.IsAlive())
	{
		// scrolling is allowed
		if (IGameState::Reacted(input))
			return true;
		
		// current attacker makes turn
		if (current_attacker == gsm->player.get())
		{
			if (PlayerUsedItem(input))
			{
				shal_change_player = true;
				GetWindow<graphics::Textbox>("z_tip").AlterLineText(0, "AI turn");
				return true;
			}

			return false;
		}
		else
		{
			ArtificialInteligence();
			shal_change_player = true;
			GetWindow<graphics::Textbox>("z_tip").AlterLineText(0, "your turn");
			return true;
		}
	}
	else 
	{
		if (!death_figured_out)
		{
			FigureOutDeath();
			return true;
		}
		else
		{
			if (StandardMenuHandlerReacted(static_cast<graphics::menu_base *>(BotWindow()), input))
				return true;

			return Page::Reacted(input);	
		}
	}
}

void game_states::Combat::GetNotification(Notify notification) 
{
	// fight has finished, player is choosing a crossroad
	if (notification != Notify::Fight)
		Page::GetNotification(notification);
	else // fight continues
	{
		if (current_attacker != gsm->player.get() || !current_attacker->IsAlive())
			throw GameException("something wrong has happened");
			
		current_attacker->GetInventory().ChosenButton().Use(rng(1,3), GetOpponent());
	}
}

Creature * game_states::Combat::GetOpponent()
{
	return current_attacker == &enemy ? gsm->player.get() : &enemy;
}

void game_states::Combat::FigureOutDeath()
{
	if (gsm->player->IsAlive())
	{
		// get inventory of an enemy
		gsm->player->GetInventory().StealWholeInventory(enemy.GetInventory());
		gsm->player->ChangeBudget(enemy.Budget());
		enemy.ChangeBudget(-1 * enemy.Budget());
		gsm->PopUp("victory");
	}
	else
	{
		remove("save.xml");
		// following command will unlink player's status bar from inventory state
		gsm->PopUp("death");
		gsm->SwitchState(menu_state);
	}
	
	RemoveWindow("fight process");
	BotWindow()->MoveTo(TopWindow()->LowestPoint(), BotWindow()->LeftPoint());
	BotWindow()->ProlongueToBottom();
	RemoveWindow("z_tip");
	death_figured_out = true;
}
