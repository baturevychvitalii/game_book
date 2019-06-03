#ifndef __GAMEBOOK_CREATURE__
#define __GAMEBOOK_CREATURE__


#include "inventory.h"

class Creature : ISerializable, public graphics::Textbox
{
    private:
        const std::string name;
        unsigned health, max_health;
        unsigned cash;
        Inventory inventory;
    public:
        Creature() = delete;
        Creature(const Creature & other) = delete;
        Creature & operator=(const Creature & other) = delete;
        ~Creature() = default;

        Creature(const xml::Tag & tag);
        Creature(const std::string & name, unsigned max_health, unsigned cash);
        xml::Tag Serialize() const override;

        Inventory & Inventory();
};

#endif
