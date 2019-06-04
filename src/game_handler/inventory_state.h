#ifndef __INVENTORY_STATE__
#define __INVENTORY_STATE__

#include "IGameState.h"

class InventoryState : public IGameState
{
	void ProcessMenuSelection(graphics::menu_base * to_test) override;
	void GetNotification(Notify notification) override;
	bool Reacted(int input) override;
    public:
		InventoryState(GameStateManager * manager);
};

#endif
