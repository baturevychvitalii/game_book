#include "combat.h"
#include "../../game_handler/colors.h"
#include "../../game_handler/game_exception.h"
#include "../../game_handler/game_state_manager.h"
#include <cstdio>

game_states::Combat::Combat(const xml::Tag & root, GameStateManager * manager)
	: Page(root, manager),
	enemy(root.Child("enemy")),
	rng(),
	current_attacker(rng(0, 100) > 20 ? gsm->player.get() : &enemy),
	death_figured_out(false)
{
	auto & pl_bar = AddWindow("player status", gsm->player->GetStatusBar());
	pl_bar.MoveTo(TopWindow()->LowestPoint(), pl_bar.LeftPoint());
	auto & en_bar = AddWindow("enemy status", enemy.GetStatusBar());
	en_bar.MoveTo(pl_bar.LowestPoint(), en_bar.LeftPoint());
	BotWindow()->MoveTo(en_bar.LowestPoint(), BotWindow()->LeftPoint());
	Commit();
}

game_states::Combat::~Combat()
{
	delete &(enemy.GetInventory());
	ReleaseWindow("player status");
}

bool game_states::Combat::PlayerUsedItem(int input)
{
	if (!gsm->player->IsAlive() || ! enemy.IsAlive())
		return false;

	if (current_attacker == gsm->player.get()) // player makes turn
	{
		if (input == 'i' || input == 'I')
		{
			if (!(gsm->player->GetInventory().Empty()))
				gsm->SwitchState(inventory_state, Notify::Fight);
			else
				enemy.ChangeHealth(-1 * current_attacker->DefaultDamage);			
			return true;
		}
	}
	else // artificial inteligence)))
	{
		Inventory & inve = current_attacker->GetInventory();
		// select random item
		if (!inve.Empty())
		{
			inve.Choose(rng(0, inve.Size()));
			if (inve.ChosenButton().GetType() == "weapon")
				GetNotification(Notify::UseOnOpponent);
			else
				GetNotification(Notify::UseOnCurrent);
		}
		else
			gsm->player->ChangeHealth(-1 * current_attacker->DefaultDamage);
	}

	return false;
}

bool game_states::Combat::Reacted(int input)
{
	// fight continues
	if (gsm->player->IsAlive() && enemy.IsAlive())
	{
		// current attacker makes turn
		bool reacted1 = PlayerUsedItem(input);
		current_attacker = GetOpponent();
		// opponent makes turn
		bool reacted2 = PlayerUsedItem(input);
		current_attacker = GetOpponent();

		if (reacted1 || reacted2)
			return true;

		return IGameState::Reacted(input);
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

	switch (notification)
	{
		case Notify::UseOnCurrent:
			{
				size_t choice = current_attacker->GetInventory().GetChoice();
				current_attacker->GetInventory()[choice].Use(rng(0,4), current_attacker);
				break;
			}
		case Notify::UseOnOpponent:
			{
				size_t choice = current_attacker->GetInventory().GetChoice();
				current_attacker->GetInventory()[choice].Use(rng(0,4), GetOpponent());
				break;
			}
		default:
			Page::GetNotification(notification);
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
		gsm->PopUp("victory");
	}
	else
	{
		if (remove("save.xml"))
			gsm->DisplayException(GameException("for some reason couldn't delete save file. game is hardcore don't forget it!!"));

		gsm->PopUp("death");
		gsm->SwitchState(menu_state);
	}
	
	death_figured_out = true;
}
