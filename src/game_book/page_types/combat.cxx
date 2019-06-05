#include "combat.h"
#include "../../game_handler/colors.h"
#include "../../game_handler/game_state_manager.h"
#include "../../utils/rng.h"

game_states::Combat::Combat(const xml::Tag & root, GameStateManager * manager)
	: Page(root, manager),
	enemy(root.Child("enemy")),
	rng(),
	current_attacker(rng(0, 100) > 20 ? gsm->player.get() : &enemy)
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

void game_states::Combat::TimeToUseItem()
{
	if (current_attacker == gsm->player.get()) // player makes turn
	{

	}
	else // artificial inteligence)))
	{
		
	}
}

bool game_states::Combat::Reacted(int input)
{
	// fight continues
	if (gsm->player->IsAlive() && enemy.IsAlive())
	{
		// current attacker makes turn
		TimeToUseItem();
		// opponent makes turn
		current_attacker = GetOpponent();
		TimeToUseItem();
		current_attacker = GetOpponent();

		return IGameState::Reacted(input);
	}
	else 
	{
		if (StandardMenuHandlerReacted(static_cast<graphics::menu_base *>(BotWindow()), input))
			return true;

		return Page::Reacted(input);	
	}
}

void game_states::Combat::GetNotification(Notify notification) 
{

	switch (notification)
	{
		case Notify::UseOnCurrent:
			size_t choice = current_attacker->GetInventory().GetChoice();
			current_attacker->GetInventory()[choice].Use(rng(0,4), current_attacker);
			break;
		case Notify::UseOnOpponent:
			size_t choice = current_attacker->GetInventory().GetChoice();
			current_attacker->GetInventory()[choice].Use(rng(0,4), GetOpponent());
			break;
		default:
			Page::GetNotification(notification);
	}
}

Creature * game_states::Combat::GetOpponent()
{
	return current_attacker == &enemy ? gsm->player.get() : &enemy;
}
