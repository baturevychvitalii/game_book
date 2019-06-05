#ifndef __INVENTORY_STATE__
#define __INVENTORY_STATE__

#include "IGameState.h"

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
