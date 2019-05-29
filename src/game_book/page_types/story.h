#ifndef __GAMEBOOK_PAGE_STORY__
#define __GAMEBOOK_PAGE_STORY__


#include "page.h"

class Story : public Page
{
    public:
        Story() = delete;
        Story(const Story & other) = delete;
        Story & operator=(const Story & other) = delete;
        
        Story(const std::string & filename, const xml::Tag & root, Creature & pleya);
        bool Play() override;
};

#endif
