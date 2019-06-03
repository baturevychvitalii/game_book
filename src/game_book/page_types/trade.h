#ifndef __GAMEBOOK_PAGE_TRADE__
#define __GAMEBOOK_PAGE_TRADE__

#include "../../game_handler/page_state.h"

class Trade : public Page
{
    bool Reacted(int input) override;
    void ProcessMenuSelection(graphics::Menu * menu) override;

    const std::string name_trader;
    Inventory trader_inventory;
    bool trade_finished;
    public:
        Trade() = delete;
        Trade(const Trade & other) = delete;
        
        Trade(const xml::Tag & root, GameStateManager * manager);
};

#endif
