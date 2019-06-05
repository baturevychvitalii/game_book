#ifndef __GAMEBOOK_PAGE_TRADE__
#define __GAMEBOOK_PAGE_TRADE__

#include "../../game_handler/page_state.h"
namespace game_states
{
	class Trade : public Page
	{
		bool Reacted(int input) override;
		void ProcessMenuSelection(graphics::menu_base * menu) override;
		void GetNotification(Notify notification) override;

		Inventory * trader_inventory;
		Inventory * player_inventory;
		graphics::menu_base * crossroads_menu;
		graphics::menu_base * current_menu;
		public:
			Trade(const xml::Tag & root, GameStateManager * manager);
	};
}

#endif
