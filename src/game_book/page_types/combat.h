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

		Creature enemy;
		RandomNumberGenerator rng;
		Creature * current_attacker;
		bool death_figured_out;
		bool shal_change_player;
		public:
			/*
			 * creates page of type Combat
			 */
			Combat(const xml::Tag & root, GameStateManager * manager);

			/*
			 * enemy has it's own inventory and status.
			 * enemy status will be owned by this screen, and deleted
			 * when turning page in GSM.
			 * enemy inventory will be deleted in here.
			 * player's status will be untuched, because it is used through linked window
			 */
			~Combat() override;

	};
}

#endif
