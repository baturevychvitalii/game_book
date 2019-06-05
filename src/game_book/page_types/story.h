#ifndef __GAMEBOOK_PAGE_STORY__
#define __GAMEBOOK_PAGE_STORY__


#include "../../game_handler/page_state.h"

class Story : public Page
{
	bool Reacted(int input) override;
    public:
        Story(const xml::Tag & root, GameStateManager * manager);
};

#endif
