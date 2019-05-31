#ifndef __GAMEBOOK_PAGE__
#define __GAMEBOOK_PAGE__

#include "creature.h"

class Game;

namespace graphics{class Window;}

class Page : ISerializable
{
    protected:
        const std::string filename;
        std::vector<std::pair<std::string, std::string>> crossroads;
        graphics::Window * top, * bot;
        Game * game;
    public:
        Page() = delete;
        Page(const Page & p) = delete;
        Page & operator=(const Page & p) = delete;
        virtual ~Page() = default;

        Page(const xml::Tag & root, Game * g);

        virtual bool Reacted(int input) = 0;
        std::string GetNextPage() const;
        xml::Tag Serialize() const override;
        graphics::Window & TopWindow();
        graphics::Window & BottomWindow();
};

#endif
