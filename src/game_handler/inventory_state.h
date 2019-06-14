#ifndef __INVENTORY_STATE__
#define __INVENTORY_STATE__

#include "IGameState.h"

/*
 * responsible for correctly showing players status and inventory
 * has 3 states:
 * usual when we are just browsing ower inventory
 * trade when we are on trade page and exchanging our items
 * fight when we are in fight and actually using our items
 */
class InventoryState : public IGameState
{
	Notify current_state;

	/*
	 * @param notification must be in {New, Trade, Fight, Continue}
	 */
	void GetNotification(Notify notification) override;
	bool Reacted(int input) override;
	void ProcessMenuSelection(graphics::menu_base *to_test) override;

    public:
		InventoryState(GameStateManager * manager);
};

#endif
