#ifndef __GAMEBOOK_PAGE__
#define __GAMEBOOK_PAGE__

#include "creature.h"

class Game;

namespace graphics{class Menu;}

class Page : public ISerializable
{
    Game * game;
    const std::string filename;
    std::vector<std::pair<std::string, std::string>> crossroads;

    public:
        Page() = delete;
        Page(const Page & p) = delete;
        Page & operator=(const Page & p) = delete;
        virtual ~Page() = default;

        Page(const xml::Tag & root, Game * g);

        virtual bool Reacted(int input);
        xml::Tag Serialize() const override;
};

#endif
