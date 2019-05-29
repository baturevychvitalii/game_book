#ifndef __GAMEBOOK_PAGE__
#define __GAMEBOOK_PAGE__

#include "graphics_common.h"
#include "creature.h"

class Page : ISerializable
{
    protected:
        const std::string filename;
        std::vector<std::pair<std::string, std::string>> crossroads;
        Creature & player;
        graphics::Screen & screen;

        void Bookmark() const;
        size_t PauseMenu() const;

        // returns -1 if chosen "Quit to main menu in Pause window"
        int DefaultPageHandling();
    public:
        Page(const Page & p) = delete;
        Page & operator=(const Page & p) = delete;
        virtual ~Page();

        Page(const std::string & filename, const xml::Tag & root, Creature & pleya);

        /*
        returns true - ok, can go to next page
                false - main menu (player died, book end, main menu requested)
        */
        virtual bool Play() = 0;
        std::string GetNextPage() const;
        xml::Tag Serialize() const override;
};

#endif
