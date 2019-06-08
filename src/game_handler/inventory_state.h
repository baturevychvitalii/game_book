#ifndef __INVENTORY_STATE__
#define __INVENTORY_STATE__

#include "IGameState.h"

/**
responsible for correctly showing players status and inventory
has 3 states:
	usual when nothing really happens
	trade when we are on trade page and exchanging our items
	fight when we are in fight and actually using our items
*/
class InventoryState : public IGameState
{
	Notify current_state;

	void CustomProcessMenuSelection(graphics::menu_base * to_test, int input = -1);
	void GetNotification(Notify notification) override;
	bool Reacted(int input) override;

	bool CustomMenuHandlerReacted(int input);
    public:
		InventoryState(GameStateManager * manager);
};

#endif
