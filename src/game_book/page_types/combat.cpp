#include "combat.h"
#include "../../game_handler/colors.h"
#include "../../game_handler/game_exception.h"
#include "../../game_handler/game_state_manager.h"
#include <cstdio>

game_states::Combat::Combat(const xml::Tag & root, GameStateManager * manager)
	: Page(root, manager),
	enemy(root.Child("enemy")),
	rng(),
	current_attacker(rng(0, 100) > 20 ? &enemy : gsm->player.get()),
	death_figured_out(false),
	shal_change_player(false)
{
	auto & status = AddWindow<graphics::Group<graphics::Group<graphics::Textbox>>>(
		"fight process",
		graphics::max_x,
		TopWindow()->LowestPoint(),
		0,
		menu_inactive_color,
		1,
		2,
		0
	);
	status.EmplaceBack(gsm->player->GetStatusBar());
	status.EmplaceBack(enemy.GetStatusBar());
	status.SetDrawBackground().Commit();
	BotWindow()->MoveTo(status.LowestPoint(), BotWindow()->LeftPoint());
	BotWindow()->ProlongueToBottom();


	//your turn
	//AI turn
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
	Commit();
}

game_states::Combat::~Combat()
{
	delete &(enemy.GetInventory());
	auto & status_group = GetWindow<graphics::Group<graphics::Group<graphics::Textbox>>>("fight process");
	status_group.Release(0);
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
			GetOpponent()->ChangeHealth(-1 * current_attacker->DefaultDamage);		

		return true;
	}

	return false;
}

void game_states::Combat::ArtificialInteligence()
{
	if (current_attacker != &enemy)
		throw GameException("wrong usage of function");

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
		GetOpponent()->ChangeHealth(-1 * current_attacker->DefaultDamage);
	
}

bool game_states::Combat::Reacted(int input)
{
	if (shal_change_player)
		current_attacker = GetOpponent();
	// fight continues
	if (gsm->player->IsAlive() && enemy.IsAlive())
	{
		// current attacker makes turn
		if (current_attacker == gsm->player.get())
		{
			if (PlayerUsedItem(input))
			{
				shal_change_player = true;
				GetWindow<graphics::Textbox>("z_tip").AlterLineText(0, "AI turn");
				return true;
			}

			shal_change_player = false;
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

	switch (notification)
	{
		case Notify::UseOnCurrent:
			{
				size_t choice = current_attacker->GetInventory().GetChoice();
				current_attacker->GetInventory()[choice].Use(rng(0, 3), current_attacker);
				break;
			}
		case Notify::UseOnOpponent:
			{
				size_t choice = current_attacker->GetInventory().GetChoice();
				current_attacker->GetInventory()[choice].Use(rng(0, 3), GetOpponent());
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
		enemy.ChangeBudget(-1 * enemy.Budget());
		gsm->PopUp("victory");
	}
	else
	{
		if (remove("save.xml"))
			gsm->DisplayException(GameException("for some reason couldn't delete save file. game is hardcore don't forget it!!"));

		gsm->PopUp("death");
		gsm->SwitchState(menu_state);
	}
	
	RemoveWindow("z_tip");
	death_figured_out = true;
}
