#ifndef __GAMEBOOK_PAGE_STORY__
#define __GAMEBOOK_PAGE_STORY__


#include "../page.h"

class Story : public Page
{
    bool Reacted(int input) override;
    public:
        Story() = delete;
        Story(const Story & other) = delete;
        Story & operator=(const Story & other) = delete;
        
        Story(const xml::Tag & root, Game * g);
};

#endif
