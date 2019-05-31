#ifndef __GAMEBOOK_PAGE_STORY__
#define __GAMEBOOK_PAGE_STORY__


#include "../../game_handler/page_state.h"

class Story : public Page
{
    public:
        Story() = delete;
        Story(const Story & other) = delete;
        Story & operator=(const Story & other) = delete;
        
        Story(const xml::Tag & root, GameStateManager * manager);
};

#endif
