#ifndef __PAGE_TYPE_COMBAT__
#define __PAGE_TYPE_COMBAT__

#include "../../game_handler/page_state.h"
#include "../../utils/rng.h"

namespace game_states
{
	class Combat : public Page
	{
		bool Reacted(int input) override;
		void GetNotification(Notify notification) override;

		Creature * GetOpponent();
		bool PlayerUsedItem(int input);
		void FigureOutDeath();
		void ArtificialInteligence();
		/*
		enemy has it's own inventory and status.
		enemy status will be owned by this screen, and deleted
		when turning page in GSM.
		enemy inventory will be deleted in destructor.
		player's status will be released because it's also owned by inventory_state
		*/
		Creature enemy;
		RandomNumberGenerator rng;
		Creature * current_attacker;
		bool death_figured_out;
		bool shal_change_player;
		public:
			Combat(const xml::Tag & root, GameStateManager * manager);
			~Combat() override;

	};
}

#endif
