#ifndef __GAMEBOOK_PAGE__
#define __GAMEBOOK_PAGE__

#include "../utils/graphics_features.h"
#include "creature.h"

class Page
{
    protected:
        const std::string header;
        std::vector<std::pair<std::string, std::string>> crossroads;

        Creature * player;

        std::string ShowCrossroad() const;
    public:
        Page(const xml::Tag & t);
        Page(const Page & p) = delete;
        Page & operator=(const Page & p) = delete;
        virtual ~Page();

        virtual std::string Play(Creature & pleya) = 0;
};

#endif
